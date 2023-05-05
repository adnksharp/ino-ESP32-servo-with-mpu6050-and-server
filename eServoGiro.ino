#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <MPU6050_6Axis_MotionApps20.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif
#define OUTPUT_READABLE_YAWPITCHROLL
#define INTERRUPT_PIN 19

#include "credentials.h"
#include "ap-utils.hpp"
#include "server/server-utils.hpp"
#include "mpu-utils.hpp"
#include "servo-utils.hpp"

byte SERVO[3] = {13, 14, 27};
float ANGLE[3] = {0, 0, 0};

SERVER srv;
accessPoint ap;
gyroscope gyro;
servomotor servo;

void setup()
{
	Serial.begin(115200);
	servo.begin(SERVO);
	Serial.println("Iniciando...");
	Serial.println("Cargando datos...");
	const size_t CAPACITY = JSON_ARRAY_SIZE(16);
	for (int i = 0; i < 3; i++)
	{
		iot.id[i] = String(i) + "-axis";
		iot.value[i] = 0.0F;
		iot.angle[i] = map(iot.value[i], -180, 180, 0, 90);
	}
	iot.Json = data.load(iot.value, iot.angle);
	Serial.println("Conectando a la red...");
	ap.load();
	ap.print();
	Serial.println("Iniciando servidor...");
	srv.load();
	srv.run();
	Serial.println("Cargando MPU6050...");
	gyro.begin();
	Serial.println("Servidor iniciado");
}

void loop()
{
	if (iot.lock)
		gyro.updates(ANGLE);
	for (byte i = 0; i < 3; i++)
	{
		float cache = ANGLE[i] * 180 / M_PI;
		iot.value[i] = float(cache);
		cache = (180 + cache) / 2;
		iot.angle[i] = byte(cache);
		servo.write(&i, &iot.angle[i]);
	}
}