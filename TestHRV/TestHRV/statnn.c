/* statnn.c        Joe Mietus        Oct 7 2008 */

/*
 statnn :
 Usage: statnn
 Reads stdin: time(sec), interval(sec), annotation and calculates nn interval stats
 Outputs: Array[6]
 nn/rr, avnn, sdnn, sdann, sdnnindx, rmssd and pnn on stderr
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "statnn.h"

#define MAXBUF 2400
#define MAXP 10
#define NNDIF 0.05
#define ABS(A) ((A) < 0 ? -(A) : (A))
#define ROFFERR 1e-10

//int main()
//{
//    double *result = getTimeResult();
//    for (int i = 0; i < T_RESULT_NUMBER; i++) {
//        printf("%g", result[i]);
//        printf("\n");
//    }
//
//    return 1;
//}


double *getTimeResult(int x, int y, double inputData[][3])
{
    char ann, lastann[2];
    int i, j, len, lflag, mflag, sflag;
    int n, nb, nrr, totrr, nnn, totnn, totnnn, np;
    static int nnx[MAXP];
    double t, lastt, rr, lastrr, end, sum, sum2;
    double ratio = 0, avnn = 0, sdnn = 0, sdann = 0, sdnnindx = 0, rmssd = 0, pnnx = 0;
    static double ratbuf[MAXBUF], avbuf[MAXBUF], sdbuf[MAXBUF];
    static double nndif[MAXP];
    
    /* default 5:00 non-overlapping segments */
    len = 300;
    
    lflag = mflag = sflag = 0;
    np = 1;
    nndif[0] = NNDIF;
    
    for (j=0; j<np; j++) {
        if (nndif[j] > 1)
            nndif[j] /= 1000;
        if (mflag)
            nndif[j] *= 1000;
    }
    
    i = 0;
    totrr = nrr = 1;
    totnnn = totnn = nnn = 0;
    rmssd = sum = sum2 = 0.0;
    
    lastt = t = 0;
    lastrr = rr = 0;
    lastann[0] = 'X';
    lastann[1] = ann = 'N';
    end = t + len;
    
    for (int index = 0; index < x; index++) {
        t = inputData[index][0];
        rr = inputData[index][1];
        char cstr = (int)inputData[index][2];
        ann = cstr;
        
        while (t > end+len) {
            i++;
            end += len;
        }
        
        if (t >= end) {
            if (nnn > 1) {
                ratbuf[i] = (double)nnn/nrr;
                sdbuf[i] = sqrt((sdbuf[i] - avbuf[i]*avbuf[i]/nnn) / (nnn-1));
                avbuf[i] /= nnn;
            }
            i++;
            nnn = nrr = 0;
            end += len;
        }
        
        nrr++;
        totrr++;
        
        if (ann == 'N' && lastann[1] == 'N') {
            nnn++;
            totnn++;
            avbuf[i] += rr;
            sum += rr;
            sdbuf[i] += rr*rr;
            sum2 += rr*rr;
            if (lastann[0] == 'N') {
                totnnn++;
                rmssd += (rr-lastrr)*(rr-lastrr);
                
                /* modified 6-15-01 */
                /* equal may not be equal do to round of error !! */
                /* if (ABS(rr-lastrr) > nndif) { */
                
                for (j=0; j<np; j++) {
                    if (ABS(rr-lastrr) - nndif[j] > ROFFERR) {
                        nnx[j]++;
                    }
                }
            }
        }
        
        lastrr = rr;
        lastann[0] = lastann[1];
        lastann[1] = ann;
    }
    
    if (nnn > 1) {
        ratbuf[i] = (double)nnn/nrr;
        sdbuf[i] = sqrt((sdbuf[i] - avbuf[i]*avbuf[i]/nnn) / (nnn-1));
        avbuf[i] /= nnn;
    }
    
    nb = ++i;
    
    ratio = (double)totnn/totrr;
    avnn = sum/totnn;
    sdnn = sqrt((sum2 - sum*sum/totnn) / (totnn-1));
    
    printf("NN/RR = %g\n", ratio);
    printf("AVNN = %g\n", avnn);
    printf("SDNN = %g\n", sdnn);
    
    sum = sum2 = 0;
    for (i=0, n=0; i<nb; i++) {
        if (ratbuf[i] != 0) {
            n++;
            sum += avbuf[i];
            sum2 += avbuf[i]*avbuf[i];
        }
    }
    if (n > 1) {
        sdann = sqrt((sum2 - sum*sum/n) / (n-1));
        printf("SDANN = %g\n", sdann);
    }
    else {
        printf("SDANN = -\n");
    }
    
    
    sum = 0;
    for (i=0, n=0; i<nb; i++) {
        if (ratbuf[i] != 0) {
            n++;
            sum += sdbuf[i];
        }
    }
    if (n > 0) {
        sdnnindx = sum/n;
        printf("SDNNIDX = %g\n", sdnnindx);
    }
    else {
        printf("SDNNIDX = -\n");
    }
    
    rmssd = sqrt(rmssd/totnnn);
    printf("rMSSD = %g\n", rmssd);
    for (j=0; j<np; j++) {
        pnnx = (double)nnx[j]/totnnn;
        
        printf("pNN%g = ", nndif[j]*1000);
        printf("%g\n", pnnx);
    }
    
    
    
    // NN/RR, AVNN, SDNN, SDANN, SDNNIDX, rMSSD, pNN50
    static double time[T_RESULT_NUMBER];
    time[0] = ratio;
    time[1] = avnn;
    time[2] = sdnn;
    time[3] = sdann;
    time[4] = sdnnindx;
    time[5] = rmssd;
    time[6] = pnnx;
    
    return time;
}

