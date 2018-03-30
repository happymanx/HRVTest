
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern "C"
{
    #include "statnn.h"
    #include "pwr.h"
    #import "lomb.h"
}

#define SIZE 1000
char line[SIZE];

void split(char **arr, char *str, const char *del) {
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
    while(fin.getline(line,sizeof(line),'\n')){
        number++;
    }
    /*
     ex: foo.frr
     0 0.600 N
     0.596 0.596 N
     1.188 0.592 N
     1.788 0.600 N
     ...
     */
    
    double inputDataForTimeDomain[number][3];

    int i = 0;
    
    fstream finx;
    finx.open("foo.frr",ios::in);
    int nnNumber = 0;
    int ssNumber = 0;
    char lastAnnotation = 'X';
    while(finx.getline(line,sizeof(line),'\n')){
        char *arr[3];
        const char *del = " ";
        split(arr, line, del);
        
        inputDataForTimeDomain[i][0] = atof(arr[0]);
        inputDataForTimeDomain[i][1] = atof(arr[1]);
        char annotation[10];
        strcpy(annotation, arr[2]);
        inputDataForTimeDomain[i][2] = (int)annotation[0];
        
        // 過濾RR為NN
        if (annotation[0] == 'N' && lastAnnotation == 'N') {
            nnNumber++;
        }
        if (annotation[0] == 'S') {
            ssNumber++;
        }
        lastAnnotation = annotation[0];

        i++;
    }
    printf("nnNumber: %i\n", nnNumber);
    printf("ssNumber: %i\n", ssNumber);
    printf("nn/rr ratio: %f\n", nnNumber/(double)number);


    printf("#Time Domain\n");
    double *timeResult = getTimeResult(number, 3, inputDataForTimeDomain);
    for (int i = 0; i < T_RESULT_NUMBER; i++) {
        printf("%g", timeResult[i]);
        printf("\n");
    }
    /*
     ex: foo.nn
     0.596 0.596
     1.188 0.592
     1.788 0.600
     2.392 0.604
     2.996 0.604
     3.588 0.592
     ...
     */
    double inputDataForFrequencyDomain[nnNumber][2];
    
    int j = 0;
    lastAnnotation = 'X';
    for (int i = 0; i < number; i++) {
        if (inputDataForTimeDomain[i][2] == 'N' && lastAnnotation == 'N') {
            inputDataForFrequencyDomain[j][0] = inputDataForTimeDomain[i][0];
            inputDataForFrequencyDomain[j][1] = inputDataForTimeDomain[i][1];

            j++;
        }
        lastAnnotation = inputDataForTimeDomain[i][2];
    }

    printf("#Frequency Domain\n");
    double *frequencyResult = getFrequencyResult(nnNumber, 2, inputDataForFrequencyDomain);

    for (int i = 0; i < F_RESULT_NUMBER; i++) {
        printf("%g", frequencyResult[i]);
        printf("\n");
    }

    return 1;
}

