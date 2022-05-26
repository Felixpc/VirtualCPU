#include <cstdio>
#include <atomic>
#include "CPU/bus/Bus.h"
#include "CPU/Register.h"
#include "CPU/Clock.h"
#include "CPU/ALU.h"
#include "CPU/RAM.h"
#include "CPU/PC.h"
#include "CPU/Controller.h"
#include "CPU/FlagRegister.h"

Bus<uint8_t> bus=Bus<uint8_t>();

Clock<uint8_t> clock1=Clock<uint8_t>();

Register<uint8_t> reg_A;
Register<uint8_t> reg_B;
Register<uint8_t> reg_out;
Register<uint8_t> reg_flags;

Register<uint8_t> instruction_register;

ALU<uint8_t> alu;

RAM<uint8_t, uint8_t, 16> ram;

FlagRegister flagregister;

PC<uint8_t> pc;

Controller<uint8_t, 16, uint16_t> controller;

void update(){
   // controller.update();
    reg_A.update();
    reg_B.update();
    reg_out.update();
    alu.update();
    ram.update();
    instruction_register.update();
    pc.update();
}

void buildup(){
    clock1.addBlockhalf(&controller);

    clock1.addBlock(&alu);
    clock1.addBlock(&reg_A);
    clock1.addBlock(&reg_B);
    clock1.addBlock(&reg_out);
    clock1.addBlock(&ram);
    clock1.addBlock(&instruction_register);
    clock1.addBlock(&pc);




    reg_A.setBus(&bus);
    reg_B.setBus(&bus);
    alu.setBus(&bus);
    ram.addressRegister.setBus(&bus);
    ram.setBus(&bus);
    instruction_register.setBus(&bus);
    pc.setBus(&bus);
    reg_out.setBus(&bus);

    ram.addressRegister.busmaskIn=0x0F;
    instruction_register.busmaskOut=0x0F;
    pc.busmaskOut=0x0F;

    ram.set(new uint8_t[16]{0b01011010,
                                0b01001111,
                                0b01010000,
                                0b00101111,
                                0b11100000,
                                0b01110111,
                                0b01100011,
                                0b11110000,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                7,
                                6,
                                5
    });

    controller.defineControllBits(new bool *[16]{
            &clock1.halted,//HLT
            &ram.addressRegister.load,//MI
            &ram.load,//RI
            &ram.enable,//RO
            &instruction_register.enable,//IO
            &instruction_register.load,//II
            &reg_A.load,//AI
            &reg_A.enable,//AO
            &alu.enable,//EO
            &alu.subtract,//SU
            &reg_B.load,//BI
            &reg_out.load,//OI
            &pc.counterenable,//CE
            &pc.enable,//CO
            &pc.load,//J
            &alu.updateflags,//FI
    });


    flagregister.addFlag(&alu.flag_carry);
    flagregister.addFlag(&alu.flag_zero);



    alu.input1=&reg_A;
    alu.input2=&reg_B;


    //alu.flagsRegister=&reg_flags;

    controller.instructionRegister=&instruction_register;

    alu.output.setBus(&bus);


}

void print(){
    printf("\n---------------------------------\n");
    printf("controll word: ");
    for(int i=0;i<15;i++){
        printf("%d", *controller.controllbits[i]);
    }
    printf("\n");
    printf("ins %d\n", instruction_register.value);
    printf("A %d\n", reg_A.value);
    printf("B %d\n", reg_B.value);
    printf("out %d\n", reg_out.value);
    printf("pc %d\n", pc.value);
    printf("bus %d\n", bus.value);
    printf("memo address %d\n", ram.addressRegister.value);
    printf("ram %d\n", ram.data[ram.addressRegister.value]);
    printf("---------------------------------\n");
}
int main() {


    buildup();

/*
    controller.setControllBits(controller.instructionset[0][0]);

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();

    controller.setControllBits(controller.instructionset[0][1]);

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();

    controller.setControllBits(controller.instructionset[1][2]);

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();


    controller.setControllBits(controller.instructionset[1][3]);
    bus.value=0;

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();

    controller.setControllBits(controller.instructionset[1][4]);
    bus.value=0;

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();

    controller.setControllBits(controller.instructionset[2][0]);
    bus.value=0;

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();

    controller.setControllBits(controller.instructionset[2][1]);
    bus.value=0;

    update();
    clock1.tickhalf();
    update();
    clock1.tick();
    update();

    print();
*/

while(true) {
    bus.value=0x00;
    update();
    controller.flag_n=flagregister.getflag_n();
    clock1.tickhalf();
    bus.value=0x00;

    update();
    clock1.tick();
    bus.value=0x00;

    update();

    print();
    usleep(10000);
if(clock1.halted)break;
}
printf("\n------------\nHLT\n");

    return 0;
}
