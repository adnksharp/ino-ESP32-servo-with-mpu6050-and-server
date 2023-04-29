# Controlling three servos with a gyroscope MPU6050/MPU9250 and ESP32

| [![IMG-20230429-130427555.jpg](https://i.postimg.cc/Dz2SnVKn/IMG-20230429-130427555.jpg)](https://postimg.cc/FYBrVBRB) | [![2023-04-29-13-04.png](https://i.postimg.cc/XJtFV28L/2023-04-29-13-04.png)](https://postimg.cc/bDHdg94S) |
| --------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------- |

Uso de un ESP32 para crear un servidor local que recibe datos de un giroscopio MPU6050/MPU9250 y controla tres servos.

## Materiales
- Kit de desarrollo ESP32
- Giroscopio MPU6050 o MPU9250
- Tres servomotores

## Librerías

- [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [AsyncTCP](https://github.com/dvarrel/ESPAsyncTCP)
- [ESP Async WebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [FS](https://github.com/espressif/arduino-esp32/tree/master/libraries/FS)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [I2Cdev](https://github.com/jrowberg/i2cdevlib)
- [Wire](https://github.com/espressif/arduino-esp32/tree/master/libraries/Wire)
- [MPU6050](https://github.com/jrowberg/i2cdevlib)

## Instalación
Para poder compilar el código es necesario tener instalado el IDE de Arduino y las librerías mencionadas anteriormente.

En Windows, la ruta es: 
```
C:\Users\%USERNAME%\Documents\Arduino\libraries
```

En Linux, la ruta es: 
```
/home/$USER/Arduino/libraries
```

En Mac, la ruta es: 
```
/Users/$USER/Documents/Arduino/libraries
```

Con las librerías instaladas, se puede compilar el código y subirlo al ESP32 clonando este repositorio o descargando el proyecto como un archivo .zip en una carpeta llamada "eServoGiro".

## Conexiones
| ESP32 | MPU6050 | Servo 1 | Servo 2 | Servo 3 |
| ----- | ------- | ------- | ------- | ------- |
| 3V3   | VCC     |         |
| V_IN  |         | VCC     | VCC     | VCC     |
| GND   | GND     | GND     | GND     | GND     |
| G21   | SDA     |         |         |         |
| G22   | SCL     |         |         |         |
| 19    | INT     |         |         |         |
| 13    |         | SIG     |         |         |
| 14    |         |         | SIG     |         |
| 27    |         |         |         | SIG     | 

## Funcionamiento
El ESP32 crea un servidor local que recibe los datos del giroscopio y los envía a la página web. 
Tanto la página web como los servos reciben los datos del giroscopio y se actualizan en tiempo real.

El ESP32 se conecta a la red WiFi con los datos ingresados en el archivo [credentials.h](credentials.h).

El giroscopio MPU6050/MPU9250 se conecta al ESP32 por medio del protocolo I2C.

Los servos se conectan a los pines PWM del ESP32.

### Página web
La página web se encuentra en la carpeta [server](server) y se puede acceder a ella desde la dirección IP del ESP32.

Para actualizar los datos de la página web, se crea una interfaz XMLHttpRequest que envía una petición GET al servidor cada 100ms para obtener los datos del giroscopio en formato JSON.

## Créditos
- [ESP32 Servo Control](https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/)
- [ESP32 Web Server](https://randomnerdtutorials.com/esp32-web-server-spiffs-spi-flash-file-system/)
- [MPU6050](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050/examples/MPU6050_DMP6)
