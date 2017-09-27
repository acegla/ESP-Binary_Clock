#include <NeoPixelBus.h>

const uint16_t PixelCount = 18;

// setup where are your bits on leds
const int h_leds_id[] = {12, 13, 14, 15, 16, 17}; // hours
const int m_leds_id[] = {6, 7, 8, 9, 10, 11};     // minutes
const int s_leds_id[] = {0, 1, 2, 3, 4, 5};       // seconds

const int * leds_id[] = {h_leds_id, m_leds_id, s_leds_id};

#define colorLightness (0.8f)
#define colorOffset 15
#define colorStart 120

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
NeoGamma<NeoGammaTableMethod> colorGamma;


void leds_setup() {
  strip.Begin();
  Serial.println("Leds init");

}

void leds_loop() {
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();
  int s = timeClient.getSeconds();

  int timeItems[] = {h, m, s};

  int __hue = colorStart;
  for (int c = 0; c < 3; ++c)
    for (int i = 0; i < 6; ++i) {
      float hue = ((__hue) % 360) / 360.0;
      __hue += colorOffset;
      RgbColor active_color = HsbColor(hue, 1.0f, colorLightness);
      RgbColor inactive_color = HsbColor(hue, 1.0f, colorLightness / 25.0);
      if ((timeItems[c] >> i) & 1)
        strip.SetPixelColor(leds_id[c][i], colorGamma.Correct(active_color));
      else
        strip.SetPixelColor(leds_id[c][i], colorGamma.Correct(inactive_color));
    }

  strip.Show();
}

