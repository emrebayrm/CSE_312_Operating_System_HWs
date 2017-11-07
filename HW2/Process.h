//
// Created by emre on 4/20/17.
//

#ifndef OSHW2_PROCESS_H
#define OSHW2_PROCESS_H

#include <string>
#include "memory.h"
#include "8080emuCPP.h"

typedef enum{READY,BLOCK,RUNNING} PState;
class Process {

private:
public:
    const std::string &getFilename() const {
        return filename;
    }

    void setFilename(const std::string &filename) {
        Process::filename = filename;
    }

    int getPid() const {
        return pid;
    }

    void setPid(int pid) {
        Process::pid = pid;
    }

    int getParentPid() const {
        return ParentPid;
    }

    void setParentPid(int ParentPid) {
        Process::ParentPid = ParentPid;
    }

    int getStartingtime() const {
        return startingtime;
    }

    void setStartingtime(int startingtime) {
        Process::startingtime = startingtime;
    }

    PState getState() const {
        return state;
    }

    void setState(PState state) {
        Process::state = state;
    }

    int getCycle() const {
        return cycle;
    }

    void setCycle(int cycle) {
        Process::cycle = cycle;
    }

    int getBaseReg() const {
        return baseReg;
    }

    void setBaseReg(int baseReg) {
        Process::baseReg = baseReg;
    }

    int getLimitReg() const {
        return LimitReg;
    }

    void setLimitReg(int LimitReg) {
        Process::LimitReg = LimitReg;
    }

    void AddCycle(int c){
        cycle += c;
    }

    int getWaitingPid() const {
        return WaitingPid;
    }

    void setWaitingPid(int WaitingPid) {
        Process::WaitingPid = WaitingPid;
    }


    Process & operator=(const Process & other);

    State8080 stateofRegs;
private:
    std::string filename;
    int pid;
    int ParentPid;
    int startingtime;
    PState state;
    int cycle;
    int baseReg;
    int LimitReg;
    int WaitingPid = -1;
    //TODO My Address Space
};


#endif //OSHW2_PROCESS_H
