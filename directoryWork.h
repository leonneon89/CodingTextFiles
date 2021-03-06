#ifndef DIRECTORYWORK_H
#define DIRECTORYWORK_H

#include <QObject>
#include <QDir>
#include <QDirIterator>
#include "fileType.h"

class DirectoryWork : public QObject
{
    Q_OBJECT

public:
    explicit DirectoryWork(QObject *parent = 0);
    ~DirectoryWork();

    void setDirectoryPath(const QString path);
    QString getDirectoryPath();
    bool hasDirectory(const QString path);
    void processDirectory();
    QList<QString> &getListNames();
    void setStringTypes(QString stringTypes);

private:
    FileType* fileTypes;
    QString path_;
    QList<QString> listNames;
};

#endif // DIRECTORYWORK_H
