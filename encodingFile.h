#ifndef ENCODINGFILE_H
#define ENCODINGFILE_H

#include <QObject>
#include <QFile>
#include <enca.h>

class EncodingFile : public QObject
{
    Q_OBJECT

public:
    explicit EncodingFile(QObject *parent = 0);
    ~EncodingFile();
    void setFileName(const QString fileName);
    QString getFileName();
    void processFile();

private slots:
    QString getEncodingType();

private:
    QString fileName_;
    QString allLines;
};

#endif // ENCODINGFILE_H
