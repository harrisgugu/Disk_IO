#include <string.h>
#include <time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

off_t getFileSize(char * filename){
    struct stat st;
    stat(filename,&st);
    return st.st_size;
}

int main(int argc, char* argv[]){

    if (argc != 5) {
        printf("Usage: %s <filename> [-r|-w] <block_size> <block_count>\n", argv[0]);
        return 1;
    }
    char* filename = argv[1];
    char* operation = argv[2];
    // get the block size and block count
    unsigned int block_size = atoi(argv[3]);
    unsigned int block_count = atoi(argv[4]);

        // buffer to store the data
    unsigned int* buffer;
    buffer = (unsigned int*)malloc(block_size*sizeof(unsigned int));
    off_t file_size = getFileSize(filename);
    int fd = open(filename,O_RDONLY);
        
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
    off_t offset = 0;
    for(int i= 0;i<block_count;i++){
        offset = lseek(fd,block_size,SEEK_CUR);
        if(offset>=file_size)
            break;
    }
    

    // get the end time

    // close the file
    close(fd);
    elapsed = (double)(clock() - start_t) / CLOCKS_PER_SEC;
    // calculate the elapsed time

    // print the read performance
    //double performance = readSize/(elapsed*1024*1024);
    //printf("Lseek performance: %f MiB/s\n", performance);        
    printf("%f", elapsed);
    //printf("XOR value: %x\n", xor_value);
    //printf("Filesize that was read: %ld\n",readSize);
}