#include "../data.hpp"
#include "../iot-config.hpp"
#include "server-data.hpp"

AsyncWebServer server(80);

IoT iot;
Data data;

struct SERVER
{
    void load()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/html", htmlindex); });
        server.on("/get-update", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
            iot.Json = data.load(iot.value, iot.angle);
            request->send(200, "text/json", iot.Json); });

        server.on("/set-update", HTTP_POST, [](AsyncWebServerRequest *request)
                  {
            //{id-0: '0-axis', value-0: -90, angle-0: 22, id-1: '1-axis', value-1: 18, …}
            int params = request->params();
            String value[params];
            for (int i = 0; i < params; i++)
            {
                AsyncWebParameter *p = request->getParam(i);
                value[i] = p->value();
            }
            Serial.println("params: " + String(params));
            for (int i = 0; i < params; i++)
                iot.value[i] = value[i].toFloat();
            request->send(200, "text/plain", "OK"); });

        server.onNotFound([](AsyncWebServerRequest *request)
                          { request->redirect("/"); });
    }

    void run()
    {
        server.begin();
    }
};