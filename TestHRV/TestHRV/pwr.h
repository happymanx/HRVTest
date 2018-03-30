//
//  pwr.h
//  TestHRV
//
//  Created by HappyBoy on 27/03/2018.
//  Copyright © 2018 Jason. All rights reserved.
//

#ifndef pwr_h
#define pwr_h

#include <stdio.h>
#define F_RESULT_NUMBER 6

/*
 Input:
 1. x: number of input data
 2. y: number of input data dimension
 3. inputData: power data, [time(sec), interval(sec)]
 
 Output:
 frequency data, 1 dimension
 Array[6]
 TOT PWR, ULF PWR, VLF PWR, LF PWR, HF PWR, LF/HF
 0~0.04, 0~0.0033, 0.0033~0.04, 0.04~0.15, 0.15~0.4, (0.04~0.15 / 0.15~0.4)
 
 #Frequency Domain
 Total = 0.00297733
 0 - 0.04 = 0.00249343
 0 - 0.0033 = 0.00231429
 0.0033 - 0.04 = 0.000179132
 0.04 - 0.15 = 4.03108e-05
 0.15 - 0.4 = 7.03036e-05
 
 */

double *getFrequencyResult(int x, int y, double inputData[][2]);

#endif /* pwr_h */
