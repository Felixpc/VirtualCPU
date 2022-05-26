//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_ALU_H
#define VIRTUALCPU_ALU_H

#include "Block.h"
#include "Register.h"

template<typename T>
class ALU : public Block<T> {
public:
    ALU(){
        output.setBus(this->bus);
    }

    Register<T> *input1;
    Register<T> *input2;
    Register<T> output;

    bool enable=false;
    bool subtract=false;

    bool flag_carry=false;
    bool flag_zero=false;

    bool updateflags=false;

    void tick() override;
    void update() override;
private:
};

template<typename T>
void ALU<T>::tick() {

}

template<typename T>
void ALU<T>::update() {
    if(subtract){
        output.value=(input1->value - input2->value);
    }else{
        output.value=(input1->value + input2->value);
        if(updateflags) {
            if ((input1->value + input2->value) > 255) {
                flag_carry = true;
            } else {
                flag_carry = false;
            }
            if(input1->value + input2->value == 0 || input1->value - input2->value == 0) {
                flag_zero = true;
            }
        }
    }
    if(enable) {
        output.enable=true;
    }else{
        output.enable=false;
    }
    output.update();
}

#endif //VIRTUALCPU_ALU_H
