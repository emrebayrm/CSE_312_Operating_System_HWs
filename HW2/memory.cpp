//
// Created by emre on 4/26/17.
//

#include "memory.h"

uint8_t &memory::at(uint32_t ind) {
    int addr = ind + baseReg;
    if(addr  >= baseReg && addr < getLimitReg() )
        return mem[addr];
    return mem[111111];/*Random place*/
}

