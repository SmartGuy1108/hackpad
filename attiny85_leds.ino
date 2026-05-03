#include <tinyNeoPixel_Static.h>

#define LED_PIN      3
#define NUM_LEDS     9
#define LED_TYPE     NEO_GRB
#define BRIGHTNESS   80

#define RAINBOW_DURATION_MS  5000UL
#define RAINBOW_STEP_MS      20UL
#define BREATHE_STEP_MS      15UL

#define BREATHE_MIN    2
#define BREATHE_MAX    200

#define BREATHE_R      0
#define BREATHE_G      0
#define BREATHE_B      255

byte pixelBuffer[NUM_LEDS * 3];

tinyNeoPixel strip = tinyNeoPixel(
    NUM_LEDS,
    LED_PIN,
    LED_TYPE,
    pixelBuffer
);

enum State { RAINBOW, BREATHING };
State currentState = RAINBOW;

unsigned long lastStepTime = 0;
uint8_t rainbowOffset = 0;
int16_t breathLevel   = BREATHE_MIN;
int8_t  breathDir     = 1;

void setup() {
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.clear();
    strip.show();
    lastStepTime = millis();
}

void loop() {
    unsigned long now = millis();

    if (currentState == RAINBOW && now >= RAINBOW_DURATION_MS) {
        currentState  = BREATHING;
        breathLevel   = BREATHE_MIN;
        breathDir     = 1;
        lastStepTime  = now;
        strip.clear();
        strip.show();
    }

    if (currentState == RAINBOW) {
        updateRainbow(now);
    } else {
        updateBreathing(now);
    }
}

void updateRainbow(unsigned long now) {
    if (now - lastStepTime < RAINBOW_STEP_MS) return;
    lastStepTime = now;

    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        uint8_t hue = rainbowOffset + (uint8_t)(i * (256UL / NUM_LEDS));
        strip.setPixelColor(i, wheelColor(hue));
    }

    strip.show();
    rainbowOffset += 2;
}

void updateBreathing(unsigned long now) {
    if (now - lastStepTime < BREATHE_STEP_MS) return;
    lastStepTime = now;

    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i,
            scaleColor(BREATHE_R, BREATHE_G, BREATHE_B, breathLevel));
    }
    strip.show();

    breathLevel += breathDir;

    if (breathLevel >= BREATHE_MAX) {
        breathLevel = BREATHE_MAX;
        breathDir   = -1;
    } else if (breathLevel <= BREATHE_MIN) {
        breathLevel = BREATHE_MIN;
        breathDir   = 1;
    }
}

uint32_t wheelColor(uint8_t pos) {
    if (pos < 85) {
        return strip.Color(255 - pos * 3, pos * 3, 0);
    } else if (pos < 170) {
        pos -= 85;
        return strip.Color(0, 255 - pos * 3, pos * 3);
    } else {
        pos -= 170;
        return strip.Color(pos * 3, 0, 255 - pos * 3);
    }
}

uint32_t scaleColor(uint8_t r, uint8_t g, uint8_t b, uint8_t scale) {
    uint8_t rs = ((uint16_t)r * scale) >> 8;
    uint8_t gs = ((uint16_t)g * scale) >> 8;
    uint8_t bs = ((uint16_t)b * scale) >> 8;
    return strip.Color(rs, gs, bs);
}
