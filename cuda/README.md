# README

This directory contain CUDA hello world code.

First install the nvidia toolkit

    sudo apt install nvidia-cuda-toolkit
    export CUDA_HOME=/usr/lib/cuda

## Useful commands

```
$ nvidia-smi
Thu Oct  7 00:45:11 2021
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 460.91.03    Driver Version: 460.91.03    CUDA Version: 11.2     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  GeForce RTX 3080    Off  | 00000000:00:05.0 Off |                  N/A |
|  0%   29C    P0     1W / 320W |      0MiB / 10018MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
```

## Links

<https://cuda-tutorial.readthedocs.io/en/latest/tutorials/tutorial01/>

### Hello World

Source

```
C

void c_hello(){
    printf("Hello World!\n");
}

int main() {
    c_hello();
    return 0;
}

CUDA

__global__ void cuda_hello(){
    printf("Hello World from GPU!\n");
}

int main() {
    cuda_hello<<<1,1>>>(); 
    return 0;
}
```

Compile

```
nvcc hello.cu -o hello
```
