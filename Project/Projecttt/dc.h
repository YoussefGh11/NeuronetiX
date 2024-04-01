/*
 * dc.h
 *
 *  Created on: Feb 21, 2024
 *      Author: PCM
 */

#ifndef DC_H_
#define DC_H_

#include "std_types.h"

typedef enum {Stop,CW,ACW}DcMotor_State;

void  DcMotor_Init(void);
void  DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_H_ */
