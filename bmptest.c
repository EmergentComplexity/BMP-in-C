#include <stdio.h>



int main() {

    char header[54] = { 
        0x42, 0x4D, 
        0xE6, 0x71, 0x0B, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x36, 0x00, 0x00, 0x00,
        0x28, 0x00, 0x00, 0x00,
        0xF4, 0x01, 0x00, 0x00,
        0xF4, 0x01, 0x00, 0x00,
        0x01, 0x00,
        0x18, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0xB0, 0x71, 0x0B, 0x00,
        0xC4, 0x0E, 0x00, 0x00,
        0xC4, 0x0E, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    FILE *fp;
    fp = fopen("test.bmp", "w+");
    for(int i = 0; i < 54; i++) {
        fputc(header[i], fp);
    }

    for(int i = 0; i < (100*500); i++) {
        fputc(255, fp);
        fputc(0, fp);
        fputc(0, fp);
    }
    for(int i = 0; i < (100*500); i++) {
        fputc(120, fp);
        fputc(120, fp);
        fputc(0, fp);
    }
    for(int i = 0; i < (100*500); i++) {
        fputc(0, fp);
        fputc(255, fp);
        fputc(0, fp);
    }
    for(int i = 0; i < (100*500); i++) {
        fputc(0, fp);
        fputc(120, fp);
        fputc(120, fp);
    }
    for(int i = 0; i < (100*500); i++) {
        fputc(0, fp);
        fputc(0, fp);
        fputc(255, fp);
    }
  


    
}