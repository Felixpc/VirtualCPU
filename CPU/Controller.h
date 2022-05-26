//
// Created by felix on 22.05.22.
//

#ifndef VIRTUALCPU_CONTROLLER_H
#define VIRTUALCPU_CONTROLLER_H


#include <bits/stdint-uintn.h>
#include "Block.h"

template<typename T, int c, typename ControllWordType>
class Controller : public Block<T> {
public:

    void tick() override;
    void update() override;
    void defineControllBits(bool *b[c]);
    void setControllBits(ControllWordType b);
    bool *controllbits[c];
    Register<T> *instructionRegister;
    uint8_t stepcounter=0;

    int flag_n=0;

#define HLT 0b0000000000000001
#define MI 0b0000000000000010
#define RI 0b0000000000000100
#define RO 0b0000000000001000
#define IO 0b0000000000010000
#define II 0b0000000000100000
#define AI 0b0000000001000000
#define AO 0b0000000010000000
#define EO 0b0000000100000000
#define SU 0b0000001000000000
#define BI 0b0000010000000000
#define OI 0b0000100000000000
#define CE 0b0001000000000000
#define CO 0b0010000000000000
#define J 0b0100000000000000
#define FI 0b1000000000000000



    uint16_t instructionset[4][16][8]={
            {
            {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0000 - NOP
            {MI|CO,RO|II|CE,IO|MI,RO|AI,0,0,0,0},// 0001 - LDA
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|FI,0,0,0},// 0010 - ADD
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|SU|FI,0,0,0},// 0011 - SUB
            {MI|CO,RO|II|CE,IO|MI,AO|RI,0,0,0,0},// 0100 - STA
            {MI|CO,RO|II|CE,IO|AI,0,0,0,0,0},// 0101 - LDI
            {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0110 - JMP
            {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0111 - JC
            {MI|CO,RO|II|CE,0,0,0,0,0,0},// 1000 - JZ
            {MI|CO,RO|II|CE,0,0,0,0,0,0},
            {MI|CO,RO|II|CE,0,0,0,0,0,0},
            {MI|CO,RO|II|CE,0,0,0,0,0,0},
            {MI|CO,RO|II|CE,0,0,0,0,0,0},
            {MI|CO,RO|II|CE,0,0,0,0,0,0},
            {MI|CO,RO|II|CE,AO|OI,0,0,0,0,0},// 1110 - OUT
            {MI|CO,RO|II|CE,HLT,0,0,0,0,0},// 1111 - HLT
            },
            {
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0000 - NOP
                    {MI|CO,RO|II|CE,IO|MI,RO|AI,0,0,0,0},// 0001 - LDA
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|FI,0,0,0},// 0010 - ADD
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|SU|FI,0,0,0},// 0011 - SUB
                    {MI|CO,RO|II|CE,IO|MI,AO|RI,0,0,0,0},// 0100 - STA
                    {MI|CO,RO|II|CE,IO|AI,0,0,0,0,0},// 0101 - LDI
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0110 - JMP
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0111 - JC
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},// 1000 - JZ
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,AO|OI,0,0,0,0,0},// 1110 - OUT
                    {MI|CO,RO|II|CE,HLT,0,0,0,0,0},// 1111 - HLT
            },
            {
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0000 - NOP
                    {MI|CO,RO|II|CE,IO|MI,RO|AI,0,0,0,0},// 0001 - LDA
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|FI,0,0,0},// 0010 - ADD
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|SU|FI,0,0,0},// 0011 - SUB
                    {MI|CO,RO|II|CE,IO|MI,AO|RI,0,0,0,0},// 0100 - STA
                    {MI|CO,RO|II|CE,IO|AI,0,0,0,0,0},// 0101 - LDI
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0110 - JMP
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0111 - JC
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 1000 - JZ
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,AO|OI,0,0,0,0,0},// 1110 - OUT
                    {MI|CO,RO|II|CE,HLT,0,0,0,0,0},// 1111 - HLT
            },
            {
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},// 0000 - NOP
                    {MI|CO,RO|II|CE,IO|MI,RO|AI,0,0,0,0},// 0001 - LDA
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|FI,0,0,0},// 0010 - ADD
                    {MI|CO,RO|II|CE,IO|MI,RO|BI,EO|AI|SU|FI,0,0,0},// 0011 - SUB
                    {MI|CO,RO|II|CE,IO|MI,AO|RI,0,0,0,0},// 0100 - STA
                    {MI|CO,RO|II|CE,IO|AI,0,0,0,0,0},// 0101 - LDI
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0110 - JMP
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 0111 - JC
                    {MI|CO,RO|II|CE,IO|J,0,0,0,0,0},// 1000 - JZ
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,0,0,0,0,0,0},
                    {MI|CO,RO|II|CE,AO|OI,0,0,0,0,0},// 1110 - OUT
                    {MI|CO,RO|II|CE,HLT,0,0,0,0,0},// 1111 - HLT
            },

    };
private:
};

template<typename T, int c, typename ControllWordType>
void Controller<T, c, ControllWordType>::tick() {


    setControllBits(instructionset[flag_n][(instructionRegister->value>>4)][stepcounter]);
    printf("step: %d\n",stepcounter);
    stepcounter++;
    if(stepcounter==5)
        stepcounter=0;
}

template<typename T, int c, typename ControllWordType>
void Controller<T, c, ControllWordType>::update() {
   // setControllBits(instructionset[(instructionRegister->value>>4)][stepcounter]);

}

template<typename T, int c, typename ControllWordType>
void Controller<T, c, ControllWordType>::defineControllBits(bool *b[c]) {
    for (int i = 0; i < c; i++) {
        this->controllbits[i] = b[i];
    }
}

template<typename T, int c, typename ControllWordType>
void Controller<T, c, ControllWordType>::setControllBits(ControllWordType b) {

    for (int i = 0; i < c; i++) {
        if((b& (1<< i))==(1<<i)){
            *this->controllbits[i] = true;
        }else{
            *this->controllbits[i] = false;

        }


    }
}


#endif //VIRTUALCPU_CONTROLLER_H
