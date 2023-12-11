#ifndef THREAD_H
#define THREAD_H
#include <QObject>
#include <QDebug>
#include <QMap>
#include <QChar>
#include <QJsonArray>
#include <QVector>
#include <QJsonDocument>
#include <QFile>
#include <mutex>
#include "Item.h"


class ToJsonThread: public QObject
{
  Q_OBJECT

public:
  ToJsonThread(QObject *parent = 0);

  ~ToJsonThread() = default;

  ToJsonThread(int countItem);

  ///
  /// \brief start thread (part 1)
  ///
  void  run1();

  void  setThreadID(const QString &value);

  void  setJsonArrForRead(const QJsonArray &jsonArrForRead);

  void  setFileName(const QString &fileName);

signals:
  ///
  /// \brief goForcreateJson
  /// \param myvec
  /// \connect_to :&Part1::completeJson
  /// for get all result from multiThread
  void  goCompleteJson();

protected:
private:
  QString            _ThreadID;         // current Thread
  QVector<Item *>    _myVec; // get all (Item*) and connect to Part1
  static std::mutex  mut;
  QString            _fileName;
};

#endif // THREAD_H
