#include "NumberToJson.h"
#include <QTextStream>
#include "ToJsonThread.h"

NumberToJson::NumberToJson(QObject *parent):
  QObject(parent)
{
  _fileName = "item.json";
}

void  NumberToJson::start(int myInt)
{
  QMap<int, QThread *> *allThread = new QMap<int, QThread *>;

  countThread = myInt / 1000;
  char   myChar = 'a';
  QFile  file(_fileName);

  if (file.open(QIODevice::Text | QIODevice::WriteOnly))
  {
    QTextStream  out(&file);
    out << "[\n";
    file.close();
  }

  for (int i = 1; i <= countThread; ++i)
  {
    QThread      *mThread = new QThread;
    ToJsonThread *task    = new ToJsonThread;
    task->moveToThread(mThread);
    connect(mThread, &QThread::started, task, &ToJsonThread::run1);
    connect(mThread, &QThread::finished, task, &ToJsonThread::deleteLater);
    connect(task, &ToJsonThread::goCompleteJson, this, &NumberToJson::CompleteJson);
    QChar  qChar = myChar;
    task->setThreadID(QString(qChar));
    task->setFileName(_fileName);
    mThread->start();
    allThread->insert(myChar, mThread);
    ++myChar;
  }
}

void  NumberToJson::CompleteJson()
{
  getItemCounter++;

  qInfo() << QString::number(getItemCounter) + "  " + QString::number(countThread);

  if (getItemCounter == countThread)
  {
    QFile    file(_fileName);
    QString  jsonString;

    if (file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
      QTextStream  out(&file);
      jsonString = out.readAll();
      file.close();
    }

    jsonString.remove(jsonString.lastIndexOf(','), jsonString.size());

    if (file.open(QIODevice::Text | QIODevice::WriteOnly))
    {
      QTextStream  out(&file);
      out << jsonString;
      out << ']';
      file.close();
    }

    qInfo() << "NumberToJson completed!! (check:{build-file}/item.json";
  }
}
