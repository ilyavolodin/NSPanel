#include <cmath>

typedef struct {
    int r;
    int g;
    int b;
} RgbColor;

typedef struct {
    double hue;
    double saturation;
    double value;
} HsvColor;

double rad2deg(float rad) {
    return fmod((360 + 180 * rad / 3.14159265359), 360.0);
}

RgbColor hsv2rgb(HsvColor color) {
    double hue = color.hue / 60;
    float chroma = (color.value * color.saturation);
    float x = chroma * (1 - std::abs(fmod(hue, 2.0) - 1));
    float valueChroma = color.value * 255;
    float valueX = (x + color.value - chroma) * 255;
    float valueZero = (color.value - chroma) * 255;
    RgbColor rgb;
    if (hue <= 1) {
        rgb.r = round(valueChroma);
        rgb.g = round(valueX);
        rgb.b = round(valueZero);
    } else if (hue <= 2) {
        rgb.r = round(valueX);
        rgb.g = round(valueChroma);
        rgb.b = round(valueZero);
    } else if (hue <= 3) {
        rgb.r = round(valueZero);
        rgb.g = round(valueChroma);
        rgb.b = round(valueX);
    } else if (hue <= 4) {
        rgb.r = round(valueZero);
        rgb.g = round(valueX);
        rgb.b = round(valueChroma);
    } else if (hue <= 5) {
        rgb.r = round(valueX);
        rgb.g = round(valueZero);
        rgb.b = round(valueChroma);
    } else {
        rgb.r = round(valueChroma);
        rgb.g = round(valueZero);
        rgb.b = round(valueX);
    }
    return rgb;
}

RgbColor rectToRGB(float x, float y) {
    double r = sqrt(x*x + y*y);
    float sat = 0;
    if (r > 1) {
        sat = 0;
    } else {
        sat = r;
    }
    HsvColor hsv = {rad2deg(atan2(y, x)), sat, 1};
    RgbColor rgb = hsv2rgb(hsv);
    return rgb;
}

RgbColor posToColor(float x, float y) {
    float r = 213.0f / 2.0f;
    float posX = round((x - r) / r * 100) / 100;
    float posY = round((r - y) / r * 100) / 100;

    RgbColor rgb = rectToRGB(posX, posY);
    return rgb;
}
