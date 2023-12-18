void initBT() {

  preferences.begin("device", false);


  String deviceName = "luxe_";
  deviceName += preferences.getString("name", "E-ink display");


  int str_length = deviceName.length() + 1;
  char char_arrayName[str_length];

  deviceName.toCharArray(char_arrayName, str_length);


  // Create the BLE Device
  BLEDevice::init(char_arrayName);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_NOTIFY);

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE);

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);


  String id1 = "lux_id1-";
  id1 += preferences.getString("id1", "none");

  String id2 = "lux_id2-";
  id2 += preferences.getString("id2", "none");

  String id3 = "lux_id3-";
  id3 += preferences.getString("id3", "none");

  String id4 = "lux_id4-";
  id4 += preferences.getString("id4", "none");


  int timePassed = millis();


  delay(2000);

  while (setupMode) {

    if (digitalRead(button_switch_right) == LOW && digitalRead(button_switch_left) == LOW) {

      buzz();
      preferences.putInt("boot", dataTime);
      dataScreen();
      dataScreen();
      writeEasyNeoPixel(0, 0, 0, 0);
      preferences.putBool("skipWiFi", true);
      Serial.println("TURNING OFFFF");
      preferences.end();
      esp_deep_sleep_start();
    }



    if (millis() - timePassed > 30000 && !deviceConnected) {
      preferences.putInt("boot", 1);
      dataScreen();
      dataScreen();
      preferences.putBool("skipWiFi", true);
      Serial.println("TURNING OFFFF");
      writeEasyNeoPixel(0, 0, 0, 0);
      buzz();
      preferences.end();
      esp_deep_sleep_start();
    }



    int str_len = id1.length() + 1;
    char char_array[str_len];
    id1.toCharArray(char_array, str_len);
    pTxCharacteristic->setValue(char_array);
    pTxCharacteristic->notify();
    delay(100);

    str_len = id2.length() + 1;
    char_array[str_len];
    id2.toCharArray(char_array, str_len);
    pTxCharacteristic->setValue(char_array);
    pTxCharacteristic->notify();
    delay(100);

    str_len = id3.length() + 1;
    char_array[str_len];
    id3.toCharArray(char_array, str_len);
    pTxCharacteristic->setValue(char_array);
    pTxCharacteristic->notify();
    delay(100);

    str_len = id4.length() + 1;
    char_array[str_len];
    id4.toCharArray(char_array, str_len);
    pTxCharacteristic->setValue(char_array);
    pTxCharacteristic->notify();
    delay(100);

// H5EK6UFBYG
    int n = WiFi.scanNetworks();
    delay(100);

    if (n == 0) {
      Serial.println("no networks found");
    } else {

      for (int i = 0; i < n; ++i) {

        int str_len = WiFi.SSID(i).length() + 1;
        char char_array[str_len];
        WiFi.SSID(i).toCharArray(char_array, str_len);
        pTxCharacteristic->setValue(char_array);
        pTxCharacteristic->notify();
        delay(100);


        Serial.println(WiFi.SSID(i));
      }
    }
  }
}