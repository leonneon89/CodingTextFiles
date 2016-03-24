#include "mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    encodingFile = new EncodingFile;
    directoryWork = new DirectoryWork;
}

void MainWindow::on_openFile_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open source file"), "/opt/EncodingTest", tr("Source Files (*.cpp *.h *.hpp)"));
    if(!filePath.isEmpty()) {
        encodingFile->setFileName(filePath);
        encodingFile->processFile();
        qDebug() << encodingFile->getFileName();
    }
}

void MainWindow::on_encodingFiles_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select a Directory", "/opt", QFileDialog::ShowDirsOnly);

    directoryWork->setDirectoryPath(path);
    if(directoryWork->isDirectory(path)) {
        directoryWork->processDirectory();
        listNames = directoryWork->getListNames();

        foreach(QString sourceName, listNames) {
            qDebug() << "       " <<sourceName;
            encodingFile->setFileName(sourceName);
            encodingFile->processFile();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(encodingFile->getFileName().size()!= 0) {
        if(ui.linuxEnd_radioButton->isChecked())
            encodingFile->changeEndLines(false);
        else if(ui.windowsEnd_radioButton->isChecked())
            encodingFile->changeEndLines(true);
    }
}
