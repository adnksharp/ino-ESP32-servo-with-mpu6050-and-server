struct servomotor
{
    byte error = 450, ret = 20;
    byte Servo[10], loaded[3];
    float angle[3];

    void begin(byte *pin)
    {
        for (byte i =0; i < sizeof(pin); i++)
        {
            Servo[i] = pin[i];
            pinMode(Servo[i], OUTPUT);
        }
    }
    void write(byte *pin, byte *angle)
    {
        if (abs(loaded[*pin] - *angle) < 1)
            return;
        loaded[*pin] = *angle;
        int Sleep = *angle * 2000 / 180;
        Sleep += error;
        for (byte c = 0; c < ret; c++)
        {
            for (byte i = 0; i < 2; i++)
            {
                digitalWrite(Servo[*pin], i == 0 ? HIGH : LOW);
                delayMicroseconds(i == 0 ? Sleep : 20000 - Sleep);
            }
        }
    }
};
