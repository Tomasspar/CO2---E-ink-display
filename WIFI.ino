void initWiFi() {

  preferences.begin("device", false);


  String ssdWifi = preferences.getString("ssid", "");
  String passwordWifi = preferences.getString("password", "");

  char charBufferName[100];
  char charBufferPassword[100];

  ssdWifi.toCharArray(charBufferName, 100);
  passwordWifi.toCharArray(charBufferPassword, 100);

  ssid = charBufferName;
  password = charBufferPassword;


  Serial.println(ssdWifi);
  Serial.println(passwordWifi);




  if (ssdWifi != "") {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");


    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
      i++;

      if (i > 5) {
        int wifiTry = preferences.getInt("wifiTry", 0);
        wifiTry += 1;
        preferences.putInt("wifiTry", wifiTry);
        break;
      }
    }



    if (WiFi.status() == WL_CONNECTED) {

      preferences.putInt("wifiTry", 0);

      String id1 = preferences.getString("id1", "none");
      String id2 = preferences.getString("id2", "none");
      String id3 = preferences.getString("id3", "none");
      String id4 = preferences.getString("id4", "none");


      HTTPClient http;

      String httpRequestData = serverName;
      httpRequestData += "?id1=";
      httpRequestData += id1;
      httpRequestData += "&id2=";
      httpRequestData += id2;
      httpRequestData += "&id3=";
      httpRequestData += id3;
      httpRequestData += "&id4=";
      httpRequestData += id4;


      Serial.println(httpRequestData);
      http.begin(httpRequestData.c_str());
      int timer = millis();
      int httpResponse = -1;

      httpResponse = http.GET();

      Serial.print("HTTP Response: ");
      Serial.println(httpResponse);

      String response = http.getString();
      Serial.println(response);

      doc.clear();
      DeserializationError error = deserializeJson(doc, response);

      if (httpResponse == 200) {



        if (doc["name_1"] != "" && doc["name_1"] != name_1) {
          String newName_1 = doc["name_1"];
          preferences.putString("name1", newName_1);
        }

        if (doc["name_2"] != "" && doc["name_2"] != name_2) {
          String newName_2 = doc["name_2"];
          preferences.putString("name2", newName_2);
        }

        if (doc["name_3"] != "" && doc["name_3"] != name_3) {
          String newName_3 = doc["name_3"];
          preferences.putString("name3", newName_3);
        }

        if (doc["name_4"] != "" && doc["name_4"] != name_4) {
          String newName_4 = doc["name_4"];
          preferences.putString("name4", newName_4);
        }


        if (doc["co2_1"] != 0) {
          ppm_1 = doc["co2_1"];
          Serial.println(ppm_1);
          preferences.putFloat("ppm_1", ppm_1);
        }

        if (doc["co2_2"] != 0) {
          ppm_2 = doc["co2_2"];
          Serial.println(ppm_2);
          preferences.putFloat("ppm_2", ppm_2);
        }

        if (doc["co2_3"] != 0) {
          ppm_3 = doc["co2_3"];
          Serial.println(ppm_3);
          preferences.putFloat("ppm_3", ppm_3);
        }

        if (doc["co2_4"] != 0) {
          ppm_4 = doc["co2_4"];
          Serial.println(ppm_4);
          preferences.putFloat("ppm_4", ppm_4);
        }


        if ((ppm_1 > 1200 && id1 != "none") || (ppm_2 > 1200 && id2 != "none") || (ppm_3 > 1200 && id3 != "none") || (ppm_4 > 1200 && id4 != "none")) {

          bool volume = preferences.getBool("volume", false);

          if (volume == 1) {
            buzz();
            buzz();
            buzz();
          }
        }


        bool m = preferences.getBool("metric", true);

        if (m) {
          if (doc["temperature_1"] != 0) {
            temp_1 = doc["temperature_1"];
            Serial.println(temp_1);
            preferences.putFloat("temp_1", temp_1);
          }

          if (doc["temperature_2"] != 0) {
            temp_2 = doc["temperature_2"];
            Serial.println(temp_2);
            preferences.putFloat("temp_2", temp_2);
          }

          if (doc["temperature_3"] != 0) {
            temp_3 = doc["temperature_3"];
            Serial.println(temp_3);
            preferences.putFloat("temp_3", temp_3);
          }

          if (doc["temperature_4"] != 0) {
            temp_4 = doc["temperature_4"];
            Serial.println(temp_4);
            preferences.putFloat("temp_4", temp_4);
          }

        } else {

          if (doc["temperature_1"] != 0) {
            temp_1 = doc["temperature_1"];
            temp_1 *= 1.8;
            temp_1 += 32;
            Serial.println(temp_1);
            preferences.putFloat("temp_1", temp_1);
          }

          if (doc["temperature_2"] != 0) {
            temp_2 = doc["temperature_2"];
            temp_2 *= 1.8;
            temp_2 += 32;
            Serial.println(temp_2);
            preferences.putFloat("temp_2", temp_2);
          }

          if (doc["temperature_3"] != 0) {
            temp_3 = doc["temperature_3"];
            temp_3 *= 1.8;
            temp_3 += 32;
            Serial.println(temp_3);
            preferences.putFloat("temp_3", temp_3);
          }

          if (doc["temperature_4"] != 0) {
            temp_4 = doc["temperature_4"];
            temp_4 *= 1.8;
            temp_4 += 32;
            Serial.println(temp_4);
            preferences.putFloat("temp_4", temp_4);
          }
        }


        if (doc["humidity_1"] != 0) {
          hum_1 = doc["humidity_1"];
          Serial.println(hum_1);
          preferences.putFloat("hum_1", hum_1);
        }

        if (doc["humidity_2"] != 0) {
          hum_2 = doc["humidity_2"];
          Serial.println(hum_2);
          preferences.putFloat("hum_2", hum_2);
        }

        if (doc["humidity_3"] != 0) {
          hum_3 = doc["humidity_3"];
          Serial.println(hum_3);
          preferences.putFloat("hum_3", hum_3);
        }

        if (doc["humidity_4"] != 0) {
          hum_4 = doc["humidity_4"];
          Serial.println(hum_4);
          preferences.putFloat("hum_4", hum_4);
        }



        up_to_date_1 = doc["up_to_date_1"];
        preferences.putBool("up_to_date_1", up_to_date_1);

        up_to_date_2 = doc["up_to_date_2"];
        preferences.putBool("up_to_date_2", up_to_date_2);

        up_to_date_3 = doc["up_to_date_3"];
        preferences.putBool("up_to_date_3", up_to_date_3);

        up_to_date_4 = doc["up_to_date_4"];
        preferences.putBool("up_to_date_4", up_to_date_4);
      } else {

        preferences.putBool("skipWiFi", false);
        Serial.println("TURNING OFFFF");
        preferences.putInt("boot", dataTime);

        esp_deep_sleep_start();
      }


      http.end();
    }

    WiFi.disconnect();
  }
}
