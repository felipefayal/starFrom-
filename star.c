#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h> 

#define WIDTH 80
#define HEIGHT 24
#define SCREEN_SIZE (WIDTH * HEIGHT)

#define COR_ESCOLHIDA 0

float A = 0, B = 0;
float z[SCREEN_SIZE]; 
char b[SCREEN_SIZE];  

const char* CORES[] = {
    "\x1b[0m", 
    "\x1b[32m", 
    "\x1b[33m", 
    "\x1b[35m", 
    "\x1b[36m", 
    "\x1b[31m"  
};

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    float i, j;
    int k;
    int frame_count = 0; 
    
    system("cls");
    hideCursor();

    for (;;) {
        memset(b, 32, SCREEN_SIZE); 
        memset(z, 0, sizeof(z));    

        for (i = 0; i < 6.28; i += 0.02) {
            float R = 3.8 + 1.4 * sin(5 * i);

            for (j = 0; j < 6.28; j += 0.05) {
                float c = sin(i), d = cos(j), f = sin(j);
                float e = sin(A), g = cos(A);
                float m = cos(B), n = sin(B);
                float h = d + R;
                
                float D = 1 / (c * h * e + f * g + 13); 
                float l = cos(i);
                float t = c * h * g - f * e;

                int x = 40 + 34 * D * (l * h * m - t * n);
                int y = 12 + 17 * D * (l * h * n + t * m);

                int o = x + WIDTH * y;
                
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                if (HEIGHT > y && y > 0 && x > 0 && WIDTH > x && D > z[o]) {
                    z[o] = D;
                    int luminance_index = N > 0 ? N : 0;
                    char *pixel = ".,-~:;=!*#$@"; 
                    if (luminance_index > 11) luminance_index = 11;
                    b[o] = pixel[luminance_index];
                }
            }
        }

        gotoxy(0, 0); 

        if (COR_ESCOLHIDA == 0) {
            int cor_atual = (frame_count / 10) % 5 + 1;
            printf("%s", CORES[cor_atual]);
        } else {
            printf("%s", CORES[COR_ESCOLHIDA]);
        }

        for(k = 0; k < SCREEN_SIZE; k++) {
            if (k % WIDTH == WIDTH - 1) b[k] = '\n';
        }
        
        fwrite(b, 1, SCREEN_SIZE, stdout);

        A += 0.04; 
        B += 0.02;
        frame_count++;
        
        Sleep(16); 
    }
    return 0;
}