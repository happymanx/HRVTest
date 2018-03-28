
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "statnn.h"
#include "pwr.h"

#define SIZEX 1000
char linex[SIZEX];

void splitx(char **arr, char *str, const char *del) {
    char *s = strtok(str, del);

    while(s != NULL) {
        *arr++ = s;
        s = strtok(NULL, del);
    }
}

int main()
{
    fstream fin;
    fin.open("foo.frr",ios::in);
    int number = 0;
    while(fin.getline(linex,sizeof(linex),'\n')){
        number++;
    }
    double inputData[number][3];

    int i = 0;
    
    while(fin.getline(linex,sizeof(linex),'\n')){
        number++;


        char *arr[3];
        const char *del = " ";
        splitx(arr, linex, del);
        
        inputData[i][0] = atof(arr[0]);
        inputData[i][1] = atof(arr[1]);
        inputData[i][2] = atof(arr[2]);

        i++;
    }


    printf("#Time Domain\n");
    double *timeResult = getTimeResult(number, 3, inputData);
    for (int i = 0; i < 7; i++) {
        printf("%g", timeResult[i]);
        printf("\n");
    }
    
    printf("#Frequency Domain\n");
    double *frequencyResult = getFrequencyResult();
    for (int i = 0; i < 6; i++) {
        printf("%g", frequencyResult[i]);
        printf("\n");
    }

    return 1;
}

