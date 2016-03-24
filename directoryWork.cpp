#include "directoryWork.h"
#include <QDebug>

DirectoryWork::DirectoryWork(QObject *parent):
    QObject(parent)
{
}

DirectoryWork::~DirectoryWork()
{
}

void DirectoryWork::setDirectoryPath(const QString path)
{
    if(isDirectory(path)) {
        path_ = path;
        qDebug() << "[DirectoryPath]. Directory Path:" << path;
    } else {
        qDebug() << "[DirectoryPath]. Directory doesn't exist! Path:" << path;
    }
}

QString DirectoryWork::getDirectoryPath()
{
    return path_;
}

bool DirectoryWork::isDirectory(const QString path)
{
    QDir dir(path);
    return dir.exists();
}

void DirectoryWork::processDirectory()
{
    listNames.clear();
    QDirIterator iterator(path_, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext())
    {
       iterator.next();
       QString str = iterator.fileInfo().absoluteFilePath();
       QString strName = iterator.fileInfo().baseName();

       if(str.endsWith(".cpp") || str.endsWith(".h") || str.endsWith(".hpp")) {
           if(!strName.startsWith("moc_") && !strName.startsWith("ui_"))
               listNames.append(str);
       }
    }

    QString strPath;
    foreach (strPath, listNames) {
       qDebug() << strPath;
    }
}

QList<QString> &DirectoryWork::getListNames()
{
    return listNames;
}
