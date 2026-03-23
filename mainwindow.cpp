#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*this->setStyleSheet("QMainWindow { background-color: #ffe5ec; } "
                        "QToolBar { background-color: pink; }");*/

    connect(ui->actionNew, &QAction::triggered,this,&MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered,this,&MainWindow::open);
    connect(ui->actionSave, &QAction::triggered,this,&MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered,this,&MainWindow::saveAs);

    connect(ui->actionFont, &QAction::triggered,this,&MainWindow::selectFont);
    connect(ui->actionBold, &QAction::triggered,this,&MainWindow::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered,this,&MainWindow::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered,this,&MainWindow::setFontItalic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newDocument()
{
    m_currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::open()
{
    QString stringFileName = QFileDialog::getOpenFileName(this,"Open the file");
    if(stringFileName.isEmpty())return;
    QFile file(stringFileName);
    m_currentFile = stringFileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
        return;
    }

    setWindowTitle(stringFileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::save()
{
    QString stringFileName = "";
    if(m_currentFile.isEmpty()){
        stringFileName = QFileDialog::getSaveFileName(this,"Save");
        if(stringFileName.isEmpty())return;
        m_currentFile = stringFileName;
    }else{
        stringFileName = m_currentFile;
    }

    QFile file(stringFileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }

    setWindowTitle(stringFileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

void MainWindow::saveAs()
{
    QString stringFileName = QFileDialog::getSaveFileName(this,"Save as");
    if(stringFileName.isEmpty())return;
    QFile file(stringFileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }

    m_currentFile = stringFileName;
    setWindowTitle(stringFileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::selectFont()
{
}

void MainWindow::setFontBold(bool bold)
{
}

void MainWindow::setFontUnderline(bool underline)
{
}

void MainWindow::setFontItalic(bool italic)
{
}


