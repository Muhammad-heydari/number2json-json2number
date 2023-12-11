#include "ToJsonThread.h"
std::mutex  ToJsonThread::mut;

ToJsonThread::ToJsonThread(QObject *parent):
  QObject(parent)
{
}

void  ToJsonThread::run1()
{
  for (int i = 1; i <= 1000; ++i)
  {
    Item *item = new Item;
    item->setId(i);
    QString  name = _ThreadID + "-" + QString::number(i);
    item->setName(name);

    _myVec.push_back(item);
  }

  QJsonObject  jsonObject;
  QStringList  jsonList;

  for (Item *item : _myVec)
  {
    jsonObject.insert(QString("_id"), QString::number(item->getId()));
    jsonObject.insert(QString("_name"), QString(item->getName()));
    QJsonDocument  doc(jsonObject);
    QString        strJson(doc.toJson());
    jsonList.append(strJson);
  }

  QFile  file(_fileName);

  if (file.open(QIODevice::Append | QIODevice::WriteOnly))
  {
    QTextStream  out(&file);
    mut.lock();

    for (int i = 0; i < jsonList.size(); ++i)
    {
      out << jsonList.at(i) << ',';
      out.flush();
    }

    mut.unlock();

    file.close();
  }

  emit  goCompleteJson();
}

void  ToJsonThread::setThreadID(const QString &value)
{
  _ThreadID = value;
}

void  ToJsonThread::setFileName(const QString &fileName)
{
  _fileName = fileName;
}
