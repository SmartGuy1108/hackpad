#include "Adafruit_TinyUSB.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define OLED_I2C_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

#define NUM_KEYS 9

const uint8_t KEY_PINS[NUM_KEYS] = {
  26, 27, 28, 29, 0, 1, 2, 4, 3
};

#define LAYER_KEY_INDEX 8

#define DEBOUNCE_MS 5

struct KeyState {
  bool     currentState;
  bool     rawState;
  uint32_t lastChangeMs;
  bool     justPressed;
  bool     justReleased;
};

KeyState keys[NUM_KEYS];

#define MOD_NONE   0x00
#define MOD_LCTRL  0x01
#define MOD_LSHIFT 0x02
#define MOD_LALT   0x04
#define MOD_LGUI   0x08

#define HID_KEY_F13 0x68
#define HID_KEY_F14 0x69
#define HID_KEY_F15 0x6A
#define HID_KEY_F16 0x6B
#define HID_KEY_F17 0x6C
#define HID_KEY_F18 0x6D
#define HID_KEY_F19 0x6E
#define HID_KEY_F20 0x6F
#define HID_KEY_F21 0x70

#define HID_KEY_Z 0x1D
#define HID_KEY_Y 0x1C
#define HID_KEY_S 0x16
#define HID_KEY_C 0x06
#define HID_KEY_V 0x19
#define HID_KEY_X 0x1B
#define HID_KEY_A 0x04
#define HID_KEY_F21_CODE HID_KEY_F21

struct MacroDef {
  const char* name;
  uint8_t     modifier;
  uint8_t     keycode;
};

const MacroDef LAYER_0[NUM_KEYS] = {
  { "F13",  MOD_NONE,  HID_KEY_F13 },
  { "F14",  MOD_NONE,  HID_KEY_F14 },
  { "F15",  MOD_NONE,  HID_KEY_F15 },
  { "F16",  MOD_NONE,  HID_KEY_F16 },
  { "F17",  MOD_NONE,  HID_KEY_F17 },
  { "F18",  MOD_NONE,  HID_KEY_F18 },
  { "F19",  MOD_NONE,  HID_KEY_F19 },
  { "F20",  MOD_NONE,  HID_KEY_F20 },
  { "[FN]", MOD_NONE,  0x00        },
};

const MacroDef LAYER_1[NUM_KEYS] = {
  { "Undo",    MOD_LCTRL,  HID_KEY_Z        },
  { "Redo",    MOD_LCTRL,  HID_KEY_Y        },
  { "Save",    MOD_LCTRL,  HID_KEY_S        },
  { "Copy",    MOD_LCTRL,  HID_KEY_C        },
  { "Paste",   MOD_LCTRL,  HID_KEY_V        },
  { "Cut",     MOD_LCTRL,  HID_KEY_X        },
  { "Sel All", MOD_LCTRL,  HID_KEY_A        },
  { "F21",     MOD_NONE,   HID_KEY_F21_CODE },
  { "[FN]",    MOD_NONE,   0x00             },
};

const MacroDef* LAYERS[2] = { LAYER_0, LAYER_1 };
const char*     LAYER_NAMES[2] = { "BASE", "FN" };

uint8_t currentLayer = 0;

uint8_t const hidDescriptor[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

Adafruit_USBD_HID usbHid(hidDescriptor, sizeof(hidDescriptor),
                          HID_ITF_PROTOCOL_KEYBOARD, 10, false);

String lastLayerName = "";
String lastKeyName   = "";

void initKeys();
void readKeys();
void sendHidKey(uint8_t modifier, uint8_t keycode);
void updateDisplay(const char* layerName, const char* keyName);

void setup() {
  Serial.begin(115200);

  usbHid.begin();

  uint32_t t = millis();
  while (!USBDevice.mounted() && millis() - t < 2000) {
    delay(10);
  }

  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
    pinMode(LED_BUILTIN, OUTPUT);
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH); delay(200);
      digitalWrite(LED_BUILTIN, LOW);  delay(200);
    }
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  initKeys();
  updateDisplay(LAYER_NAMES[currentLayer], "---");

  Serial.println("Macropad ready.");
}

void loop() {
  readKeys();

  uint8_t targetLayer = keys[LAYER_KEY_INDEX].currentState ? 1 : 0;
  if (targetLayer != currentLayer) {
    currentLayer = targetLayer;
    updateDisplay(LAYER_NAMES[currentLayer], "---");
  }

  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    if (!keys[i].justPressed) continue;
    if (i == LAYER_KEY_INDEX) continue;

    const MacroDef& macro = LAYERS[currentLayer][i];

    if (macro.keycode != 0x00) {
      sendHidKey(macro.modifier, macro.keycode);
      Serial.print("Key ");
      Serial.print(i + 1);
      Serial.print(" -> ");
      Serial.println(macro.name);
    }

    updateDisplay(LAYER_NAMES[currentLayer], macro.name);
  }

  delay(1);
}

void initKeys() {
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
    keys[i].currentState  = false;
    keys[i].rawState      = true;
    keys[i].lastChangeMs  = 0;
    keys[i].justPressed   = false;
    keys[i].justReleased  = false;
  }
}

void readKeys() {
  uint32_t now = millis();

  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    keys[i].justPressed  = false;
    keys[i].justReleased = false;

    bool newRaw = (digitalRead(KEY_PINS[i]) == LOW);

    if (newRaw != keys[i].rawState) {
      keys[i].rawState     = newRaw;
      keys[i].lastChangeMs = now;
    }

    if ((now - keys[i].lastChangeMs) >= DEBOUNCE_MS) {
      if (newRaw != keys[i].currentState) {
        keys[i].currentState = newRaw;
        if (newRaw) {
          keys[i].justPressed  = true;
        } else {
          keys[i].justReleased = true;
        }
      }
    }
  }
}

void sendHidKey(uint8_t modifier, uint8_t keycode) {
  if (!usbHid.ready()) return;

  uint8_t report[6] = { keycode, 0, 0, 0, 0, 0 };
  usbHid.keyboardReport(0, modifier, report);
  delay(12);
  usbHid.keyboardRelease(0);
  delay(5);
}

void updateDisplay(const char* layerName, const char* keyName) {
  String lName(layerName);
  String kName(keyName);

  if (lName == lastLayerName && kName == lastKeyName) return;

  lastLayerName = lName;
  lastKeyName   = kName;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("L: ");
  display.println(layerName);
  display.drawLine(0, 18, SCREEN_WIDTH - 1, 18, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 24);
  display.print("K: ");
  display.println(keyName);
  display.display();
}
