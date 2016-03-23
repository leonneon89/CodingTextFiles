#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "encodingFile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    
private slots:
    void on_openFile_pushButton_clicked();

private:
    Ui::MainWindow ui;
    EncodingFile* encodingFile;
};

#endif // MAINWINDOW_H
