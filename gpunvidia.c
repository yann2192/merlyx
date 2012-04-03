#include "gpunvidia.h"

void fprintf_nvidia(FILE * f, struct cudaDeviceProp * p)
{
    fprintf(f, "Device name : %s \n", p->name);
    fprintf(f, "Version : %u.%u\n",p->major, p->minor);
    fprintf(f, "Global memory available (in byte) : %lu\n", p->totalGlobalMem);
    fprintf(f, "Shared memory available (by thread in byte) : %lu\n", p->sharedMemPerBlock);
    fprintf(f, "32-bit registers available (by thread) : %ud\n", p->regsPerBlock);
    fprintf(f, "The warp size in threads : %ud\n", p->warpSize);
    fprintf(f, "Maximum threads per blocks : %ud\n", p->maxThreadsPerBlock);
    fprintf(f, "Clock rate (in kHz) : %ud\n", p->clockRate);
    fprintf(f, "Total const memory (in byte) : %lu\n", p->totalConstMem);
    fprintf(f, "Texture alignment (in byte) : %lu\n", p->textureAlignment);
    fprintf(f, "Number of multiprocessors : %ud\n", p->multiProcessorCount);
    fprintf(f, "Run time limit? : %ud\n", p->kernelExecTimeoutEnabled);
    fprintf(f, "memPitch (in byte): %lu\n", p->memPitch);
    fprintf(f, "Maximum size of each dimension of a block : %ud %ud %ud\n", p->maxThreadsDim[0], p->maxThreadsDim[1],p->maxThreadsDim[2]);
    fprintf(f, "maximum size of each dimension of a grid : %ud %ud %ud\n", p->maxGridSize[0], p->maxGridSize[1],p->maxGridSize[2]);
    fprintf(f, "deviceOverlap : %ud\n", p->deviceOverlap);
    fprintf(f, "integrated : %d\n", p->integrated);
    fprintf(f, "canMapHostMemory : %d\n", p->canMapHostMemory);
    fprintf(f, "computeMode : %d\n", p->computeMode);
    fprintf(f, "\n");
}

int getNvidiaInfo(FILE * f)
{
    struct cudaDeviceProp deviceProp;
    int i;
    int numDevice;
    void * handle;
    /*cudaError_t (*cudaChooseDevice)(int *, struct cudaDeviceProp *);*/
    cudaError_t (*cudaGetDeviceProperties)(struct cudaDeviceProp *, int);
    cudaError_t (*cudaGetDeviceCount)(int *);

    handle = dlopen("/usr/local/cuda/lib64/libcudart.so", RTLD_LAZY);
    if(!handle) {
        fprintf(f, "Fail to load CUDA\n");
        return 0;
    }
    dlerror();

    /*cudaChooseDevice = dlsym(handle, "cudaChooseDevice");*/
    cudaGetDeviceProperties = dlsym(handle, "cudaGetDeviceProperties");
    cudaGetDeviceCount = dlsym(handle, "cudaGetDeviceCount");

    /*if(cudaChooseDevice(&numDevice, &deviceProp) == cudaSuccess){*/
    if(cudaGetDeviceCount(&numDevice) == cudaSuccess) {
        for(i=0;i < numDevice; ++i) {
            if(cudaGetDeviceProperties(&deviceProp, i) == cudaErrorInvalidDevice)
                fprintf(f, "Error, selected device not found");
            else
                fprintf_nvidia(f, &deviceProp);
        }
    }else{
        fprintf(f, "Error with cudaChooseDevice");
    }
    dlclose(handle);
    return 0;
}

