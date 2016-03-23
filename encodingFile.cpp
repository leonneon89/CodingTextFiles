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
    QFile file(fileName_);
    if(!file.open(QIODevice::ReadOnly)) {
        cout << "[EncodingFile]. Error open source file for reading:" << fileName_.toStdString().c_str() << endl;
    }

    cout << "[EncodingFile]. Open source file:" << fileName_.toStdString().c_str() << endl;

    allLines.clear();
    while (!file.atEnd()) {
        allLines.append(file.readLine());
    }
    file.close();

    EncaAnalyser enca = enca_analyser_alloc(getLanguageName(language).toStdString().c_str());
    int sizeOfFile = allLines.size();
    unsigned char *buffStr =(unsigned char *) malloc (sizeOfFile);
    memset(buffStr, 0, sizeof(sizeOfFile));
    memcpy(buffStr, allLines.toStdString().c_str(), sizeOfFile);
    EncaEncoding enc = enca_analyse(enca, buffStr, sizeOfFile);
    free(buffStr);
    enca_analyser_free(enca);
    QString coding = enca_charset_name(enc.charset, ENCA_NAME_STYLE_ENCA);
    return coding;
}

void EncodingFile::encodeFile(QString sourceCodeName)
{
    QTextCodec *pCodec = QTextCodec::codecForName(sourceCodeName.toStdString().c_str());
    QTextCodec::setCodecForTr(pCodec);
    QTextCodec::setCodecForCStrings(pCodec);

    QFile fileWrite(fileName_);
    if(!fileWrite.open(QIODevice::ReadWrite)) {
        cout << "[EncodingFile]. Error open source file for writing:" << fileName_.toStdString().c_str() << endl;
    }

    allLines.clear();
    while (!fileWrite.atEnd()) {
        allLines.append(fileWrite.readLine());
    }

    pCodec = QTextCodec::codecForName(getCodeFileName(UTF_8).toStdString().c_str());
    QTextCodec::setCodecForTr(pCodec);
    QTextCodec::setCodecForCStrings(pCodec);

    QString hatFile = tr("// Encoding for ") + getCodeFileName(UTF_8) + "\n";
    QTextStream out(&fileWrite);
    out.seek(0);
    out.setCodec(pCodec);
    out << hatFile;
    out << allLines;
    fileWrite.close();
}
