#ifndef MEDIATOR_2
#define MEDIATOR_2

#include "Supplier.h"
class Mediator2 : public virtual Supplier
{
public:
    Mediator2(int x, int y, std::string &name);
    int getCost() const override;
};

#endif