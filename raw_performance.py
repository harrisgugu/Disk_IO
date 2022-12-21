import os, sys,math

def main ():
    filename = "ubuntuiso.iso"
    file_size = os.path.getsize(filename)
    block_size = 10000
    block_count = 1000
    #This is for raw performance
    # for i in range (5000,1000000,5000):
    #     block_size =i
    #     block_count = math.ceil(file_size/block_size)
    #     res= os.popen('./run ubuntuiso.iso -r {} {}'.format(block_size,block_count)).read()
    #     print(res)
    
    #This is for part 4
    # for i in range (1000,1000000,20000):
    #     block_size =i
    #     block_count = math.ceil(file_size/block_size)
    #     wo_cache= os.popen('./run ubuntuiso.iso -r {} {}'.format(block_size,block_count)).read()
    #     print(wo_cache)

    print("without Cache")
    for i in range (1000,1000000,20000):
        block_size =i
        block_count = math.ceil(file_size/block_size)
        #os.system('sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"')
        w_cache= os.popen('./run ubuntuiso.iso -r {} {}'.format(block_size,block_count)).read()
        print(w_cache)

    #This is for Part 5
    # block_size=  1
    # for i in range(1000,10000000,100000):
    #     block_count = i
    #     readtime = os.popen('./run ubuntuiso.iso -r {} {}'.format(block_size,block_count)).read()
    #     lseektime = os.popen('./lseek ubuntuiso.iso -r {} {}'.format(block_size,block_count)).read()
    #     print(readtime,lseektime)

if __name__ == '__main__':
    main()

