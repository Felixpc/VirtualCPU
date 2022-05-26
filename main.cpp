#include <cstdio>
#include <atomic>
#include "CPU/bus/Bus.h"
#include "CPU/Register.h"
#include "CPU/Clock.h"
#include "CPU/ALU.h"
#include "CPU/RAM.h"
#include "CPU/PC.h"
#include "CPU/Controller.h"

Bus<uint8_t> bus=Bus<uint8_t>();

Clock<uint8_t> clock1=Clock<uint8_t>();

Register<uint8_t> reg_A;
Register<uint8_t> reg_B;
Register<uint8_t> reg_out;


Register<uint8_t> instruction_register;

ALU<uint8_t> alu;

RAM<uint8_t, uint8_t, 16> ram;

PC<uint8_t> pc;

Controller<uint8_t, 15> controller;

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

    ram.set(new uint8_t[16]{0b01010011,
                                0b01001111,
                                0b01010000,
                                0b00101111,
                                0b11100000,
                                0b01100011,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                0x00,
                                7,
                                6,
                                5
    });

    controller.defineControllBits(new bool *[15]{
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
    });







    alu.input1=&reg_A;
    alu.input2=&reg_B;

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


/*
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
*/



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
