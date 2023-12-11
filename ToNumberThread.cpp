#include "ToNumberThread.h"
std::mutex       ToNumberThread::mut;
QVector<Item *>  ToNumberThread::_items;

ToNumberThread::ToNumberThread(QObject *parent):
  QObject(parent)
{
}

void  ToNumberThread::run2()
{
  int  ThreadID = _ThreadID.toInt();

  for (int i = ((ThreadID - 1) * 1000); i < (ThreadID * 1000); i++)
  {
    QJsonObject  qobj  = _jsonArrForRead[i].toObject();
    int          qid   = QString(qobj.value("_id").toString()).toInt();
    QString      qname = qobj.value("_name").toString();
// qInfo() << qid << "  " << qname;

    mut.lock();

    _items.push_back(new Item(qid, qname));

    mut.unlock();
  }

  emit  goForResult(_items);
}

void  ToNumberThread::setThreadID(const QString &value)
{
  _ThreadID = value;
}

void  ToNumberThread::setJsonArrForRead(const QJsonArray &jsonArrForRead)
{
  _jsonArrForRead = jsonArrForRead;
}
