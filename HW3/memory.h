#ifndef H_MEMORY
#define H_MEMORY

#include "memoryBase.h"
#include "Page.h"
#include "HardDrive.h"
#include <cstdlib>

// This is just a simple memory with no virtual addresses.
// You will write your own memory with base and limit registers.
#define MAINMEMORYSIZE 0x2000
class memory: public MemoryBase {
public:
	memory(int debugMode);
    ~memory();
	virtual uint8_t & at(uint32_t ind);
	virtual uint8_t & physicalAt(uint32_t ind);

    void CopyValesBetweenGivenindexes(int from,int to,int size);

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
    void printPageTable();

    int getTotalFaults(){ return totalFaults;};

    void disableCounting(){
        oldDebug = debugMode;
        debugMode = -1;
    }
    void restoreToNormal(){debugMode = oldDebug;}
private:
    int oldDebug;
    int totalFaults = 0;
    int debugMode;
    HardDrive hardDrive;
	Page *pages[8];  /*  MAINMEMORYSIZE / PAGESIZE = 8 */
    int baseReg=0;
	int LimitReg=0;
    short nextReplacement = 0;
    int isWeHave(int pageNumber) const;
};

#endif