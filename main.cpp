#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QtDebug>
#include <QThread>
#include "ToJsonThread.h"
#include "NumberToJson.h"
#include "JsonToNumber.h"
#include <QTimer>

int  main(int argc, char *argv[])
{
  QCoreApplication  a(argc, argv);
  QTimer            timer;

  timer.start();

  std::string  myInputAsString;
  std::cout << "Enter number or fileName :(number x1000) (1'000<number<100'000) : ";
  std::cin >> myInputAsString;
  QString  myInput            = QString::fromStdString(myInputAsString);
  bool     CheckInputISNumber = false;

  myInput.toInt(&CheckInputISNumber);
  QFile  file(myInput);

  if (CheckInputISNumber == true)
  {
    int  myInt = myInput.toInt();

    if ((myInt <= 100000) && (myInt >= 1000))
    {
      qInfo() << "ok!! start NumberToJson";

      NumberToJson *part1 = new NumberToJson;
      part1->start(myInt);
    }
    else
    {
      qInfo() << "wrong number";

      return 0;
    }
  }
  else if (!file.exists())
  {
    qInfo() << "fileName not exist!!";
  }
  else
  {
    qInfo() << "ok!! start JsonToNumber from my Folder";
    JsonToNumber *part2 = new JsonToNumber;
    part2->start(myInput);
  }

  timer.remainingTime();
  timer.stop();

  return a.exec();
}
