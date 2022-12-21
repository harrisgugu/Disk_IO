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

int main(int argc, char* argv[])
{
    //The requirement: ./run <filename> [-r|-w] <block_size> <block_count>
    // check if the required number of arguments are provided
    if (argc < 5) {
        printf("Usage: %s <filename> [-r|-w] <block_size> <block_count>\n", argv[0]);
        return 1;
    }
    // get the filename and operation to be performed
    char* filename = argv[1];
    char* operation = argv[2];

    // get the block size and block count
    unsigned int block_size = atoi(argv[3]);
    unsigned int block_count = atoi(argv[4]);

    if(block_count<1){
        printf("Error: Block count cannot be less than 1\n");
        return 1;
    }

        // buffer to store the data
    unsigned int* buffer;
    buffer = (unsigned int*)malloc(block_size*sizeof(unsigned int));

    if (strcmp(operation, "-w") == 0) {
        // open the file for writing
        // check if the file is open
        int fd = open(filename,O_WRONLY|O_CREAT,0744);
        
        

        // get the start time
        time_t start = time(NULL);

        // write the file in blocks
        for (int i = 0; i < block_count; i++) {
            write(fd,buffer,block_size);
        }

        // get the end time
        time_t end = time(NULL);

        // close the file
        close(fd);

        // calculate the elapsed time
        double elapsed = difftime(end, start);

        // print the write performance
        printf("Write performance: %f MiB/s\n", (block_size * block_count) / (elapsed * 1024 * 1024));        
        printf("Time taken: %f seconds\n", elapsed);
    }
    else if (strcmp(operation, "-r") == 0) {
        // open the file for reading
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
        for (int i = 0; i < block_count; i++) {
            int read_bytes=  read(fd,buffer,block_size);
            //printf("readbytes: %d\n",read_bytes);
            if(read_bytes<=0)
                break;
            xor_value ^= xorbuf(buffer,block_size);
            
            //printf("xor value: %x\n", xor_value);


        }

        // get the end time
        clock_t end_t = clock();

        // close the file
        close(fd);

        // calculate the elapsed time
        double elapsed = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        // print the read performance
        unsigned long filesize=  (unsigned long)getFileSize(filename);
        double performance = filesize/(elapsed*1024*1024);
        //printf("Read performance: %f MiB/s\n", performance);  
        // printf("Read performance: %f MiB/s\n", performance);        
        //printf("%f",elapsed);
        printf("%f",performance);
        // printf("XOR value: %x\n", xor_value);
        // printf("filesize: %ld\n",filesize);
    }
    else {
        printf("Error: Invalid operation\n");
        return 1;
    }

    return 0;
}

