/*
 * cellular.h
 *
 *  Created on: 14.12.2016
 *      Author: beat
 */

#ifndef FW_LIB_CELLULAR_CELLULAR_H_
#define FW_LIB_CELLULAR_CELLULAR_H_

#define SARA_G350

struct cellular_contact {
	int index;
	char* name;
	char* number;
};

#include "sara_g350.h"
#include "sim800.h"

#endif /* FW_LIB_CELLULAR_CELLULAR_H_ */
