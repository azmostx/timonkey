#include <graphx.h>
#include <ti/getcsc.h>
#include "Standard.h"
#include <sys/rtc.h>
#include <sys/timers.h>

#define ONE_SECOND      32768
#define MAIN_GREY   0
#define SUB_GREY    1
#define WHITE   2
#define YELLOW  3
#define RED 4

void begin();

void end();

bool step();

void draw();

void generateToken(char line[]);

bool correctTokenTracker[5][10];
bool shouldItRun;
bool resultsScreen;
char tokens[5][11];
int currentIndexOfNumber;
int wrongTyped;
int totalTyped;
unsigned int timer;
unsigned int durationOfTimer;

int main() {
    timer_Disable(1);
    srand(rtc_Time());
    durationOfTimer = 30;
    begin();
    gfx_Begin();
    gfx_ZeroScreen();
    gfx_SetDrawBuffer();
    gfx_palette[MAIN_GREY] = gfx_RGBTo1555(50, 52, 55);
    gfx_palette[SUB_GREY] = gfx_RGBTo1555(100, 102, 105);
    gfx_palette[WHITE] = gfx_RGBTo1555(209, 208, 197);
    gfx_palette[YELLOW] = gfx_RGBTo1555(226, 183, 20);
    gfx_palette[RED] = gfx_RGBTo1555(202, 71, 84);
    timer_Set(1, ONE_SECOND);
    timer_SetReload(1, ONE_SECOND);

    bool isItRunning = false;
    resultsScreen = false;
    while (step()) {
        if (shouldItRun && !isItRunning) {
            isItRunning = true;
            timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);
        }
        if (timer == 0) {
            resultsScreen = true;
            begin();
        }
        if (!shouldItRun && isItRunning) {
            isItRunning = false;
            timer_Disable(1);
        }
        if (isItRunning && timer_ChkInterrupt(1, TIMER_RELOADED)) {
            timer--;
            timer_AckInterrupt(1, TIMER_RELOADED);
        }
        gfx_BlitScreen();
        draw();
        gfx_SwapDraw();
    }
    gfx_End();
    end();
    return 0;
}

void begin() {
    for (int i = 0; i < 10; i++) {
        tokens[0][i] = ' ';
        tokens[1][i] = ' ';
    }
    tokens[0][10] = '\0';
    tokens[1][10] = '\0';
    for (int i = 2; i < 5; i++) {
        generateToken(tokens[i]);
    }
    currentIndexOfNumber = 0;
    timer = durationOfTimer;
    shouldItRun = false;
    if (!resultsScreen) {
        wrongTyped = 0;
        totalTyped = 0;
    }
}

void end() {
}

bool step() {
    sk_key_t key = os_GetCSC();
    if (resultsScreen) {
        if (key == sk_Alpha) {
            resultsScreen = false;
            wrongTyped = 0;
            totalTyped = 0;
        }
        if (key == sk_Mode) return false;
        return true;
    }
    if (!shouldItRun && key == sk_Left) {
        if (durationOfTimer > 15) durationOfTimer /= 2;
        timer = durationOfTimer;
        return true;
    }
    if (!shouldItRun && key == sk_Right) {
        if (durationOfTimer < 960) durationOfTimer *= 2;
        timer = durationOfTimer;
        return true;
    }
    if (key == sk_Alpha) {
        begin();
        return true;
    }
    if (key == sk_Mode) return false;
    if (key == sk_Enter) {
        if (currentIndexOfNumber != 10) return true;
        bool isDone = true;
        for (int i = 0; i < 10 && isDone; i++) isDone = correctTokenTracker[2][i];
        if (!isDone) return true;
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                tokens[i - 1][j] = tokens[i][j];
                correctTokenTracker[i - 1][j] = correctTokenTracker[i][j];
            }
        }
        generateToken(tokens[4]);
        currentIndexOfNumber = 0;
        return true;
    }
    if (key == sk_Left || key == sk_Del) {
        if (currentIndexOfNumber > 0) {
            currentIndexOfNumber--;
            totalTyped--;
        }
        return true;
    }
    if (key == sk_Clear) {
        totalTyped -= currentIndexOfNumber;
        currentIndexOfNumber = 0;
        return true;
    }
    if (currentIndexOfNumber == 10) return true;
    if (key == sk_0) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '0';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_1) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '1';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_2) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '2';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_3) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '3';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_4) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '4';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_5) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '5';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_6) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '6';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_7) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '7';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_8) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '8';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_9) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '9';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_DecPnt) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '.';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    if (key == sk_Chs) {
        correctTokenTracker[2][currentIndexOfNumber] = tokens[2][currentIndexOfNumber] == '-';
        if (!correctTokenTracker[2][currentIndexOfNumber]) wrongTyped++;
        totalTyped++;
        currentIndexOfNumber++;
        shouldItRun = true;
    }
    return true;
}

void draw() {
    gfx_SetColor(MAIN_GREY);
    gfx_FillRectangle(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT);
    gfx_SetFontData(font);
    gfx_SetMonospaceFont(8);
    if (resultsScreen) {
        gfx_SetTextFGColor(YELLOW);
        gfx_SetTextScale(2, 2);
        gfx_SetTextXY(96, 88);
        gfx_PrintString("CPM: ");
        gfx_SetTextXY(186, 88);
        if (totalTyped - wrongTyped < 0) wrongTyped = totalTyped;
        gfx_PrintInt((totalTyped - wrongTyped) * ((int) (60 / (float) durationOfTimer)), 3);
        gfx_SetTextXY(88, 112);
        gfx_PrintString("ACC: ");
        gfx_SetTextXY(178, 112);
        int percent = totalTyped ? (int) (100 - wrongTyped * 100.f / totalTyped) : 0;
        if (percent < 0) percent = 0;
        gfx_PrintInt(percent, 3);
        gfx_SetTextXY(226, 112);
        gfx_PrintChar('%');
        gfx_SetTextXY(80, 136);
        gfx_PrintString("TIME: ");
        gfx_SetTextXY(176, 136);
        gfx_PrintUInt(durationOfTimer, 3);
        gfx_SetTextXY(224, 136);
        gfx_PrintChar('s');
        gfx_SetTextScale(1, 1);
        gfx_SetTextXY(104, 170);
        gfx_PrintString("Restart: alpha");
        gfx_SetTextXY(120, 182);
        gfx_PrintString("Quit: mode");
        return;
    }
    gfx_SetTextXY(40, 88);
    gfx_SetTextFGColor(YELLOW);
    gfx_SetTextScale(1, 1);
    gfx_PrintUInt(timer, 2);
    if (!shouldItRun) {
        gfx_SetTextXY(36, 224);
        gfx_PrintString("Change Time: < & > | Quit: mode");
    } else {
        gfx_SetTextXY(52, 224);
        gfx_PrintString("Restart: alpha | Quit: mode");
    }
    gfx_SetTextXY(120, 64);
    gfx_PrintString(tokens[0]);
    gfx_SetTextXY(120, 168);
    gfx_SetTextFGColor(SUB_GREY);
    gfx_PrintString(tokens[4]);
    gfx_SetTextScale(2, 2);
    gfx_SetTextXY(80, 80);
    gfx_SetTextFGColor(YELLOW);
    gfx_PrintString(tokens[1]);
    gfx_SetTextXY(80, 144);
    gfx_SetTextFGColor(SUB_GREY);
    gfx_PrintString(tokens[3]);
    gfx_SetTextScale(3, 3);
    int x = 40;
    for (int i = 0; i < currentIndexOfNumber; i++) {
        gfx_SetTextXY(x, 108);
        if (correctTokenTracker[2][i]) gfx_SetTextFGColor(WHITE);
        else gfx_SetTextFGColor(RED);
        gfx_PrintChar(tokens[2][i]);
        x += 24;
    }
    gfx_SetTextFGColor(SUB_GREY);
    for (int i = currentIndexOfNumber; i < 10; i++) {
        gfx_SetTextXY(x, 108);
        gfx_PrintChar(tokens[2][i]);
        x += 24;
    }
    gfx_SetColor(SUB_GREY);
    gfx_Rectangle(36, 104, 248, 32);
}

void generateToken(char line[]) {
    int i = 0;
    bool negative = rand() % 2 == 0;
    if (negative) {
        line[0] = '-';
        i = 1;
    }
    int decimal = rand() % 8;
    for (; i < 10; i++) {
        line[i] = !decimal ? '.' : (rand() % 10 + '0');
        decimal--;
    }
    line[10] = '\0';
}