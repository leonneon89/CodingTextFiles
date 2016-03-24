#include "encodingFile.h"
#include <QDebug>
#include <QTextCodec>
#include <iostream>

using namespace std;

EncodingFile::EncodingFile(QObject *parent) :
    QObject(parent)
{
}

EncodingFile::~EncodingFile()
{
}

void EncodingFile::setFileName(const QString fileName) {
    fileName_ = fileName;
}

QString EncodingFile::getFileName() {
    return fileName_;
}

void EncodingFile::processFile()
{
    QString encodeTypeName = getEncodingType(RUSSIAN);

    if(encodeTypeName != getCodeFileName(UTF_8) && encodeTypeName != getCodeFileName(ASCII)) {
        qDebug() << "This is not UTF-8 encoding. Current encoding:" << encodeTypeName;
        encodeFile(encodeTypeName);
    } else {
        qDebug() << "Get file codding: " << encodeTypeName;
    }
}

QString EncodingFile::getLanguageName(Languages language)
{
    QString lang;
    switch (language)
    {
        case RUSSIAN: lang = "ru"; break;
        case ENGLISH: lang = "en"; break;
        case KOREAN: lang = "ko"; break;
        case BELARUS: lang = "be"; break;
        default: break;
    }
    return lang;
}

QString EncodingFile::getCodeFileName(Codings code)
{
    QString currCode;
    switch (code)
    {
        case UTF_8: currCode = "UTF-8"; break;
        case ASCII: currCode = "ASCII"; break;
        case WINDOWS_1251: currCode = "CP1251"; break;
        case KOI8_R: currCode = "KOI8-R"; break;
        default: break;
    }
    return currCode;
}

QString EncodingFile::getEncodingType(Languages language)
{
    setTextCodec(getCodeFileName(ASCII));
    updateContentFile();

    QString buff = getBufferOfContent();
    int sizeOfBuff = buff.size();

    EncaAnalyser enca = enca_analyser_alloc(getLanguageName(language).toStdString().c_str());
    unsigned char *buffStr =(unsigned char *) malloc (sizeOfBuff);
    memset(buffStr, 0, sizeof(sizeOfBuff));
    memcpy(buffStr, buff.toStdString().c_str(), sizeOfBuff);
    EncaEncoding enc = enca_analyse(enca, buffStr, sizeOfBuff);
    free(buffStr);
    enca_analyser_free(enca);
    return enca_charset_name(enc.charset, ENCA_NAME_STYLE_ENCA);
}

void EncodingFile::encodeFile(QString sourceCodeName)
{
    setTextCodec(sourceCodeName);
    updateContentFile();
    encodingFile(getCodeFileName(UTF_8));
}

QList<QString> EncodingFile::getContentFile(QString absPathName)
{
    QList<QString> listString;
    QFile fileIn(absPathName);
    if(!fileIn.open(QIODevice::ReadOnly)) {
        qDebug() << "[EncodingFile]. Error open source file for writing:" << fileName_.toStdString().c_str();
    }
    while (!fileIn.atEnd()) {
        listString.append(fileIn.readLine());
    }
    fileIn.close();
    return listString;
}

void EncodingFile::changeEndLines(bool winStyle)
{
    QMutableListIterator<QString> it(contentFile);
    QString line;
    while(it.hasNext()) {
        line = it.next();
        if(winStyle) {
            it.setValue(line.replace("\n", "\r\n"));
        } else {
            it.setValue(line.replace("\r\n", "\n"));
        }
    }
}

void EncodingFile::setTextCodec(QString codeName)
{
    pCodec = QTextCodec::codecForName(codeName.toStdString().c_str());
    QTextCodec::setCodecForTr(pCodec);
    QTextCodec::setCodecForCStrings(pCodec);
    QTextCodec::setCodecForLocale(pCodec);
}

QString EncodingFile::getBufferOfContent()
{
    QString buff;
    QListIterator<QString> it(contentFile);
    while(it.hasNext()) {
        buff.append(it.next());
    }
    return buff;
}

void EncodingFile::updateContentFile()
{
    if(!contentFile.isEmpty())
        contentFile.clear();

    contentFile = getContentFile(fileName_);
}

void EncodingFile::encodingFile(QString codeName)
{
    setTextCodec(codeName);

    QFile fileOut(fileName_);
    if(!fileOut.open(QIODevice::ReadWrite)) {
        qDebug() << "[EncodingFile]. Error open source file for writing:" << fileName_.toStdString().c_str();
    }

    QString hatFile = tr("// Encoding to ") + codeName + "\n";
    QTextStream out(&fileOut);
    out.seek(0);
    out.setCodec(pCodec);
    out << hatFile;
    foreach(QString line, contentFile) {
        out << line;
    }
    fileOut.close();
}
