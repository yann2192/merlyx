#include "gpunvidia.h"

void fprintf_nvidia(FILE * f, struct cudaDeviceProp * p, char html)
{
    print(f, html, "Device name                                 : %s", p->name);
    print(f, html, "Version                                     : %u.%u",p->major, p->minor);
    print(f, html, "Global memory available (in byte)           : %lu", p->totalGlobalMem);
    print(f, html, "Shared memory available (by thread in byte) : %lu", p->sharedMemPerBlock);
    print(f, html, "32-bit registers available (by thread)      : %ud", p->regsPerBlock);
    print(f, html, "The warp size in threads                    : %ud", p->warpSize);
    print(f, html, "Maximum threads per blocks                  : %ud", p->maxThreadsPerBlock);
    print(f, html, "Clock rate (in kHz)                         : %ud", p->clockRate);
    print(f, html, "Total const memory (in byte)                : %lu", p->totalConstMem);
    print(f, html, "Texture alignment (in byte)                 : %lu", p->textureAlignment);
    print(f, html, "Number of multiprocessors                   : %ud", p->multiProcessorCount);
    print(f, html, "Run time limit?                             : %ud", p->kernelExecTimeoutEnabled);
    print(f, html, "memPitch (in byte)                          : %lu", p->memPitch);
    print(f, html, "Maximum size of each dimension of a block   : %ud %ud %ud", p->maxThreadsDim[0], p->maxThreadsDim[1],p->maxThreadsDim[2]);
    print(f, html, "maximum size of each dimension of a grid    : %ud %ud %ud", p->maxGridSize[0], p->maxGridSize[1],p->maxGridSize[2]);
    print(f, html, "deviceOverlap                               : %ud", p->deviceOverlap);
    print(f, html, "integrated                                  : %d", p->integrated);
    print(f, html, "canMapHostMemory                            : %d", p->canMapHostMemory);
    print(f, html, "computeMode                                 : %d", p->computeMode);
    print_nl(f, html);
}

int getNvidiaInfo(FILE * f, char html)
{
    struct cudaDeviceProp deviceProp;
    int i;
    int numDevice;
    void * handle;
    cudaError_t (*cudaGetDeviceProperties)(struct cudaDeviceProp *, int);
    cudaError_t (*cudaGetDeviceCount)(int *);

    handle = dlopen("/usr/local/cuda/lib64/libcudart.so", RTLD_LAZY);
    if(!handle) {
        print(f, html, "Fail to load CUDA");
        return 0;
    }
    dlerror();

    cudaGetDeviceProperties = dlsym(handle, "cudaGetDeviceProperties");
    cudaGetDeviceCount = dlsym(handle, "cudaGetDeviceCount");

    if(cudaGetDeviceCount(&numDevice) == cudaSuccess) {
        for(i=0;i < numDevice; ++i) {
            if(cudaGetDeviceProperties(&deviceProp, i) == cudaErrorInvalidDevice)
                print(f, html, "Error, selected device not found");
            else
                fprintf_nvidia(f, &deviceProp, html);
        }
    }else{
        print(f, html, "Error with cudaChooseDevice");
    }
    dlclose(handle);
    return 0;
}

