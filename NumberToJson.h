#ifndef PART1_H
#define PART1_H
#include <QThread>
#include <QObject>
#include <iostream>
#include <QVector>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "Item.h"

class NumberToJson: public QObject
{
  Q_OBJECT

public:
  NumberToJson(QObject *parent = 0);

  ~NumberToJson() = default;

  void  start(int myInt);

public slots:
  void  CompleteJson();

protected:
private:
  int              countThread    = 0;
  int              getItemCounter = 0;
  QVector<Item *>  resultVec;
  QString          _fileName;
};

#endif // PART1_H
