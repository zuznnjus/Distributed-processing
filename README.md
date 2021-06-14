# Distributed-processing

## Implementation of the distributed processing problem:
* no central elements
* fully asynchronous
* communication using MPI (Message Passing Interface)

## Run project
* default settings
```
make run
```
* custom settings
```
make run N=8 ARGS="-W 10 -SZ 10 -K 15 -MIN 1 -MAX 10"
```
