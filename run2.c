#include <string.h>
#include <time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


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

    if (argc != 3) {
        printf("Usage: %s <filename> <block_size> \n", argv[0]);
        return 1;
    }
    char* filename = argv[1];

    // get the block size and block count
    unsigned int block_size = atoi(argv[2]);
    unsigned int block_count = 0;

        // buffer to store the data
    unsigned int* buffer;
    buffer = (unsigned int*)malloc(block_size*sizeof(unsigned int));

    int fd = open(filename,O_RDONLY);
        // check if the
    if (fd==-1) {
        printf("Error opening file for reading\n");
        return 1;
    }
            // get the start time
    clock_t start_t = clock();
    //int read_bytes;
    // read the file in blocks
    unsigned int xor_value = 0;
    double elapsed;
    int8_t reach_end = 0;
    int read_bytes = 0;
    while((read_bytes = read(fd,buffer,block_size))>0){
        block_count++; 
        xor_value ^= xorbuf(buffer,block_size);
        if(read_bytes<block_size){
            reach_end = 1;
            break;
        }
        elapsed = (double)(clock() - start_t) / CLOCKS_PER_SEC;
        if(elapsed>15.0)
            break;
    }

    // get the end time

    // close the file
    close(fd);

    // calculate the elapsed time

    // print the read performance
    unsigned long readSize = reach_end?getFileSize(filename):block_count*block_size;
    double performance = readSize/(elapsed*1024*1024);
    printf("Read performance: %f MiB/s\n", performance);        
    printf("Time taken: %f seconds\n", elapsed);
    printf("XOR value: %x\n", xor_value);
    printf("Filesize that was read: %ld\n",readSize);
}