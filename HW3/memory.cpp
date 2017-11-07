//
// Created by emre on 4/26/17.
//

#include "memory.h"
#include <iostream>
using namespace std;
uint8_t &memory::at(uint32_t ind) {
    long  addr;
    // Calculate adress
    addr = getBaseReg() + ind;
    int whichPage = addr / (PAGESIZE); // 128 is total page that we have
    int inTable;

    // look that we have
    if( (inTable = isWeHave(whichPage)) != -1 ){
        return (pages[inTable]->getData(ind % PAGESIZE));
    }
    else{// Do Page replacement
        if(debugMode != -1) {
            if (debugMode == 3)
                printPageTable();

            ++totalFaults;
        }
        Page *page = hardDrive.getAt(whichPage);
        *pages[nextReplacement] = *page;
        nextReplacement = (short) ((nextReplacement+1) % 8);
        return page->getData(ind % PAGESIZE);
    }
}

memory::memory(int debugMode) {
    this->debugMode = debugMode;
    for (int i = 0; i < 8; ++i) {
        pages[i] = new Page(i);
    }

}

memory::~memory() {
    for (int i = 0; i < 8; ++i) {
        delete pages[i];
    }
}

int memory::isWeHave(int pageNumber) const {
    int i;
    for (i = 0; i < 8; i++) {
        if(pages[i]->getPageNumber() == pageNumber)
            return i;
    }
    return -1;
}

uint8_t &memory::physicalAt(uint32_t ind) {
    Page *page;
    int whichPage = ind / (PAGESIZE);
    int inTable = isWeHave(whichPage);
    if(inTable != -1){
        return pages[inTable]->getData(ind % PAGESIZE);
    }else {// Page Fault
        if(debugMode != -1) {
            if (debugMode == 3)
                printPageTable();

            ++totalFaults;
        }
        hardDrive.setAt(*pages[nextReplacement]);
        page = hardDrive.getAt(whichPage);
        *pages[nextReplacement] = *page;
        nextReplacement = (short) ((nextReplacement+1) % 8);
        return page->getData(ind % PAGESIZE);
    }
}

void memory::CopyValesBetweenGivenindexes(int from, int to, int size) {
    for (int i = from; i < from+size ; ++i) {
        physicalAt(to++) = physicalAt(i);
    }
}

void memory::printPageTable() {
    cout << "Page Tables : " << endl;
    for (int i = 0; i < 8; ++i) {
        cout << " Page Number :" << pages[i]->getPageNumber() <<  endl;
    }
    cout << endl;
}



