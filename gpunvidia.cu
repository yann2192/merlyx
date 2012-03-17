#include <stdio.h>

void printProperties(struct cudaDeviceProp * p){
	printf("Device name : %s \n", p->name);
	printf("Version : %d.%d\n",p->major, p->minor);
	printf("Global memory available (in byte) : %d\n", p->totalGlobalMem);
	printf("Shared memory available (by thread in byte) : %d\n", p->sharedMemPerBlock);
	printf("32-bit registers available (by thread) : %d\n", p->regsPerBlock);
	printf("The warp size in threads : %d\n", p->warpSize);
	printf("Maximum threads per blocks : %d\n", p->maxThreadsPerBlock);
	printf("Clock rate (in kHz) : %d\n", p->clockRate);
	printf("Total const memory (in byte) : %d\n", p->totalConstMem);
	printf("Texture alignment (in byte) : %d\n", p->textureAlignment);
	printf("Number of multiprocessors : %d\n", p->multiProcessorCount);
	printf("Run time limit? : %d\n", p->kernelExecTimeoutEnabled);
	printf("memPitch (in byte): %d\n", p->memPitch);
	printf("Maximum size of each dimension of a block : %d %d %d\n", p->maxThreadsDim[0], p->maxThreadsDim[1],p->maxThreadsDim[2]);
	printf("maximum size of each dimension of a grid : %d %d %d\n", p->maxGridSize[0], p->maxGridSize[1],p->maxGridSize[2]);
	printf("deviceOverlap : %d\n", p->deviceOverlap);
	printf("integrated : %\n", p->integrated);
	printf("canMapHostMemory : %\n", p->canMapHostMemory);
	printf("computeMode : %s\n", p->computeMode);
} 

int main(){
	struct cudaDeviceProp deviceProp;
	int numDevice;
	
	if(cudaChooseDevice(&numDevice, &deviceProp) == cudaSuccess){
		if(cudaDeviceProperties(&deviceProp, numDevice) == cudaErrorInvalidDevice)
			printf("Error, selected device not found");
		else
			printProperties(&deviceProp);
	}else{
		printf("Error with cudaChooseDevice");
	}
	return 0;
}