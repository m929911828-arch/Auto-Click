#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TARGET_X 1060
#define TARGET_Y 488
#define RED_R 206
#define RED_G 38
#define RED_B 54
#define GREEN_R 75
#define GREEN_G 219
#define GREEN_B 106
#define TOLERANCE 20
#define CHECK_INTERVAL 50

bool isColorMatch(COLORREF color, int r, int g, int b, int tolerance) {
    int cr = GetRValue(color);
    int cg = GetGValue(color);
    int cb = GetBValue(color);
    return abs(cr - r) <= tolerance && abs(cg - g) <= tolerance && abs(cb - b) <= tolerance;
}

void mouseClick(int x, int y) {
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    printf("Clicked at (%d, %d)\n", x, y);
}

int main() {
    HDC hScreen = GetDC(NULL);
    if (!hScreen) {
        printf("Failed to get screen DC!\n");
        system("pause");
        return 1;
    }

    bool wasRed = false;
    printf("========== Color Click Script ==========\n");
    printf("Monitoring at: (%d, %d)\n", TARGET_X, TARGET_Y);
    printf("Color tolerance: %d\n", TOLERANCE);
    printf("Press Ctrl+C to stop.\n");
    printf("========================================\n\n");

    while (1) {
        COLORREF pixel = GetPixel(hScreen, TARGET_X, TARGET_Y);

        if (isColorMatch(pixel, RED_R, RED_G, RED_B, TOLERANCE)) {
            wasRed = true;
        } else if (wasRed && isColorMatch(pixel, GREEN_R, GREEN_G, GREEN_B, TOLERANCE)) {
            mouseClick(TARGET_X, TARGET_Y);
            wasRed = false;
        }

        Sleep(CHECK_INTERVAL);
    }

    ReleaseDC(NULL, hScreen);
    return 0;
}
