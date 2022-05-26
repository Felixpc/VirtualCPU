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
   /* if(enable) {
        this->bus->value|=(value&this->busmaskOut);
    }*/
    if(load){
        value=(this->bus->value&this->busmaskIn);
    }
}

template<typename T>
void Register<T>::update() {
    if(enable) {
        this->bus->value|=(value&this->busmaskOut);
    }
}


#endif //VIRTUALCPU_REGISTER_H
