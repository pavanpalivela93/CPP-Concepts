#ifndef CONSUMER
#define CONSUMER

#include "mediator1.h"
#include "mediator2.h"

class Consumer : public Mediator1, public Mediator2
{
public:
    Consumer(int x, int y, std::string &name);
    int getCost() const override;
};
#endif