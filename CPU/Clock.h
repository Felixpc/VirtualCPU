//
// Created by felix on 21.05.22.
//

#ifndef VIRTUALCPU_CLOCK_H
#define VIRTUALCPU_CLOCK_H

#include <vector>
#include "Block.h"
template<typename T>
class Clock {
public:
    std::vector<Block<T>*> blocks = std::vector<Block<T>*>();
    std::vector<Block<T>*> blockshalf = std::vector<Block<T>*>();

    void addBlock(Block<T>* block);
    void addBlockhalf(Block<T>* block);
    void tick();
    void tickhalf();
    bool halted = false;
private:
};
template<typename T>
void Clock<T>::tick() {
    if(halted) return;
    for (auto &block : blocks) {
        block->tick();
    }



}
template<typename T>
void Clock<T>::addBlock(Block<T>* block) {
    blocks.push_back(block);
}

template<typename T>
void Clock<T>::addBlockhalf(Block<T> *block) {
    blockshalf.push_back(block);
}

template<typename T>
void Clock<T>::tickhalf() {
    if(halted) return;
    for (auto &block : blockshalf) {
        block->tick();
    }
}


#endif //VIRTUALCPU_CLOCK_H
