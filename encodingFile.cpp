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
    QFile file(fileName_);
    if (!file.open(QIODevice::ReadWrite)) {
        cout << "Error open source file:" << fileName_.toStdString().c_str() << endl;
        return;
    }

    cout << "Open source file:" << fileName_.toStdString().c_str() << endl;

    QString line;
    while (!file.atEnd()) {
        line = file.readLine();
        allLines.append(line);
        cout << line.toStdString().c_str();
    }
    cout << endl;
    file.close();

    EncaAnalyser enca = enca_analyser_alloc("ru");
    int sizeOfFile = allLines.size();
    unsigned char *buffStr =(unsigned char *) malloc (sizeOfFile);
    memset(buffStr, 0, sizeof(sizeOfFile));
    memcpy(buffStr, allLines.toStdString().c_str(), sizeOfFile);
    EncaEncoding enc = enca_analyse(enca, buffStr, sizeOfFile);

    qDebug("[%d]=%s", ENCA_NAME_STYLE_HUMAN, enca_charset_name(enc.charset, ENCA_NAME_STYLE_HUMAN));
    qDebug("[%d]=%s", ENCA_NAME_STYLE_ENCA, enca_charset_name(enc.charset, ENCA_NAME_STYLE_ENCA));

    enca_analyser_free(enca);
    free(buffStr);

//    QTextCodec *pCodec = QTextCodec::codecForName("utf-8");
//    QTextCodec::setCodecForCStrings( pCodec);


//    QString lineCommon;


//    EncaAnalyser enca = enca_analyser_alloc("ru");

//    unsigned char str[lineCommon.size()];
//    memset(str, 0, sizeof(str));
//    QString tempStr;
//    tempStr.append(fileList_.at(0).toStdString().c_str());
//    tempStr.append(fileList_.at(1).toStdString().c_str());
//    tempStr.append(fileList_.at(2).toStdString().c_str());
//    tempStr.append(fileList_.at(3).toStdString().c_str());

//    memcpy(str, tempStr.toStdString().c_str(), tempStr.size());

//    memcpy(str, lineCommon.toStdString().c_str(), lineCommon.size());

//    EncaEncoding enc = enca_analyse(enca, str, sizeof(str));

//    qDebug("[%d]=%s", ENCA_NAME_STYLE_HUMAN, enca_charset_name(enc.charset, ENCA_NAME_STYLE_HUMAN));
//    enca_analyser_free(enca);

//    pCodec = QTextCodec::codecForName("Windows-1251");
//    QTextCodec::setCodecForCStrings(pCodec);

//    QString fileNameWrite = fileName_;
//    fileNameWrite.replace(fileNameWrite.indexOf('.'), 0, "_");

//    QFile fileWrite(fileNameWrite);
//    if( !fileWrite.open( QIODevice::WriteOnly))
//    {
//        cout << "Can'not open file for write" << endl;
//        return;
//    }

//    QTextStream in( &fileWrite);
////    in.setCodec(pCodec);

//    fileList_.push_front("//Current coding windows-1251\n");
//    QListIterator<QString> i(fileList_);
//    while (i.hasNext())
//        in << i.next();
    //    fileWrite.close();
}

QString EncodingFile::getEncodingType()
{
    QFile file(fileName_);
    if (!file.open(QIODevice::ReadWrite)) {
//        cout << "Error open source file:" << fileName_.toStdString().c_str() << endl;
//        return;
    }

    cout << "Open source file:" << fileName_.toStdString().c_str() << endl;

    QString line;
    while (!file.atEnd()) {
        line = file.readLine();
        allLines.append(line);
        cout << line.toStdString().c_str();
    }
    cout << endl;
    file.close();

    EncaAnalyser enca = enca_analyser_alloc("ru");
    int sizeOfFile = allLines.size();
    unsigned char *buffStr =(unsigned char *) malloc (sizeOfFile);
    memset(buffStr, 0, sizeof(sizeOfFile));
    memcpy(buffStr, allLines.toStdString().c_str(), sizeOfFile);
    EncaEncoding enc = enca_analyse(enca, buffStr, sizeOfFile);
    enca_analyser_free(enca);
    free(buffStr);
    QString coding = enca_charset_name(enc.charset, ENCA_NAME_STYLE_ENCA);
    return coding;
}
