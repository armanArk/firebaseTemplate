#ifdef DEBUG
inline void xDebug(const char *message)
{
    Serial.print(message);
}

inline void xDebugln(const char *message)
{
    Serial.println(message);
}
#else
inline void xDebug(const char *message)
{
    // Do nothing in release mode
    (void)message; // Suppress unused parameter warning
}

inline void xDebugln(const char *message)
{
    // Do nothing in release mode
    (void)message; // Suppress unused parameter warning
}
#endif
