struct Data
{
    String JSON[3] = {"id", "value", "angle"};

    String load(float *value, byte *angle)
    {
        const size_t CAPACITY = JSON_ARRAY_SIZE(16);

        StaticJsonDocument<CAPACITY> test;
        for (int i = 0; i < 3; i++)
        {
            test[JSON[0] + "-" + String(i)] = String(i) + "-axis";
            test[JSON[1] + "-" + String(i)] = value[i];
            test[JSON[2] + "-" + String(i)] = angle[i];
        }
        String json;
        serializeJson(test, json);
        return json;
    }
};
