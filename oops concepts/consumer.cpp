#include "consumer.h"

Consumer::Consumer(int x, int y, std::string &name) : Supplier(x, y, name), Mediator1(x, y, name), Mediator2(x, y, name)
{
}

int Consumer::getCost() const
{
    return Mediator1::getCost() + Mediator2::getCost();
}