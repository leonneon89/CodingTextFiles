#ifndef FILETYPES_H
#define FILETYPES_H

#include <QObject>
#include <QStringList>

class FileType : public QObject
{
    Q_OBJECT

public:
    explicit FileType(QObject *parent = 0);
    ~FileType();
    void setFileTypes(QString strTypes);
    QStringList getFileTypes();

private:
    QStringList types;
};

#endif // FILETYPES_H
