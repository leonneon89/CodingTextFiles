#include "fileType.h"
#include <QDebug>

FileType::FileType(QObject *parent):
    QObject(parent)
{
}

FileType::~FileType()
{
}

void FileType::setFileTypes(QString strTypes)
{
    types = strTypes.split(QRegExp(";|,| |:"), QString::SkipEmptyParts);

    QMutableListIterator<QString> it(types);
    QString type;
    while(it.hasNext()) {
        type = it.next();
        type.push_front(".");
        it.setValue(type);
        qDebug() << "[FileTypes]. " << type;
    }
}

QStringList FileType::getFileTypes()
{
    return types;
}

