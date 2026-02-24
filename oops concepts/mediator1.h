#ifndef MEDIATOR_1
#define MEDIATOR_1

#include "Supplier.h"
class Mediator1 : public virtual Supplier
{
public:
    Mediator1(int x, int y, std::string &name);
    int getCost() const override;
};

#endif