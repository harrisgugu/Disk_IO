#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

off_t getFileSize(char * filename){
    struct stat st;
    stat(filename,&st);
    return st.st_size;
}

int main(int argc, char* argv[]){

    printf("before start%d",1);
    if (argc != 2) {
        printf("Usage: %s <filename> \n", argv[0]);
        return 1;
    }
    char* filename = argv[1];
    printf("before file%d",1);
    // get the block size and block count
    unsigned int block_count = 1;
    unsigned int block_size = 1;
    unsigned int file_size = (unsigned int)getFileSize(filename);
    unsigned int optimal_size = 1;
    double fastest_speed;
    printf("hello");
    // buffer to store the data
    while(block_size<file_size){
        unsigned int* buffer;
        block_count = ceil(file_size/block_count);
        buffer = (unsigned int*)malloc(block_size*sizeof(unsigned int));
        int fd = open(filename,O_RDONLY);
            // check if the
        if (fd==-1) {
            printf("Error opening file for reading\n");
            return 1;
        }
        // get the start time
        clock_t start_t = clock();
        // read the file in blocks
        unsigned int xor_value = 0;
        double elapsed;
        int read_bytes = 0;
        int8_t reach_end = 0;
        for(int i = 0;i<block_count;i++){
            read_bytes = read(fd,buffer,block_size);
            xor_value ^= xorbuf(buffer,block_size);
            if(read_bytes<block_size){
                reach_end = 1;
                break;
            }
        }

        // get the end time
        clock_t end_t = clock();
        elapsed = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        // close the file
        close(fd);
        // calculate the elapsed time
        double performance = file_size/(elapsed*1024*1024);
        if(performance>fastest_speed){
            fastest_speed = performance;
            optimal_size = block_size;
        }
        printf("Current speed: %f, Current Block_size: %d",performance,block_size);
        printf("Fastest Speed:%f, Best Block_size: %d",fastest_speed,optimal_size);
        block_size*=2;
        //we double the block_size after each iteration
    }
    return 0;
}
