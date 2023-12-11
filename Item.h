#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include <QJsonObject>
class Item
{
public:
  Item();

  ~Item() = default;

  Item(int id, QString name);

  void  setId(int id);

  void  setName(QString &name);

  int  getId() const;

  QString  getName() const;

protected:
private:
  int      _id   = 0;
  QString  _name = "";
};

#endif // ITEM_H
