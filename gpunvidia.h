#ifndef __GPUNVIDIA__
#define __GPUNVIDIA__

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

void fprintf_nvidia(FILE * f, struct cudaDeviceProp * p);
int getNvidiaInfo(FILE * f);

#endif
