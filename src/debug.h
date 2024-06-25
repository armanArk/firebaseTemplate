#if DEBUG == 1
#define xDebug(x) Serial.print(x)
#define xDebugln(x) Serial.println(x)
#else
#define xDebug(x)
#define xDebugln(x)
#endif