#ifndef CONVERTRGBA_H
#define CONVERTRGBA_H

// Function to convert RGBA values to normalized float values (0 to 1).
void convertRGBA(float &colorR, float &colorG, float &colorB, unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
    colorR = R / 255.0f;
    colorG = G / 255.0f;
    colorB = B / 255.0f;
}
#endif // CONVERTRGBA_H
