#include "consumer.h"

int main()
{
    std::string str = "navya";
    Consumer *c = new Consumer(10, 10, str);
    std::cout << c->getCost() << "\n";

    Supplier *c1 = new Consumer(10, 10, str);
    std::cout << c1->getCost() << "\n";

    Supplier *m1 = new Mediator1(10, 10, str);
    std::cout << m1->getCost() << "\n";

    Supplier *m2 = new Mediator2(10, 10, str);
    std::cout << m2->getCost() << "\n";
}
