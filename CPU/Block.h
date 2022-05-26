//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_BLOCK_H
#define VIRTUALCPU_BLOCK_H

template<typename T>
class Block {
public:
    virtual void tick() = 0;
    virtual void update() = 0;
    Bus<T> *bus;
    T busmaskIn=0xFF;
    T busmaskOut=0xFF;
    void setBus(Bus<T> *bus);
};

template<typename T>
void Block<T>::setBus(Bus<T> *bus) {
    this->bus = bus;
}

#endif //VIRTUALCPU_BLOCK_H
