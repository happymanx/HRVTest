/* pwr.c        Joe Mietus        Oct 7 2008 */

/*
 pwr :
 Usage: pwr
 Calculate total (and relative) power in fft between lo and hi.
 
 Input:
 
 Output: Array[6]
 TOT PWR, ULF PWR, VLF PWR, LF PWR, HF PWR, LF/HF
 0~0.04, 0~0.0033, 0.0033~0.04, 0.04~0.15, 0.15~0.4, (0.04~0.15 / 0.15~0.4)
 */

#include <stdio.h>
#include <stdlib.h>
#include "pwr.h"

//extern "C"
//{
    #include "lomb.h"
//}

#define MAXBANDS 10

double *getFrequencyResult(int x, int y, double inputData[][2])
{
    double **powerData = getPowerResult(x, y, inputData);
    
    int n, nbands;
    double lo[MAXBANDS], hi[MAXBANDS], pr[MAXBANDS], tot;
    double freq[2], mag[2], pwr;
    
//    FILE *ifile;
//    ifile = fopen("foo.fft", "rt");
//
//    if (ifile == NULL) {
//        exit(1);
//    }
    
    nbands = 5;
    
    // TOT PWR
    lo[0] = 0.0;
    hi[0] = 0.04;
    // ULF PWR
    lo[1] = 0.0;
    hi[1] = 0.0033;
    // VLF PWR
    lo[2] = 0.0033;
    hi[2] = 0.04;
    // LF PWR
    lo[3] = 0.04;
    hi[3] = 0.15;
    // HF PWR
    lo[4] = 0.15;
    hi[4] = 0.4;
    
    tot = 0.0;
    
    freq[0] = powerData[0][0];
    mag[0] = powerData[0][1];
    freq[1] = powerData[1][0];
    mag[1] = powerData[1][1];

//    if (fscanf(ifile, "%lf%lf", &freq[0], &mag[0]) != 2)
//        exit(2);
//    if (fscanf(ifile, "%lf%lf", &freq[1], &mag[1]) != 2)
//        exit(2);
    
    pwr = mag[0]*mag[0];
    tot += pwr;
    for (n=0; n<nbands; n++) {
        if (freq[0] >= lo[n] && freq[0] <= hi[n])
            pr[n] += pwr;
    }
    freq[0] = freq[1];
    mag[0] = mag[1];
    
    for (int i = 2; i < x * 2; i++) {
        freq[1] = powerData[i][0];
        mag[1] = powerData[i][1];

        pwr = mag[0]*mag[0];
        tot += pwr;
        for (n=0; n<nbands; n++) {
            if (freq[0] >= lo[n] && freq[0] <= hi[n])
                pr[n] += pwr;
        }
        freq[0] = freq[1];
        mag[0] = mag[1];
    }
    
//    while (fscanf(ifile, "%lf%lf", &freq[1], &mag[1]) == 2) {
//        pwr = mag[0]*mag[0];
//        tot += pwr;
//        for (n=0; n<nbands; n++) {
//            if (freq[0] >= lo[n] && freq[0] <= hi[n])
//                pr[n] += pwr;
//        }
//        freq[0] = freq[1];
//        mag[0] = mag[1];
//    }
    
    pwr = mag[0]*mag[0];
    tot += pwr;
    for (n=0; n<nbands; n++) {
        if (freq[0] >= lo[n] && freq[0] <= hi[n])
            pr[n] += pwr;
    }
    
    printf("Total = %g\n", tot);
    for (n=0; n<nbands; n++) {
        printf("%g - %g = %g", lo[n], hi[n], pr[n]);
        printf("\n");
    }
    
    double TOT_PWR = pr[0];
    double ULF_PWR = pr[1];
    double VLF_PWR = pr[2];
    double LF_PWR = pr[3];
    double HF_PWR = pr[4];
    double LF_HF = pr[3]/pr[4];

    // TOT PWR, ULF PWR, VLF PWR, LF PWR, HF PWR, LF/HF
    static double frequency[F_RESULT_NUMBER];
    frequency[0] = TOT_PWR;
    frequency[1] = ULF_PWR;
    frequency[2] = VLF_PWR;
    frequency[3] = LF_PWR;
    frequency[4] = HF_PWR;
    frequency[5] = LF_HF;

    return frequency;
}
