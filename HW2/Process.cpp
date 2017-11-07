//
// Created by emre on 4/20/17.
//

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



