/*
 * unzip.h
 *
 *  Created on: 19 maj 2014
 *      Author: grzybek
 */

#ifndef UNZIP_H_
#define UNZIP_H_

#include "stm32f10x.h"

u32 uncompressKernel(u32 dest_ptr, unsigned long destLength, u32 src_ptr, u32 sourceLength);

#endif /* UNZIP_H_ */
