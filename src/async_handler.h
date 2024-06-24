class Async
{
private:
    unsigned long interval;
    void (*func)(void);
    unsigned long lastTime;
    bool timerEnabled;
    unsigned long intervalLeft;
    unsigned long delayTime;
    unsigned long intervalAdder;

public:
    Async(void (*f)(void), unsigned long interval)
    {
        this->interval = interval;
        this->func = f;
        this->lastTime = millis();
        this->timerEnabled = true;
    }

    void call()
    {
        if (!timerEnabled)
        {
            return; // Timer is off, do not execute func
        }

        unsigned long currentTime = millis();
        this->delayTime = currentTime - this->lastTime;

        // get countdown left
        this->intervalLeft = (this->interval + this->intervalAdder) - this->delayTime;
        if (this->intervalLeft < 0)
            this->intervalLeft = 0;
        if (this->delayTime >= this->interval)
        {
            func();
            this->intervalAdder = 0;
            this->lastTime = currentTime;
        }
    }

    unsigned long getInterval()
    {
        return this->interval / 1000;
    }
    unsigned long getDelayTime()
    {
        return this->delayTime / 1000;
    }
    unsigned long getIntervalLeft()
    {
        return this->intervalLeft / 1000;
    }
    unsigned long getIntervalAdder()
    {
        return this->intervalAdder / 1000;
    }
    void setInterval(unsigned long interval)
    {
        this->interval = interval;
        this->timerEnabled = true;
    }
    void addInterval(unsigned long interval)
    {
        this->intervalAdder = this->intervalAdder + interval;
    }
    void callVoid()
    {
        func();
    }
    void reset(unsigned long newInterval)
    {
        this->interval = newInterval;
        this->lastTime = millis();               // Reset the last execution time
        this->timerEnabled = (newInterval != 0); // Enable the timer if newInterval is not 0
    }

    void turnOffTimer()
    {
        this->timerEnabled = false;
    }

    void turnOnTimer()
    {
        this->timerEnabled = true;
    }
};
