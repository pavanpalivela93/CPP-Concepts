#include <iostream>

#ifndef SUPPLIER_H
#define SUPPLIER_H
class Supplier
{
private:
  int x;
  int y;
  std::string name;

public:
  Supplier(int _x, int _y, const std::string &_name);
  virtual ~Supplier();
  virtual int getCost() const = 0;
};

#endif