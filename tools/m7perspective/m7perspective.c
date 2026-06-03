#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
    int scale = 1;
    float zoom = 1;

    int baseXScale = 512;
    float stepXZoom = 0.025;
    int baseYScale = 4096;
    float stepYZoom = 0.05;

    if(argc > 1 && argc <= 5){
        if(argc >= 2){ baseXScale = atoi(argv[1]); }
        if(argc >= 3){ stepXZoom = atof(argv[2]); }
        if(argc >= 4){ baseYScale = atoi(argv[3]); }
        if(argc >= 5){ stepYZoom = atof(argv[4]); }
    }

    char* filename = "perspective.txt";
    
    if(remove(filename) == 0){
        printf("removed %s\n", filename);
    }

    FILE *fout;
    fout = fopen(filename, "w");

    int valuesPerRow = 16;

    //X
    zoom = 1;
    // fprintf(fout,"////////\n////////\n  X\n");
    fprintf(fout, "const u8 perspectiveX[264] = {\nSKYLINEY, 256 & 255, 256 >> 8, 0xFF, \n");
    int xItems = valuesPerRow;
    for (int i = 0; i != 128; i++){
        fprintf(fout, "%i, %i", scale&255, scale/256);
        scale = (int) (baseXScale / zoom);
        zoom+=stepXZoom;

        if(i != 127){
            fprintf(fout,", ");
        }

        xItems -= 2;
        if(xItems == 0){
            fprintf(fout,"\n");
            xItems = valuesPerRow;
        }
    }
    fprintf(fout, "};\n\n");

    //Y
    zoom = 1;
    // fprintf(fout,"////////\n////////\n  Y\n");
    fprintf(fout, "const u8 perspectiveY[264] = {\nSKYLINEY, 256 & 255, 256 >> 8, 0xFF, \n");
    int yItems = valuesPerRow;
    for (int i = 0; i != 128; i++){
        fprintf(fout, "%i, %i", scale&255, scale/256);
        scale = (int) (baseYScale / zoom);
        zoom+=stepYZoom;

        if(i != 127){
            fprintf(fout,", ");
        }

        yItems -= 2;
        if(yItems == 0){
            fprintf(fout,"\n");
            yItems = valuesPerRow;
        }
    }
    fprintf(fout, "};\n\n");

    fclose(fout);

    return 0;
}