#include "Item.h"

Item::Item()
{
}

Item::Item(int id, QString name):
  _id{id}, _name{name}
{
}

void  Item::setId(int id)
{
  _id = id;
}

void  Item::setName(QString &name)
{
  _name = name;
}

int  Item::getId() const
{
  return _id;
}

QString  Item::getName() const
{
  return _name;
}
