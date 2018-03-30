//
//  lomb.h
//  TestHRV
//
//  Created by HappyBoy on 27/03/2018.
//  Copyright © 2018 Jason. All rights reserved.
//

#ifndef lomb_h
#define lomb_h

#include <stdio.h>

/*
 Input:
 1. x: number of input data
 2. y: number of input data dimension
 3. inputData: nn interval, [time(sec), interval(sec)]
 
 Output:
 power data, 2 dimension
 
 */

double **getPowerResult(int x, int y, double inputData[][2]);

#endif /* lomb_h */
