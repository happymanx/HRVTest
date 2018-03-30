//
//  statnn.h
//  TestHRV
//
//  Created by HappyBoy on 28/03/2018.
//  Copyright © 2018 Jason. All rights reserved.
//

#ifndef statnn_h
#define statnn_h

#include <stdio.h>

#define T_RESULT_NUMBER 7

/*
 Input:
 1. x: number of input data
 2. y: number of input data dimension
 3. inputData: rr interval, [time(sec), interval(sec), annotation]
 
 Output:
 time data, 1 dimension
 nn/rr, avnn, sdnn, sdann, sdnnindx, rmssd and pnn on stderr
 
 #Time Domain
 NN/RR = 0.97226
 AVNN = 0.640491
 SDNN = 0.0522677
 SDANN = 0.0466348
 SDNNIDX = 0.0209309
 rMSSD = 0.0306986
 pNN50 = 0.0639232
 
 */

double *getTimeResult(int x, int y, double inputData[][3]);

#endif /* statnn_h */
