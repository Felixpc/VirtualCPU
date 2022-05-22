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
    void addBlock(Block<T>* block);
    void tick();
private:
};
template<typename T>
void Clock<T>::tick() {
    for (auto &block : blocks) {
        block->tick();
    }



}
template<typename T>
void Clock<T>::addBlock(Block<T>* block) {
    blocks.push_back(block);
}


#endif //VIRTUALCPU_CLOCK_H
