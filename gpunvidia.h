#ifndef __GPUNVIDIA__
#define __GPUNVIDIA__

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include "output.h"

void fprintf_nvidia(FILE * f, struct cudaDeviceProp * p, char html);
int getNvidiaInfo(FILE * f, char html);

#endif
