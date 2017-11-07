//
// Created by emre on 5/27/17.
//

#include "HardDrive.h"

HardDrive::HardDrive() {
    howBig = 128;
    for (int i = 0; i < howBig; ++i) {
        Space[i] = new Page(i);
    }
}

Page * HardDrive::getAt(int i) {
    return Space[i];
}

void HardDrive::setAt(Page &newPage) {
    *Space[newPage.getPageNumber()] = newPage;
}

HardDrive::~HardDrive() {
    for (int i = 0; i < howBig; ++i) {
        delete Space[i];
    }
}



