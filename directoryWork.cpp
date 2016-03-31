#include "directoryWork.h"
#include <QDebug>

DirectoryWork::DirectoryWork(QObject *parent):
    QObject(parent)
{
    fileTypes = new FileType;
}

DirectoryWork::~DirectoryWork()
{
}

void DirectoryWork::setDirectoryPath(const QString path)
{
    if(hasDirectory(path)) {
        path_ = path;
        qDebug() << "[DirectoryPath]. Current directory Path:" << path;
    } else {
        qDebug() << "[DirectoryPath]. Selected directory doesn't exist! Path:" << path;
    }
}

QString DirectoryWork::getDirectoryPath()
{
    return path_;
}

bool DirectoryWork::hasDirectory(const QString path)
{
    QDir dir(path);
    return dir.exists();
}

void DirectoryWork::processDirectory()
{
    listNames.clear();
    QDirIterator iterator(path_, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    QStringList fileType = fileTypes->getFileTypes();

    while(iterator.hasNext())
    {
       iterator.next();
       QString str = iterator.fileInfo().absoluteFilePath();
       QString strName = iterator.fileInfo().baseName();

       foreach (QString type, fileType) {
           if(str.endsWith(type)) {
               if(!strName.startsWith("moc_") && !strName.startsWith("ui_")) {
                   listNames.append(str);
               }
           }
       }
    }

    QString strPath;
    foreach (strPath, listNames) {
        qDebug() << "[DirectoryWork]. " << strPath;
    }
}

QList<QString> &DirectoryWork::getListNames()
{
    return listNames;
}

void DirectoryWork::setStringTypes(QString stringTypes)
{
    fileTypes->setFileTypes(stringTypes);
}
