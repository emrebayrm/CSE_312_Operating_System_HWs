#include <iostream>
#include <string>
#include "8080emuCPP.h"
#include "gtuos.h"

static const int quanta = 100;
using namespace std;
uint64_t GTUOS::handleCall(CPU8080 & cpu){

    int read;
    uint16_t address;
    std::string str;
    int cycle = 10;

    switch (cpu.state->a){
        case 1:             //PRINT_B
            std::cout << (int) cpu.state->b << std::endl;
            break;
        case 2:             //PRINT_MEM
            std::cout << (int)cpu.memory->at(calculateTheAddress(cpu.state->b,cpu.state->c)) << std::endl;
            break;
        case 3:             //READ_B
            std::cin >> read;
            cpu.state->b = (uint8_t) read;
            break;
        case 4:             //READ_MEM
            std::cin >> read;
            cpu.memory->at(calculateTheAddress(cpu.state->b,cpu.state->c)) = read;
            break;
        case 5:            //PRINT_STR
            std::cout << &cpu.memory->at(cpu.state->b*256 + cpu.state->c);
            break;
        case 6:             //READ_STR
            cycle = 100;
            std::cin >> str;
            address = calculateTheAddress(cpu.state->b,cpu.state->c);

            for (int i = 0; i < str.length() ; ++i, address++)
                cpu.memory->at(address) = str.at(i);
            break;
        case 7:             // Fork
            if(this->processQueue.size() < 4){
                Process *process = new Process;
                *process = *RunningPrcs; // make a copy

                process->setPid(++pidcounter);
                process->setParentPid(RunningPrcs->getPid());
                process->setStartingtime(TotalELapsedTime);
                int emptyAddr = giveMeEmptyAddressSpace();
                process->setBaseReg(emptyAddr);
                process->setLimitReg(emptyAddr + 0x3FFF);

                dynamic_cast<memory*>(cpu.memory)->CopyValesBetweenGivenindexes(RunningPrcs->getBaseReg(),process->getBaseReg(),0x3FFF);

                cpu.state->b = (uint8_t) pidcounter;
                RunningPrcs->stateofRegs.b = (uint8_t)pidcounter;

                //Goes on same code with differnt pc
//                process->stateofRegs.pc = process->getBaseReg() + RunningPrcs->stateofRegs.pc; //TODO When MMU done
//                process->stateofRegs.sp = RunningPrcs->stateofRegs.sp + process->getBaseReg();
                process->stateofRegs.b = 0;
                processQueue.push_back(process);
            }
            else{
                RunningPrcs->stateofRegs.b = 1;
            }

            cycle = 50;
            break;
        case 8:             //exec
            if(this->processQueue.size() < 4) {
                std::string filename;
                address = calculateTheAddress(cpu.state->b, cpu.state->c);

                for (int i = 0; cpu.memory->at(address) != '\0'; ++i, address++)
                    filename.append(1,cpu.memory->at(address));
                int emptyAddr = RunningPrcs->getBaseReg();
                cpu.ReadFileIntoMemoryAt(filename.c_str(), (uint32_t) (emptyAddr)); //TODO ofset ??
                RunningPrcs->setFilename(filename);
                RunningPrcs->stateofRegs.pc = 0;
            }
            cycle = 80;
            break;
        case 9:             //waitpid
            RunningPrcs->setState(BLOCK);
            RunningPrcs->setWaitingPid(RunningPrcs->stateofRegs.b);
            cycle = 80;
            break;
    }
    return cycle;
}



int GTUOS::calculateTheAddress(uint8_t i, uint8_t c) {
    uint16_t address = 0;
    address = i << 8;
    address = address + c;
    return address;
}

void GTUOS::printMemory(const CPU8080 & cpu) {
    FILE* file = fopen("exe.mem","w");
    dynamic_cast<memory *>(cpu.memory)->disableCounting();
    for (int i = 0x00000; i < 0x20000 ; i += 0x00010) {
        fprintf(file,"%05x    %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",
               i,cpu.memory->physicalAt(i),
               cpu.memory->physicalAt(i+0x00001),
               cpu.memory->physicalAt(i+0x00002),
               cpu.memory->physicalAt(i+0x00003),
               cpu.memory->physicalAt(i+0x00004),
               cpu.memory->physicalAt(i+0x00005),
               cpu.memory->physicalAt(i+0x00006),
               cpu.memory->physicalAt(i+0x00007),
               cpu.memory->physicalAt(i+0x00008),
               cpu.memory->physicalAt(i+0x00009),
               cpu.memory->physicalAt(i+0x0000A),
               cpu.memory->physicalAt(i+0x0000B),
               cpu.memory->physicalAt(i+0x0000C),
               cpu.memory->physicalAt(i+0x0000D),
               cpu.memory->physicalAt(i+0x0000E),
               cpu.memory->physicalAt(i+0x0000F));
    }
    dynamic_cast<memory*>(cpu.memory)->restoreToNormal();
}

void GTUOS::printCPUstates(const CPU8080 &cpu) {
    cout << "A : " << (int)cpu.state->a << "  " <<
            "B : " << (int)cpu.state->b << "  " <<
            "C : " << (int)cpu.state->c << "  " <<
            "D : " << (int)cpu.state->d << "  " <<
            "E : " << (int)cpu.state->e << "  " <<
            "H : " << (int)cpu.state->h << "  " <<
            "L : " << (int)cpu.state->l << "  " <<
            "Condition Code Regs :  " << (int)cpu.state->cc.ac << "  " <<
                                         (int)cpu.state->cc.cy << "  " <<
                                         (int)cpu.state->cc.p  << "  " <<
                                         (int)cpu.state->cc.s  << "  " <<
                                         (int)cpu.state->cc.z  << "  " <<
            "Stack Pointer   : " << (int)cpu.state->sp << "  " <<
            "Program Counter : " << (int)cpu.state->pc << "  " << endl;
}

bool GTUOS::boot(CPU8080 &cpu, int debugMode, std::string filename) {
    char dead;
    Process *process = new Process;
    int cost;
    int contextSwitch = 0;

    /*TODO readfile into a memory*/

    EmptySlots[0].isAvailable = false;

    //Create Starting Process
    process->setBaseReg(EmptySlots[0].addr);
    process->setCycle(0);
    process->setLimitReg(EmptySlots[0].addr + 0x3FFF);//16kb
    process->setParentPid(3);
    process->setPid(3);
    process->setStartingtime(0);
    process->setState(READY);
    process->setFilename(filename);
    State8080 *state =(State8080*) malloc(sizeof(State8080));
    process->stateofRegs = *state;

    RunningPrcs = process;

    dynamic_cast<memory*>(cpu.memory)->setBaseReg(RunningPrcs->getBaseReg());
    dynamic_cast<memory*>(cpu.memory)->setLimitReg(RunningPrcs->getLimitReg());
    do {
        do {
            RunningPrcs->setState(RUNNING);
            if (debugMode == 2) {
                std::cout << "press any key to continue ..." << std::endl;
                scanf("%c", &dead);
                dynamic_cast<memory*>(cpu.memory)->printPageTable();
            }

            cost = cpu.Emulate8080p(debugMode);
            TotalELapsedTime += cost;
            contextSwitch += cost;

            RunningPrcs->AddCycle(cost);

            updateRunningProcess(cpu);

            if (cpu.isSystemCall()) {
                cost += handleCall(cpu);
                TotalELapsedTime += cost;
                contextSwitch += cost;
                updateRunningProcess(cpu);
            }
            //if it is Blocked after sys call Actually just for WaitPid sys call
            //Do Context Switching
            if (RunningPrcs->getState() == BLOCK) {
                    doContextSwitching(cpu);
                    contextSwitch = 0;
            }
            else if (contextSwitch > quanta) { //Then Check Normal Context Switching
                cout  << "Running Process name : " << RunningPrcs->getFilename();
                cout  << "                id   : " << RunningPrcs->getPid() << endl;
                cout  << "              Total Spent Time (cycles) : " << contextSwitch <<endl;
                doContextSwitching(cpu);
                contextSwitch = 0;
                cout << "   Switching to name : " << RunningPrcs->getFilename()
                     << "                id   : " << RunningPrcs->getPid()<< endl;
                if(debugMode == 3){
                    printAllProcess();
                }
            }
            // cout<< "Cycle in : "  << contextSwitch << endl;
        }
        while (!cpu.isHalted());
        cout << "id numbber :  " << RunningPrcs->getPid() << "  Prcocess Exitted " << endl;
        if(processQueue.size() == 0)
            break;
        RunningPrcs = processQueue.front();
        processQueue.pop_front();
        cpu.state = &(RunningPrcs->stateofRegs);
        cout << "   Switching to :: " << RunningPrcs->getPid() << endl;
    }while(RunningPrcs != NULL);
    printMemory(cpu);

    cout << endl << endl;
    cout << "Total Replacements :  " << dynamic_cast<memory*>(cpu.memory)->getTotalFaults() << endl;
}

GTUOS::GTUOS() {
    EmptySlots[0].addr = 0;
    EmptySlots[0].isAvailable = true;
    EmptySlots[1].addr = 0x4000;
    EmptySlots[1].isAvailable = true;
    EmptySlots[2].addr = 0x8000;
    EmptySlots[2].isAvailable = true;
    EmptySlots[3].addr = 0xB000;
    EmptySlots[3].isAvailable = true;
    pidcounter = 3;
    RunningPrcs = nullptr;
}

void GTUOS::updateRunningProcess(CPU8080 &cpu) {
    /*
    cpu.state->pc = RunningPrcs->stateofRegs.pc;    cpu.state->cc = RunningPrcs->stateofRegs.cc;
    cpu.state->d  = RunningPrcs->stateofRegs.d;     cpu.state->a = RunningPrcs->stateofRegs.a;
    cpu.state->b  = RunningPrcs->stateofRegs.b;     cpu.state->c = RunningPrcs->stateofRegs.c;
    cpu.state->e  = RunningPrcs->stateofRegs.e;     cpu.state->h = RunningPrcs->stateofRegs.h;
    cpu.state->l  = RunningPrcs->stateofRegs.l;     cpu.state->sp = RunningPrcs->stateofRegs.sp;
    cpu.state->int_enable = RunningPrcs->stateofRegs.int_enable;

     */
    RunningPrcs->stateofRegs = *cpu.state;
}

int GTUOS::giveMeEmptyAddressSpace() {
    for (int i = 0; i < 4; ++i) {
        if(EmptySlots[i].isAvailable){
            EmptySlots[i].isAvailable = false;
            return EmptySlots[i].addr;
        }
    }
}

void GTUOS::doContextSwitching(CPU8080 &cpu8080) {
    if(processQueue.size() == 0)
        return;
    Process *temp;
    temp = processQueue.front();
    int i = 0;
    while(temp->getState() == BLOCK && i < processQueue.size()){
        if( isThatProcessKilled(temp->getWaitingPid())){
            temp->setWaitingPid(0);
            temp->setState(READY);
            break;
        }
        processQueue.push_back(temp);
        processQueue.pop_front();
        temp = processQueue.front();
        ++i;
    }
    if(temp->getState() == BLOCK)
        return;
    if(RunningPrcs->getState() == RUNNING)
        RunningPrcs->setState(READY);
    processQueue.pop_front();
    processQueue.push_back(RunningPrcs);

    temp->setState(RUNNING);
    RunningPrcs = temp;

    cpu8080.state = &(RunningPrcs->stateofRegs);
    dynamic_cast<memory*>(cpu8080.memory)->setBaseReg(RunningPrcs->getBaseReg());
    dynamic_cast<memory*>(cpu8080.memory)->setLimitReg(RunningPrcs->getLimitReg());
}

bool GTUOS::isThatProcessKilled(int pid) {
    bool flag = false;
    for (int i = 0; i < processQueue.size(); ++i){
        if(processQueue.front()->getPid() != pid)
            flag = true;
        processQueue.push_back(processQueue.front());
        processQueue.pop_front();
    }

    return RunningPrcs->getPid() != pid || flag;
}

void GTUOS::printAllProcess() {
    cout << "All Process' " << endl;
    RunningPrcs->printMe();
    for(int i = 0; i < processQueue.size() ; ++i){
        processQueue[i]->printMe();
    }
}





