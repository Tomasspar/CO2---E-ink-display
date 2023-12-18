#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <WiFi.h>
#include <Preferences.h>
#include <Esp.h>
#include <ArduinoJson.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <Update.h>



#define VERSION 3




BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
BLECharacteristic *temperatureCharacteristic;
BLECharacteristic *humidityCharacteristic;
BLECharacteristic *co2Characteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;


char *ssid = "";
char *password = "";

float temp = 0;
float hum = 0;
float ppm = 0;

bool setupMode = false;

int totalLength;  //total size of firmware
int currentLength = 0;

void initWiFi();
void initBT();
void initDataBT();
void measure_and_report();

SensirionI2CScd4x scd4x;
Preferences preferences;
DynamicJsonDocument doc(1024);

const char *serverName = "https://us-central1-co2-sensor-ab3c5.cloudfunctions.net/uploadData";



#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"  // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define enviornmentService BLEUUID((uint16_t)0x181A)

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60          /* Time ESP32 will go to sleep (in seconds) */

#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 8
#define BUZZER 3

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    //esp_deep_sleep_start();
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    preferences.begin("device", false);

    if (rxValue.length() > 0) {


      deserializeJson(doc, rxValue);
      JsonObject obj = doc.as<JsonObject>();
      String dongleId = obj["id"];
      String refreshRate = obj["refresh"];
      String ssdWifi = obj["ssid"];
      String passwordWifi = obj["password"];

      String deviceName = obj["name"];

      if (deviceName != "") {
        preferences.putString("name", deviceName);
      }

      preferences.putBool("production", true);



      preferences.putInt("refreshRate", refreshRate.toInt());

      String newWifiMode = obj["wifiMode"];
      if (newWifiMode == "true") {
        preferences.putBool("wifiMode", true);
      } else {
        preferences.putBool("wifiMode", false);
      }



      char charBufferName[100];
      char charBufferPassword[100];
      ssdWifi.toCharArray(charBufferName, 100);
      passwordWifi.toCharArray(charBufferPassword, 100);

      ssid = charBufferName;
      password = charBufferPassword;

      if (ssid != "") {
        preferences.putString("ssid", ssid);
        preferences.putString("password", password);
      }



      setupMode = false;

    }
  }
};





void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }

  Wire.begin(6, 7);

  uint16_t error;
  char errorMessage[256];

  scd4x.begin(Wire);


  error = scd4x.measureSingleShot();
  if (error) {
    Serial.print("Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }




  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(0, INPUT);


  preferences.begin("device", false);

  int refreshRate = preferences.getInt("refreshRate", 180);
  if (refreshRate == 0) {
    refreshRate = 90;
  }



  int bootCount = preferences.getInt("bootCount", 0);
  bootCount++;
  preferences.putInt("bootCount", bootCount);

  String ssidWifi = preferences.getString("ssid", "");
  bool wifiMode = preferences.getBool("wifiMode", false);
  String id = preferences.getString("id", "");


  int bootTime = bootCount * 5;

  Serial.println(refreshRate);
  Serial.println(bootTime);
  Serial.println(ssidWifi);
  Serial.println(id);

  if (id == "") {
    analogWrite(RED_LED, 0);
    analogWrite(GREEN_LED, 255);
  } else {
    analogWrite(RED_LED, 255);
    analogWrite(GREEN_LED, 255);
  }


  if (digitalRead(0)) {
    setupMode = true;
  }





  bool production = preferences.getBool("production", false);

  esp_sleep_enable_timer_wakeup(5 * uS_TO_S_FACTOR);


  if (!production && bootTime >= refreshRate && id != "") {

    if (setupMode) {
      Serial.println("SETUP MODE - TRUE");
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 0);
      initBT();

    } else {

      Serial.println("WIFI AND BLUETOOTH DATA TRANSMIT");
      analogWrite(RED_LED, 255);
      analogWrite(GREEN_LED, 0);
      preferences.putInt("bootCount", 0);
      initDataBT();
      initWiFi();
    }


  } else {


    if (setupMode) {
      Serial.println("SETUP MODE - TRUE");
      analogWrite(RED_LED, 0);
      analogWrite(GREEN_LED, 0);
      initBT();
    }


    if (wifiMode == true && ssidWifi != "" && bootTime >= refreshRate && id != "") {
      Serial.println("WIFI AND BLUETOOTH DATA TRANSMIT");
      analogWrite(RED_LED, 255);
      analogWrite(GREEN_LED, 0);
      preferences.putInt("bootCount", 0);
      initDataBT();
      initWiFi();
    }



    if (wifiMode == false && bootTime >= refreshRate && id != "") {
      Serial.println("BLUETOOTH DATA TRANSMIT");
      analogWrite(RED_LED, 255);
      analogWrite(GREEN_LED, 0);
      // analogWrite(BLUE_LED, 255);
      preferences.putInt("bootCount", 0);
      initDataBT();
    }
  }
}



void loop() {



  if (!setupMode) {
    delay(100);
    esp_deep_sleep_start();
  }
}

void initBT() {

  String deviceName = "lux_";
  deviceName += preferences.getString("name", "LUXAFOR DONGLE");



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

  String id = preferences.getString("id", "none");



  int str_len = id.length() + 1;
  char char_array[str_len];

  id.toCharArray(char_array, str_len);


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);



  int timePassed = millis();

  delay(3000);

  while (setupMode) {


    if (digitalRead(0)) {
      setupMode = false;
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      esp_deep_sleep_start();
    }


    if (!deviceConnected && millis() - timePassed > 120000) {
      setupMode = false;
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      esp_deep_sleep_start();
    }



    pTxCharacteristic->setValue(char_array);
    pTxCharacteristic->notify();
    delay(100);
    Serial.println(char_array);

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


  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}






void initDataBT() {

  String deviceName = preferences.getString("name", "lux_DONGLE");

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
  temperatureCharacteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0x2A6E),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  temperatureCharacteristic->addDescriptor(new BLE2902());

  BLEDescriptor TemperatureDescriptor(BLEUUID((uint16_t)0x2901));
  TemperatureDescriptor.setValue("Temperature");
  temperatureCharacteristic->addDescriptor(&TemperatureDescriptor);

  humidityCharacteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0x2A6F),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  humidityCharacteristic->addDescriptor(new BLE2902());

  BLEDescriptor HumidityDescriptor(BLEUUID((uint16_t)0x2901));
  HumidityDescriptor.setValue("Humidity");
  humidityCharacteristic->addDescriptor(&HumidityDescriptor);

  co2Characteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0x2B8C),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  co2Characteristic->addDescriptor(new BLE2902());

  BLEDescriptor Co2Descriptor(BLEUUID((uint16_t)0x2901));
  Co2Descriptor.setValue("co2");
  co2Characteristic->addDescriptor(&Co2Descriptor);


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

  ppm = 0;

  int measure_tries = 0;

  Serial.println("BLUETOOTH");
  while (ppm == 0 && measure_tries < 6) {
    measure_tries++;
    measure_and_report();
  }

  if (measure_tries < 5) {

    String id = preferences.getString("id", "none");

    int str_len = id.length() + 1;
    char char_array[str_len];

    id.toCharArray(char_array, str_len);

    for (int i = 0; i < 5; i++) {


      pTxCharacteristic->setValue(char_array);
      pTxCharacteristic->notify();

      char co2String[4];
      dtostrf(ppm, 1, 0, co2String);
      co2Characteristic->setValue(co2String);
      co2Characteristic->notify();
      delay(100);


      char humString[3];
      dtostrf(hum, 1, 0, humString);
      humidityCharacteristic->setValue(humString);
      humidityCharacteristic->notify();
      delay(100);


      char tempString[5];
      dtostrf(temp, 1, 1, tempString);
      temperatureCharacteristic->setValue(tempString);
      temperatureCharacteristic->notify();

      delay(500);
    }
  }
}






void initWiFi() {

  Serial.println("WIFI");
  int measure_tries = 0;
  while (ppm == 0 && measure_tries < 10) {
    measure_tries++;
    measure_and_report();
  }


  if (measure_tries < 9) {


    preferences.begin("device", false);

    String ssdWifi = preferences.getString("ssid", "");
    String passwordWifi = preferences.getString("password", "");
    Serial.println(passwordWifi);
    String id = preferences.getString("id", "none");
    bool production = preferences.getBool("production", false);


    char charBufferName[100];
    char charBufferPassword[100];

    ssdWifi.toCharArray(charBufferName, 100);
    passwordWifi.toCharArray(charBufferPassword, 100);

    ssid = charBufferName;
    password = charBufferPassword;



    if (production) {
      WiFi.begin(ssid, password);
    } else {
       WiFi.begin("*********", "***********");
    }

    Serial.print("Connecting to WiFi ..");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
      i++;

      if (i > 8) {
        int connectionTry = preferences.getInt("connectionTry", 0);
        connectionTry++;
        if (connectionTry >= 10) {
          tone(BUZZER, 1000);
          delay(500);
          noTone(BUZZER);
        }
        preferences.putInt("connectionTry", connectionTry);
        break;
      }
    }



    if (WiFi.status() == WL_CONNECTED) {
      preferences.putInt("connectionTry", 0);
      int refreshRate = preferences.getInt("refreshRate", 180);
      if (refreshRate == 0) {
        refreshRate = 180;
      }
      String deviceName = preferences.getString("name", "DONGLE");

      if (deviceName == "null") {
        deviceName = "LUXAFOR%20DONGLE";
      }

      const char *char_array = deviceName.c_str();
      String char_array_copy = "";

      for (int i = 0; i < deviceName.length(); i++) {

        if (char_array[i] == ' ') {
          char_array_copy += "%20";
        } else {
          char_array_copy += char_array[i];
        }
      }

      deviceName = char_array_copy;

      uint16_t eror;
      char errorMessage[256];
      // stop potentially previously started measurement
      eror = scd4x.stopPeriodicMeasurement();
      if (eror) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(eror, errorMessage, 256);
        Serial.println(errorMessage);
      }

      float offset = 0.0;
      eror = scd4x.getTemperatureOffset(offset);
      delay(5);

      HTTPClient http;

      String httpRequestData = serverName;
      httpRequestData += "?id=";
      httpRequestData += id;
      httpRequestData += "&temperature=";
      httpRequestData += temp;
      httpRequestData += "&humidity=";
      httpRequestData += hum;
      httpRequestData += "&co2=";
      httpRequestData += ppm;
      httpRequestData += "&upload=";
      httpRequestData += refreshRate;
      httpRequestData += "&name=";
      httpRequestData += deviceName;
      httpRequestData += "&version=";
      httpRequestData += VERSION;
      httpRequestData += "&tempoffset=";
      httpRequestData += offset;
      httpRequestData += "&production=";
      httpRequestData += production;

      Serial.println(httpRequestData);
      http.begin(httpRequestData.c_str());
      int httpResponse = http.GET();

      if (httpResponse == 200) {
        Serial.print("HTTP Response: ");
        Serial.println(httpResponse);

        String response = http.getString();
        Serial.println(response);

        doc.clear();
        DeserializationError error = deserializeJson(doc, response);

        String idReturn = doc["id"];
        int newRefreshRate = doc["newUploadRate"];
        String newName = doc["newName"];
        String updateFileLocation = doc["location"];

        bool isProduction = true;
        bool changeProduction = false;
        isProduction = doc["production"];
        changeProduction = doc["changeProduction"];

        bool notification = false;
        notification = doc["notification"];

        if (notification) {
          preferences.putBool("notification", true);
        } else {
          preferences.putBool("notification", false);
        }


        if (changeProduction) {

          bool temp = preferences.getBool("production", true);

          if (temp != isProduction) {
            preferences.putBool("production", isProduction);

            if (isProduction) {
              analogWrite(RED_LED, 0);
              analogWrite(GREEN_LED, 255);
              tone(BUZZER, 1000);
              delay(500);
              noTone(BUZZER);
              analogWrite(RED_LED, 255);
              analogWrite(GREEN_LED, 0);
              delay(500);

              analogWrite(RED_LED, 0);
              analogWrite(GREEN_LED, 255);
              tone(BUZZER, 1000);
              delay(500);
              noTone(BUZZER);
              analogWrite(RED_LED, 255);
              analogWrite(GREEN_LED, 0);
              delay(500);

              analogWrite(RED_LED, 0);
              analogWrite(GREEN_LED, 255);
              tone(BUZZER, 1000);
              delay(500);
              noTone(BUZZER);
              analogWrite(RED_LED, 255);
              analogWrite(GREEN_LED, 0);
              delay(500);


              analogWrite(RED_LED, 0);
              analogWrite(GREEN_LED, 255);
              delay(9999999999);
            }
          }
        }


        float temperatureCalibration = 0.0;
        temperatureCalibration = doc["temperatureFactoryCalibration"];
        Serial.println(temperatureCalibration);

        float co2Calibration = 0.0;
        co2Calibration = doc["co2FactoryCalibration"];
        Serial.println(co2Calibration);

        bool factoryReset = false;
        factoryReset = doc["factoryReset"];

        if (temperatureCalibration != 0.0 && temperatureCalibration > 0) {

          uint16_t error;
          char errorMessage[256];
          Serial.println("TEMPERATURE CALIBRATION");
          // stop potentially previously started measurement
          error = scd4x.stopPeriodicMeasurement();
          if (error) {
            Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
            errorToString(error, errorMessage, 256);
            Serial.println(errorMessage);
          }

          delay(500);

          error = scd4x.setTemperatureOffset(temperatureCalibration);
          delay(5);
        }


        if (co2Calibration > 0) {

          uint16_t error;
          char errorMessage[256];
          Serial.println("CO2 CALIBRATION");
          // stop potentially previously started measurement
          error = scd4x.stopPeriodicMeasurement();
          if (error) {
            Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
            errorToString(error, errorMessage, 256);
            Serial.println(errorMessage);
          }

          delay(500);
          uint16_t frcCorrection = 100.0;
          error = scd4x.performForcedRecalibration(co2Calibration, frcCorrection);
          delay(500);
        }


        if (factoryReset) {
          uint16_t error;
          char errorMessage[256];
          Serial.println("FACTORY CALIBRATION");
          // stop potentially previously started measurement
          error = scd4x.stopPeriodicMeasurement();
          if (error) {
            Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
            errorToString(error, errorMessage, 256);
            Serial.println(errorMessage);
          }

          delay(500);
          scd4x.performFactoryReset();
          delay(500);
        }

        Serial.println(newRefreshRate);
        Serial.println(newName);

        preferences.putInt("refreshRate", newRefreshRate);

        if (newName) {
          preferences.putString("name", newName);
        }


        if (updateFileLocation != "") {

          http.end();
          http.begin(updateFileLocation);

          int resp = http.GET();

          if (resp == 200) {

            totalLength = http.getSize();
            // transfer to local variable
            int len = totalLength;

            // this is required to start firmware update process
            Update.begin(UPDATE_SIZE_UNKNOWN);

            uint8_t buff[128] = { 0 };

            WiFiClient *stream = http.getStreamPtr();
            // read all data from server
            Serial.println("Updating firmware...");
            while (http.connected() && (len > 0 || len == -1)) {
              // get available data size
              size_t size = stream->available();
              if (size) {
                // read up to 128 byte
                int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                // pass to function
                updateFirmware(buff, c);
                if (len > 0) {
                  len -= c;
                }
              }
              delay(1);
            }

          } else {
            Serial.println("Cannot download firmware file.");
          }
        }
      }


      http.end();
    }
  }
}










void measure_and_report() {

  uint16_t error;
  char errorMessage[256];



  delay(1000);

  // Read Measurement
  uint16_t co2 = 0;
  float temperature = 0.0f;
  float humidity = 0.0f;
  bool isDataReady = false;
  error = scd4x.getDataReadyFlag(isDataReady);


  uint16_t targetCo2Concentration = 1360.0;
  uint16_t frcCorrection = 100.0;


  uint16_t asEnabled = 0;
  float offset = 0.0;


  delay(5);


  if (error) {
    Serial.print("Error trying to execute readMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    return;
  }
  if (!isDataReady) {
    return;
  }
  error = scd4x.readMeasurement(co2, temperature, humidity);
  if (error) {
    Serial.print("Error trying to execute readMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else if (co2 == 0) {
    Serial.println("Invalid sample detected, skipping.");
  } else {
    Serial.print("Co2:");
    Serial.print(co2);
    Serial.print("\t");
    Serial.print("Temperature:");
    Serial.print(temperature);
    Serial.print("\t");
    Serial.print("Humidity:");
    Serial.println(humidity);
  }

  temp = temperature;
  hum = humidity;
  ppm = co2;

  bool notify = preferences.getBool("notification", false);

  if (notify && ppm > 1200) {
    tone(BUZZER, 1000);
    delay(500);
    noTone(BUZZER);
  }
}






void updateFirmware(uint8_t *data, size_t len) {
  Update.write(data, len);


  currentLength += len;
  // Print dots while waiting for update to finish
  //Serial.print('.');
  // if current length of written firmware is not equal to total firmware size, repeat
  if (currentLength != totalLength) return;
  Update.end(true);
  Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
  // Restart ESP32 to see changes
  ESP.restart();
}
