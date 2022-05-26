//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_PC_H
#define VIRTUALCPU_PC_H

#include "Block.h"

template<typename T>
class PC : public Block<T> {
public:
    void tick() override;
    void update() override;

    bool enable = false;
    bool load = false;
    bool counterenable = false;
    T value = 0;
private:
};

template<typename T>
void PC<T>::tick() {
    if(counterenable){
        value++;
    }
    /*if(enable) {
        this->bus->value|=value;
    }*/
    if(load){
        value=this->bus->value;
    }
}

template<typename T>
void PC<T>::update() {
    if(enable) {
        this->bus->value|=value;
    }
}

#endif //VIRTUALCPU_PC_H
