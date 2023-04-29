struct accessPoint
{
	char ssid[20], pass[20], ip[20];

	void print()
	{
		Serial.println("SSID: " + String(ssid) + "\thost: http://" + String(ip));
	}

	void load()
	{
		WiFi.begin(id, password);
		int Sleep = millis();
		while (WiFi.status() != WL_CONNECTED)
		{
			delay(200);
			Serial.print("* ");
			if (millis() - Sleep > 15000)
			{
				Serial.println("Error al conectar");
				ESP.restart();
			}
		}
		IPAddress IP = WiFi.localIP();
		strcpy(ip, IP.toString().c_str());
		strcpy(ssid, id);
		strcpy(pass, password);
		Serial.println(" OK");
	}

	void create()
	{
		WiFi.softAP(id, password);
		IPAddress IP = WiFi.softAPIP();
		strcpy(ip, IP.toString().c_str());
		strcpy(ssid, id);
		strcpy(pass, password);
		Serial.println(" OK");
	}
};
