//
// Created by felix on 26.05.22.
//

#ifndef VIRTUALCPU_FLAGREGISTER_H
#define VIRTUALCPU_FLAGREGISTER_H

#include <vector>

class FlagRegister {
public:
    std::vector<bool*> flags = std::vector<bool*>();
    int index=0;
    void addFlag(bool *b);
    int getflag_n();
private:
};

void FlagRegister::addFlag(bool *b) {
    flags.push_back(b);
}

int FlagRegister::getflag_n() {
    int flags_n=0;
    for(int i=0; i<flags.size(); i++) {
        flags_n|=*flags[i]?(1<<i):0;
    }
    return flags_n;
}

#endif //VIRTUALCPU_FLAGREGISTER_H
