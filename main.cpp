#include <iostream>
#include "CPU/bus/Bus.h"
#include "CPU/Register.h"
#include "CPU/Clock.h"
#include "CPU/ALU.h"
#include "CPU/RAM.h"
#include "CPU/PC.h"

Bus<uint8_t> bus=Bus<uint8_t>();

Clock<uint8_t> clock1=Clock<uint8_t>();

Register<uint8_t> reg_A;
Register<uint8_t> reg_B;

Register<uint8_t> instruction_register;

ALU<uint8_t> alu;

RAM<uint8_t, uint8_t, 16> ram;

PC<uint8_t> pc;

void update(){
    bus.value=0x00;

    reg_A.update();
    reg_B.update();
    alu.update();
    ram.update();
    instruction_register.update();
    pc.update();
}

void buildup(){
    clock1.addBlock(&alu);
    clock1.addBlock(&reg_A);
    clock1.addBlock(&reg_B);
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

    ram.set(new uint8_t[16]{0x07,
                                0x08,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00
    });


    alu.input1=&reg_A;
    alu.input2=&reg_B;

    alu.output.setBus(&bus);


}


int main() {
    std::cout << "Hello, World!" << std::endl;

    buildup();

    reg_A.enable=false;
    reg_B.enable=false;
    reg_A.load=false;
    reg_B.load=false;
    alu.enable=false;

    instruction_register.enable=false;
    instruction_register.load=false;

    ram.addressRegister.enable=false;
    ram.enable=false;
    ram.addressRegister.load=false;
    ram.load=false;

    ram.addressRegister.value=0x01;


    ram.enable=true;
    reg_A.load=true;

    pc.counterenable=true;

    update();
    clock1.tick();
    update();
    pc.counterenable=false;

    ram.enable=false;
    reg_A.load=false;

    pc.enable=true;
    ram.addressRegister.value=0x05;
    ram.load=true;

    update();
    clock1.tick();
    update();

    printf("A: 0x%02X\n", reg_A.value);
    printf("B: 0x%02X\n", reg_B.value);
    printf("alu: 0x%02X\n", alu.output.value);
    printf("ram5: 0x%02X\n", ram.data[5]);


/*
    reg_A.value=0x02;

    reg_A.enable=true;
    reg_B.load=true;


    update();
    clock1.tick();
    update();

    printf("A: 0x%02X\n", reg_A.value);
    printf("B: 0x%02X\n", reg_B.value);
    printf("alu: 0x%02X\n", alu.output.value);

    printf("bus: 0x%02X\n", bus.value);

    reg_A.enable=false;
    reg_B.load=false;
    reg_B.enable=false;
    reg_A.load=true;
    alu.enable=true;

    update();
    clock1.tick();
    update();

    printf("A: 0x%02X\n", reg_A.value);
    printf("B: 0x%02X\n", reg_B.value);
    printf("alu: 0x%02X\n", alu.output.value);

    printf("bus: 0x%02X\n", bus.value);
*/

    return 0;
}
