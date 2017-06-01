#include <stdio.h>

#define BUFFER_SIZE 4

int test(unsigned int reg, unsigned char *val, unsigned int rl, unsigned int vl)
{
    unsigned int n = rl+vl;
    unsigned char ob[n];  //outbuf
    
    if(rl == 1){
        ob[0] = reg & 0xFF;
    }else if(rl == 2){
        ob[0] = (reg >> 8) & 0xFF;
        ob[1] = reg & 0xFF;
    }else{
        printf("ERROR. rl out of range");
        return 1;
    }
    
    int i;
    int j = 0;
    for(i=rl; i<n; i++){
        if(j<vl){
            ob[i] = val[j++];
        }else{
            printf("ERROR: j exceeded range\n");
            return 1;
        }
    }
    
    for(i=0; i<n; i++){
        printf("ob[%d] = 0x%x\n", i, ob[i]);
    }
    
    printf("test() b: \t0x%x\n", val[3]);
    val[3] = 0x42;
    printf("test() a: \t0x%x\n", val[3]);
    
    return 0;
}

int main()
{
    unsigned int reg = 0x001c;
    unsigned char buf[BUFFER_SIZE] = {0x00,0x08,0x13,0x85};
    printf("Before: \t0x%x\n", buf[3]);
    test(reg, buf, 3, 4);
    printf("After: \t\t0x%x\n", buf[3]);

    return 0;
}