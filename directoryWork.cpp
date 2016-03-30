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
        qDebug() << "[DirectoryWork]. " << strPath;
    }
}

QList<QString> &DirectoryWork::getListNames()
{
    return listNames;
}
