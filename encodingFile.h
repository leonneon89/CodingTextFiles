#ifndef ENCODINGFILE_H
#define ENCODINGFILE_H

#include <QObject>
#include <QFile>
#include <enca.h>

class EncodingFile : public QObject
{
    Q_OBJECT

    enum Languages
    {
        RUSSIAN,
        ENGLISH,
        KOREAN,
        BELARUS
    };

    enum Codings
    {
        UTF_8,
        WINDOWS_1251,
        ASCII,
        KOI8_R
    };

public:
    explicit EncodingFile(QObject *parent = 0);
    ~EncodingFile();
    void setFileName(const QString fileName);
    QString getFileName();
    void processFile();

private slots:
    QString getLanguageName(Languages language);
    QString getCodeFileName(Codings code);
    QString getEncodingType(Languages language);
    void encodeFile(QString sourceCodeName);

private:
    QString fileName_;
    QString allLines;
};

#endif // ENCODINGFILE_H
