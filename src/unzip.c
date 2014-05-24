/*
 * unzip.c
 *
 *  Created on: 19 maj 2014
 *      Author: grzybek
 */


#include "unzip.h"
#include "zlib.h"


u32 uncompressKernel(u32 dest_ptr, unsigned long destLength, u32 src_ptr, u32 sourceLength)
{
    u32 successCode = 0;

    /* uncompress return success code, if 0 ok . It could be possible to
       load other runtime to run if compression fails but here is trusted
       to calculated checksum. Uncompressed file itself includes 32-bit CRC.*/
    successCode = uncompress((u8*)dest_ptr, &destLength, (u8*)src_ptr, sourceLength);

    return(successCode);
}
