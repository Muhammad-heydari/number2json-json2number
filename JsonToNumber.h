#ifndef PART2_H
#define PART2_H
#include <QString>
#include <QTextStream>
#include <QtDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QThread>
#include <QObject>
#include "Item.h"


class JsonToNumber: public QObject
{
  Q_OBJECT

public:
  JsonToNumber(QObject *parent = 0);

  ~JsonToNumber() = default;

  void  start(QString myInput);

public slots:
  void  showResult(QVector<Item *> );

protected:
private:
  int  _countThread    = 0;
  int  _getItemCounter = 0;
};

#endif // PART2_H
