//
//  NVDSP_C.c
//  Everapp
//
//  Created by Artem on 9/9/18.
//  Copyright © 2018 Everappz. All rights reserved.
//

#include "NVDSPC.h"
#include <libkern/OSAtomic.h>
#include <Accelerate/Accelerate.h>

/*
- (void)filterData:(float *)data numFrames:(UInt32)numFrames numChannels:(UInt32)numChannels {
    switch (numChannels) {
        case 1:
            [self filterContiguousData:data numFrames:numFrames channel:0];
            break;
        case 2: {
            float left[numFrames + 2];
            float right[numFrames + 2];
            
            [self deinterleave:data left:left right:right length:numFrames];
            [self filterContiguousData:left numFrames:numFrames channel:0];
            [self filterContiguousData:right numFrames:numFrames channel:1];
            [self interleave:data left:left right:right length:numFrames];
            
            break;
        }
        default:
            NSLog(@"WARNING: Unsupported number of channels %u", (unsigned int)numChannels);
            break;
    }
}
*/


void c_filterContiguousData(float *data, unsigned int numFrames, unsigned int channel,float realTimeCoeffs[5],float *gInputKeepBuffer[2],float *gOutputKeepBuffer[2]){
    
    // Provide buffer for processing
    float tInputBuffer[numFrames + 2];
    float tOutputBuffer[numFrames + 2];
    
    // Copy the data
    memcpy(tInputBuffer, gInputKeepBuffer[channel], 2 * sizeof(float));
    memcpy(tOutputBuffer, gOutputKeepBuffer[channel], 2 * sizeof(float));
    memcpy(&(tInputBuffer[2]), data, numFrames * sizeof(float));
    
    // Do the processing
    vDSP_deq22(tInputBuffer, 1, realTimeCoeffs, tOutputBuffer, 1, numFrames);
    
    // Copy the data
    memcpy(data, tOutputBuffer + 2, numFrames * sizeof(float));
    memcpy(gInputKeepBuffer[channel], &(tInputBuffer[numFrames]), 2 * sizeof(float));
    memcpy(gOutputKeepBuffer[channel], &(tOutputBuffer[numFrames]), 2 * sizeof(float));
}

void c_applyGain(float *ioData, float gain, unsigned int numFrames, unsigned int numChannels){
    vDSP_vsmul(ioData, 1, &gain, ioData, 1, numFrames*numChannels);
}
