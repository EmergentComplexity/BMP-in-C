// make a bitmap BMP image
//   - this code produces and image of 5 rows going from blue at the bottom to red at the top
//   - image size is defined by variables
//
// Author: Peter Sanchez
// Date: 9_4_2022

#include <stdio.h>

int height = 300; // must be divisable by 5 since we are making 5 rows
int width = 15;

// fill 4 bytes in the header array given an int. 
// bytes in a BMP file are written like this:
// (16^1 + 16^0)   (16^3 + 16^2)   (16^5 + 16^4) (16^7 + 16^6)
// 
void fillHeaderVal( int val,int placeHigh, unsigned char* header) {
   
    header[placeHigh] = ((val & 0xFF000000) >> (6*4));
    printf("\n %X  ", ((val & 0xFF000000) >> (6*4)));
    header[placeHigh - 1] = ((val & 0x00FF0000) >> (4*4));
     printf("%X  ", ((val & 0x00FF0000) >> (4*4)));
    header[placeHigh - 2] = ((val & 0x0000FF00) >> (2*4));
     printf("%X  ", ((val & 0x0000FF00) >> (2*4)));
    header[placeHigh - 3] = (val & 0x000000FF);
     printf("%X  \n", (val & 0x000000FF));

}


int main() {

    // BMP images have a 54 byte header
    unsigned char header[54] = { 
        0x42, 0x4D, // "BM"
        0, 0, 0, 0, // image size with header
        0x00, 0x00,
        0x00, 0x00,
        0x36, 0x00, 0x00, 0x00,
        0x28, 0x00, 0x00, 0x00,
        0, 0, 0, 0, // width
        0, 0, 0, 0, // height
        0x01, 0x00,
        0x18, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0, 0, 0, 0, // image size excluding header

        0xC4, 0x0E, 0x00, 0x00,
        0xC4, 0x0E, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    int bitmapSize = 3 * width * height;
    int fileSize = bitmapSize + 54;
    fillHeaderVal(fileSize, 5, header);
    printf("%X \n", fileSize );
    printf("%X %X %X %X ", header[2], header[3], header[4], header[5]);
    fillHeaderVal(width, 21, header);
    fillHeaderVal(height, 25, header);
    fillHeaderVal(bitmapSize, 37, header);

    // Add padding so that each line width in bytes is multiple of 4 even if the pixel width is not
    //    - 3 colors, R, G, B, so lines take 3*width bytes
    //    - the line width in bytes % 4 gives us the distance from the last multiple of 4
    //    - then subtract this from 4 to get the distance to the next multiple of 4 and therefore the padding
    int padding =(4 -  ((3 * width)  % 4)); 
    if(padding == 4) {  // do not add padding if line width in bytes is already multiple of 4
        padding = 0;
    }


    FILE *fp;
    fp = fopen("test2.bmp", "wb"); // write in binary mode 

    // write the header out to the file
    for(int i = 0; i < 54; i++) {
        fputc(header[i], fp);
        printf("%X ", header[i] );
    }

    // make blue row 
    for(int i = 0; i < ((height/5) *width); i++) {
        fputc(255, fp); // blue
        fputc(0, fp);   // green
        fputc(0, fp);   // red
        if(((i +1) % width == 0)   ) { // add padding when width is reached
            for( int j = 0; j < padding; j++) {
                    fputc(0, fp);
            }
        }
    }
    
    // make blue-green row
    for(int i = 0; i < ((height/5)*width); i++) {
        fputc(120, fp);
        fputc(120, fp);
        fputc(0, fp);
        if((i + 1) % width == 0) {
            for( int j = 0; j < padding; j++) {
                fputc(0, fp);
            }
        }
    }

    // make green row
    for(int i = 0; i < ((height/5)*width); i++) {
        fputc(0, fp);
        fputc(255, fp);
        fputc(0, fp);
        if((i+ 1) % width == 0) {
            for( int j = 0; j < padding; j++) {
                fputc(0, fp);
            }
        }
    }

    // make green-red row
    for(int i = 0; i < ((height/5)*width); i++) {
        fputc(0, fp);
        fputc(120, fp);
        fputc(120, fp);
        if((i + 1) % width == 0) {
            for( int j = 0; j < padding; j++) {
                fputc(0, fp);
            }
        }
    }

    // make red row
    for(int i = 0; i < ((height/5)*width); i++) {
        fputc(0, fp);
        fputc(0, fp);
        fputc(255, fp);
        if(i % width == 0) {
            for( int j = 0; j < padding; j++) {
                fputc(0, fp);
            }
        }
    }
  
}