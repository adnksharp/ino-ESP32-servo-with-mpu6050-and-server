MPU6050 mpu;
volatile bool mpuInterrupt = false;
void dmpDataReady()
{
    mpuInterrupt = true;
}
struct gyroscope
{
    bool dmpReady = false;
    uint8_t mpuIntStatus, devStatus;
    uint16_t packetSize, fifoCount;
    uint8_t fifoBuffer[64];

    Quaternion q;
    VectorInt16 aa;
    VectorInt16 aaReal;
    VectorInt16 aaWorld;
    VectorFloat gravity;

    float ypr[3];

    uint8_t teapotPacket[14] = {'$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n'};

    void begin()
    {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
#endif
        Serial.println(F("Inicializando MPU6050..."));
        mpu.initialize();
        pinMode(INTERRUPT_PIN, INPUT);
        Serial.println(mpu.testConnection() ? F("MPU6050 conectado") : F("MPU6050 error de conexión"));

        devStatus = mpu.dmpInitialize();
        mpu.setXGyroOffset(220);
        mpu.setYGyroOffset(76);
        mpu.setZGyroOffset(-85);
        mpu.setZAccelOffset(1788);
        if (devStatus == 0)
        {
            mpu.CalibrateAccel(6);
            mpu.CalibrateGyro(6);
            mpu.PrintActiveOffsets();
            Serial.println(F("Inicializando DMP..."));
            mpu.setDMPEnabled(true);
            attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
            mpuIntStatus = mpu.getIntStatus();
            dmpReady = true;
            packetSize = mpu.dmpGetFIFOPacketSize();
        }
        else
        {
            Serial.print(F("Error DMP: "));
            Serial.println(devStatus);
        }
    }
    // void update() get yrp pointer
    void updates(float *YPR)
    {
        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer) && devStatus == 0)
        {
#ifdef OUTPUT_READABLE_YAWPITCHROLL
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
#endif
        }

        for (byte i = 0; i < 3; i++)
            YPR[i] = ypr[i];
    }
};