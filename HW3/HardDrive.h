//
// Created by emre on 5/27/17.
//

#ifndef OSHW3_HARDDRIVE_H
#define OSHW3_HARDDRIVE_H


#include "8080emuCPP.h"
#include "Page.h"

/* 128 kb hdd */
#define HDDSIZE 0x20000

class HardDrive {
public:

    HardDrive();
    ~HardDrive();
    Page * getAt(int i);

    void setAt(Page &newPage);

private:
    Page *Space[128];
    int howBig;
};


#endif //OSHW3_HARDDRIVE_H
