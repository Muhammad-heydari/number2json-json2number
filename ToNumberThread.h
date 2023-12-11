#ifndef THREAD2_H
#define THREAD2_H
#include <QObject>
#include <QDebug>
#include <QMap>
#include <QChar>
#include <QJsonArray>
#include <QVector>
#include <mutex>
#include "Item.h"

class ToNumberThread: public QObject
{
  Q_OBJECT

public:
  ToNumberThread(QObject *parent = 0);

  ~ToNumberThread() = default;

  ///
  /// \brief start thread (part 2)
  ///
  void  run2();

  void  setThreadID(const QString &value);

  void  setJsonArrForRead(const QJsonArray &jsonArrForRead);

signals:
  ///
  /// \brief goForResult
  /// \param myvec
  /// \connect_to: &Part2::showResult
  /// for get all result from multiThread
  void  goForResult(QVector<Item *> myvec);

protected:
private:
  QString                 _ThreadID;    // current Thread
  QJsonArray              _jsonArrForRead; // get json from part 2
  static QVector<Item *>  _items; // get all result as Vector from multiThreading
  static std::mutex       mut;
};

#endif // THREAD2_H
