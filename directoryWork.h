#ifndef DIRECTORYWORK_H
#define DIRECTORYWORK_H

#include <QObject>
#include <QDir>
#include <QDirIterator>

class DirectoryWork : public QObject
{
    Q_OBJECT

public:
    explicit DirectoryWork(QObject *parent = 0);
    ~DirectoryWork();

    void setDirectoryPath(const QString path);
    QString getDirectoryPath();
    bool isDirectory(const QString path);
    void processDirectory();
    QList<QString> &getListNames();

private:
    QString path_;
    QList<QString> listNames;
};

#endif // DIRECTORYWORK_H
