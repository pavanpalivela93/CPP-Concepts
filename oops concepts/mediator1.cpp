#include "mediator1.h"
Mediator1::Mediator1(int x, int y, std::string &name) : Supplier(x, y, name)
{
}
int Mediator1::getCost() const
{
    return 100;
}