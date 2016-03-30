#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "encodingFile.h"
#include "directoryWork.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
private slots:
    void on_openFile_pushButton_clicked();
    void on_pushButton_clicked();
    void on_encodingTextFile_pushButton_clicked();
    void on_encodingDirectory_pushButton_clicked();
    void on_openDirectory_pushButton_clicked();

private:
    Ui::MainWindow ui;
    EncodingFile* encodingFile;
    DirectoryWork* directoryWork;
    QList<QString> listNames;
};

#endif // MAINWINDOW_H
