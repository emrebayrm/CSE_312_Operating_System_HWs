#ifndef H_GTUOS
#define H_GTUOS

#include <queue>
#include "8080emuCPP.h"
#include "Process.h"


typedef struct {
    int addr;
    bool isAvailable;
}Slot;

class GTUOS{
	public:
        GTUOS();

		uint64_t handleCall(CPU8080 & cpu);
		void printMemory(const CPU8080 & cpu);
    	void printCPUstates(const CPU8080 & cpu);
		int calculateTheAddress(uint8_t i, uint8_t c);
        bool boot(CPU8080 &cpu, int debugMode, std::string filename);
		void updateRunningProcess(CPU8080 &cpu);
    private:
        int lastIndex = 0;
        int TotalELapsedTime = 0;
        int pidcounter = 3;
		Slot EmptySlots[4];
        std::deque<Process *> processQueue;
        Process *RunningPrcs;

        int giveMeEmptyAddressSpace();

        void doContextSwitching(CPU8080 &cpu8080);

        bool isThatProcessKilled(int pid);

	void printAllProcess();
};

#endif
