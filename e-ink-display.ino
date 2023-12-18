#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>
#include <Esp.h>
#include <iostream>
#include <bitset>
#include <WiFi.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <EasyNeoPixels.h>

const char *serverName = "https://us-central1-co2-sensor-ab3c5.cloudfunctions.net/getDisplayData";
const char *pairingCodeName = "https://us-central1-co2-sensor-ab3c5.cloudfunctions.net/getDisplayPairingCode";
const char *findDonglePairName = "https://us-central1-co2-sensor-ab3c5.cloudfunctions.net/findDonglePairToDisplay";



void initBT();
void settings();
void dataScreen();




BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
BLECharacteristic *temperatureCharacteristic;
BLECharacteristic *humidityCharacteristic;
BLECharacteristic *co2Characteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;


#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"  // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define enviornmentService BLEUUID((uint16_t)0x181A)

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 30          /* Time ESP32 will go to sleep (in seconds) */
#define VERSION 1



//int dataTime = 721;
int dataTime = 2400;
//int dataTime = 20;

bool setupMode = true;
bool BTon = false;


float temp_1 = 0;
float hum_1 = 0;
float ppm_1 = 0;

float temp_2 = 0;
float hum_2 = 0;
float ppm_2 = 0;

float temp_3 = 0;
float hum_3 = 0;
float ppm_3 = 0;

float temp_4 = 0;
float hum_4 = 0;
float ppm_4 = 0;

bool up_to_date_1 = true;
bool up_to_date_2 = true;
bool up_to_date_3 = true;
bool up_to_date_4 = true;

String name_1 = "";
String name_2 = "";
String name_3 = "";
String name_4 = "";

int code = 0;
bool codeRetrived = false;

const int leftButton = 1;
const int rightButton = 0;

//void initWiFi();
Preferences preferences;
DynamicJsonDocument doc(1024);

char *ssid = "LMT-4E8A";
char *password = "";

int interactionTimer = 0;
int setupscreen = 1;
bool interacation = false;


class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
    BTon = true;
  };

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    BTon = false;
    // delay(500);
    // esp_deep_sleep_start();
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    preferences.begin("device", false);

    if (rxValue.length() > 0) {



      deserializeJson(doc, rxValue);
      JsonObject obj = doc.as<JsonObject>();
      String ssdWifi = obj["ssid"];
      String passwordWifi = obj["password"];
      String deviceName = obj["name"];

      String id1 = obj["id1"];
      String id2 = obj["id2"];
      String id3 = obj["id3"];
      String id4 = obj["id4"];

      String name1 = obj["name1"];
      String name2 = obj["name2"];
      String name3 = obj["name3"];
      String name4 = obj["name4"];

      String version = obj["version"];

      if (id1 != "") {
        preferences.putString("id1", id1);
      } else {
        preferences.putString("id1", "none");
      }

      if (id2 != "") {
        preferences.putString("id2", id2);
      } else {
        preferences.putString("id2", "none");
      }

      if (id3 != "") {
        preferences.putString("id3", id3);
      } else {
        preferences.putString("id3", "none");
      }

      if (id4 != "") {
        preferences.putString("id4", id4);
      } else {
        preferences.putString("id4", "none");
      }



      if (name1 != "") {
        preferences.putString("name1", name1);
      } else {
        preferences.putString("name1", "");
      }

      if (name2 != "") {
        preferences.putString("name2", name2);
      } else {
        preferences.putString("name2", "");
      }

      if (name3 != "") {
        preferences.putString("name3", name3);
      } else {
        preferences.putString("name3", "");
      }

      if (id4 != "") {
        preferences.putString("name4", name4);
      } else {
        preferences.putString("name4", "");
      }




      preferences.putFloat("ppm_1", 0);
      preferences.putFloat("ppm_2", 0);
      preferences.putFloat("ppm_3", 0);
      preferences.putFloat("ppm_4", 0);

      preferences.putFloat("temp_1", 0);
      preferences.putFloat("temp_2", 0);
      preferences.putFloat("temp_3", 0);
      preferences.putFloat("temp_4", 0);

      preferences.putFloat("hum_1", 0);
      preferences.putFloat("hum_2", 0);
      preferences.putFloat("hum_3", 0);
      preferences.putFloat("hum_4", 0);


      Serial.println("*********");
      Serial.println(ssdWifi);
      Serial.println(passwordWifi);
      Serial.println(id1);
      Serial.println(name1);
      Serial.println(id2);
      Serial.println(name2);
      Serial.println(id3);
      Serial.println(name3);
      Serial.println(id4);
      Serial.println(name4);
      Serial.println(version);
      Serial.println("*********");


      /*
      char charBufferName[100];
      char charBufferPassword[100];
      ssdWifi.toCharArray(charBufferName, 100);
      passwordWifi.toCharArray(charBufferPassword, 100);

      ssid = charBufferName;
      password = charBufferPassword;
      */

      if (ssdWifi != "") {
        preferences.putString("ssid", ssdWifi);
        preferences.putString("password", passwordWifi);
      }

      setupMode = false;


      Serial.println("*********");
      Serial.print("Received Value: ");
      for (int i = 0; i < rxValue.length(); i++)
        Serial.print(rxValue[i]);

      Serial.println();
      Serial.println("*********");


      // preferences.putInt("boot", 36);
      writeEasyNeoPixel(0, 0, 0, 0);
      preferences.putBool("skipWiFi", false);
      Serial.println("TURNING OFFFF");
      preferences.putInt("boot", dataTime);

      esp_deep_sleep_start();
      // preferences.end();
      // esp_deep_sleep_start();
    }
  }
};





//IO settings
int BUSY_Pin = 4;
int RES_Pin = 5;
int DC_Pin = 6;
int CS_Pin = 7;
int SCK_Pin = 8;
int SDI_Pin = 9;




#define EPD_W21_MOSI_0 digitalWrite(SDI_Pin, LOW)
#define EPD_W21_MOSI_1 digitalWrite(SDI_Pin, HIGH)

#define EPD_W21_CLK_0 digitalWrite(SCK_Pin, LOW)
#define EPD_W21_CLK_1 digitalWrite(SCK_Pin, HIGH)

#define EPD_W21_CS_0 digitalWrite(CS_Pin, LOW)
#define EPD_W21_CS_1 digitalWrite(CS_Pin, HIGH)

#define EPD_W21_DC_0 digitalWrite(DC_Pin, LOW)
#define EPD_W21_DC_1 digitalWrite(DC_Pin, HIGH)
#define EPD_W21_RST_0 digitalWrite(RES_Pin, LOW)
#define EPD_W21_RST_1 digitalWrite(RES_Pin, HIGH)
#define isEPD_W21_BUSY digitalRead(BUSY_Pin)
////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display1(void);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clean(void);
unsigned char HRES, VRES_byte1, VRES_byte2;



byte matrixDisplay[15000];

byte matrix[100][150];
boolean matrixBit[300][400];

boolean bitArray[120000];
boolean bitArrayNumber[5184];

int buzzer = 3;

int button_switch_left = 1;
int button_switch_right = 0;

#define switched_left true
#define switched_right true
#define triggered_left true
#define triggered_right true
#define interrupt_trigger_type RISING
#define debounce 50




void buzz() {
  int b = 1;

  for (int i = 0; i < 100; i++) {
    digitalWrite(buzzer, HIGH);
    delay(1);
    digitalWrite(buzzer, LOW);
    delay(1);
  }
}

volatile bool interrupt_process_status_left = {
  !triggered_left
};

volatile bool interrupt_process_status_right = {
  !triggered_right
};

void button_interrupt_handler_left() {

  if (interrupt_process_status_left == !triggered_left) {
    if (digitalRead(button_switch_left) == LOW) {
      interrupt_process_status_left = triggered_left;
      interactionTimer = millis();
    }
  }
}

void button_interrupt_handler_right() {

  if (interrupt_process_status_right == !triggered_right) {
    if (digitalRead(button_switch_right) == LOW) {
      interrupt_process_status_right = triggered_right;
      interactionTimer = millis();
    }
  }
}

bool read_button_left() {
  int button_reading;
  static bool switching_pending = false;
  static long int elapse_timer;
  if (interrupt_process_status_left == triggered_left) {
    button_reading = digitalRead(button_switch_left);
    if (button_reading == HIGH) {
      switching_pending = true;
      elapse_timer = millis();
      delay(100);
    }
    if (switching_pending && button_reading == LOW) {
      if (millis() - elapse_timer >= debounce) {
        switching_pending = false;
        interrupt_process_status_left = !triggered_left;
        return switched_left;
      }
    }
  }
  return !switched_left;
}

bool read_button_right() {
  int button_reading;
  static bool switching_pending = false;
  static long int elapse_timer;
  if (interrupt_process_status_right == triggered_right) {
    button_reading = digitalRead(button_switch_right);
    if (button_reading == HIGH) {
      switching_pending = true;
      elapse_timer = millis();
      delay(100);
    }
    if (switching_pending && button_reading == LOW) {
      if (millis() - elapse_timer >= debounce) {
        switching_pending = false;
        interrupt_process_status_right = !triggered_right;
        return switched_right;
      }
    }
  }
  return !switched_right;
}





void dataScreen() {


  Serial.println("DATA SCREEN");

  preferences.begin("device", false);

  ppm_1 = preferences.getFloat("ppm_1", 0);
  ppm_2 = preferences.getFloat("ppm_2", 0);
  ppm_3 = preferences.getFloat("ppm_3", 0);
  ppm_4 = preferences.getFloat("ppm_4", 0);

  hum_1 = preferences.getFloat("hum_1", 0);
  hum_2 = preferences.getFloat("hum_2", 0);
  hum_3 = preferences.getFloat("hum_3", 0);
  hum_4 = preferences.getFloat("hum_4", 0);

  temp_1 = preferences.getFloat("temp_1", 0);
  temp_2 = preferences.getFloat("temp_2", 0);
  temp_3 = preferences.getFloat("temp_3", 0);
  temp_4 = preferences.getFloat("temp_4", 0);

  up_to_date_1 = preferences.getBool("up_to_date_1", true);
  up_to_date_2 = preferences.getBool("up_to_date_2", true);
  up_to_date_3 = preferences.getBool("up_to_date_3", true);
  up_to_date_4 = preferences.getBool("up_to_date_4", true);

  name_1 = preferences.getString("name1", "");
  name_2 = preferences.getString("name2", "");
  name_3 = preferences.getString("name3", "");
  name_4 = preferences.getString("name4", "");


  clearArray();


  String id1 = preferences.getString("id1", "none");
  String id2 = preferences.getString("id2", "none");
  String id3 = preferences.getString("id3", "none");
  String id4 = preferences.getString("id4", "none");


  if (id4 != "none") {

    Display_four();

  } else if (id3 != "none") {

    Display_three();

  } else if (id2 != "none") {

    Display_two();

  } else if (id1 != "none") {

    Display_one();

  } else {

    addElement(44, 105, 135);
  }


  refreshScreen();
  writeEasyNeoPixel(0, 0, 0, 0);
}







void setup() {

  esp_sleep_enable_timer_wakeup(0.25 * uS_TO_S_FACTOR);
  //  writeEasyNeoPixel(0, 0, 255, 0);


  pinMode(button_switch_left, INPUT);
  /* attachInterrupt(digitalPinToInterrupt(button_switch_left),
                  button_interrupt_handler_left,
                  interrupt_trigger_type);
*/


  pinMode(button_switch_right, INPUT);
  /* attachInterrupt(digitalPinToInterrupt(button_switch_right),
                  button_interrupt_handler_right,
                  interrupt_trigger_type);
*/



  pinMode(buzzer, OUTPUT);

  Serial.begin(115200);


  setupEasyNeoPixels(19, 1);

  // writeEasyNeoPixel(0, 255, 255, 0);
  // delay(1000);
  // writeEasyNeoPixel(0, 0, 0, 0);


  pinMode(BUSY_Pin, INPUT);
  pinMode(RES_Pin, OUTPUT);
  pinMode(DC_Pin, OUTPUT);
  pinMode(CS_Pin, OUTPUT);
  pinMode(SCK_Pin, OUTPUT);
  pinMode(SDI_Pin, OUTPUT);


  Serial.println("WAKEUP");


  // Analog read
  pinMode(2, INPUT);
  pinMode(20, INPUT);


  preferences.begin("device", false);

  bool turned_off = preferences.getBool("off", false);

  pinMode(18, OUTPUT);

  bool isCharging = digitalRead(20);

  if (turned_off == 1 && (digitalRead(button_switch_right) == LOW || isCharging == 1)) {
    writeEasyNeoPixel(0, 255, 0, 0);
    delay(50);
    digitalWrite(18, LOW);
    delay(500);
    buzz();
    clearArray();

    addElement(119, 135, 138);
    refreshScreen();
    refreshScreen();
    preferences.putBool("off", false);
    preferences.putInt("boot", dataTime);
    preferences.putBool("skipWiFi", true);
    writeEasyNeoPixel(0, 0, 0, 0);
  }


  //digitalWrite(18, LOW);

  Serial.print("TURNED OFF: ");
  Serial.println(turned_off);

  if (turned_off == 0) {
    digitalWrite(18, LOW);

    bool isCharging = digitalRead(20);
    bool isChargingState = preferences.getBool("charging", false);

    if (isCharging != isChargingState) {
      preferences.putBool("charging", isCharging);
      writeEasyNeoPixel(0, 0, 0, 0);
      preferences.putBool("skipWiFi", true);
      preferences.putInt("boot", dataTime);
      esp_deep_sleep_start();
    }



  } else {
    writeEasyNeoPixel(0, 0, 0, 0);
    delay(100);
    digitalWrite(18, HIGH);
  }





  ppm_1 = preferences.getFloat("ppm_1", 0);
  ppm_2 = preferences.getFloat("ppm_2", 0);
  ppm_3 = preferences.getFloat("ppm_3", 0);
  ppm_4 = preferences.getFloat("ppm_4", 0);

  hum_1 = preferences.getFloat("hum_1", 0);
  hum_2 = preferences.getFloat("hum_2", 0);
  hum_3 = preferences.getFloat("hum_3", 0);
  hum_4 = preferences.getFloat("hum_4", 0);

  temp_1 = preferences.getFloat("temp_1", 0);
  temp_2 = preferences.getFloat("temp_2", 0);
  temp_3 = preferences.getFloat("temp_3", 0);
  temp_4 = preferences.getFloat("temp_4", 0);

  name_1 = preferences.getString("name1", "");
  name_2 = preferences.getString("name2", "");
  name_3 = preferences.getString("name3", "");
  name_4 = preferences.getString("name4", "");
}



void loop() {


  bool turned_off = preferences.getBool("off", false);

  if (turned_off == 0) {

    if (digitalRead(button_switch_right) == LOW || digitalRead(button_switch_left) == LOW) {
      buzz();
      settings(false);
      settings(false);
    }





    String ssdWifi = preferences.getString("ssid", "");
    String passwordWifi = preferences.getString("password", "8DVDSX5LUD");


    int boot = preferences.getInt("boot", 1);
    Serial.print("BOOT : ");
    Serial.println(boot);
    boot += 1;
    preferences.putInt("boot", boot);

    if (boot >= dataTime && interactionTimer == 0) {
      //  if (boot > 10 && interactionTimer == 0) {

      Serial.println("WIFI");
      Serial.println(ssdWifi);

      if (ssdWifi != "") {

        bool skipWiFi = preferences.getBool("skipWiFi", false);

        if (skipWiFi) {
          preferences.putBool("skipWiFi", false);
          dataScreen();
        } else {

          clearArray();
          addElement(122, 128, 138);
          refreshScreen();
          refreshScreen();
          initWiFi();
        }


        dataScreen();




      } else {

        dataScreen();
        dataScreen();
      }

      preferences.putInt("boot", 1);
      preferences.end();
      delay(500);
      esp_deep_sleep_start();
    }




    if (interactionTimer == 0) {
      Serial.println("SLEEP");
      writeEasyNeoPixel(0, 0, 0, 0);
      preferences.end();
      delay(500);
      esp_deep_sleep_start();
    }



    while (millis() - interactionTimer < 10000) {



      writeEasyNeoPixel(0, 0, 255, 0);



      if (digitalRead(button_switch_left) == LOW) {

        delay(150);

        if (digitalRead(button_switch_right) == LOW) {
          writeEasyNeoPixel(0, 255, 100, 0);
          buzz();
          writeEasyNeoPixel(0, 0, 0, 0);
          buzz();
          writeEasyNeoPixel(0, 255, 100, 0);
          buzz();
          writeEasyNeoPixel(0, 0, 0, 0);

          if (setupscreen == 1) {
            bool v = preferences.getBool("volume", false);
            if (v) {
              preferences.putBool("volume", false);
            } else {
              preferences.putBool("volume", true);
            }
          }


          if (setupscreen == 2) {
            bool m = preferences.getBool("metric", true);
            if (m) {
              preferences.putBool("metric", false);
            } else {
              preferences.putBool("metric", true);
            }
          }


          if (setupscreen == 3) {
            bool theme = preferences.getBool("light", true);
            if (theme) {
              preferences.putBool("light", false);
            } else {
              preferences.putBool("light", true);
            }
          }



          if (setupscreen == 4) {

            setupMode = true;
            writeEasyNeoPixel(0, 0, 0, 255);
            delay(500);
            Serial.println("FIRST");
            interactionTimer = 0;
            initBT();
            // initWiFi();
          }


          if (setupscreen == 5) {

            setupMode = true;
            writeEasyNeoPixel(0, 0, 0, 255);
            delay(500);
            Serial.println("FIRST");
            interactionTimer = 0;
          }

          settings(true);
        } else {

          buzz();

          if (setupscreen == 1) {
            setupscreen = 5;
          } else {
            setupscreen--;
          }

          settings(false);
        }
      }




      if (digitalRead(button_switch_right) == LOW) {


        delay(150);

        if (digitalRead(button_switch_left) == LOW) {
          writeEasyNeoPixel(0, 255, 100, 0);
          buzz();
          writeEasyNeoPixel(0, 0, 0, 0);
          buzz();
          writeEasyNeoPixel(0, 255, 100, 0);
          buzz();
          writeEasyNeoPixel(0, 0, 0, 0);

          if (setupscreen == 1) {
            bool v = preferences.getBool("volume", false);
            if (v) {
              preferences.putBool("volume", false);
            } else {
              preferences.putBool("volume", true);
            }
          }


          if (setupscreen == 2) {
            bool m = preferences.getBool("metric", true);
            if (m) {
              preferences.putBool("metric", false);
            } else {
              preferences.putBool("metric", true);
            }
          }


          if (setupscreen == 3) {
            bool theme = preferences.getBool("light", true);
            if (theme) {
              preferences.putBool("light", false);
            } else {
              preferences.putBool("light", true);
            }
          }



          if (setupscreen == 4) {

            setupMode = true;
            writeEasyNeoPixel(0, 0, 0, 255);
            delay(500);
            Serial.println("SECOND");
            interactionTimer = 0;
            initBT();
          }


          if (setupscreen == 5) {

            setupMode = true;
            writeEasyNeoPixel(0, 0, 0, 255);
            delay(500);
            Serial.println("FIRST");
            interactionTimer = 0;
          }

          settings(true);

        } else {


          buzz();

          if (setupscreen == 5) {
            setupscreen = 1;
          } else {
            setupscreen++;
          }

          settings(false);
        }
      }





      // Serial.println("STAY");
    }



    dataScreen();
    dataScreen();
  }

  preferences.end();
  delay(500);
  esp_deep_sleep_start();
}








void settings(bool change) {

  preferences.putInt("boot", 30);


  Serial.print("SETUP SCREEN: ");
  Serial.println(setupscreen);

  interactionTimer = millis();
  writeEasyNeoPixel(0, 255, 0, 0);

  //digitalWrite(18, HIGH);

  clearArray();

  addElement(55, 15, 134);
  addElement(56, 358, 134);

  addElement(57, 52, 267);


  if (setupscreen == 1) {

    bool v = preferences.getBool("volume", false);
    if (v) {
      addElement(49, 150, 100);
    } else {
      addElement(50, 150, 100);
    }
  }


  if (setupscreen == 2) {
    bool m = preferences.getBool("metric", true);
    if (m) {
      addElement(52, 180, 110);
    } else {
      addElement(51, 185, 110);
    }
  }


  if (setupscreen == 3) {
    bool theme = preferences.getBool("light", true);
    if (theme) {
      addElement(54, 144, 131);
    } else {
      addElement(53, 146, 131);
    }
  }


  if (setupscreen == 4) {
    addElement(43, 140, 90);
  }

  if (setupscreen == 5 && change == 0) {
    Serial.println("OFF");
    // addElement(164, 130, 116);
    addElement(117, 164, 130);
  }



  if (setupscreen == 5 && change) {
    Serial.println("OFF");
    clearArray();
    addElement(118, 133, 138);
    refreshScreen();
    writeEasyNeoPixel(0, 0, 0, 0);
    preferences.putBool("off", true);
    delay(2000);
    clearArray();
    addElement(44, 105, 135);
    addElement(120, 186, 185);
    refreshScreen();
    delay(100);
    writeEasyNeoPixel(0, 0, 0, 0);
    delay(100);
    digitalWrite(18, HIGH);
    delay(100);
    preferences.putInt("boot", 1);
    preferences.end();
    delay(500);
    esp_deep_sleep_start();
  }



  refreshScreen();



  if (change) {

    if (setupscreen == 2) {
      bool m = preferences.getBool("metric", true);

      if (m == true) {

        Serial.println("METRIC");

        temp_1 -= 32;
        temp_1 *= 0.55;
        preferences.putFloat("temp_1", temp_1);

        temp_2 -= 32;
        temp_2 *= 0.55;
        preferences.putFloat("temp_2", temp_2);

        temp_3 -= 32;
        temp_3 *= 0.55;
        preferences.putFloat("temp_3", temp_3);

        temp_4 -= 32;
        temp_4 *= 0.55;
        preferences.putFloat("temp_4", temp_4);

      } else {

        Serial.println("IMPERIAL");
        temp_1 *= 1.8;
        temp_1 += 32;
        preferences.putFloat("temp_1", temp_1);

        temp_2 *= 1.8;
        temp_2 += 32;
        preferences.putFloat("temp_2", temp_2);

        temp_3 *= 1.8;
        temp_3 += 32;
        preferences.putFloat("temp_3", temp_3);

        temp_4 *= 1.8;
        temp_4 += 32;
        preferences.putFloat("temp_4", temp_4);
      }
    }

    interactionTimer = millis() - 16000;
  } else {
    interactionTimer = millis();
  }




  writeEasyNeoPixel(0, 0, 255, 0);
}















void statusBar() {


  int value = 0;  //analogRead(2);


  for (int i = 0; i < 50; i++) {
    value += analogRead(2);
    delay(10);
  }

  value = value / 50;

  Serial.print("ANALOG ");
  Serial.println(value);

  bool isCharging = digitalRead(20);


  if (isCharging == 1) {
    addElement(29, 360, 5);
    preferences.putBool("charging", true);

  } else {

    if (value >= 2350) {
      //batteryFull
      addElement(30, 360, 5);
    }

    if (value < 2350 && value >= 2330) {
      //battery5Bar
      addElement(31, 360, 5);
    }

    if (value < 2330 && value >= 2300) {
      //battery4Bar
      addElement(32, 360, 5);
    }

    if (value < 2300 && value >= 2270) {
      //battery3Bar
      addElement(33, 360, 5);
    }

    if (value < 2270 && value >= 2220) {
      //battery2Bar
      addElement(34, 360, 5);
    }

    if (value < 2220 && value >= 2190) {
      //battery2Bar
      addElement(34, 360, 5);
    }

    if (value < 2190 && value >= 2150) {
      //battery1Bar
      addElement(35, 360, 5);
    }

    if (value < 2150) {
      //battery0Bar
      // addElement(36, 360, 5);

      clearArray();
      addElement(118, 133, 138);
      refreshScreen();
      writeEasyNeoPixel(0, 0, 0, 0);
      preferences.putBool("off", true);
      delay(2000);
      clearArray();
      addElement(44, 105, 135);
      addElement(120, 186, 185);
      refreshScreen();
      delay(100);
      writeEasyNeoPixel(0, 0, 0, 0);
      delay(100);
      digitalWrite(18, HIGH);
      delay(100);
      preferences.putInt("boot", 1);
      preferences.end();
      delay(500);
      esp_deep_sleep_start();
    }
  }



  String ssidWifi = preferences.getString("ssid", "");
  int wifiTry = preferences.getInt("wifiTry", 0);

  if (wifiTry < 6 && ssidWifi != "") {

    int n = WiFi.scanNetworks();
    bool found = false;

    if (n == 0) {
      //wifiNot
      addElement(40, 10, 5);

    } else {


      for (int i = 0; i < n; ++i) {
        if (ssidWifi == WiFi.SSID(i)) {
          Serial.println(WiFi.RSSI(i));

          int rssi = WiFi.RSSI(i);


          if (rssi > -64) {
            //wifi
            addElement(39, 10, 5);

          } else if (rssi > -80) {
            //wifi_60
            addElement(114, 10, 5);

          } else {
            //wifi_20
            addElement(115, 10, 5);
          }


          found = true;
        }
      }


      if (!found) {
        //wifiNot
        addElement(40, 10, 5);
      }
    }


  } else {
    //wifiNot
    addElement(40, 10, 5);
  }


  bool volume = preferences.getBool("volume", false);

  if (volume) {

    addElement(58, 40, 2);
  } else {

    addElement(59, 40, 2);
  }
}






void refreshScreen() {

  EPD_init();
  PIC_display_Clean();
  draw();
  EPD_refresh();
}


void clearArray() {
  for (long i = 0; i < 120000; i++) {
    bitArray[i] = 1;
  }
}


void draw() {

  int byteSplit = 0;
  char input_binary_string[8];
  int widthS = 0;


  EPD_W21_WriteCMD(0x13);

  bool theme = preferences.getBool("light", true);

  /* if (interacation) {
    theme = true;
  }*/

  for (int i = 0; i < 120000; i++) {


    if (bitArray[i] == theme) {
      input_binary_string[byteSplit] = '1';
    } else {
      input_binary_string[byteSplit] = '0';
    }

    byteSplit++;

    widthS++;
    

    if (widthS == 400) {
      widthS = 0;
   
    }



    if (byteSplit == 8) {
      byteSplit = 0;
      long value = strtol(input_binary_string, NULL, 2);

      EPD_W21_WriteDATA(value);

    }

  }
}








void addElement(int item, int posX, int posY) {

  String input = "";
  int w = 0;
  int h = 0;





  // 0 -------------- w = 39; h = 79;
  String zeroL = "0 8 23 13 29 9 31 7 33 5 35 3 37 2 37 2 37 1 134 5 33 7 31 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 31 7 133 1 37 2 37 2 37 3 35 4 35 5 33 8 29 12 25 592 ";

  // 1 -------------- w = 26; h = 79;
  String oneL = "23 3 23 3 23 3 23 3 23 3 23 3 23 3 23 3 23 3 23 3 23 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 11 15 393 ";

  // 2 -------------- w = 38; h = 79;
  String twoL = "0 7 22 14 27 9 30 7 32 5 34 4 35 2 36 2 36 2 37 1 37 1 37 1 16 5 16 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 1 15 7 15 23 15 22 16 22 15 23 15 22 16 22 15 22 16 21 17 21 16 21 16 21 17 20 17 21 17 20 17 20 17 20 17 21 17 20 17 20 17 20 18 20 17 20 17 20 18 19 18 20 17 20 18 19 18 19 18 20 18 19 18 19 18 19 37 1 37 1 37 1 37 1 37 1 37 1 37 1 37 1 37 1 37 1 37 571 ";

  // 3 -------------- w = 39; h = 79;
  String threeL = "0 8 22 14 27 11 30 8 32 6 34 4 35 4 36 3 36 2 37 2 37 2 37 2 17 4 17 1 15 7 16 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 24 15 24 15 24 14 25 14 24 15 14 25 14 25 14 24 15 24 15 23 16 22 17 23 16 24 15 24 15 25 14 25 24 15 24 15 25 15 24 15 24 15 24 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 7 16 1 16 6 16 1 37 2 37 2 37 3 36 3 36 3 35 5 34 5 33 7 31 10 28 13 24 593 ";

  // 4 -------------- w = 39; h = 79;
  String fourL = "0 21 16 30 15 30 16 30 15 30 16 30 15 30 15 31 15 30 15 30 16 30 15 30 16 30 15 30 16 30 15 30 15 31 15 30 15 30 16 30 15 30 16 30 15 30 15 31 15 30 15 31 15 30 15 30 16 30 15 30 15 4 15 12 15 4 15 11 15 5 15 11 15 5 15 10 15 6 15 10 15 6 15 9 15 7 15 9 14 8 15 8 15 8 15 7 15 9 15 7 15 9 15 7 14 10 15 7 45 1 45 1 45 1 45 1 45 1 45 1 45 1 45 1 45 1 45 1 45 1 45 25 15 31 15 31 15 31 15 31 15 31 15 31 15 31 15 31 15 31 15 31 15 697 ";

  // 5 -------------- w = 39; h = 79;
  String fiveL = "37 2 37 2 37 2 37 2 37 2 37 2 37 2 37 2 37 2 37 2 37 2 15 24 15 24 15 24 15 24 15 24 15 24 15 24 15 24 15 24 15 24 15 24 26 13 32 7 34 5 35 4 36 3 37 2 37 2 37 2 38 1 38 1 38 1 38 23 16 24 15 24 15 24 15 24 15 24 15 24 15 24 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 16 6 16 1 38 1 38 1 38 1 38 1 37 3 36 3 35 5 34 6 32 8 30 11 25 593 ";

  // 6 -------------- w = 39; h = 79;
  String sixL = "0 7 22 15 27 10 31 7 33 5 35 4 35 3 37 2 37 2 37 2 37 2 37 2 16 5 16 2 15 7 15 2 14 8 15 2 14 9 14 2 14 9 14 2 14 9 14 2 14 9 14 2 14 9 14 2 14 9 14 2 14 25 14 25 14 25 14 25 14 25 14 25 30 9 33 6 34 5 35 4 36 3 37 2 37 2 38 1 38 1 38 1 38 1 14 8 16 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 14 9 15 1 15 8 15 1 15 8 15 1 38 1 38 1 38 1 38 1 37 3 36 3 36 4 34 6 32 8 30 11 26 592 ";

  // 7 -------------- w = 37; h = 79;
  String sevenL = "406 1 36 22 15 21 15 22 15 22 15 21 15 22 15 22 15 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 22 15 21 16 21 15 21 16 21 16 21 15 21 16 21 16 21 15 21 16 21 16 573 ";

  // 8 -------------- w = 39; h = 79;
  String eightL = "0 8 23 13 29 9 31 7 33 5 35 3 37 2 37 2 37 1 133 7 31 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 15 1 15 7 15 2 37 2 37 3 35 4 34 7 31 7 33 5 35 3 37 2 37 2 37 1 15 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 30 9 132 1 37 2 37 2 37 3 35 4 35 5 33 8 29 12 25 592 ";

  // 9 -------------- w = 39; h = 79;
  String nineL = "0 8 22 14 28 9 32 6 34 5 35 3 36 3 37 1 38 1 38 1 38 1 38 1 16 6 16 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 16 7 15 1 38 1 38 1 38 1 38 2 37 2 37 3 36 4 35 6 33 8 31 24 15 24 15 24 15 24 15 24 15 2 14 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 15 8 15 1 16 7 15 1 38 1 38 2 37 2 37 2 37 2 36 4 35 5 33 7 31 9 29 12 25 592 ";



  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // 10 ------------- w = 19; h = 47;
  String zeroS = "0 3 13 5 15 3 17 1 45 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 45 1 17 2 17 3 15 211 ";

  // 11 ------------- w = 13; h = 47;
  String oneS = "11 2 11 2 11 2 11 2 11 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 7 6 119 ";

  // 12 ------------- w = 18; h = 47;
  String twoS = "0 3 12 5 14 3 16 1 17 1 17 1 7 4 6 1 6 5 6 1 6 5 6 1 6 5 6 1 6 5 6 1 6 5 6 1 6 5 6 1 6 5 6 12 6 11 7 11 6 11 7 11 7 10 7 11 7 10 7 11 7 10 7 11 7 10 7 11 7 10 7 11 6 11 7 10 7 11 7 10 7 11 7 10 90 162 ";

  // 13 ------------- w = 19; h = 47;
  String threeS = "0 3 12 5 15 4 16 2 18 1 18 1 7 4 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 12 7 12 7 12 7 6 13 6 12 7 12 7 12 7 13 6 13 12 7 12 7 12 7 12 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 6 5 7 1 7 4 7 1 18 1 18 2 16 3 16 4 14 174 ";

  // 14 ------------- w = 22; h = 47;
  String fourS = "0 11 6 15 7 15 6 15 7 15 6 16 6 15 7 15 6 15 7 15 6 16 6 15 6 16 6 15 7 15 6 15 7 15 6 16 6 15 6 4 6 6 6 4 6 5 7 4 6 5 6 5 6 4 7 5 6 4 6 6 6 4 6 6 6 3 6 7 6 3 110 13 6 16 6 16 6 16 6 16 6 16 6 16 6 201 ";

  // 15 ------------- w = 18; h = 48;
  String fiveS = "97 11 7 11 7 11 7 11 7 11 7 11 7 11 7 11 7 11 15 3 17 1 17 1 36 11 7 12 6 12 6 12 6 12 6 12 6 12 13 5 13 5 13 5 13 5 13 5 13 5 13 5 42 1 17 1 16 3 14 182 ";

  // 16 ------------- w = 19; h = 47;
  String sixS = "0 3 13 5 15 3 17 2 17 1 26 5 14 5 14 5 14 5 14 5 14 5 14 5 14 5 14 12 7 12 7 12 16 3 18 1 18 1 45 5 14 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 25 1 18 1 17 2 17 4 14 173 ";

  // 17 ------------- w = 18; h = 47;
  String sevenS = "90 11 6 12 6 11 7 11 7 11 6 11 7 11 7 11 6 12 6 11 7 11 6 12 6 11 7 11 7 11 6 12 6 11 7 11 6 12 6 11 7 11 7 11 6 11 7 11 7 11 6 12 6 11 7 11 6 12 6 11 7 11 7 11 6 11 7 172 ";

  // 18 ------------- w = 19; h = 47;
  String eightS = "0 3 13 5 15 3 17 1 45 5 13 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 13 5 25 2 17 2 17 2 17 1 25 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 13 6 44 1 17 2 17 3 15 173 ";

  // 19 ------------- w = 19; h = 47;
  String nineS = "0 3 13 4 16 3 17 1 18 1 18 1 7 5 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 18 1 18 2 17 2 17 4 15 13 6 13 6 13 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 18 1 18 2 17 2 16 4 14 174 ";

  // 20 ------------- w = 7; h = 47;
  String dot = "56 273 ";



  ///////////////////////////////////////////////////////////////////////////////////////////

  // 21 ------------- w = 19; h = 47;
  String C = "0 2 13 5 16 2 17 2 18 1 18 1 6 5 7 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 13 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 6 6 6 1 18 1 18 1 18 2 16 4 14 174 ";

  // 22 ------------- w = 19; h = 47;
  String F = "17 2 17 2 17 2 17 2 17 2 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 15 4 15 4 15 4 15 4 15 4 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 12 7 183 ";

  // 23 ------------- w = 20; h = 40;
  String temperature = "0 7 6 13 8 11 10 9 12 8 4 4 4 8 4 4 4 8 4 4 4 8 4 2 6 8 4 2 6 8 4 2 6 8 4 4 4 8 4 4 4 8 4 4 4 8 4 2 6 8 4 2 6 8 4 2 6 8 4 4 4 8 4 4 4 8 12 8 12 8 12 8 12 7 14 5 16 3 18 1 199 2 18 3 16 5 14 7 12 10 9 5 ";

  // 24 ------------- w = 28; h = 40;
  String humidity = "0 13 2 25 4 23 6 21 8 20 9 18 10 17 5 2 5 15 5 4 5 13 5 6 5 11 5 8 5 9 6 8 6 8 5 10 5 7 5 12 5 5 5 14 5 4 4 16 4 3 4 18 4 2 4 18 4 1 4 20 8 20 8 20 7 22 6 22 6 22 6 22 6 22 6 22 6 22 7 20 8 20 8 20 4 1 4 18 4 2 5 17 4 3 4 16 4 4 5 14 5 5 5 12 5 7 6 8 6 9 18 11 16 13 14 16 10 9 ";

  // 25 ------------- w = 36; h = 47;
  String percentage = "0 2 10 12 5 8 12 11 5 7 14 9 6 7 14 9 5 8 14 8 6 8 5 4 5 8 5 9 5 4 5 7 6 9 5 4 5 7 5 10 5 4 5 6 6 10 5 4 5 6 5 11 5 4 5 5 6 11 5 4 5 5 5 12 5 4 5 4 6 12 5 4 5 4 5 13 5 4 5 3 6 13 5 4 5 3 6 13 6 2 6 3 5 14 14 2 6 3 8 3 14 2 5 2 12 2 12 2 6 1 13 3 10 3 5 2 14 14 6 2 14 14 5 3 5 4 5 13 6 3 5 4 5 13 5 4 5 4 5 12 6 4 5 4 5 12 5 5 5 4 5 11 6 5 5 4 5 11 5 6 5 4 5 10 6 6 5 4 5 10 6 6 5 4 5 10 5 7 5 4 5 9 6 7 5 4 5 9 5 8 5 4 5 8 6 8 14 8 5 9 14 7 6 9 13 8 5 11 11 326 ";

  // 26 ------------- w = 15; h = 15;
  String degree = "0 5 5 8 9 5 4 3 4 3 3 7 3 2 2 9 2 1 3 9 5 11 4 11 4 11 5 9 3 1 2 9 2 2 3 7 3 3 4 3 4 5 9 8 5 5 ";

  // 27 ------------- w = 25; h = 25;
  String triangle = "19 6 19 6 19 6 19 7 17 8 17 9 15 10 15 11 13 12 13 13 11 15 9 16 9 17 7 18 7 19 5 20 5 213 ";

  // 28 ------------- w = 300; h = 5;
  String line = "1500 ";



  // 29 ------------- w = 36; h = 18;
  String batteryFullCharging = "0 1 30 5 32 4 2 28 2 4 2 1 2 7 1 15 1 1 2 4 2 1 3 12 1 5 1 5 2 4 2 1 4 2 1 5 1 14 8 1 5 12 1 9 8 1 6 15 1 2 1 2 8 1 7 3 1 16 8 1 8 8 1 10 8 1 9 14 1 3 8 1 10 9 1 7 8 1 11 3 1 12 8 1 12 5 1 3 1 2 1 2 2 4 2 1 13 14 2 4 2 28 2 4 32 5 30 5 ";

  // 30 ------------- w = 36; h = 18;
  String batteryFull = "0 1 30 5 32 4 2 28 2 4 2 1 26 1 2 4 2 1 26 1 2 4 2 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 8 1 26 1 2 4 2 1 26 1 2 4 2 28 2 4 32 5 30 5 ";

  // 31 ------------- w = 36; h = 18;
  String battery5bar = "0 1 31 4 33 3 2 29 2 3 2 1 20 8 2 3 2 1 20 8 2 3 2 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 7 1 20 8 2 3 2 1 20 8 2 3 2 29 2 3 33 4 31 4 ";

  // 32 ------------- w = 36; h = 18;
  String battery4bar = "0 1 31 4 33 3 2 29 2 3 2 1 16 12 2 3 2 1 16 12 2 3 2 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 7 1 16 12 2 3 2 1 16 12 2 3 2 29 2 3 33 4 31 4 ";

  // 33 ------------- w = 36; h = 18;
  String battery3bar = "0 1 31 4 33 3 2 29 2 3 2 1 12 16 2 3 2 1 12 16 2 3 2 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 7 1 12 16 2 3 2 1 12 16 2 3 2 29 2 3 33 4 31 4 ";

  // 34 ------------- w = 36; h = 18;
  String battery2bar = "0 1 31 4 33 3 2 29 2 3 2 1 8 20 2 3 2 1 8 20 2 3 2 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 7 1 8 20 2 3 2 1 8 20 2 3 2 29 2 3 33 4 31 4 ";

  // 35 ------------- w = 36; h = 18;
  String battery1bar = "0 1 31 4 33 3 2 29 2 3 2 1 4 24 2 3 2 1 4 24 2 3 2 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 7 1 4 24 2 3 2 1 4 24 2 3 2 29 2 3 33 4 31 4 ";

  // 36 ------------- w = 36; h = 18;
  String battery0bar = "0 1 31 4 33 3 2 29 2 3 2 29 2 3 2 29 2 3 2 29 7 29 7 29 7 29 7 29 7 29 7 29 7 29 7 29 2 3 2 29 2 3 2 29 2 3 33 4 31 4 ";



  // 37 ------------- w = 13; h = 19;
  String bluetooth = "0 6 3 10 4 9 5 2 3 3 6 1 4 2 2 1 4 1 4 1 2 2 3 2 6 1 3 4 8 6 6 8 4 8 6 6 8 4 6 1 3 2 4 1 2 2 7 2 2 1 7 3 6 7 5 8 4 9 3 4 ";

  // 38 ------------- w = 20; h = 20;
  String bluetoothNot = "2 8 2 8 3 7 3 7 4 6 4 7 4 5 5 7 4 4 6 7 4 3 2 1 4 7 4 2 6 9 4 1 5 11 4 1 3 13 4 1 1 15 4 15 6 13 3 1 4 11 3 2 5 9 3 3 6 8 2 4 7 13 4 1 3 12 3 3 3 11 2 5 3 18 2 ";

  // 39 ------------- w = 25; h = 18;
  String wifi = "0 8 9 13 15 8 19 5 8 6 7 3 6 11 6 1 5 15 9 5 6 6 4 1 1 5 11 5 1 7 13 10 7 3 7 8 5 7 5 9 2 11 2 16 3 20 7 17 9 17 7 19 5 21 3 11 ";

  // 40 ------------- w = 22; h = 18;
  String wifiNot = "0 1 3 19 4 1 10 8 16 6 18 3 7 7 6 1 9 8 8 3 4 1 2 6 3 1 1 4 10 4 1 6 12 9 14 8 3 3 4 1 3 9 1 5 4 1 1 13 8 13 10 13 10 13 4 2 4 13 2 4 4 19 3 2 ";

  // 41 ------------- w = 62; h = 32;
  String PPM = "13 5 14 4 8 7 7 4 15 3 15 3 8 7 7 4 16 2 16 2 8 6 8 4 16 2 16 2 8 6 8 4 16 2 17 1 9 5 8 4 6 4 6 2 7 3 7 1 9 5 8 4 6 4 6 2 7 3 7 1 9 4 9 4 6 4 6 2 7 3 7 1 10 3 9 4 6 4 6 2 7 3 7 1 10 3 9 4 6 4 6 2 7 3 7 1 10 2 10 4 6 4 6 2 7 3 7 1 10 2 10 4 6 4 6 2 7 3 7 1 11 1 10 4 16 2 17 1 22 4 16 2 16 2 6 1 15 4 16 2 16 2 6 1 15 4 16 2 16 2 6 1 8 1 6 4 15 3 15 3 6 1 8 1 6 4 12 6 12 6 6 2 7 1 6 4 6 12 7 11 6 2 6 2 6 4 6 12 7 11 6 2 6 2 6 4 6 12 7 11 6 3 5 2 6 4 6 12 7 11 6 10 6 4 6 12 7 11 6 10 6 4 6 12 7 11 6 10 6 4 6 12 7 11 6 10 6 4 6 12 7 11 6 10 6 376 ";

  // 42 ------------- w = 57; h = 41;
  String cloud = "0 24 9 46 13 42 17 38 21 35 7 9 7 33 6 12 7 31 6 15 6 29 6 17 6 27 6 19 5 27 5 21 5 25 5 23 4 25 4 24 5 23 5 25 4 23 4 26 4 21 6 26 4 18 9 27 4 16 9 28 4 15 9 29 4 14 7 32 4 14 6 33 8 9 5 11 5 4 4 12 9 6 5 11 7 2 6 11 10 5 4 12 7 1 8 11 10 4 4 12 3 1 3 1 3 2 3 2 2 11 7 2 5 12 3 5 3 2 3 1 4 12 6 1 4 13 3 5 3 2 3 1 1 1 2 13 5 1 4 13 3 5 3 2 3 3 2 14 9 13 3 1 3 1 3 2 3 2 2 15 9 13 7 1 8 1 2 17 8 13 7 2 6 2 4 15 8 14 5 4 4 3 4 15 8 49 9 47 5 1 5 46 5 1 6 44 5 3 7 41 6 4 8 37 7 6 50 8 48 11 45 14 41 7 ";

  // 43 ------------- w = 120; h = 120;
  String bluetoothConnecting = "0 1365 4 116 5 115 6 114 7 113 8 112 9 111 10 110 11 109 12 108 13 107 14 106 15 105 16 104 17 103 18 77 1 24 19 75 3 23 20 73 5 22 8 1 12 71 7 21 8 2 12 69 9 20 8 3 12 67 11 19 8 4 12 66 12 18 8 5 12 66 12 17 8 6 12 66 12 16 8 7 12 24 2 40 12 15 8 8 12 22 3 41 12 14 8 9 12 20 5 41 12 13 8 10 12 18 6 42 12 12 8 11 12 16 8 42 12 11 8 10 12 16 9 43 12 10 8 9 12 17 10 43 12 9 8 8 12 19 9 44 12 8 8 7 12 20 10 44 12 7 8 6 12 22 9 45 12 6 8 5 12 23 9 46 12 5 8 4 12 25 9 46 12 4 8 3 12 26 9 47 12 3 8 2 12 27 9 48 12 2 8 1 12 29 8 49 12 1 20 16 2 12 9 49 31 16 3 12 9 50 29 16 5 11 9 51 27 16 6 12 8 52 25 16 7 12 8 53 23 16 8 12 8 54 21 16 10 11 9 54 19 16 11 11 9 55 17 16 12 11 9 56 15 16 13 11 9 57 13 16 14 11 9 57 13 16 14 11 9 56 15 16 13 11 9 55 17 16 12 11 9 54 19 16 11 11 9 53 21 16 10 11 9 52 23 16 8 12 8 52 25 16 7 12 8 51 27 16 6 12 8 50 29 16 5 11 9 49 31 16 3 12 9 48 12 1 20 16 2 12 9 47 12 2 8 1 12 29 8 47 12 3 8 2 12 27 9 46 12 4 8 3 12 26 9 45 12 5 8 4 12 25 9 44 12 6 8 5 12 23 9 44 12 7 8 6 12 22 9 43 12 8 8 7 12 20 10 42 12 9 8 8 12 19 9 42 12 10 8 9 12 17 10 41 12 11 8 10 12 17 8 41 12 12 8 11 12 17 7 40 12 13 8 10 12 19 5 40 12 14 8 9 12 21 4 39 12 15 8 8 12 23 2 39 12 16 8 7 12 25 1 38 12 17 8 6 12 64 12 18 8 5 12 65 11 19 8 4 12 67 9 20 8 3 12 69 7 21 8 2 12 71 5 22 8 1 12 73 3 23 20 75 1 24 19 101 18 102 17 103 16 104 15 105 14 106 13 107 12 108 11 109 10 110 9 111 8 112 7 113 6 114 5 115 4 1391 ";

  // 44 ------------- w = 186; h = 39;
  String luxafor = "0 187 8 14 8 7 8 4 9 7 9 11 10 13 20 6 17 9 19 7 8 14 8 7 8 4 9 7 9 10 12 12 20 5 19 8 21 5 8 14 8 7 8 4 10 5 10 10 12 12 20 4 21 7 22 4 8 14 8 7 8 5 9 5 9 11 12 12 20 4 21 7 22 4 8 14 8 7 8 5 9 5 9 11 12 12 20 3 23 6 23 3 8 14 8 7 8 6 9 3 9 11 14 11 20 3 23 6 23 3 8 14 8 7 8 6 9 3 9 11 14 11 8 15 9 5 9 6 8 6 9 3 8 14 8 7 8 7 8 3 8 12 14 11 8 15 8 7 8 6 8 7 8 3 8 14 8 7 8 7 9 1 9 12 14 11 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 8 8 1 8 13 14 11 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 8 8 1 8 12 16 10 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 8 17 12 7 2 7 10 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 9 15 13 7 2 7 10 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 9 15 13 7 2 7 10 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 10 13 13 8 2 8 9 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 10 13 13 8 2 8 9 8 15 8 7 8 6 8 8 7 3 8 14 8 7 8 11 11 14 8 2 8 9 8 15 8 7 8 6 8 7 8 3 8 14 8 7 8 11 11 14 7 4 7 9 18 5 8 7 8 6 8 6 9 3 8 14 8 7 8 12 9 14 8 4 8 8 18 5 8 7 8 6 23 3 8 14 8 7 8 11 11 13 8 4 8 8 18 5 8 7 8 6 23 3 8 14 8 7 8 11 11 13 8 4 8 8 18 5 8 7 8 6 22 4 8 14 8 7 8 10 13 12 7 6 7 8 18 5 8 7 8 6 21 5 8 14 8 7 8 10 13 12 7 6 7 8 8 15 8 7 8 6 20 6 8 14 8 7 8 9 15 10 8 6 8 7 8 15 8 7 8 6 18 8 8 14 8 7 8 9 15 10 8 6 8 7 8 15 8 7 8 6 8 2 8 8 8 14 8 7 8 9 15 10 22 7 8 15 8 7 8 6 8 2 9 7 8 14 8 7 8 8 8 1 8 9 22 7 8 15 8 7 8 6 8 3 8 7 8 14 8 7 8 8 8 1 8 8 24 6 8 15 8 7 8 6 8 3 9 6 8 14 8 7 8 7 9 1 9 7 24 6 8 15 8 7 8 6 8 3 9 6 8 14 8 7 8 7 8 3 8 7 24 6 8 15 8 7 8 6 8 4 9 5 8 14 8 7 8 6 9 3 9 6 24 6 8 15 8 7 8 6 8 4 9 5 8 14 9 5 9 6 9 3 9 6 8 8 8 6 8 15 9 5 9 6 8 5 9 4 19 3 23 5 9 5 9 4 8 10 8 5 8 15 23 6 8 5 9 4 19 3 23 5 9 5 9 4 8 10 8 5 8 15 23 6 8 6 9 3 19 4 21 5 10 5 10 3 8 10 8 5 8 16 21 7 8 6 9 3 19 4 21 5 9 7 9 3 8 10 8 5 8 16 21 7 8 7 9 2 19 5 19 5 10 7 10 1 9 10 9 4 8 17 19 8 8 7 9 2 19 7 15 7 9 9 9 1 8 12 8 4 8 18 17 9 8 8 8 1 ";



  // 45 ------------- w = 400; h = 5;
  String large_line = "2000 ";

  // 46 ------------- w = 400; h = 2;
  String large_thin_line = "800 ";

  // 47 ------------- w = 180; h = 2;
  String small_thin_line = "360 ";

  // 48 ------------- w = 2; h = 260;
  String vertical_thin_line = "520 ";


  // 49 ------------- w = 100; h = 100;
  String volume_large = "0 1358 3 97 6 94 8 83 1 8 10 80 2 8 12 77 3 8 13 75 4 8 15 72 5 9 15 70 6 12 13 68 7 14 12 66 8 16 11 64 9 17 11 62 10 19 10 60 11 20 10 58 12 21 10 56 13 22 10 54 14 23 9 53 15 24 9 51 16 25 8 50 17 6 2 17 9 48 18 6 4 16 8 47 11 1 7 6 6 15 8 45 11 2 7 6 7 14 8 44 11 3 7 6 8 14 8 26 27 4 7 6 9 13 8 26 26 5 7 6 10 13 7 26 25 6 7 6 10 13 8 25 24 7 7 6 11 12 8 25 23 8 7 6 11 13 7 25 22 9 7 6 12 12 7 25 21 10 7 6 12 12 7 25 7 24 7 6 13 11 8 24 7 24 7 6 13 11 8 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 12 7 24 7 24 7 6 13 11 8 24 7 24 7 6 12 12 8 24 21 10 7 6 12 12 7 25 22 9 7 6 12 12 7 25 23 8 7 6 11 13 7 25 24 7 7 6 11 12 8 25 25 6 7 6 10 13 8 25 26 5 7 6 9 14 7 26 27 4 7 6 9 13 8 43 11 3 7 6 8 14 8 44 11 2 7 6 7 14 8 46 11 1 7 6 5 15 9 47 18 6 4 16 8 49 17 6 2 17 9 50 16 24 9 52 15 24 9 53 14 23 9 55 13 22 9 57 12 21 10 58 11 19 11 60 10 18 11 62 9 17 11 64 8 15 12 66 7 13 13 68 6 11 14 70 5 8 16 72 4 8 15 74 3 8 13 77 2 8 12 79 1 8 10 90 8 92 5 95 2 1340 ";

  // 50 ------------- w = 100; h = 100;
  String volume_large_off = "0 1008 3 96 5 94 7 92 9 43 3 45 10 42 6 42 11 41 8 41 11 40 10 40 11 30 2 7 12 39 11 28 3 7 14 38 11 26 4 7 15 38 11 24 5 8 15 38 11 22 6 11 14 37 11 20 7 14 12 37 11 18 8 16 11 37 11 16 9 17 11 37 11 14 10 19 10 37 11 12 11 20 9 38 11 10 12 21 9 38 11 10 11 22 9 38 11 10 10 23 8 39 11 10 9 23 9 39 11 10 8 24 9 39 11 10 7 25 8 40 11 10 6 7 2 17 8 40 11 10 5 7 4 15 8 41 11 10 4 7 5 15 8 41 11 10 3 7 6 14 8 26 27 10 2 7 7 14 7 26 28 10 1 7 8 13 8 25 29 17 9 12 8 25 30 16 9 13 7 25 31 15 10 12 7 25 32 14 10 12 8 24 33 13 10 12 8 24 7 16 11 12 11 12 7 24 7 17 11 11 11 12 7 24 7 18 11 10 11 12 7 24 7 19 11 10 10 12 7 24 7 20 11 10 9 12 7 24 7 21 11 10 8 12 7 24 7 22 11 10 7 12 7 24 7 23 11 10 6 12 7 24 7 24 11 10 5 12 7 24 7 25 11 10 4 12 7 24 7 25 12 10 3 12 7 24 7 25 13 10 2 12 7 24 21 11 14 22 8 24 22 10 15 21 7 25 23 9 16 20 7 25 24 8 17 19 7 25 25 7 18 17 8 25 26 6 7 1 11 16 7 26 27 5 7 2 11 14 8 44 10 4 7 3 11 13 8 45 10 3 7 4 11 11 8 47 10 2 7 5 11 10 8 48 10 1 7 6 11 10 6 50 17 7 11 10 5 51 16 8 11 10 3 53 15 9 11 10 2 54 14 10 11 66 13 11 11 66 12 12 11 66 11 13 11 66 10 14 11 66 9 15 11 66 8 15 12 66 7 13 15 66 6 10 19 66 5 7 23 66 4 7 24 66 3 7 13 1 11 66 2 7 12 3 11 66 1 7 10 6 11 73 8 9 11 72 5 13 11 71 2 17 11 90 11 90 11 90 10 91 9 92 7 94 5 96 3 98 1 515 ";


  // 51 ------------- w = 42; h = 100;
  String F_large = "36 6 36 6 36 6 36 6 36 6 36 6 36 6 36 6 36 6 36 6 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 31 11 31 11 31 11 31 11 31 11 31 11 31 11 31 11 31 11 31 11 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 30 12 828 ";

  // 52 ------------- w 40; h = 100;
  String C_large = "0 7 25 13 29 10 32 7 34 5 35 4 37 3 37 3 38 2 38 1 39 1 14 11 14 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 27 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 13 13 13 1 16 8 15 1 39 2 38 2 37 3 37 4 35 5 35 6 33 8 31 11 27 18 18 731 ";


  // 53 ------------- w = 115; h = 50;
  String Dark = "18 17 11 12 18 10 9 7 10 3 21 14 12 11 21 7 9 6 11 3 23 11 13 11 22 6 9 6 10 4 23 11 13 11 23 5 9 6 10 4 24 10 13 11 23 5 9 5 10 5 24 10 14 10 24 4 9 5 10 5 24 9 15 10 24 4 9 4 11 5 9 5 10 9 15 10 24 4 9 4 10 6 9 6 9 9 15 10 9 5 10 4 9 4 10 6 9 6 9 9 16 9 9 5 10 4 9 3 10 7 9 6 9 9 16 9 9 5 10 4 9 3 10 7 9 6 9 8 17 9 9 5 10 4 9 2 11 7 9 6 9 8 17 9 9 5 10 4 9 2 10 8 9 6 9 8 8 1 9 8 9 5 10 4 9 2 10 8 9 6 9 8 8 1 9 8 9 5 10 4 9 1 10 9 9 6 9 7 9 1 9 8 9 5 10 4 9 1 10 9 9 6 9 7 9 1 9 8 9 5 10 4 9 1 10 9 9 6 9 7 9 2 9 7 9 5 10 4 19 10 9 6 9 7 8 3 9 7 24 4 19 10 9 6 9 6 9 3 9 7 24 4 18 11 9 6 9 6 9 3 9 7 23 5 19 10 9 6 9 6 9 3 9 7 23 5 19 10 9 6 9 6 9 4 9 6 23 5 19 10 9 6 9 6 8 5 9 6 22 6 9 1 10 9 9 6 9 5 9 5 9 6 20 8 9 1 10 9 9 6 9 5 23 6 9 1 9 9 9 1 11 8 9 6 9 5 24 5 9 1 10 8 9 2 10 8 9 6 9 5 24 5 9 2 9 8 9 2 10 8 9 6 9 4 25 5 9 2 10 7 9 3 10 7 9 6 9 4 25 5 9 2 10 7 9 3 10 7 9 6 9 4 26 4 9 3 10 6 9 3 11 6 9 6 9 4 26 4 9 3 10 6 9 4 10 6 9 5 10 4 26 4 9 4 10 5 9 4 10 6 24 3 10 8 9 4 9 4 10 5 9 5 10 5 24 3 9 9 9 4 9 5 10 4 9 5 10 5 24 3 9 9 10 3 9 5 10 4 9 5 11 4 23 4 9 9 10 3 9 5 11 3 9 6 10 4 22 4 10 10 9 3 9 6 10 3 9 6 10 4 21 5 10 10 9 3 9 6 11 2 9 6 11 1268 ";

  // 54 ------------- w = 120; h = 50;
  String Light = "9 13 9 11 12 10 9 7 9 2 23 6 9 13 10 7 18 7 9 7 9 2 24 5 9 13 10 6 20 6 9 7 9 2 24 5 9 13 10 5 22 5 9 7 9 2 24 5 9 13 10 4 23 5 9 7 9 2 24 5 9 13 10 4 24 4 9 7 9 2 24 5 9 13 10 4 24 4 9 7 9 2 24 5 9 13 10 4 10 4 10 4 9 7 9 3 23 5 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 19 9 7 9 9 10 12 9 13 10 4 9 19 9 7 9 9 10 12 9 13 10 4 9 19 9 7 9 9 10 12 9 13 10 4 9 19 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 2 13 4 25 9 10 12 9 13 10 4 9 3 12 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 9 13 10 4 9 5 10 4 9 7 9 9 10 12 20 2 10 4 10 4 10 4 9 7 9 9 10 12 20 2 10 4 24 4 9 7 9 9 10 12 20 2 10 4 24 4 9 7 9 9 10 12 20 2 10 4 23 5 9 7 9 9 10 12 20 2 10 5 22 5 9 7 9 9 10 12 20 2 10 6 20 6 9 7 9 9 10 12 20 2 10 7 18 7 9 7 9 9 10 1332 ";



  // 55 ------------ w = 40; h = 40;
  String Left = "0 24 4 34 6 32 8 31 9 29 11 27 13 25 15 24 16 22 18 20 20 18 22 17 23 15 25 13 27 12 28 12 28 12 28 12 28 13 27 15 25 17 23 19 21 20 20 22 18 24 16 25 15 27 13 29 11 31 9 32 8 34 6 36 4 332 ";

  // 56 ------------ w = 40; h = 40;
  String Right = "4 36 6 34 8 32 9 31 11 29 13 27 15 25 16 24 18 22 20 20 21 19 23 17 25 15 27 13 28 12 28 12 28 12 28 12 27 13 25 15 23 17 22 18 20 20 18 22 16 24 15 25 13 27 11 29 9 31 8 32 6 34 4 356 ";



  // 57 ------------ w = 293; h = 18;
  String info = "0 23 3 9 3 13 3 44 3 27 3 12 3 114 3 53 3 9 3 13 3 44 3 27 3 12 3 114 3 30 3 4 3 13 3 9 3 13 3 44 3 27 3 12 3 114 3 30 3 4 3 13 3 9 3 13 3 44 3 20 3 4 3 12 3 20 3 5 3 40 3 40 3 25 3 2 3 4 3 13 3 9 3 13 3 44 3 20 3 4 3 12 3 20 3 5 3 40 3 40 3 25 3 2 3 4 3 4 5 4 3 4 8 8 8 3 5 3 3 4 3 4 3 1 3 1 4 7 8 5 5 3 7 2 7 8 8 3 3 3 3 1 7 1 7 3 5 3 3 1 4 5 6 6 7 3 5 10 6 5 5 4 3 4 5 6 5 3 10 4 3 3 7 3 3 3 9 7 9 2 7 2 3 4 3 4 3 1 9 6 9 3 7 2 7 2 8 7 9 2 3 3 3 1 7 1 7 2 7 2 9 3 8 5 7 2 7 8 8 3 7 3 3 3 7 4 7 2 10 4 3 2 9 2 3 3 9 7 9 1 9 1 4 3 3 3 4 1 10 5 9 2 9 1 7 2 8 7 9 2 3 3 3 1 7 1 7 1 9 1 10 1 9 5 7 1 9 6 9 2 9 2 3 2 9 2 9 1 17 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 1 4 3 3 3 4 1 10 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 10 1 3 4 2 7 3 3 3 3 3 6 3 4 2 2 3 3 3 2 3 2 3 3 3 2 4 2 3 3 3 2 10 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 2 3 3 3 3 3 2 4 2 4 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 4 2 4 1 3 13 3 3 3 3 3 6 3 8 3 3 3 2 3 2 3 3 3 2 3 3 3 3 3 2 10 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 2 3 2 5 2 3 2 3 4 3 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 3 4 3 1 7 9 3 3 3 3 3 6 7 4 3 3 3 2 3 2 3 3 3 2 3 9 3 2 3 4 3 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 2 4 1 5 1 4 2 3 4 3 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 3 4 3 2 7 8 3 3 3 3 3 7 7 3 9 2 3 2 9 2 3 9 3 2 3 4 3 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 3 3 1 5 1 3 3 3 4 3 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 3 4 3 3 7 7 3 3 3 3 3 8 7 2 8 3 3 2 8 3 3 9 3 2 3 4 3 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 3 13 3 3 4 3 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 3 3 3 3 3 5 3 3 3 3 3 1 3 4 3 7 3 7 3 3 3 3 3 12 3 2 3 8 3 2 3 8 3 3 3 3 3 2 3 4 3 2 3 3 3 2 3 3 3 3 3 7 3 3 3 1 3 3 3 4 5 1 5 4 3 4 3 5 3 3 3 2 3 3 3 3 3 4 3 2 3 7 3 3 3 2 4 1 4 3 3 5 3 3 3 3 3 1 3 4 3 1 2 4 3 7 3 3 3 3 3 6 2 4 3 2 3 3 3 2 3 2 3 3 3 2 4 2 3 3 3 2 3 4 3 2 9 2 3 3 9 7 9 1 9 4 4 3 4 4 3 4 3 5 9 2 9 3 5 2 3 2 3 7 9 2 9 3 5 3 5 1 9 1 3 4 3 1 9 7 5 1 9 6 9 2 9 2 3 2 9 2 9 3 8 4 3 3 7 3 3 3 9 7 9 2 7 5 4 3 4 4 3 4 3 5 9 3 7 4 5 2 3 2 3 7 9 3 7 4 5 3 5 2 7 2 3 4 3 1 8 8 5 2 7 7 8 3 9 2 3 2 9 3 7 4 8 4 3 4 5 4 3 4 8 8 8 3 5 7 2 5 2 5 3 4 3 5 8 5 5 5 5 2 3 2 3 7 8 5 5 5 5 3 5 3 5 3 3 4 3 2 6 9 5 3 5 9 6 5 7 3 3 3 7 5 5 5 5 ";


  // 58 ------------ w = 28; h = 28;
  String volume_small = "0 100 1 24 1 2 4 20 2 2 5 18 3 4 4 16 4 5 4 14 5 6 4 12 6 1 3 3 3 7 11 1 4 2 3 7 8 1 2 1 4 3 3 6 6 3 2 1 5 2 3 6 3 6 2 1 5 2 3 6 3 6 2 1 5 2 3 6 6 3 2 1 5 2 3 6 7 2 2 1 4 3 3 6 11 1 4 2 3 12 6 1 3 3 3 13 5 6 4 14 4 5 4 16 3 3 5 18 2 2 5 20 1 2 4 24 1 95 ";

  // 59 ------------ w = 26; h = 26;
  String volume_off_small = "0 54 1 24 3 11 2 10 4 7 1 2 4 9 4 5 2 2 5 9 4 3 3 4 4 9 4 2 3 5 4 9 4 2 2 2 1 3 3 7 7 2 1 2 2 3 2 7 8 4 3 2 3 6 9 3 3 2 3 6 2 4 4 2 3 2 3 6 2 5 4 2 2 2 3 6 6 2 4 2 1 2 3 6 7 1 5 4 3 6 14 3 2 12 5 1 4 2 2 13 4 2 4 17 3 3 4 17 2 2 6 17 1 2 7 19 2 2 4 23 4 23 2 29 ";



  // 60 ------------ w = 188; h = 50;
  String All_good = "0 32 9 4 9 107 8 51 9 4 9 106 10 27 12 11 9 4 9 106 10 4 11 12 12 11 9 4 9 106 10 4 11 12 12 11 9 4 9 106 10 4 11 11 14 10 9 4 9 106 10 4 11 11 14 10 9 4 9 106 10 4 11 11 14 10 9 4 9 106 10 5 10 11 14 10 9 4 9 106 10 5 10 10 15 10 9 4 9 106 10 5 10 10 16 9 9 4 9 106 10 5 10 10 16 9 9 4 9 18 8 2 9 7 16 11 15 11 8 1 10 5 9 11 16 9 9 4 9 16 21 6 19 7 19 7 21 5 9 11 16 9 9 4 9 16 21 5 20 6 21 5 22 5 9 10 18 8 9 4 9 15 22 4 22 5 21 5 22 5 9 10 18 8 9 4 9 15 22 4 22 4 23 3 23 5 9 10 8 1 9 8 9 4 9 15 22 4 22 4 23 3 23 5 9 10 8 2 8 8 9 4 9 15 22 4 23 3 23 3 23 5 9 9 9 2 9 7 9 4 9 15 9 3 10 4 9 4 10 3 9 5 9 3 10 3 10 5 9 9 9 2 9 7 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 5 9 9 9 2 9 7 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 5 9 9 8 3 9 7 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 5 9 9 8 3 9 7 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 5 9 8 9 4 9 6 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 6 8 8 9 4 9 6 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 6 8 8 9 4 9 6 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 6 8 8 9 4 9 6 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 6 8 7 24 5 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 6 8 7 24 5 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 21 24 5 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 21 24 5 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 20 26 4 9 4 9 15 9 4 9 4 9 4 10 3 9 5 9 3 10 3 10 20 26 4 9 4 9 15 9 3 10 4 9 4 10 3 9 5 9 3 10 3 10 5 9 6 26 4 9 4 9 15 22 4 9 4 10 3 9 5 9 3 10 3 10 5 9 6 26 4 9 4 9 15 22 4 10 3 10 3 10 3 10 3 23 5 9 6 9 8 9 4 9 4 9 15 22 4 22 4 23 3 23 5 9 5 10 8 10 3 9 4 9 15 22 4 22 4 23 3 23 5 9 5 9 9 10 3 9 4 9 16 21 4 22 5 21 5 22 5 9 5 9 10 9 3 9 4 9 16 21 5 21 5 21 5 22 5 9 5 9 10 9 3 9 4 9 18 9 1 9 5 20 7 19 7 21 5 9 4 10 10 10 2 9 4 9 28 9 7 17 9 17 9 10 1 9 5 9 86 9 167 21 167 21 167 21 167 20 168 20 168 19 169 18 288 ";

  // 61 ------------ w = 149; h = 23;
  String Just_setting_up = "0 79 4 71 4 70 4 71 4 70 4 71 4 23 4 29 4 3 4 3 4 71 4 23 4 29 4 3 4 78 4 2 4 1 4 3 7 1 7 6 7 4 7 2 14 1 4 2 8 3 9 6 4 2 4 2 8 23 4 2 4 1 4 2 8 1 7 6 8 2 9 1 14 1 4 2 9 2 9 6 4 2 4 2 8 23 4 2 4 1 4 2 8 1 7 6 8 2 9 1 14 1 4 2 9 2 9 6 4 2 4 2 9 22 4 2 4 1 4 2 4 1 3 2 4 8 3 2 3 2 4 2 3 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 22 4 2 4 1 4 2 4 6 4 8 3 7 4 2 3 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 22 4 2 4 1 4 2 7 3 4 8 7 3 9 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 22 4 2 4 1 4 2 8 2 4 8 8 2 9 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 17 4 1 4 2 4 1 4 3 7 2 4 9 7 2 9 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 17 4 1 4 2 4 1 4 7 3 2 4 13 3 2 4 7 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 17 4 1 4 2 4 1 4 2 4 1 3 2 4 8 4 1 3 2 4 1 4 2 4 3 4 3 4 2 4 1 4 2 3 2 4 6 4 2 4 2 3 2 4 1 4 2 4 1 4 1 9 2 9 2 8 2 6 6 8 2 9 2 6 1 6 1 4 2 4 1 4 2 9 6 10 2 9 1 4 2 4 1 4 1 9 2 9 2 8 3 5 6 8 2 9 2 6 1 6 1 4 2 4 1 4 2 9 7 9 2 9 1 4 2 4 1 4 2 7 4 8 2 8 3 5 6 8 2 9 3 5 2 5 1 4 2 4 1 4 2 9 7 9 2 8 2 4 2 4 1 4 102 4 18 3 119 9 18 3 119 8 19 3 119 8 19 3 172 ";




  // 62 ----------- w = 14; h = 27;
  String l_A = "0 4 6 8 6 8 6 7 7 7 8 6 8 6 8 5 9 5 9 5 4 1 5 4 4 1 5 4 4 2 4 3 5 2 4 3 5 2 4 3 12 2 12 2 12 1 5 4 4 1 5 4 10 4 9 5 5 84 ";

  // 63 ---------- W = 14; H = 27;
  String l_B = "10 4 11 3 12 2 12 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 12 2 12 2 12 2 12 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 12 2 12 2 11 101 ";

  // 64 ---------- w = 14; h = 27;
  String l_C = "0 3 6 6 10 4 11 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 9 5 9 5 9 5 9 5 9 5 9 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 3 11 3 10 87 ";

  // 65 ---------- w = 14; h = 27;
  String l_D = "10 4 11 3 12 2 12 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 12 2 12 2 11 87 ";

  // 66 ---------- w = 14; h = 27;
  String l_E = "11 3 11 3 11 3 11 3 5 9 5 9 5 9 5 9 5 9 10 4 10 4 10 4 10 4 5 9 5 9 5 9 5 9 5 9 11 3 11 3 11 87 ";

  // 67 ---------- w = 14; h = 27;
  String l_F = "11 3 11 3 11 3 11 3 5 9 5 9 5 9 5 9 5 9 10 4 10 4 10 4 10 4 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 93 ";

  // 68 ---------- w = 14; h = 27;
  String l_G = "0 3 6 6 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 9 5 9 5 9 5 1 6 2 5 1 6 2 5 1 6 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 87 ";

  // 69 ---------- w = 14; h = 27;
  String l_H = "4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 12 2 12 2 12 2 12 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 2 4 4 4 86 ";

  // 70 ---------- w = 14; h = 27;
  String l_I = "4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 94 ";

  // 71 ---------- w = 14; h = 27;
  String l_J = "0 6 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 9 5 3 4 2 5 3 5 1 5 3 5 1 5 3 5 1 5 3 5 1 5 3 11 3 11 4 9 88 ";

  // 72 ---------- w = 14; h = 27;
  String l_K = "5 3 5 1 5 3 5 1 5 2 5 2 5 2 5 2 5 2 5 2 5 1 5 3 5 1 5 3 10 4 10 4 9 5 9 5 9 5 10 4 10 4 10 4 5 1 5 3 5 1 5 3 5 2 5 2 5 2 5 2 5 2 5 2 5 3 5 85 ";

  // 73 ---------- w = 14; h = 27;
  String l_L = "4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 10 4 10 4 10 88 ";

  // 74 ---------- w = 16; h = 27;
  String l_M = "5 6 10 6 11 4 12 4 12 4 12 4 13 2 14 2 14 2 43 1 6 1 8 1 6 1 8 1 6 1 8 1 6 1 8 2 4 2 8 2 4 2 8 8 8 8 8 8 8 8 4 96 ";

  // 75 ---------- w = 14; h = 27;
  String l_N = "4 4 4 2 5 3 4 2 5 3 4 2 5 3 4 2 6 2 4 2 6 2 4 2 6 2 4 2 7 1 4 2 7 1 4 2 7 1 4 2 12 2 4 1 7 2 4 1 7 2 4 1 7 2 4 1 7 2 4 2 6 2 4 2 6 2 4 2 6 2 4 3 5 2 4 3 5 2 4 3 5 86 ";

  // 76 ---------- w = 14; h = 27;
  String l_O = "0 2 7 6 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 87 ";

  // 77 ---------- w = 14; h = 27;
  String l_P = "0 1 9 4 12 2 12 2 12 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 5 3 4 2 12 2 12 2 12 2 11 3 5 9 5 9 5 9 5 9 5 9 5 9 5 93 ";

  // 78 ---------- w = 14; h = 27;
  String l_Q = "0 2 7 6 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 9 5 10 5 9 6 43 ";

  // 79 ---------- w = 14; h = 27;
  String l_R = "10 4 11 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 2 11 3 10 4 5 1 4 4 5 1 5 3 5 1 5 3 5 2 5 2 5 2 5 2 5 2 6 1 5 3 5 85 ";

  // 80 ---------- w = 14; h = 27;
  String l_S = "0 3 6 6 10 4 10 3 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 9 5 9 10 4 11 4 11 5 9 9 5 9 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 3 10 4 10 87 ";

  // 81 ---------- w = 14; h = 27;
  String l_T = "12 2 12 2 12 2 12 6 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 90 ";

  // 82 ---------- w = 14; h = 27;
  String l_U = "5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 87 ";

  // 83 ---------- w = 16; h = 27;
  String l_V = "5 4 5 2 5 4 5 2 5 4 5 3 4 4 4 4 4 4 4 4 5 2 5 4 5 2 5 4 5 2 5 5 4 2 4 6 4 2 4 6 4 2 4 6 10 6 10 7 8 8 8 8 8 8 8 8 8 9 6 10 6 10 6 102 ";

  // 84 ---------- w = 22; h = 27;
  String l_W = "5 4 4 5 9 3 6 3 10 3 6 3 5 1 4 3 6 3 4 2 4 3 6 3 4 2 4 3 6 3 4 2 5 2 6 3 4 2 5 2 6 2 5 2 5 1 8 1 5 3 4 1 8 1 4 4 4 1 8 1 4 4 4 1 8 1 4 4 4 1 8 1 4 4 4 1 3 2 3 1 4 4 8 2 8 5 7 2 7 6 7 2 7 6 7 2 7 6 7 2 7 6 6 4 6 6 6 4 5 136 ";

  // 85 ---------- w = 14; h = 27;
  String l_X = "5 4 4 1 6 2 5 2 5 2 5 2 5 2 4 4 10 4 10 5 8 6 8 6 7 8 6 8 6 8 6 8 6 7 8 6 8 5 10 4 10 3 5 2 5 2 5 2 5 2 4 3 5 1 5 4 5 84 ";

  // 86 ---------- w = 14; h = 27;
  String l_Y = "5 4 10 4 5 1 4 4 4 2 5 3 4 2 5 2 5 3 4 2 4 4 4 2 4 4 5 1 4 5 8 6 8 6 8 7 6 8 6 8 6 9 4 10 4 10 4 10 4 10 4 10 4 10 4 89 ";

  // 87 ---------- w = 14; h = 27;
  String l_Z = "0 1 11 3 11 3 11 3 11 9 4 9 5 9 4 9 5 9 5 8 5 9 5 8 5 9 5 8 5 9 5 8 5 9 5 8 5 9 12 2 12 2 12 86 ";

  // 88 ---------- w = 14; h = 27;
  String l_0 = "0 3 6 6 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 87 ";

  // 89 ---------- w = 14; h = 27;
  String l_1 = "7 7 7 7 7 7 7 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 10 4 91 ";

  // 90 ---------- w = 14; h = 27;
  String l_2 = "0 3 6 6 10 4 10 3 11 3 5 2 4 3 5 2 4 3 5 2 4 3 5 2 4 9 5 9 5 8 5 9 5 8 5 8 6 8 5 8 5 9 5 8 5 9 10 4 10 4 10 87 ";

  // 91 ---------- w = 14; h = 27;
  String l_3 = "0 3 6 6 10 3 11 3 11 3 5 2 4 3 5 2 4 3 5 2 4 3 5 2 4 10 4 6 8 6 8 6 8 7 7 10 4 3 5 2 4 3 5 2 4 3 5 2 4 3 5 2 4 3 11 3 11 4 9 88 ";

  // 92 ---------- w = 14; h = 27;
  String l_4 = "0 7 4 9 5 9 4 9 5 9 4 9 5 9 4 9 5 9 4 9 5 9 4 2 4 3 5 2 4 3 4 3 4 2 5 3 4 2 42 1 13 8 4 10 4 10 4 86 ";

  // 93 ---------- w = 14; h = 27;
  String l_5 = "0 1 11 3 11 3 11 3 11 3 4 10 4 10 4 10 4 10 10 4 10 4 11 9 5 9 5 9 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 3 10 4 10 87 ";

  // 94 ---------- w = 14; h = 27;
  String l_6 = "0 3 6 6 10 4 11 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 9 11 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 3 11 3 10 87 ";

  // 95 ---------- w = 14; h = 27;
  String l_7 = "0 1 11 3 11 3 11 3 10 9 5 9 5 9 4 9 5 9 5 9 5 9 4 9 5 9 5 9 4 9 5 9 5 9 4 9 5 9 5 9 4 9 5 92 ";

  // 96 ---------- w = 14; h = 27;
  String l_8 = "0 3 6 6 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 3 10 3 12 2 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 10 87 ";

  // 97 ---------- w = 14; h = 27;
  String l_9 = "0 2 7 6 10 3 11 3 12 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 12 3 11 9 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 5 2 12 2 11 4 10 87 ";

  // 98 ---------- w = 14; h = 27;
  String l_dot = "4 10 4 10 4 10 4 10 4 318 ";

  // 99 ---------- w = 14; h = 27;
  String l_dash = "8 6 8 6 8 342 ";

  // 100 -------- w = 14; h = 27;
  String l_col = "0 14 4 10 4 10 4 10 4 10 4 10 4 10 4 276 ";





  // 101 ------- w = 30; h = 61;
  String m0 = "0 6 18 9 23 6 26 4 26 3 28 2 28 2 28 1 72 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 25 4 43 1 28 2 28 2 28 2 28 3 26 5 24 8 20 395 ";

  // 102 ------- w = 30; h = 61;
  String m1 = "18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 402 ";

  // 103 ------- w = 30; h = 61;
  String m2 = "0 5 18 10 22 7 24 5 26 3 27 3 28 2 28 2 28 2 28 2 11 5 12 2 11 5 12 2 11 5 12 2 11 5 12 2 11 5 12 2 11 5 12 2 11 5 12 2 11 5 12 18 12 18 11 18 12 18 12 17 12 17 13 17 12 17 13 16 13 16 13 17 13 16 13 16 13 16 14 16 13 16 13 16 14 15 14 16 13 16 14 15 14 15 14 16 14 15 28 2 28 2 28 2 28 2 28 2 28 2 28 2 28 392 ";

  // 104 ------- w = 30; h = 61;
  String m3 = "0 5 18 10 22 7 25 5 25 4 27 3 27 3 27 2 29 1 29 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 18 12 18 12 18 12 17 12 11 19 11 19 11 18 12 17 13 18 12 19 11 19 11 19 19 12 18 12 18 12 18 12 2 11 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 12 5 12 1 13 3 13 1 29 2 28 2 27 3 27 3 27 4 25 6 23 9 19 396 ";

  // 105 ------- w = 35; h = 61;
  String m4 = "0 16 12 22 12 23 12 22 12 23 11 23 12 23 11 23 12 22 12 23 12 22 12 23 12 22 12 23 11 23 12 23 11 23 12 22 12 23 12 22 12 23 11 23 12 2 11 10 11 3 11 9 12 3 11 9 11 4 11 8 12 4 11 7 12 5 11 7 11 6 11 6 12 6 11 6 11 7 11 6 11 7 11 6 34 1 34 1 34 1 34 1 34 1 34 1 34 1 34 1 34 19 11 24 11 24 11 24 11 24 11 24 11 24 11 24 11 461 ";

  // 106 ------- w = 30; h = 61;
  String m5 = "28 2 28 2 28 2 28 2 28 2 28 2 28 2 28 2 28 2 12 18 12 18 12 18 12 18 12 18 12 18 12 18 12 18 24 6 26 4 27 3 28 2 28 2 28 2 29 1 29 17 13 18 12 18 12 18 12 18 12 18 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 12 5 12 1 12 4 13 1 29 1 29 1 28 2 28 3 27 4 25 6 23 8 20 396 ";

  // 107 ------- w = 30; h = 61;
  String m6 = "0 5 18 10 22 7 24 5 26 3 28 2 28 2 28 2 28 2 28 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 19 11 19 11 19 11 19 21 9 25 5 26 4 27 3 28 2 28 2 29 1 29 1 29 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 11 6 12 1 12 5 12 1 29 1 29 1 29 1 28 3 27 3 26 5 24 8 20 396 ";

  // 108 ------- w = 30; h = 61;
  String m7 = "28 2 28 2 28 2 28 2 28 2 28 2 28 2 28 2 27 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 18 11 18 12 18 12 17 12 18 12 18 12 17 12 18 12 18 12 17 12 18 12 18 12 17 12 18 12 18 12 17 12 18 12 18 12 17 12 406 ";

  // 109 ------- w = 30; h = 61;
  String m8 = "0 5 19 9 23 6 26 4 26 3 28 2 28 2 28 1 72 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 12 1 11 6 11 2 28 2 28 3 26 5 24 5 26 3 28 2 28 2 28 2 11 6 11 1 12 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 24 6 42 1 28 2 28 2 28 2 28 3 26 5 24 8 20 395 ";

  // 110 ------- w = 30; h = 61;
  String m9 = "0 5 19 9 23 6 25 4 27 3 28 2 28 1 29 1 29 1 29 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 12 6 11 1 29 1 29 1 29 2 28 2 28 3 27 4 26 5 25 9 21 19 11 19 11 19 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 11 6 11 2 12 4 12 2 28 2 28 2 28 2 28 3 26 4 26 5 24 8 20 395 ";

  // 111 ------- w = 79; h = 15;
  String aph = "0 34 2 25 2 16 5 3 5 3 3 4 3 8 2 4 4 5 4 8 2 4 3 4 2 3 6 2 6 2 4 2 4 8 2 3 6 3 6 7 2 3 2 1 2 3 2 3 2 2 3 1 2 2 3 1 4 2 4 7 2 4 2 2 2 3 2 2 2 6 2 4 2 1 2 2 2 4 2 3 2 1 2 3 2 1 10 7 2 4 2 2 2 3 2 2 2 6 2 4 2 1 2 2 2 4 2 3 2 1 2 3 2 1 2 1 4 1 2 7 2 4 6 3 2 2 2 6 2 4 2 1 2 1 2 5 2 2 3 1 2 2 3 1 2 2 2 2 2 6 2 6 4 4 2 9 2 6 3 2 2 5 6 2 6 2 2 2 2 2 2 6 2 14 2 9 2 10 2 2 3 1 5 3 5 3 2 6 2 6 2 14 2 9 2 10 2 1 2 1 4 6 2 6 2 6 2 5 2 15 2 2 2 4 2 10 2 2 2 1 4 6 2 6 2 6 2 5 2 15 2 2 2 4 2 10 2 2 2 1 4 6 2 6 2 6 2 5 2 15 6 4 2 9 2 3 2 1 4 6 2 6 2 6 2 4 2 17 4 4 2 10 2 4 3 31 2 25 2 50 2 25 2 20 ";

  // 112 ------- w = 79; h = 15;
  String aph_F = "0 34 2 25 2 16 5 3 5 4 2 4 2 9 2 4 4 4 6 7 2 11 2 3 6 2 6 2 4 2 4 8 2 3 6 3 6 7 2 4 3 4 2 3 2 2 3 1 2 2 3 1 4 2 4 7 2 4 2 2 2 3 2 10 2 4 2 1 2 2 2 4 2 3 2 1 2 3 2 1 10 7 2 4 2 2 2 3 2 10 2 4 2 1 2 2 2 4 2 3 2 1 2 3 2 1 2 1 4 1 2 7 2 4 6 3 2 10 2 4 2 1 2 1 2 5 2 2 3 1 2 2 3 1 2 2 2 2 2 6 2 6 4 4 5 6 2 5 2 1 2 1 2 5 6 2 6 2 2 2 2 2 2 6 2 14 5 6 2 6 3 1 2 2 3 1 5 3 5 3 2 6 2 6 2 14 2 9 2 10 2 1 2 1 4 6 2 6 2 6 2 5 2 15 2 8 2 10 2 2 2 1 4 6 2 6 2 6 2 5 2 15 2 8 2 10 2 2 2 1 4 6 2 6 2 6 2 5 2 15 2 8 2 9 2 3 2 1 4 6 2 6 2 6 2 4 2 16 2 7 2 10 2 4 3 31 2 25 2 50 2 25 2 20 ";


  // 113 ------------- w = 2; h = 134;
  String vertical_thin_line_short = "268 ";




  // 114 ------------- w = 25; h = 18;
  String wifi_60 = "0 160 5 18 9 14 5 3 5 11 4 7 4 10 2 11 2 65 5 19 7 19 5 21 3 23 1 12 ";

  // 115 ------------- w = 25; h = 18;
  String wifi_20 = "0 311 3 21 5 19 7 19 5 21 3 23 1 12 ";




  // 116 ------------ w = 10; h = 5;
  String minus = "50 ";



  // 117 ----------- w = 74; h = 39;
  String off = "0 78 16 9 20 4 20 4 18 8 20 4 20 3 20 7 20 4 20 2 22 6 20 4 20 2 22 6 20 4 20 2 22 6 20 4 20 2 9 4 9 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 18 6 18 4 8 6 8 6 18 6 18 4 8 6 8 6 18 6 18 4 8 6 8 6 18 6 18 4 8 6 8 6 18 6 18 4 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 8 6 8 6 8 16 8 14 9 4 9 6 8 16 8 14 22 6 8 16 8 14 22 6 8 16 8 14 22 6 8 16 8 15 20 7 8 16 8 16 18 8 8 16 8 17 16 9 8 16 8 13 ";

  // 118 ----------- w = 134; h = 25;
  String turning_off = "0 182 3 51 3 6 3 21 11 36 3 50 5 4 5 20 11 36 3 50 5 4 5 20 11 89 3 6 3 26 3 93 3 6 3 26 3 5 3 4 3 4 6 4 6 5 3 5 6 6 7 13 8 3 7 2 7 24 3 5 3 4 3 3 7 3 8 4 3 4 8 4 9 11 10 2 7 2 7 24 3 5 3 4 3 3 7 2 10 3 3 3 10 2 11 10 10 2 7 2 7 24 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 4 3 4 3 6 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 11 10 3 4 3 4 3 6 3 26 3 5 4 2 4 3 3 6 3 4 3 3 3 3 3 4 3 3 10 10 3 4 3 4 3 6 3 4 3 2 3 2 3 9 3 6 8 4 3 6 3 4 3 3 3 3 3 4 3 4 9 10 10 4 3 6 3 4 3 2 3 2 3 9 3 6 8 4 3 6 3 4 3 3 3 3 3 4 3 10 3 10 10 4 3 6 3 4 3 2 3 2 3 9 3 8 4 6 3 6 3 4 3 3 3 3 3 4 3 10 3 11 8 5 3 6 3 4 3 2 3 2 3 77 3 125 9 125 8 126 7 60 ";

  // 119 ----------- w = 130; h = 25;
  String turning_on = "0 178 3 80 11 36 3 80 11 36 3 80 11 123 3 127 3 5 3 4 3 4 6 4 6 5 3 5 6 6 7 14 5 7 6 28 3 5 3 4 3 3 7 3 8 4 3 4 8 4 9 12 7 5 8 27 3 5 3 4 3 3 7 2 10 3 3 3 10 2 11 10 9 3 10 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 3 5 3 10 3 3 3 3 3 4 3 26 3 5 3 4 3 3 3 6 3 4 3 3 3 3 3 4 3 2 11 10 3 3 3 3 3 4 3 26 3 5 4 2 4 3 3 6 3 4 3 3 3 3 3 4 3 3 10 10 3 3 3 3 3 4 3 4 3 3 3 3 3 7 3 6 8 4 3 6 3 4 3 3 3 3 3 4 3 4 9 10 9 3 3 4 3 4 3 3 3 3 3 7 3 6 8 4 3 6 3 4 3 3 3 3 3 4 3 10 3 11 7 4 3 4 3 4 3 3 3 3 3 7 3 8 4 6 3 6 3 4 3 3 3 3 3 4 3 10 3 12 5 5 3 4 3 4 3 3 3 3 3 75 3 121 9 121 8 122 7 56 ";


  // 120 ----------- w = 28; h = 20;
  String off_indicator = "0 15 3 6 3 15 5 4 5 14 5 4 5 14 3 6 3 16 3 6 3 3 8 3 7 2 17 2 7 2 17 2 7 2 10 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 3 4 3 4 3 6 3 2 10 4 3 6 3 2 10 4 3 6 3 3 8 5 3 6 3 2 ";


  // 121 ---------- w = 30; h = 15;
  String alert = "0 14 2 27 4 25 6 23 8 21 4 2 4 19 5 2 5 17 6 2 6 15 7 2 7 13 8 2 8 11 9 2 9 9 22 7 11 2 11 5 12 2 12 3 28 1 30 ";


  // 122 ---------- w = 144; h = 24;
  String reading_sign = "0 42 3 3 3 41 3 49 8 34 3 3 3 41 3 49 9 33 3 3 3 41 3 49 9 33 3 47 3 15 3 31 3 3 3 33 3 47 3 15 3 31 3 3 3 4 8 4 4 1 3 4 4 1 3 3 3 5 6 7 7 11 4 1 3 3 4 1 3 2 7 3 4 1 3 18 3 3 3 3 10 2 9 3 9 3 3 4 8 5 9 9 9 2 9 2 7 2 9 18 3 3 3 3 10 2 9 3 9 3 3 3 10 3 11 8 9 2 9 2 7 2 9 18 3 3 3 3 3 4 3 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 3 3 3 3 3 4 3 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 9 3 3 4 3 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 9 3 10 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 8 4 10 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 3 1 4 4 10 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 3 2 4 3 3 9 3 3 3 3 3 3 3 3 3 3 3 4 3 3 3 5 3 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 3 2 4 3 3 4 3 2 3 3 3 3 3 3 3 3 3 3 3 4 3 3 11 8 3 3 3 2 3 3 3 4 3 4 3 3 3 18 3 3 4 2 3 4 3 2 3 3 3 3 3 3 3 3 3 3 3 4 3 4 10 8 3 3 3 2 3 3 3 4 3 4 3 3 3 3 3 3 3 3 6 3 4 2 10 2 9 3 9 3 3 3 3 4 3 5 9 8 9 2 9 4 3 4 9 3 3 3 3 3 6 4 3 2 10 2 9 3 9 3 3 3 3 4 3 11 3 8 9 2 9 4 3 4 9 3 3 3 3 3 6 4 3 3 8 4 4 1 3 4 4 1 3 3 3 3 3 4 3 11 3 9 4 1 3 3 4 1 3 4 3 5 4 1 3 3 3 3 3 3 3 74 3 135 9 135 8 136 7 69 ";


  // 123 ---------- w = 32; h = 12;
  String good = "0 1 5 4 4 4 4 3 6 1 7 2 6 2 6 2 9 3 2 2 2 2 2 2 2 2 2 2 2 3 4 7 2 2 2 2 2 2 2 2 2 3 4 7 2 2 2 2 2 2 2 2 2 3 4 7 2 2 2 2 2 2 2 2 2 3 4 1 4 2 2 2 2 2 2 2 2 2 2 3 4 1 4 2 2 2 2 2 2 2 2 2 2 3 4 3 2 2 2 2 2 2 2 2 2 2 2 3 4 3 2 2 2 2 2 2 2 2 2 2 2 3 9 2 6 2 6 2 7 1 5 4 4 4 4 3 6 1 ";


  // 124 ---------- w = 56; h = 12;
  String not_great = "0 3 3 3 2 5 2 1 5 2 5 5 3 5 5 2 5 3 3 3 2 5 2 1 5 2 6 4 3 4 7 1 5 2 2 1 2 3 2 3 2 2 2 5 2 2 2 3 2 1 2 3 2 3 2 1 2 5 2 1 2 3 2 3 2 2 2 5 2 2 2 3 2 1 2 3 2 6 2 5 2 1 2 3 2 3 2 2 2 5 2 2 2 3 2 1 2 3 2 6 2 4 2 3 2 2 2 3 2 2 4 3 6 2 2 3 2 2 2 6 4 2 2 3 2 2 2 3 2 2 4 3 5 3 2 3 2 2 2 1 4 1 4 2 7 3 2 1 2 3 2 5 4 4 7 2 2 1 4 1 2 4 7 3 2 1 2 3 2 5 5 3 7 2 2 3 2 1 2 4 2 3 2 3 2 1 2 3 2 5 2 1 2 3 2 3 2 2 2 3 2 1 2 3 2 5 2 3 3 4 5 2 2 2 2 1 2 5 2 1 7 1 7 5 2 3 3 4 5 2 2 2 2 1 2 5 2 2 5 2 5 ";

  // 125 ---------- w = 24; h = 12;
  String bad = "6 5 3 4 5 1 7 4 3 4 8 3 2 3 2 1 2 3 2 2 4 3 2 3 2 1 2 3 2 2 4 3 2 3 2 1 2 3 2 2 8 3 2 3 2 2 2 2 4 3 2 2 2 3 2 2 2 2 4 3 2 2 7 2 2 2 4 3 2 2 7 2 2 2 4 3 2 2 2 3 2 2 2 2 9 1 2 5 2 1 12 2 2 5 2 1 5 1 ";

  switch (item) {
    case 0:
      input = zeroL;
      w = 39;
      h = 79;
      break;

    case 1:
      input = oneL;
      w = 26;
      h = 79;
      break;

    case 2:
      input = twoL;
      w = 38;
      h = 79;
      break;

    case 3:
      input = threeL;
      w = 39;
      h = 79;
      break;

    case 4:
      input = fourL;
      w = 46;
      h = 79;
      break;

    case 5:
      input = fiveL;
      w = 39;
      h = 79;
      break;

    case 6:
      input = sixL;
      w = 39;
      h = 79;
      break;

    case 7:
      input = sevenL;
      w = 37;
      h = 79;
      break;

    case 8:
      input = eightL;
      w = 39;
      h = 79;
      break;

    case 9:
      input = nineL;
      w = 39;
      h = 79;
      break;

    case 10:
      input = zeroS;
      w = 19;
      h = 47;
      break;

    case 11:
      input = oneS;
      w = 13;
      h = 47;
      break;

    case 12:
      input = twoS;
      w = 18;
      h = 47;
      break;

    case 13:
      input = threeS;
      w = 19;
      h = 47;
      break;

    case 14:
      input = fourS;
      w = 22;
      h = 47;
      break;

    case 15:
      input = fiveS;
      w = 18;
      h = 48;
      break;

    case 16:
      input = sixS;
      w = 19;
      h = 47;
      break;

    case 17:
      input = sevenS;
      w = 18;
      h = 47;
      break;

    case 18:
      input = eightS;
      w = 19;
      h = 47;
      break;

    case 19:
      input = nineS;
      w = 19;
      h = 47;
      break;

    case 20:
      input = dot;
      w = 7;
      h = 47;
      break;

    case 21:
      input = C;
      w = 19;
      h = 47;
      break;

    case 22:
      input = F;
      w = 19;
      h = 47;
      break;

    case 23:
      input = temperature;
      w = 20;
      h = 40;
      break;

    case 24:
      input = humidity;
      w = 28;
      h = 40;
      break;

    case 25:
      input = percentage;
      w = 36;
      h = 47;
      break;

    case 26:
      input = degree;
      w = 15;
      h = 15;
      break;

    case 27:
      input = triangle;
      w = 25;
      h = 25;
      break;

    case 28:
      input = line;
      w = 300;
      h = 5;
      break;

    case 29:
      input = batteryFullCharging;
      w = 36;
      h = 18;
      break;

    case 30:
      input = batteryFull;
      w = 36;
      h = 18;
      break;

    case 31:
      input = battery5bar;
      w = 36;
      h = 18;
      break;

    case 32:
      input = battery4bar;
      w = 36;
      h = 18;
      break;

    case 33:
      input = battery3bar;
      w = 36;
      h = 18;
      break;

    case 34:
      input = battery2bar;
      w = 36;
      h = 18;
      break;

    case 35:
      input = battery1bar;
      w = 36;
      h = 18;
      break;

    case 36:
      input = battery0bar;
      w = 36;
      h = 18;
      break;

    case 37:
      input = bluetooth;
      w = 13;
      h = 19;
      break;

    case 38:
      input = bluetoothNot;
      w = 20;
      h = 20;
      break;

    case 39:
      input = wifi;
      w = 25;
      h = 18;
      break;

    case 40:
      input = wifiNot;
      w = 22;
      h = 18;
      break;

    case 41:
      input = PPM;
      w = 62;
      h = 32;
      break;

    case 42:
      input = cloud;
      w = 57;
      h = 41;
      break;

    case 43:
      input = bluetoothConnecting;
      w = 120;
      h = 120;
      break;

    case 44:
      input = luxafor;
      w = 186;
      h = 39;
      break;

    case 45:
      input = large_line;
      w = 400;
      h = 5;
      break;

    case 46:
      input = large_thin_line;
      w = 400;
      h = 2;
      break;

    case 47:
      input = small_thin_line;
      w = 180;
      h = 2;
      break;

    case 48:
      input = vertical_thin_line;
      w = 2;
      h = 260;
      break;

    case 49:
      input = volume_large;
      w = 100;
      h = 100;
      break;

    case 50:
      input = volume_large_off;
      w = 100;
      h = 100;
      break;

    case 51:
      input = F_large;
      w = 42;
      h = 100;
      break;

    case 52:
      input = C_large;
      w = 40;
      h = 100;
      break;

    case 53:
      input = Dark;
      w = 115;
      h = 50;
      break;

    case 54:
      input = Light;
      w = 120;
      h = 50;
      break;

    case 55:
      input = Left;
      w = 40;
      h = 40;
      break;

    case 56:
      input = Right;
      w = 40;
      h = 40;
      break;

    case 57:
      input = info;
      w = 293;
      h = 18;
      break;

    case 58:
      input = volume_small;
      w = 28;
      h = 28;
      break;

    case 59:
      input = volume_off_small;
      w = 26;
      h = 26;
      break;

    case 60:
      input = All_good;
      w = 188;
      h = 50;
      break;

    case 61:
      input = Just_setting_up;
      w = 149;
      h = 23;
      break;

    case 62:
      input = l_A;
      w = 14;
      h = 27;
      break;

    case 63:
      input = l_B;
      w = 14;
      h = 28;
      break;

    case 64:
      input = l_C;
      w = 14;
      h = 27;
      break;

    case 65:
      input = l_D;
      w = 14;
      h = 27;
      break;

    case 66:
      input = l_E;
      w = 14;
      h = 27;
      break;

    case 67:
      input = l_F;
      w = 14;
      h = 27;
      break;

    case 68:
      input = l_G;
      w = 14;
      h = 27;
      break;

    case 69:
      input = l_H;
      w = 14;
      h = 27;
      break;

    case 70:
      input = l_I;
      w = 14;
      h = 27;
      break;

    case 71:
      input = l_J;
      w = 14;
      h = 27;
      break;

    case 72:
      input = l_K;
      w = 14;
      h = 27;
      break;

    case 73:
      input = l_L;
      w = 14;
      h = 27;
      break;

    case 74:
      input = l_M;
      w = 16;
      h = 27;
      break;

    case 75:
      input = l_N;
      w = 14;
      h = 27;
      break;

    case 76:
      input = l_O;
      w = 14;
      h = 27;
      break;

    case 77:
      input = l_P;
      w = 14;
      h = 27;
      break;

    case 78:
      input = l_Q;
      w = 14;
      h = 27;
      break;

    case 79:
      input = l_R;
      w = 14;
      h = 27;
      break;

    case 80:
      input = l_S;
      w = 14;
      h = 27;
      break;

    case 81:
      input = l_T;
      w = 14;
      h = 27;
      break;

    case 82:
      input = l_U;
      w = 14;
      h = 27;
      break;

    case 83:
      input = l_V;
      w = 16;
      h = 27;
      break;

    case 84:
      input = l_W;
      w = 22;
      h = 27;
      break;

    case 85:
      input = l_X;
      w = 14;
      h = 27;
      break;

    case 86:
      input = l_Y;
      w = 14;
      h = 27;
      break;

    case 87:
      input = l_Z;
      w = 14;
      h = 27;
      break;

    case 88:
      input = l_0;
      w = 14;
      h = 27;
      break;

    case 89:
      input = l_1;
      w = 14;
      h = 27;
      break;

    case 90:
      input = l_2;
      w = 14;
      h = 27;
      break;

    case 91:
      input = l_3;
      w = 14;
      h = 27;
      break;

    case 92:
      input = l_4;
      w = 14;
      h = 27;
      break;

    case 93:
      input = l_5;
      w = 14;
      h = 27;
      break;

    case 94:
      input = l_6;
      w = 14;
      h = 27;
      break;

    case 95:
      input = l_7;
      w = 14;
      h = 27;
      break;

    case 96:
      input = l_8;
      w = 14;
      h = 27;
      break;

    case 97:
      input = l_9;
      w = 14;
      h = 27;
      break;

    case 98:
      input = l_dot;
      w = 14;
      h = 27;
      break;

    case 99:
      input = l_dash;
      w = 14;
      h = 27;
      break;

    case 100:
      input = l_col;
      w = 14;
      h = 27;
      break;

    case 101:
      input = m0;
      w = 30;
      h = 61;
      break;

    case 102:
      input = m1;
      w = 30;
      h = 61;
      break;

    case 103:
      input = m2;
      w = 30;
      h = 61;
      break;

    case 104:
      input = m3;
      w = 30;
      h = 61;
      break;

    case 105:
      input = m4;
      w = 35;
      h = 61;
      break;

    case 106:
      input = m5;
      w = 30;
      h = 61;
      break;

    case 107:
      input = m6;
      w = 30;
      h = 61;
      break;

    case 108:
      input = m7;
      w = 30;
      h = 61;
      break;

    case 109:
      input = m8;
      w = 30;
      h = 61;
      break;

    case 110:
      input = m9;
      w = 30;
      h = 61;
      break;

    case 111:
      input = aph;
      w = 79;
      h = 15;
      break;

    case 112:
      input = aph_F;
      w = 79;
      h = 15;
      break;

    case 113:
      input = vertical_thin_line_short;
      w = 2;
      h = 134;
      break;

    case 114:
      input = wifi_60;
      w = 25;
      h = 18;
      break;

    case 115:
      input = wifi_20;
      w = 25;
      h = 18;
      break;

    case 116:
      input = minus;
      w = 10;
      h = 5;
      break;

    case 117:
      input = off;
      w = 74;
      h = 39;
      break;

    case 118:
      input = turning_off;
      w = 134;
      h = 25;
      break;

    case 119:
      input = turning_on;
      w = 130;
      h = 25;
      break;

    case 120:
      input = off_indicator;
      w = 28;
      h = 20;
      break;

    case 121:
      input = alert;
      w = 30;
      h = 15;
      break;
  }



  if (item == 122) {
    input = reading_sign;
    w = 144;
    h = 24;
  }


  if (item == 123) {
    input = good;
    w = 32;
    h = 12;
  }


  if (item == 124) {
    input = not_great;
    w = 56;
    h = 12;
  }


  if (item == 125) {
    input = bad;
    w = 24;
    h = 12;
  }


  int count = 0;
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == ' ') {
      count++;
    }
  }



  int output[count];
  char *token;
  count = 0;
  int lastIndex = 0;
  for (int i = 0; i < input.length(); i++) {
    // Serial.print(input[i]);

    if (input[i] == ' ') {
      output[count] = input.substring(lastIndex, i).toInt();
      // Serial.println(output[count]);
      count++;
      lastIndex = i + 1;
    }
  }
  output[count] = input.substring(lastIndex).toInt();



  int itemSum = 0;
  int colum = 0;
  int row = 0;
  for (int i = 0; i < count; i++) {
    itemSum += output[i];
  }


  int index = 0;
  bool toggle = true;
  bool bitCharArray[itemSum];

  for (int j = 0; j < count; j++) {

    for (int i = 0; i < output[j]; i++) {
      if (toggle) {
        // Serial.print('1');

        bitArray[(posY + row - 1) * 400 + (posX + colum - 1)] = false;
        // Serial.print((posY + row - 1)*w + (posX + colum - 1));
        // Serial.print(" - ");
      } else {
        //Serial.print('0');
        //  bitArray[(posY + row - 1)*400 + (posX + colum - 1)] = true;
        // Serial.print((posY + row - 1)*w + (posX + colum - 1));
        // Serial.print(" - ");
      }

      colum++;
      if (colum == w) {
        // Serial.println();
        // Serial.print(row);
        // Serial.print(" ------ ");
        colum = 0;
        row++;
      }
    }

    if (toggle) {
      toggle = false;
    } else {
      toggle = true;
    }
  }
}















///////////////////EXTERNAL FUNCTION////////////////////////////////////////////////////////////////////////
/////////////////////delay//////////////////////////////////////
void driver_delay_us(unsigned int xus)  //1us
{
  for (; xus > 1; xus--)
    ;
}
void driver_delay_xms(unsigned long xms)  //1ms
{
  unsigned long i = 0, j = 0;

  for (j = 0; j < xms; j++) {
    for (i = 0; i < 256; i++)
      ;
  }
}
void DELAY_S(unsigned int delaytime) {
  int i, j, k;
  for (i = 0; i < delaytime; i++) {
    for (j = 0; j < 4000; j++) {
      for (k = 0; k < 222; k++)
        ;
    }
  }
}
//////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate) {
  unsigned char i;
  while (xrate) {
    for (i = 0; i < 2; i++)
      ;
    xrate--;
  }
}


void SPI_Write(unsigned char value) {
  unsigned char i;
  SPI_Delay(1);
  for (i = 0; i < 8; i++) {
    EPD_W21_CLK_0;
    SPI_Delay(1);
    if (value & 0x80)
      EPD_W21_MOSI_1;
    else
      EPD_W21_MOSI_0;
    value = (value << 1);
    SPI_Delay(1);
    driver_delay_us(1);
    EPD_W21_CLK_1;
    SPI_Delay(1);
  }
}

void EPD_W21_WriteCMD(unsigned char command) {
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_0;  // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command) {
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_1;  // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}



/////////////////EPD settings Functions/////////////////////
void EPD_W21_Init(void) {
  EPD_W21_RST_0;  // Module reset
  delay(100);     //At least 10ms
  EPD_W21_RST_1;
  delay(100);
}





void EPD_init(void) {
  EPD_W21_Init();  //Electronic paper IC reset

  /*
  EPD_W21_WriteCMD(0x06);   //boost soft start
  EPD_W21_WriteDATA(0x17);  //A
  EPD_W21_WriteDATA(0x17);  //B
  EPD_W21_WriteDATA(0x17);  //C
  */

  EPD_W21_WriteCMD(0x04);  //Power on

  Serial.println("DISPLAY INIT");

  lcd_chkstatus();  //waiting for the electronic paper IC to release the idle signal

  EPD_W21_WriteCMD(0x00);   //panel setting
  EPD_W21_WriteDATA(0x1f);  //LUT from OTP
  EPD_W21_WriteDATA(0x0d);  //VCOM to 0V
}


void EPD_refresh(void) {
  EPD_W21_WriteCMD(0x12);  //DISPLAY REFRESH
  driver_delay_xms(500);   //!!!The delay here is necessary, 200uS at least!!!

  Serial.println("DISPLAY REFRESH");

  lcd_chkstatus();
}


void EPD_sleep(void) {
  EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING
  EPD_W21_WriteDATA(0xf7);

  EPD_W21_WriteCMD(0X02);  //power off

  lcd_chkstatus();
  EPD_W21_WriteCMD(0X07);  //deep sleep
  EPD_W21_WriteDATA(0xA5);
}





void PIC_display_Clean(void) {
  unsigned int i;


  EPD_W21_WriteCMD(0x10);  //Transfer old data
  for (i = 0; i < 15000; i++) {
    EPD_W21_WriteDATA(0xff);
  }



  EPD_W21_WriteCMD(0x13);  //Transfer new data
  for (i = 0; i < 15000; i++) {
    EPD_W21_WriteDATA(0xff);
  }

  Serial.println("DISPLAY CLEAN");
}



void lcd_chkstatus(void) {

  unsigned char busy;
  int timer = millis();

  if (!interacation) {

    do {
      EPD_W21_WriteCMD(0x71);
      busy = isEPD_W21_BUSY;
      busy = !(busy & 0x01);
    } while (busy && millis() - timer < 10000);
    // } while (busy);
  }

  driver_delay_xms(500);


  //delay(200);
}
