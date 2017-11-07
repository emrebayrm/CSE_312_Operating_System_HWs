//
// Created by emre on 4/20/17.
//

#include <iostream>
#include "Process.h"

Process &Process::operator=(const Process &other) {
    if(&other != this )
    {
        this->pid = other.pid;
        this->baseReg = other.baseReg;
        this->cycle = other.cycle;
        this->filename = other.filename;
        this->LimitReg = other.LimitReg;
        this->startingtime = other.startingtime;
        this->ParentPid = other.ParentPid;
        this->state = other.state;
        this->stateofRegs = other.stateofRegs;
    }
    return *this;
}

void Process::printMe() {
    using namespace std;
    std::cout << "Process Name        : " << getFilename() << std::endl;
    std::cout << "        Pid         : " << getPid() << std::endl;
    std::cout << "        Total Cycle : " << getCycle() << std::endl;
    std::cout << "        state       : " << (getState() == RUNNING ? "RUNNING" : (getState() == READY ? "READY" : "BLOCKED")) << std::endl;
    cout << " Registers : " << endl;
    cout << "A : " << (int)stateofRegs.a << "  " <<
            "B : " << (int)stateofRegs.b << "  " <<
            "C : " << (int)stateofRegs.c << "  " <<
            "D : " << (int)stateofRegs.d << "  " <<
            "E : " << (int)stateofRegs.e << "  " <<
            "H : " << (int)stateofRegs.h << "  " <<
            "L : " << (int)stateofRegs.l << "  " <<
            "Condition Code Regs :  " << (int)stateofRegs.cc.ac << "  " <<
                                         (int)stateofRegs.cc.cy << "  " <<
                                         (int)stateofRegs.cc.p  << "  " <<
                                         (int)stateofRegs.cc.s  << "  " <<
                                         (int)stateofRegs.cc.z  << "  " <<
            "Stack Pointer   : " << (int)stateofRegs.sp << "  " <<
            "Program Counter : " << (int)stateofRegs.pc << "  " << endl;

}




