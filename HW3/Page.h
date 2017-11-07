//
// Created by emre on 5/27/17.
//

#ifndef OSHW3_PAGE_H
#define OSHW3_PAGE_H

/* 1 kb */
#include "8080emuCPP.h"

#define PAGESIZE 0x400

class Page {
public:
    Page(int pageNumber){
        this->pageNumber = pageNumber;
    }
    int getPageNumber() const {
        return pageNumber;
    }
    uint8_t &getData(long x) {
        return (data[x]);
    }

    uint8_t getData(int x) const{
        return data[x];
    }

    uint8_t changeData(int x, uint8_t _data){
        data[x] = _data;
    }

    bool isModified() const {
        return modifiedBit;
    }

    bool isReferenced() const{
        return referencedBit;
    }

    bool isPresent() const{
        return present;
    }

    /* Replacement */
    void operator = (const Page &p ) {
        pageNumber = p.pageNumber;
        modifiedBit = p.isModified();
        referencedBit = p.isReferenced();
        present = p.isPresent();
        for (int i = 0; i < PAGESIZE; ++i) {
            changeData(i,p.getData(i));
        }
    }
private:
    int pageNumber;
    bool modifiedBit  = false;
    bool referencedBit = false;
    bool present = false;
    uint8_t data[PAGESIZE];
};


#endif //OSHW3_PAGE_H
