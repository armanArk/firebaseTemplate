/**
 * SYNTAX:
 *
 * initializeApp(<AsyncClient>, <FirebaseApp>, <user_auth_data>);
 *
 * <AsyncClient> - The async client.
 * <FirebaseApp> - The authentication and access token handler.
 * <user_auth_data> - The user auth data (user_auth_data struct) that holds the user input sign-in credentials and token.
 *
 * The <user_auth_data> can be obtained from the following sign-in credentials, access key, auth token providers classs via getAuth function i.e.
 * CustomAuth, ServiceAuth, UserAuth, NoAuth, CustomToken, AccessToken, IDToken, LegacyToken.
 *
 * SYNTAX:
 *
 * ServiceAuth::ServiceAuth(<TimeStatusCallback>, <client_email>, <project_id>, <private_key>, <expire>);
 *
 * <TimeStatusCallback> - The time status callback that provide the UNIX timestamp value used for JWT token signing.
 * <client_email> - The service account client Email.
 * <project_id> - The service account project ID.
 * <private_key> - The service account private key.
 * <expire> - The expiry period in seconds (less than 3600), 3300 is the default value.
 *
 * NOTE:
 *
 * To reduce the stack usage of BearSSL engine crpto function, the JWT token creation process
 * will be performed outside the FirebaseApp.
 *
 * The JWT token processor required for ServiceAuth and CustomAuth authentications.
 *
 * JWTClass::loop(<auth_data_t *>)
 *
 * The complete usage guidelines, please visit https://github.com/mobizt/FirebaseClient
 */

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_GIGA)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#elif __has_include(<WiFiNINA.h>) || defined(ARDUINO_NANO_RP2040_CONNECT)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#elif __has_include(<WiFiS3.h>) || defined(ARDUINO_UNOWIFIR4)
#include <WiFiS3.h>
#elif __has_include(<WiFiC3.h>) || defined(ARDUINO_PORTENTA_C33)
#include <WiFiC3.h>
#elif __has_include(<WiFi.h>)
#include <WiFi.h>
#endif

#include <FirebaseClient.h>
#include "example/env.h"

#define WIFI_SSID2 "agrox"
#define WIFI_PASSWORD2 "agrox12345"

const char PRIVATE_KEY[] PROGMEM = FIREBASE_PRIVATE_KEY;

void timeStatusCB(uint32_t &ts);

void asyncCB(AsyncResult &aResult);

void printResult(AsyncResult &aResult);

void getMsg(String title, String message);

String reverseString(String str);

void sendNotif(String body);

FirebaseWiFi wifimulti;
DefaultWiFiNetwork network(wifimulti, true);

ServiceAuth sa_auth(timeStatusCB, FIREBASE_CLIENT_EMAIL, FIREBASE_PROJECT_ID, PRIVATE_KEY, 3000 /* expire period in seconds (<3600) */);

FirebaseApp app;

#if defined(ESP32) || defined(ESP8266) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFiClientSecure.h>
WiFiClientSecure sslClient2, sslClient1;
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_UNOWIFIR4) || defined(ARDUINO_GIGA) || defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_NANO_RP2040_CONNECT)
#include <WiFiSSLClient.h>
WiFiSSLClient sslClient2;
#endif

using AsyncClient = AsyncClientClass;

AsyncClient aClient2(sslClient2, getNetwork(network));
AsyncClient aClient1(sslClient1, getNetwork(network));
RealtimeDatabase Database;

Messaging messaging;

void setup()
{
    // optional
    wifimulti.addAP(WIFI_SSID, WIFI_PASSWORD);
    wifimulti.addAP(WIFI_SSID2, WIFI_PASSWORD2);

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    Serial.println("Initializing app...");

#if defined(ESP32) || defined(ESP8266) || defined(PICO_RP2040)
    sslClient1.setInsecure();
    sslClient2.setInsecure();
#if defined(ESP8266)
    ssl_client.setBufferSizes(4096, 1024);
#endif
#endif

    // Initialize the FirebaseApp or auth task handler.
    // To deinitialize, use deinitializeApp(app).
    // aClient1 = messaging,push
    // aClient2 = messaging,stream
    initializeApp(aClient1, app, getAuth(sa_auth), asyncCB, "authTask");
    app.getApp<RealtimeDatabase>(Database);
    app.getApp<Messaging>(messaging);

    Database.url(FIREBASE_DATABASE_URL);
    Database.setSSEFilters("get,put,patch");
    Database.get(aClient2, "/test/stream", asyncCB, true, "streamTask");
}

void loop()
{
    // The async task handler should run inside the main loop
    // without blocking delay or bypassing with millis code blocks.

    Database.loop();

    // The JWT token processor required for ServiceAuth and CustomAuth authentications.
    // JWT is a static object of JWTClass and it's not thread safe.
    // In multi-threaded operations (multi-FirebaseApp), you have to define JWTClass for each FirebaseApp,
    // and set it to the FirebaseApp via FirebaseApp::setJWTProcessor(<JWTClass>), before calling initializeApp.
    JWT.loop(app.getAuth());

    app.loop();

    static bool taskComplete = false;
    if (app.ready() & !taskComplete)
    {
        taskComplete = true;
        // Serial.println("Sending message...");
        sendNotif("FROM LOOP");

        JsonWriter writer;
        object_t json, obj1, obj2;
        writer.create(obj1, "ms", millis());
        writer.create(obj2, "rand", random(10000, 30000));
        writer.join(json, 2, obj1, obj2);
        Database.set<object_t>(aClient1, "/test/stream/number", json, asyncCB, "setTask");
    }
    // To get the authentication time to live in seconds before expired.
    // app.ttl();
}

void timeStatusCB(uint32_t &ts)
{
#if defined(ESP8266) || defined(ESP32) || defined(CORE_ARDUINO_PICO)
    if (time(nullptr) < FIREBASE_DEFAULT_TS)
    {

        configTime(3 * 3600, 0, "pool.ntp.org");
        while (time(nullptr) < FIREBASE_DEFAULT_TS)
        {
            delay(100);
        }
    }
    ts = time(nullptr);
#elif __has_include(<WiFiNINA.h>) || __has_include(<WiFi101.h>)
    ts = WiFi.getTime();
#endif
}

void asyncCB(AsyncResult &aResult)
{
    // WARNING!
    // Do not put your codes inside the callback and printResult.

    printResult(aResult);
}

void printResult(AsyncResult &aResult)
{
    if (aResult.isEvent())
    {
        Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
    }

    if (aResult.isDebug())
    {
        Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
    }

    if (aResult.isError())
    {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
    }

    if (aResult.available())
    {
        Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
    }
}
void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}
void sendNotif(String body)
{
    getMsg("testing", body);
}

void getMsg(String title, String message)
{
    Messages::Message msg;
    String topic = reverseString(FIREBASE_UID);
    Serial.print("topic:");
    Serial.println(topic);
    msg.topic(topic);
    Messages::Notification notification;
    notification.body(message).title(title);
    object_t data, obj1;
    JsonWriter writer;
    writer.create(obj1, "name", string_t("wrench"));
    writer.join(data, 1, obj1);
    msg.data(data);
    data.clear();
    Messages::AndroidConfig androidConfig;
    androidConfig.priority(Messages::AndroidMessagePriority::_HIGH);
    Messages::AndroidNotification androidNotification;
    androidNotification.notification_priority(Messages::NotificationPriority::PRIORITY_HIGH);
    androidConfig.notification(androidNotification);
    msg.android(androidConfig);
    msg.notification(notification);
    messaging.send(aClient1, Messages::Parent(FIREBASE_PROJECT_ID), msg, asyncCB);
}
String reverseString(String str)
{
    int length = str.length();
    char charArray[length + 1];
    str.toCharArray(charArray, length + 1);

    for (int i = 0; i < length / 2; i++)
    {
        char temp = charArray[i];
        charArray[i] = charArray[length - 1 - i];
        charArray[length - 1 - i] = temp;
    }

    return String(charArray);
}