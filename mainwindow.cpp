#include "mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    encodingFile = new EncodingFile;
    directoryWork = new DirectoryWork;
    fileTypes = new FileType;
}

void MainWindow::on_openFile_pushButton_clicked()
{    
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open source file"), "/opt/EncodingTest", tr("Source Files (*.cpp *.h *.hpp)"));
    if(!filePath.isEmpty()) {
        encodingFile->setFileName(filePath);
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

void MainWindow::on_encodingTextFile_pushButton_clicked()
{
    if(encodingFile->getFileName().size() != 0) {
        qDebug() << "Encoding file: " << encodingFile->getFileName() << "to UFT-8";
        encodingFile->processFile();
    }
}

void MainWindow::on_encodingDirectory_pushButton_clicked()
{
    if(directoryWork->hasDirectory(directoryWork->getDirectoryPath())) {
        directoryWork->processDirectory();
        listNames = directoryWork->getListNames();

        foreach(QString sourceName, listNames) {
            qDebug() << "[MainWindow]. " << sourceName;
            encodingFile->setFileName(sourceName);
            encodingFile->processFile();
        }
    }
}

void MainWindow::on_openDirectory_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select a Directory", "/opt", QFileDialog::ShowDirsOnly);
    directoryWork->setDirectoryPath(path);
}

void MainWindow::on_inputFileTypes_pushButton_clicked()
{
    directoryWork->setStringTypes(ui.fileTypes_lineEdit->text());
}
