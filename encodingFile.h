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
        BELARUSSIAN,
        BULGARIAN,
        CZECH,
        ESTONIAN,
        CROATIAN,
        HUNGARIAN,
        LITHUANIAN,
        LATVIAN,
        POLISH,
        RUSSIAN,
        SLOVAK,
        SLOVENE,
        UKRAINIAN,
        CHINESE
    };

    enum Codings
    {
        UTF_7,
        UTF_8,
        WINDOWS_1251,
        ASCII,
        KOI8_R,
        KOI8_U
    };

public:
    explicit EncodingFile(QObject *parent = 0);
    ~EncodingFile();
    void setFileName(const QString fileName);
    QString getFileName();
    void processFile();
    void changeEndLines(bool winStyle);


private slots:
    QString getLanguageName(Languages language);
    QString getCodeFileName(Codings code);
    QString getEncodingType(Languages language);
    void encodeFile(QString sourceCodeName);
    QList<QString> getContentFile(QString absPathName);
    void setTextCodec(QString codeName);
    QString getBufferOfContent();
    void updateContentFile();
    void encodingFile(QString codeName);

private:
    QString fileName_;
    QString allLines;
    QList<QString> contentFile;
    QTextCodec *pCodec;        
};

#endif // ENCODINGFILE_H
