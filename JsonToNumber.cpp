#include "JsonToNumber.h"
#include "ToNumberThread.h"

JsonToNumber::JsonToNumber(QObject *parent):
  QObject(parent)
{
}

void  JsonToNumber::start(QString myInput)
{
  QFile    file(myInput);
  QString  jsonString;

  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QTextStream  data(&file);
    jsonString = data.readAll();
    file.close();
  }

  QJsonDocument         jsonDoc   = QJsonDocument::fromJson(jsonString.toUtf8());
  QJsonArray            jsonarray = jsonDoc.array();
  QVector<Item>         myvec;
  int                   countItem   = jsonarray.size();
  int                   countThread = countItem / 1000;
  QMap<int, QThread *> *allThread   = new QMap<int, QThread *>;

  _countThread = countThread;

  for (int i = 1; i <= countThread; ++i)
  {
    QThread        *mThread = new QThread;
    ToNumberThread *task    = new ToNumberThread();
    task->moveToThread(mThread);
    connect(mThread, &QThread::started, task, &ToNumberThread::run2);
    connect(mThread, &QThread::finished, task, &ToNumberThread::deleteLater);
    qRegisterMetaType<QVector<Item *>>("QVector<Item*>");
    connect(task, &ToNumberThread::goForResult, this, &JsonToNumber::showResult);
    task->setThreadID(QString::number(i));
    task->setJsonArrForRead(jsonarray);
    mThread->start();
    allThread->insert(i, mThread);
  }
}

void  JsonToNumber::showResult(QVector<Item *> items)
{
  ++_getItemCounter;

  qInfo() << QString::number(_getItemCounter) << " of " << QString::number(_countThread) << "Thread ";

  if (_getItemCounter == _countThread)
  {
    for (Item *item : items)
    {
      qInfo() << QString::number(item->getId()) << "  " << item->getName();
    }
  }

  qInfo() << "JsonToNumber completed!!";
}
