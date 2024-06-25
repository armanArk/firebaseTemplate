/**
 * SYNTAX:
 *
 * Messaging::send(<AsyncClient>, <Messages::Parent>, <Messages::Message>, <AsyncResult>);
 *
 * <AsyncClient> - The async client.
 * The <Messages::Parent> - The Messages::Parent object included project Id in its constructor.
 * The <Messages::Message> - The Messages::Message object that holds the information of message to send.
 * <AsyncResult> - The async result (AsyncResult).
 *
 * The Firebase project Id should be only the name without the firebaseio.com.
 *
 * The complete usage guidelines, please visit https://github.com/mobizt/FirebaseClient
 */
#include <Arduino.h>
#define DEBUG 1
#include "debug.h"
#include <ArduinoJson.h>
#include <async_handler.h>
#include <RTClib.h>
#include <TimeLib.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncTCP.h>
void pushFB();
void firebaseUpdateSensor();

Async pushFBAsync(pushFB, 10 * 1000);

enum enumData
{
  METHODE_FIREBASE_SET,
  METHODE_FIREBASE_UPDATE,
  METHODE_FIREBASE_PUSH,
  OUTPUT_FLUSH,
  OUTPUT_NUTRIENT,
  MODE_MANUAL,
  MODE_OTOMATIS,
  SWITCH_STATE_ON,
  SWITCH_STATE_OFF,
  TANK_STATE_LOW,
  TANK_STATE_NORMAL,
  METHODE_DFT,
  METHODE_NFT,
  STATE_IDLE,
  STATE_DOSING,
  STATE_DOSE_PH,
  STATE_DOSE_PPM,
  STATE_FILL_WATER,
  STATE_DISPOSE,
  STATE_DRIP,
  STATE_BACKWASH,
  STATE_CIRCULATION,
  STATE_FLUSH,
  NEX_SCREEN_BOOTING,
  NEX_SCREEN_HOME,
  NEX_SCREEN_DRIP,
  NEX_SCREEN_DRIP_ADD,
  NEX_SCREEN_SETTING,
  NEX_SCREEN_SETTING_FERTIGASI,
  NEX_SCREEN_CLIMATE,
  NEX_SCREEN_SETTING_CLIMATE,
  NEX_SCREEN_KALIBRASI,
  NEX_SCREEN_NOTIF,
  NEX_SCREEN_SETTING_NFT,
  NEX_SCREEN_SETTING_WIFI,
  NEX_SCREEN_MANUAL,
  NEX_SCREEN_FERTIGASI,
  NEX_SCREEN_FERTIGASI_DFT,
  NEX_SCREEN_FERTIGASI_NFT,
  NEX_SCREEN_SET_FERT_PH,
  NEX_SCREEN_SET_FERT_PPM,
  NEX_SCREEN_SET_FERT_TEMP,
  NEX_SCREEN_FAILSAFE,
  NEX_SCREEN_LOGIN,
  PARSER_TYPE_STRING,
  PARSER_TYPE_NUM_LONG,
  PARSER_TYPE_NUM_FLOAT,
  PARSER_TYPE_SWITCH,
  PARSER_TYPE_DATETIME_ISO8601,
  SET_PARAM_SWITCH_DISABLE_NIGHT,
  SET_PARAM_FLOAT_MAIN,
  SET_PARAM_STATE_FLUSH,
  SET_PARAM_GMT,
  SET_PARAM_CLIMATE_TEMP_MIN,
  SET_PARAM_CLIMATE_TEMP_MAX,
  SET_PARAM_NOTIF_TANK_ABMIX,
  SET_PARAM_NOTIF_TANK_EMPTY,
  SET_PARAM_NOTIF_DRIP_ON,
  SET_PARAM_NOTIF_DRIP_COMPLETE,
  SET_PARAM_NOTIF_PH,
  SET_PARAM_NOTIF_TDS,
  SET_PARAM_NOTIF_DOSE_RESULT,
  SET_PARAM_NOTIF_TANK_FILLING_COMPLETE,
  SET_PARAM_HST_AWAL,
  SET_PARAM_METHODE_FERTIGASI,
  SET_PARAM_MODE_FERTIGASI,
  SET_PARAM_MODE_CLIMATE,
  SET_PARAM_LAST_ACTIVE,
  SET_PARAM_DOSING_TIMEOUT_PH,
  SET_PARAM_DOSING_TIMEOUT_PPM,
  SET_PARAM_DELAY_BACKWASH,
  SET_PARAM_INTERVAL_REPORT,
  SET_PARAM_MARGIN_PPM,
  SET_PARAM_INTERVAL_OFF_PPM,
  SET_PARAM_INTERVAL_ON_PPM,
  SET_PARAM_MODE_PPM,
  SET_PARAM_PH,
  SET_PARAM_PH_MIN,
  SET_PARAM_PH_MAX,
  SET_PARAM_SCH_PPM,
  SET_PARAM_SCH_DRIP,
  SET_PARAM_HUMIDITY_ON,
  SET_PARAM_HUMIDITY_OFF,
  SET_PARAM_TEMP_MAX,
  SET_PARAM_TEMP_MIN,
  SET_PARAM_HUMIDITY_MAX,
  SET_PARAM_HUMIDITY_MIN,
  SET_PARAM_PPM_SWITCH_SCH,
  SET_PARAM_DRIP_SWITCH_SCH,
  SET_PARAM_PH_VOLT_9,
  SET_PARAM_PH_VOLT_7,
  SET_PARAM_PH_VOLT_4,
  SET_PARAM_PPM_TARGET,
  SET_PARAM_DOSE_INTERVAL,
  SET_PARAM_LOCK_METHODE,
  SET_PARAM_STATE_TANK_ABMIX,
  SET_PARAM_STATE_BACKWASH,
  SET_PARAM_STATE_PH_UP,
  SET_PARAM_STATE_PH_DOWN,
  SET_PARAM_STATE_DRIP,
  SET_PARAM_STATE_DRAIN,
  SET_PARAM_STATE_ABMIX,
  SET_PARAM_STATE_TANK_FILL,
  SET_PARAM_STATE_TEMP,
  SET_PARAM_STATE_BLOWER,
  SET_PARAM_STATE_MISTING,
  SET_PARAM_FERT_BACKWASH_TIME,
  SET_PARAM_COMMAND,
  SET_PARAM_COMMAND_RESPONSE,
  SET_PARAM_STATE_COOLING_PAD,
  PREF_PARAM_SWITCH_ENABLE_DOSE_AT_BOOT,
  PREF_PARAM_FERT_PPM_PID_COMPLETE_QTY,
  PREF_PARAM_FERT_PH_PID_COMPLETE_QTY,
  PREF_PARAM_FERT_PPM_PID_COMPLETE_MARGIN,
  PREF_PARAM_FERT_PH_PID_COMPLETE_MARGIN,
  PREF_PARAM_FERT_DISABLE_AT_NIGHT,
  PREF_PARAM_FERT_BACKWASH_TIME,
  PREF_PARAM_FERT_PID_PPM_INTERVAL,
  PREF_PARAM_FERT_PID_PPM_OUTPUT_PERCENTAGE,
  PREF_PARAM_FERT_PID_PH_INTERVAL,
  PREF_PARAM_FERT_PID_PH_OUTPUT_PERCENTAGE,
  PREF_PARAM_NOTIF_TANK_ABMIX,
  PREF_PARAM_FERT_METHODE,
  PREF_PARAM_FIREBASE_FBS_API_KEY,
  PREF_PARAM_FIREBASE_FBS_DATABASE_URL,
  PREF_PARAM_FIREBASE_FBS_USER_EMAIL,
  PREF_PARAM_FIREBASE_FBS_USER_PASSWORD,
  PREF_PARAM_FIREBASE_FBS_WEB_PUSH_KEY,
  PREF_PARAM_FIREBASE_FBS_DEVICE_ID,
  PREF_PARAM_FIREBASE_FBS_UID,
  PREF_PARAM_GMT,
  PREF_PARAM_CLIM_TEMP_MAX,
  PREF_PARAM_CLIM_TEMP_MIN,
  PREF_PARAM_NOTIF_TANK_EMPTY,
  PREF_PARAM_NOTIF_DRIP_ON,
  PREF_PARAM_NOTIF_DRIP_COMPLETE,
  PREF_PARAM_NOTIF_PH,
  PREF_PARAM_NOTIF_TDS,
  PREF_PARAM_NOTIF_DOSE_RESULT,
  PREF_PARAM_NOTIF_TANK_FILLING_COMPLETE,
  PREF_PARAM_DOSING_TIMEOUT_PPM,
  PREF_PARAM_DOSING_TIMEOUT_PH,
  PREF_PARAM_PPM_SWITCH_SCH,
  PREF_PARAM_DRIP_SWITCH_SCH,
  PREF_PARAM_HST_AWAL,
  PREF_PARAM_SCHEDULE_PPM,
  PREF_PARAM_JADWAL_DRIP,
  PREF_PARAM_SCHEDULE_NFT,
  PREF_PARAM_ALWAYS_ON_NFT,
  PREF_PARAM_INTERVAL_OFF_MIST,
  PREF_PARAM_INTERVAL_ON_MIST,
  PREF_PARAM_MIN_MISTING,
  PREF_PARAM_MAX_MISTING,
  PREF_PARAM_FERT_TEMP_MIN,
  PREF_PARAM_FERT_TEMP_MAX,
  PREF_PARAM_MODE_CLIMATE,
  PREF_PARAM_MODE_FERTIGASI,
  PREF_PARAM_TARGET_PPM,
  PREF_PARAM_INTERVAL_ON_PPM,
  PREF_PARAM_INTERVAL_OFF_PPM,
  PREF_PARAM_INTERVAL_REPORT,
  PREF_PARAM_MARGIN_PPM,
  PREF_PARAM_WIFI_SSID,
  PREF_PARAM_WIFI_PASS,
  PREF_PARAM_PH_VOLT_4,
  PREF_PARAM_PH_VOLT_7,
  PREF_PARAM_PH_VOLT_9,
  PREF_PARAM_PH_MIN,
  PREF_PARAM_PH_MAX,
  PREF_PARAM_LAST_ACTIVE,
  PREF_PARAM_PPM_PID_KP,
  PREF_PARAM_PPM_PID_KI,
  PREF_PARAM_PPM_PID_KD,
  PREF_PARAM_PH_PID_KP,
  PREF_PARAM_PH_PID_KI,
  PREF_PARAM_PH_PID_KD,
  PREF_PARAM_FAILSAFE_BELOW_PPM,
  PREF_PARAM_FAILSAFE_COUNTER,
  PREF_PARAM_FAILSAFE_OUTSIDE_PH,
  PREF_PARAM_DOSE_INTERVAL,
  PREF_PARAM_LOCK_METHODE,
  PREF_PARAM_KEY_UNLOCK,
  NEX_BOOT_INFO,
  NEX_HOME_DEVICE_ID,
  NEX_HOME_TANK_WATER,
  NEX_HOME_TANK_ABMIX_LEVEL,
  NEX_HOME_METHODE,
  NEX_HOME_HST_AWAL,
  NEX_HOME_WAKTU,
  NEX_HOME_PH,
  NEX_HOME_PH_INDICATOR,
  NEX_HOME_PH_MAX,
  NEX_HOME_PH_MIN,
  NEX_HOME_PH_SET,
  NEX_HOME_PH_MARGIN,
  NEX_HOME_PH_DELAY_ON,
  NEX_HOME_PH_DELAY_OFF,
  NEX_HOME_PH_DOSE,
  NEX_HOME_PPM,
  NEX_HOME_PPM_MARGIN,
  NEX_HOME_PPM_SET,
  NEX_HOME_PPM_DOSE,
  NEX_HOME_PPM_DELAY_ON,
  NEX_HOME_PPM_DELAY_OFF,
  NEX_HOME_PPM_INDICATOR,
  NEX_HOME_TEMP,
  NEX_HOME_TEMP_SET,
  NEX_HOME_TEMP_MAX,
  NEX_HOME_TEMP_MIN,
  NEX_HOME_TEMP_CHILLER,
  NEX_HOME_TEMP_INDICATOR,
  NEX_HOME_FERTIGASI_MODE,
  NEX_HOME_FERTIGASI_STATE,
  NEX_HOME_SOIL_EC,
  NEX_HOME_SOIL_TEMP,
  NEX_HOME_SOIL_HUM,
  NEX_HOME_SOIL_N,
  NEX_HOME_SOIL_P,
  NEX_HOME_SOIL_K,
  NEX_HOME_PIC_WIFI,
  NEX_HOME_DRIP,
  NEX_HOME_STATE_PH,
  NEX_HOME_DRIP_REMAINING,
  NEX_HOME_INFO_INTERNET_TEXT,
  NEX_HOME_JADWAL_PPM,
  NEX_HOME_SWITCH_SCHEDULE_PPM,
  NEX_HOME_SWITCH_SCHEDULE_DRIP,
  NEX_CLIMATE_HUMIDITY_DELAY_ON,
  NEX_CLIMATE_HUMIDITY_DELAY_OFF,
  NEX_CLIMATE_HUMIDITY_1,
  NEX_CLIMATE_HUMIDITY_2,
  NEX_CLIMATE_HUMIDITY_3,
  NEX_CLIMATE_TEMPERATURE_1,
  NEX_CLIMATE_TEMPERATURE_2,
  NEX_CLIMATE_TEMPERATURE_3,
  NEX_CLIMATE_HUMIDITY_MAX,
  NEX_CLIMATE_HUMIDITY_MIN,
  NEX_CLIMATE_HUMIDITY_MODE,
  NEX_CLIMATE_HUMIDITY_MISTING,
  NEX_CLIMATE_TEMP,
  NEX_CLIMATE_TEMP_MAX,
  NEX_CLIMATE_TEMP_MIN,
  NEX_CLIMATE_TEMP_MODE,
  NEX_CLIMATE_HUMIDITY_AVERAGE,
  NEX_CLIMATE_TEMPERATURE_AVERAGE,
  NEX_CLIMATE_STATE_COOLING_PAD,
  NEX_CLIMATE_STATE_FAN,
  NEX_CLIMATE_SET_HUMIDITY,
  NEX_CLIMATE_MODE,
  NEX_CLIMATE_SET_TEMP,
  NEX_CLIMATE_FAN,
  NEX_CLIMATE_MISTING,
  NEX_WIFI_INFO,
  NEX_WIFI_SSID,
  NEX_WIFI_RSSI,
  NEX_WIFI_CONN,
  NEX_WIFI_INET,
  NEX_WIFI_SERV,
  NEX_WIFI_UPTIME,
  NEX_WIFI_HEAP,
  NEX_MANUAL_MODE_FERT,
  NEX_MANUAL_MODE_CLIM,
  NEX_MANUAL_SWITCH_PUMP_FILL,
  NEX_MANUAL_SWITCH_VALVE_BACKWASH,
  NEX_MANUAL_SWITCH_VALVE_SIRAM,
  NEX_MANUAL_SWITCH_NFT,
  NEX_MANUAL_SWITCH_PUMP_DISTRIBUSI,
  NEX_MANUAL_SWITCH_MISTING,
  NEX_MANUAL_SWITCH_FAN,
  NEX_NOTIF_TANK_EMPTY,
  NEX_NOTIF_DRIP_ON,
  NEX_NOTIF_DRIP_COMPLETE,
  NEX_NOTIF_PH,
  NEX_NOTIF_TDS,
  NEX_NOTIF_DOSE_RESULT,
  NEX_NOTIF_TANK_FILLING_COMPLETE,
  NEX_NOTIF_TANK_ABMIX_LEVEL,
  NEX_DRIP_ADD_INFO,
  NEX_FERT_DOSE_PPM_TIMEOUT,
  NEX_FERT_DOSE_PH_TIMEOUT,
  NEX_FERT_SWITCH_DISABLE_DOSE_NIGHT,
  NEX_FERT_DOSE_DETAIL,
  NEX_FERT_PIPE_FILL_1,
  NEX_FERT_PIPE_FILL_2,
  NEX_FERT_PIPE_FILL_3,
  NEX_FERT_PIPE_DIS_1,
  NEX_FERT_PIPE_DIS_2,
  NEX_FERT_PIPE_BAC_1,
  NEX_FERT_PIPE_BAC_2,
  NEX_FERT_PIPE_BAC_3,
  NEX_FERT_PIPE_BAC_4,
  NEX_FERT_PIPE_BAC_5,
  NEX_FERT_PIPE_DRIP_1,
  NEX_FERT_PIPE_DRIP_2,
  NEX_FERT_PIPE_DRIP_3,
  NEX_FERT_PIPE_DISPOSE_1,
  NEX_FERT_PIPE_DISPOSE_2,
  NEX_FERT_PIPE_DISPOSE_3,
  NEX_FERT_PIPE_FLUSH,
  NEX_FERT_PIPE_DOSE_PH_UP,
  NEX_FERT_PIPE_DOSE_PH_DOWN,
  NEX_FERT_PIPE_DOSE_PPM_UP,
  NEX_FERT_PIPE_DOSE_PPM_DOWN,
  NEX_FERT_PH,
  NEX_FERT_PPM,
  NEX_FERT_TEMP,
  NEX_FERT_STATE,
  NEX_FERT_PIC_PUMP_FILL,
  NEX_FERT_PIC_PUMP_DISTRIBUTION,
  NEX_FERT_PIC_PERISTALTIC_PPM_UP,
  NEX_FERT_PIC_PERISTALTIC_PPM_DOWN,
  NEX_FERT_PIC_PERISTALTIC_PH_UP,
  NEX_FERT_PIC_PERISTALTIC_DOWN,
  NEX_FERT_PIC_VALVE_DISPOSE,
  NEX_FERT_PIC_VALVE_DRIP,
  NEX_FERT_PIC_VALVE_BAC,
  NEX_FERT_PIC_VALVE_FILL,
  NEX_FERT_PIC_VALVE_FLUSH,
  NEX_FERT_PIC_PLANT_1,
  NEX_FERT_PIC_PLANT_2,
  NEX_FERT_PIC_PLANT_3,
  NEX_FERT_PIC_DRIP,
  NEX_FERT_PIC_DISPOSE,
  NEX_FERT_MODE,
  NEX_CALIB_INFO,
  NEX_SET_FERT_MODE,
  NEX_SET_CLIMATE_HUM_MAX,
  NEX_SET_CLIMATE_HUM_MIN,
  NEX_SET_CLIMATE_HUM_DEL_ON,
  NEX_SET_CLIMATE_HUM_DEL_OFF,
  NEX_SET_CLIMATE_TEMP_MIN,
  NEX_SET_CLIMATE_TEMP_MAX,
  NEX_SET_CLIMATE_MODE,
  NEX_SET_FERT_MODE_FERT,
  NEX_SET_FERT_METHODE,
  NEX_SET_FERT_DOSE_TO_PH,
  NEX_SET_FERT_DOSE_TO_PPM,
  NEX_SET_FERT_DELAY_BAC,
  NEX_SET_FERT_DOSE_INTERVAL,
  NEX_LOGIN_QR,
  NEX_SWITCH_FAILSAFE_OUTSIDE,
  NEX_SWITCH_FAILSAFE_COUNTER,
  NEX_SWITCH_FAILSAFE_BELOW_PPM,
};

static const char *stringify[] =
    {
        "SET",
        "UPDATE",
        "PUSH",
        "FLUSH",
        "NUTRIENT",
        "MANUAL",
        "OTOMATIS",
        "HIDUP",
        "MATI",
        "LOW",
        "NORMAL",
        "DFT",
        "NFT",
        "IDLE",
        "DOSING",
        "DOSE PH",
        "DOSE PPM",
        "FILL TANK",
        "DRAIN",
        "DRIP ACTIVE",
        "BACKWASH",
        "CIRCULATION",
        "FLUSH",
        "scr_boot",
        "scr_home",
        "scr_drip",
        "scr_drip_add",
        "scr_set",
        "scr_set_fert",
        "scr_clim",
        "scr_set_clim",
        "scr_calib",
        "scr_notif",
        "scr_set_nft",
        "scr_set_wifi",
        "scr_manual",
        "scr_fert",
        "scr_fert_dft",
        "scr_fert_nft",
        "scr_fert_ph",
        "scr_fert_ppm",
        "scr_fert_temp",
        "scr_fert_fsafe",
        "scr_login",
        "PARSER_TYPE_STRING",
        "PARSER_TYPE_NUM_LONG",
        "PARSER_TYPE_NUM_FLOAT",
        "PARSER_TYPE_SWITCH",
        "PARSER_TYPE_DATETIME_ISO8601",
        "set_dose_dis_night",
        "set_float_main",
        "set_state_flush",
        "set_gmt",
        "set_clim_temp_min",
        "set_clim_temp_max",
        "set_notif_tank_abmix",
        "set_notif_tank_empty",
        "set_notif_drip_on",
        "set_notif_drip_compl",
        "set_notif_ph",
        "set_notif_tds",
        "set_notif_dose_res",
        "set_notif_fill_compl",
        "set_hst_awal",
        "set_fert_methode",
        "set_mode_fertigasi",
        "set_mode_climate",
        "set_last_active",
        "set_dose_to_ph",
        "set_dose_to_ppm",
        "set_delay_backwash",
        "set_interval_report",
        "set_margin_ppm",
        "set_interval_off_ppm",
        "set_interval_on_ppm",
        "set_mode_ppm",
        "set_ph",
        "set_ph_min",
        "set_ph_max",
        "set_sch_ppm",
        "set_sch_penyiraman",
        "set_interval_on_mist",
        "set_interval_off_mist",
        "set_fert_temp_max",
        "set_fert_temp_min",
        "set_clim_hum_max",
        "set_clim_hum_min",
        "set_sw_ppm_sch",
        "set_sw_drip_sch",
        "set_ph_volt_9",
        "set_ph_volt_7",
        "set_ph_volt_4",
        "set_ppm_target",
        "set_dose_interval",
        "set_lock_methode",
        "set_state_tank_ab",
        "set_state_backwash",
        "set_state_ph_up",
        "set_state_ph_down",
        "set_state_drip",
        "set_state_drain",
        "set_state_abmix",
        "set_state_tank_fill",
        "set_state_temp",
        "set_state_blower",
        "set_state_misting",
        "set_bw_time",
        "set_cmd",
        "set_cmd_response",
        "set_state_cool_pad",
        "enblDoseBoot",
        "qtyComplppm",
        "qtyComplph",
        "margComplPpm",
        "margComplPh",
        "disDoseNight",
        "bwTime",
        "pidPpmInt",
        "pidPpmOut",
        "pidPhInt",
        "pidPhOut",
        "tankAbmix",
        "fertMethode",
        "fbsApiKey",
        "fbsDbUrl",
        "fbsUserEmail",
        "fbsUserPass",
        "fbsWebPushKey",
        "fbsDevId",
        "fbsUid",
        "gmt",
        "climTempMax",
        "climTempMin",
        "notifTankEmpty",
        "notifDripOn",
        "notifDripComp",
        "notifPh",
        "notifTds",
        "notifDoseResult",
        "notifTankCompl",
        "doseToPpm",
        "doseToPh",
        "ppmSwitchSch",
        "dripSwitchSch",
        "varHstAwal",
        "schPpm",
        "schDrip",
        "varFertJadwalNftStr",
        "alwaysOnNft",
        "intOffMist",
        "intOnMist",
        "minMist",
        "maxMist",
        "minTemp",
        "maxTemp",
        "modeClimate",
        "modeFertigasi",
        "targetPpm",
        "intOnPpm",
        "intOffPpm",
        "intervalReport",
        "marginPpm",
        "wifiSsid",
        "wifiPass",
        "phVolt4",
        "phVolt7",
        "phVolt9",
        "phMin",
        "phMax",
        "lastActive",
        "ppmPidKp",
        "ppmPidKi",
        "ppmPidKd",
        "phPidKp",
        "phPidKi",
        "phPidKd",
        "FSbelowPpm",
        "FSCounter",
        "FSOutside",
        "doseInterval",
        "lockMethode",
        "keyUnlock",
        "bootInfo",
        "homeDeviceId",
        "homeWaterTank",
        "homeAbmixTank",
        "homeMethode",
        "homeHst",
        "homeWaktu",
        "homePh",
        "homeIndicPh",
        "homePhMax",
        "homePhMin",
        "homePhSet",
        "homePhMar",
        "homePhOn",
        "homePhOff",
        "homePhDose",
        "homePpm",
        "homePpmMar",
        "homePpmSet",
        "homePpmDose",
        "homePpmOn",
        "homePpmOff",
        "homeIndicPpm",
        "homeTemp",
        "homeTempSet",
        "homeTempMax",
        "homeTempMin",
        "homeChiller",
        "homeTempIndic",
        "homeMode",
        "homeFertSta",
        "homeSoilEc",
        "homeSoilTemp",
        "homeSoilHum",
        "homeSoilN",
        "homeSoilP",
        "homeSoilK",
        "homePicWifi",
        "homeDrip",
        "homeStatePh",
        "homeRemainDrip",
        "homeInetInfo",
        "homeSchPpm",
        "homeSwPpm",
        "homeSwDrip",
        "climHumOn",
        "climHumOff",
        "climHum1",
        "climHum2",
        "climHum3",
        "climTemp1",
        "climTemp2",
        "climTemp3",
        "climHumMax",
        "climHumMin",
        "climHumMode",
        "climHumMist",
        "climTemp",
        "climTempMax",
        "climTempMin",
        "climTempMode",
        "climHumAvg",
        "climTempAvg",
        "climCoolingPad",
        "climFan",
        "climSetHum",
        "climMode",
        "climSetTemp",
        "climFan",
        "climMist",
        "setWifiInfo",
        "setWifiSsid",
        "setWifiRssi",
        "setWifiCon",
        "setWifiInet",
        "setWifiServerC",
        "setWifiUptime",
        "setWifiHeap",
        "manCbFert",
        "manCbClim",
        "manSwPumpFill",
        "manSwValvBac",
        "manSwValvSir",
        "manSwNft",
        "manSwPumpDis",
        "manSwMist",
        "manSwFan",
        "notifEmpty",
        "notifDripOn",
        "notifDripComp",
        "notifPh",
        "notifTds",
        "notifDoseRes",
        "notifTankCompl",
        "notifTankNutr",
        "dripAddInfo",
        "fertDosePpmTo",
        "fertDosePhTo",
        "disableDose",
        "fertDoseIn",
        "fertPipFill1",
        "fertPipFill2",
        "fertPipFill3",
        "fertPipDis1",
        "fertPipDis2",
        "fertPipBac1",
        "fertPipBac2",
        "fertPipBac3",
        "fertPipBac4",
        "fertPipBac5",
        "fertPipDrip1",
        "fertPipDrip2",
        "fertPipDrip3",
        "fertPipDispo1",
        "fertPipDispo2",
        "fertPipDispo3",
        "fertPipFlush",
        "fertPipPhUp",
        "fertPipPhDown",
        "fertPipPpmUp",
        "fertPipPpmDown",
        "fertPh",
        "fertPpm",
        "fertTemp",
        "fertState",
        "picPumpFill",
        "picPumpDis",
        "picPeriPpmUp",
        "picPeriPpmDown",
        "picPeriPhUp",
        "picPeriPhDown",
        "picValvDisp",
        "picValvDrip",
        "picValvBac",
        "picValvFill",
        "picValvFlush",
        "picPlant1",
        "picPlant2",
        "picPlant3",
        "fertPicDrip",
        "fertPicDispose",
        "fertMode",
        "calibInfo",
        "setFertMode",
        "setClimHumMax",
        "setClimHumMin",
        "setClimHumOn",
        "setClimHumOff",
        "setClimTempMin",
        "setClimTempMax",
        "setClimMode",
        "setFertMode",
        "setMethode",
        "numDoseToPh",
        "numDoseToPpm",
        "numDelayBac",
        "numDoseIntv",
        "qr0",
        "swFSOutside",
        "swFSCounter",
        "swFSPpmLow",
};

String FBS_UID = "lm9E73h7rohh7gh00sbe8WBZRwa2";
int FBS_DEVICE_ID = 1;
String firebaseRcvPath;
String firebaseRcvData;
String firebaseRcvEvent;
String firebasePathSetParameter = "/smart_farm/" + String(FBS_UID) + "/data/" + "data_device_" + String(FBS_DEVICE_ID) + "/set_parameter/";
String firebasePathSensorStatus = "/smart_farm/" + String(FBS_UID) + "/data/" + "data_device_" + String(FBS_DEVICE_ID) + "/sensor_status";
String firebasePathReport = "/smart_farm/" + String(FBS_UID) + "/data/" + "data_device_" + String(FBS_DEVICE_ID) + "/report";
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
#include <WiFiClientSecure.h>
#include <String.h> // Include the String class if necessary

#define WIFI_SSID "Berjaya2025"
#define WIFI_PASSWORD "Darkangel123"
#define DATABASE_SECRET "ijVgN7gIS5my6JZ3K5NeLKAXjIa6fCNPhKQSQadU"
#define DATABASE_URL "https://smartgh-d4eb3-default-rtdb.firebaseio.com/"
#define FIREBASE_PROJECT_ID "smartgh-d4eb3"
#define FIREBASE_CLIENT_EMAIL "firebase-adminsdk-i97zu@smartgh-d4eb3.iam.gserviceaccount.com"
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDGtLX0flILABVK\n23L4A/K614jU528Y0PrJRytnB0yVR2nO3eQmSLqObv3eN8UCmzJF9eeWws5B2OGO\n/vwhqkQI8FWSYkRBpvOidmtvjcJWeZLdI95H5Fsiv//Q+ZrWNklrkeVSYdhYePFH\n08QEJGN9U7kBsTQUePsjQlXGuHNiOtCLKsIuzaX7EA6SBR+n4BwLsbMto0cwtAKC\nEUuVIbspGxIsT85+BQ7CERpaxmcj42LvpCtNAnfchtk1Kk6zWN18U4VgpQB2x7W0\n3TLch4P9Bjl2Vpij6xovnbub/66Xf5jsntUz0udAB4gYplWMIlury9f3SXV1VFTZ\najI2tRAtAgMBAAECggEAARMoKs7mHbYd515BhHLtBLK2xEQON0mmGaGfa/q/oM0W\nlu5fVg+tpqiWCfYuRCHXx0YZvxiFqhiEu9PIRFxZ6tx18glDCkHfboEKert/Eh2t\nPDH9+VCUZ583QIehHUiE5CaRYX0zAOOClptgI4+Y1Cw4Q3iUagnvfdTVhvIneaAK\nYQBHbZdvaELAqNKp0Vje8laV7YaOBGjDqZNbJ2Z3wq7RrEMT+LQLMk9iYduIAYXI\nXbcgtAAPj68Eqbu+KRzlXQwtYwhqFvrWKcTwbHAFOKI+7ipmd5mjMKbQgA0rnNXU\nHXQuHSA8SR43qMZkif2snjfyCJ8yyK0e07FCpo938QKBgQDlm56Y2PJNRo7r857E\nWqLN4J16OzeaCmK08tEYTUa0HOOjN87+edNJFdEXV9HLHfh2DweOh+8AOS5anfQ4\nxSB5RjrRmvOclrbSjgBsU2z9Tr2Nq0EUudxAS3/v6P+eI0ZYKWxItC6ehaUIqoVQ\nNlJZM/cp9hg15g1UatYJ6z+LFQKBgQDdi8cRPK42n3JjjqP/lPTg+TpNzwxSi+/D\nBge1FNtFw/HZxhrSVzrfDa5cYfrYpPEk2E/DT+XtiDU4XGyvIRcwnmq2glDlNyMy\n30vYrZzCJXYerZk17CYcewqMm8S64DoC0LR8Y/KzWZ2DaFB0oR9d5Y0BXRkf4DoA\nNL6EIu7WuQKBgQC0YWNhNN52Mv5JA6UxIPtRvio5QphV3d7ZxQDblKn9Cc0UBt4J\nMW/5tLgFHKrmZW8yYHBRWx06EbIG4pxglQ0D+VZwIMlNtWF/XKucbpXrEpb72xRP\n0gvkPuwNcACRHak/zZsSKuuNAfU7L6t37pUXGyoLvxgaD9ddAGmSdUwAWQKBgBWs\nFcYm5HftcxgwHPTkkmvrlXuFFJSCoeq3DUv2hVi2yVLfYUJQTC8DvJnG7+3/fKN5\nEZxulXR+DY6849jh6M3VwWSnLNivYx8X3uiMWzhWx85KdyFiP3wrwSVuG3mYc7RQ\nzEca0+QdkR4It04hcNsTmI6Yl9uZaLMadcShUjHpAoGAVpwFo8tf+gXyEnFARHTu\nUnDPcdpblwSnZs15qA35ZW6t3c6PI0KDuz3p7JCaU46JyyFfEBb9WkPxqxGRkWbc\n7c0m4BBjq9xiqwfmtP9gApz/JEfNU5D+O1K0WkRKWaucG7ibxUg6gjRuKGhJMG6M\nsqvOZYC+Nk3ySZEjkwO90Tk=\n-----END PRIVATE KEY-----\n";

void setSensorData(object_t &json, const char *path, const char *unit, const char *title, const char *value);
WiFiClientSecure ssl1, ssl2;
WiFiClientSecure ssl_client;
void getMsg(Messages::Message &msg);
void timeStatusCB(uint32_t &ts);
void printResult(AsyncResult &aResult);
DefaultNetwork network; // initilize with boolean parameter to enable/disable network reconnection
AsyncClientClass client1(ssl1, getNetwork(network));
ServiceAuth sa_auth(timeStatusCB, FIREBASE_CLIENT_EMAIL, FIREBASE_PROJECT_ID, PRIVATE_KEY, 3000 /* expire period in seconds (<= 3600) */);
FirebaseApp app;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client, getNetwork(network));
Messaging messaging;
AsyncResult aResult_no_callback;
bool taskCompleted = false;
RealtimeDatabase Database;
AsyncResult result1, result2;
LegacyToken dbSecret(DATABASE_SECRET);
String reverseString(String str);

void printError(int code, const String &msg)
{
  Serial.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

void setup()
{
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

  Serial.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

  Serial.println("Initializing app...");

  ssl1.setInsecure();
  ssl_client.setInsecure();

  initializeApp(aClient, app, getAuth(sa_auth), aResult_no_callback);
  // initializeApp(client1, app, getAuth(dbSecret));

  // Binding the FirebaseApp for authentication handler.
  // To unbind, use messaging.resetApp();
  app.getApp<Messaging>(messaging);
  app.getApp<RealtimeDatabase>(Database);

  // // Set your database URL
  Database.url(DATABASE_URL);
  String firebasePathSetParameter = "/smart_farm/SLzDtb0A2fZh3UK/data/data_device_1/set_parameter/";

  Database.get(client1, firebasePathSetParameter.c_str(), result1, true /* this option is for Stream connection */);

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.begin();
}
void firebaseUpdateFert();
void loop()
{
  // The async task handler should run inside the main loop
  // without blocking delay or bypassing with millis code blocks.

  // The JWT token processor required for ServiceAuth and CustomAuth authentications.
  // JWT is a static object of JWTClass and it's not thread safe.
  // In multi-threaded operations (multi-FirebaseApp), you have to define JWTClass for each FirebaseApp,
  // and set it to the FirebaseApp via FirebaseApp::setJWTProcessor(<JWTClass>), before calling initializeApp.

  pushFBAsync.call();

  JWT.loop(app.getAuth());

  app.loop();

  messaging.loop();

  Database.loop();

  printResult(aResult_no_callback);
  printResult(result1);
  if (app.ready() && !taskCompleted)
  {
    taskCompleted = true;

    Serial.println("Sending message...");

    Messages::Message msg;
    getMsg(msg);

    messaging.send(aClient, Messages::Parent(FIREBASE_PROJECT_ID), msg, aResult_no_callback);
  }
}
String firebaseWithPath(String path, String child)
{
  return path + "/" + child;
}
void setPushReport(JsonWriter &_writer, object_t &json, const char *sensorName, float sensorValue, const char *format)
{
  object_t _objSensorName, _objValue;
  char sensorValueStr[20];
  snprintf(sensorValueStr, sizeof(sensorValueStr), format, sensorValue);
  char dataPath[30];
  _writer.create(_objSensorName, "sensor_name", sensorName);
  _writer.create(_objValue, "value", sensorValueStr);
  _writer.join(json, 2, _objSensorName, _objValue);
}
void pushFB()
{
  // firebaseUpdateFert();
  // firebaseUpdateSensor();
  // firebaseUpdateClimate();
}
void getMsg(Messages::Message &msg)
{
  String topic = reverseString(FBS_UID);
  Serial.print("topic:");
  Serial.println(topic);
  msg.topic(topic);
  Messages::Notification notification;
  notification.body("Notification body").title("Notification title");
  object_t data, obj1, obj2, obj3, obj4;
  JsonWriter writer;
  writer.create(obj1, "name", string_t("wrench"));
  writer.create(obj2, "mass", string_t("1.3kg"));
  writer.create(obj3, "count", string_t("3"));
  writer.join(data, 3 /* no. of object_t (s) to join */, obj1, obj2, obj3);
  msg.data(data);
  data.clear();
  Messages::AndroidConfig androidConfig;
  androidConfig.priority(Messages::AndroidMessagePriority::_HIGH);
  Messages::AndroidNotification androidNotification;
  androidNotification.notification_priority(Messages::NotificationPriority::PRIORITY_HIGH);
  androidConfig.notification(androidNotification);
  msg.android(androidConfig);
  msg.notification(notification);
}
void timeStatusCB(uint32_t &ts)
{
#if defined(ESP8266) || defined(ESP32) || defined(CORE_ARDUINO_PICO)
  if (time(nullptr) < FIREBASE_DEFAULT_TS)
  {

    configTime(7 * 3600, 0, "pool.ntp.org");
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
void printResult(AsyncResult &aResult)
{
  if (aResult.isEvent())
  {
    Serial.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
  }

  // if (aResult.isDebug())
  // {
  //   Serial.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
  // }

  if (aResult.isError())
  {
    Serial.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
  }

  if (aResult.available())
  {
    RealtimeDatabaseResult &RTDB = aResult.to<RealtimeDatabaseResult>();
    if (RTDB.isStream())
    {
      Serial.println("----------------------------");
      Serial.printf("task: %s\n", aResult.uid().c_str());
      Serial.printf("event: %s\n", RTDB.event().c_str());
      Serial.printf("path: %s\n", RTDB.dataPath().c_str());
      Serial.printf("data: %s\n", RTDB.to<const char *>());
      Serial.printf("type: %d\n", RTDB.type());
      firebaseRcvPath = String(RTDB.dataPath());
      firebaseRcvData = String(RTDB.to<const char *>());
      firebaseRcvEvent = String(RTDB.event());
      Serial.println("=============");
      Serial.println("event:" + String(firebaseRcvEvent == "put"));
      Serial.println("path:" + String(firebaseRcvPath == "/"));
      Serial.println("=============");
      if (firebaseRcvEvent == "put")
      {
        firebaseStreamProcess();
      }
    }
    else
    {
      Serial.println("----------------------------");
      Serial.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
    }
  }
}
void setSensorData(object_t &json, const char *path, const char *unit, const char *title, const char *value)
{
  json.initObject();
  JsonWriter _writer;
  object_t objValue, objUnit, objTitle;
  char key[50]; // A buffer to construct JSON keys
  _writer.create(objValue, "value", value);
  _writer.create(objUnit, "unit", unit);
  _writer.create(objTitle, "title", title);
  _writer.join(json, 3, objValue, objUnit, objTitle);
  _writer.create(json, path, json);
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