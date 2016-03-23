#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    encodingFile = new EncodingFile;
}

void MainWindow::on_openFile_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open source file"), "/opt/EncodingTest", tr("Source Files (*.cpp *.h *.hpp)"));
    if(!filePath.isEmpty()) {
        encodingFile->setFileName(filePath);
        encodingFile->processFile();
    }
}
