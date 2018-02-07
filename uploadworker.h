#ifndef UPLOADWORKER_H
#define UPLOADWORKER_H

#include <QFileInfoList>
#include <QObject>


class UploadWorker: public QObject
{
    Q_OBJECT

public:
    explicit UploadWorker(){}
public slots:
    void doWork(QFileInfoList files,
                QString path,QString sercertKey,
                QString accessKey,QString bucket);
signals:
    void resultReady(int value);
};

#endif // UPLOADWORKER_H
