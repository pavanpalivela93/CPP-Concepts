#include "mediator2.h"
Mediator2::Mediator2(int x, int y, std::string &name) : Supplier(x, y, name)
{
}
int Mediator2::getCost() const
{
    return 200;
}