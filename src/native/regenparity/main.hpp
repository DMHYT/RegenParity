#include <mod.h>

#include "recovered.hpp"

#ifndef REGENPARITY_MAIN_HPP
#define REGENPARITY_MAIN_HPP


class RegenParityModule : public Module {
    public:
    static void tickHungerAttributeDelegate(HungerAttributeDelegate*);
    static void healForExhaustion(HungerAttributeDelegate*, Player*);
    RegenParityModule(): Module("regenparity") {}
    virtual void initialize();
};


#endif //REGENPARITY_MAIN_HPP