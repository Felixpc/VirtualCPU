//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_RAM_H
#define VIRTUALCPU_RAM_H

#include "Block.h"
#include "Register.h"

template<typename T, typename addrtype, int depth>
class RAM : public Block<T>{
public:


    Register<addrtype> addressRegister;
    void tick() override;
    void update() override;
    void set(const T m[depth]);

    bool enable=false;
    bool load=false;
    T data[depth];
private:
};

template<typename T, typename addrtype, int depth>
void RAM<T, addrtype, depth>::tick() {
    if(enable) {
        this->bus->value|=(data[addressRegister.value]&this->busmaskOut);
    }
    if(load) {
        data[addressRegister.value]=(this->bus->value&this->busmaskIn);
    }
    addressRegister.tick();
}

template<typename T, typename addrtype, int depth>
void RAM<T, addrtype, depth>::update() {
    if(enable) {
        this->bus->value|=(data[addressRegister.value]&this->busmaskOut);
    }
    addressRegister.update();
}

template<typename T, typename addrtype, int depth>
void RAM<T, addrtype, depth>::set(const T m[depth]){
        for(int j = 0; j < depth; j++){
            this->data[j] = m[j];
        }
}


#endif //VIRTUALCPU_RAM_H
