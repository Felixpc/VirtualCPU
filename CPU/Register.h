//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_REGISTER_H
#define VIRTUALCPU_REGISTER_H

#include "bus/Bus.h"
#include "Block.h"

template<typename T>
class Register : public Block<T>{
public:
    T value=0x00;
    bool enable=false;
    bool load=false;
    void tick() override;
    void update() override;

private:

};

template<typename T>
void Register<T>::tick() {
    if(enable) {
        this->bus->value|=value;
    }
    if(load){
        value=this->bus->value;
    }
}

template<typename T>
void Register<T>::update() {
    if(enable) {
        this->bus->value|=value;
    }
}


#endif //VIRTUALCPU_REGISTER_H
