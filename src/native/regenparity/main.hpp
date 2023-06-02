#include <mod.h>

#include "recovered.hpp"

#ifndef REGENPARITY_MAIN_HPP
#define REGENPARITY_MAIN_HPP


class RegenParityModule : public Module {
    public:
    RegenParityModule(): Module("regenparity") {}
    virtual void initialize();
};


#endif //REGENPARITY_MAIN_HPP