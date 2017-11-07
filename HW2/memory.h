#ifndef H_MEMORY
#define H_MEMORY

#include "memoryBase.h"
#include <cstdlib>

// This is just a simple memory with no virtual addresses. 
// You will write your own memory with base and limit registers.

class memory: public MemoryBase {
public:
	memory(){mem = (uint8_t*) malloc(0x10000);}
	~memory(){ free(mem);}
	virtual uint8_t & at(uint32_t ind);
	virtual uint8_t & physicalAt(uint32_t ind) { return mem[ind];}
    void CopyValesBetweenGivenindexes(int from,int to,int size){
        for (int i = from; i < from+size ; ++i) {
            mem[to++] = mem[i];
        }
    }
    int getBaseReg() const {
        return baseReg;
    }

    void setBaseReg(int baseReg) {
        memory::baseReg = baseReg;
    }

    int getLimitReg() const {
        return LimitReg;
    }

    void setLimitReg(int LimitReg) {
        memory::LimitReg = LimitReg;
    }

private:
	uint8_t * mem;
    int baseReg=0;
	int LimitReg=0x10000;
};

#endif