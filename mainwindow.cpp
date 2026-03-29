#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    changeInterfaceLightMode();

    //Files
    connect(ui->actionNew, &QAction::triggered,this,&MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered,this,&MainWindow::open);
    connect(ui->actionSave, &QAction::triggered,this,&MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered,this,&MainWindow::saveAs);
    connect(ui->actionExport_as_PDF, &QAction::triggered,this,&MainWindow::exportAsPdf);

    //Font methods
    connect(ui->actionFont, &QAction::triggered,this,&MainWindow::selectFont);
    connect(ui->actionBold, &QAction::toggled,this,&MainWindow::setFontBold);
    connect(ui->actionUnderline, &QAction::toggled,this,&MainWindow::setFontUnderline);
    connect(ui->actionItalic, &QAction::toggled,this,&MainWindow::setFontItalic);

    //User interface changes
    connect(ui->actionPink, &QAction::triggered,this,&MainWindow::changeInterfacePink);
    connect(ui->actionBlue, &QAction::triggered,this,&MainWindow::changeInterfaceBlue);
    connect(ui->actionGreen, &QAction::triggered,this,&MainWindow::changeInterfaceGreen);
    connect(ui->actionYellow, &QAction::triggered,this,&MainWindow::changeInterfaceYellow);
    connect(ui->actionDark_mode, &QAction::triggered,this,&MainWindow::changeInterfaceDarkMode);
    connect(ui->actionLight_mode,&QAction::triggered,this,&MainWindow::changeInterfaceLightMode);
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
    QString stringFileName = QFileDialog::getOpenFileName(this,"Open File",
                                                          "",
                                                          "Text (*.txt);;HTML (*.html *.htm)");
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
    if (stringFileName.endsWith(".html") || stringFileName.endsWith(".htm")) {
        ui->textEdit->setHtml(text);
    } else {
        ui->textEdit->setPlainText(text);
    }

    file.close();
}

void MainWindow::save()
{
    QString stringFileName = "";
    if(m_currentFile.isEmpty()){
        stringFileName = QFileDialog::getSaveFileName(this,"Save",
                                                      "",
                                                      "Text (*.txt);;HTML (*.html *.htm)");
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
    QString stringFileName = QFileDialog::getSaveFileName(this,"Save as",
                                                          "",
                                                          "Text (*.txt);;HTML (*.html *.htm)");
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

void MainWindow::exportAsPdf()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exportar como PDF",
        "",
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    ui->textEdit->document()->print(&printer);
}

void MainWindow::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected,this);

    if(fontSelected){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::setFontBold(bool bold)
{
    QTextCharFormat format;
    format.setFontWeight(bold ? QFont::Bold : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::setFontUnderline(bool underline)
{
    QTextCharFormat format;
    format.setFontUnderline(underline);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::setFontItalic(bool italic)
{
    QTextCharFormat format;
    format.setFontItalic(italic);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::changeInterfacePink()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #ffe5ec;
            color: #3d1f2b;
        }

        QTextEdit {
            background-color: #fff8fa;
            color: #3d1f2b;
            border: 1px solid #f4b6c2;
        }

        QMenuBar {
            background-color: #f8c8d8;
            color: #3d1f2b;
        }

        QMenuBar::item {
            background: transparent;
            color: #3d1f2b;
        }

        QMenuBar::item:selected {
            background-color: #f4b6c2;
        }

        QMenu {
            background-color: #fff0f5;
            color: #3d1f2b;
            border: 1px solid #f4b6c2;
        }

        QMenu::item:selected {
            background-color: #f4b6c2;
        }

        QToolBar {
            background-color: #f8bbd0;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: #3d1f2b;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #f4b6c2;
        }

        QToolButton:checked {
            background-color: #ec9ab5;
        }

        QStatusBar {
            background-color: #f8c8d8;
            color: #3d1f2b;
        }
    )");
}

void MainWindow::changeInterfaceBlue()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #caf0f8;
            color: #12303a;
        }

        QTextEdit {
            background-color: #f1fbfe;
            color: #12303a;
            border: 1px solid #81c3d7;
        }

        QMenuBar {
            background-color: #a9d6e5;
            color: #12303a;
        }

        QMenuBar::item {
            background: transparent;
            color: #12303a;
        }

        QMenuBar::item:selected {
            background-color: #81c3d7;
        }

        QMenu {
            background-color: #eaf8fc;
            color: #12303a;
            border: 1px solid #81c3d7;
        }

        QMenu::item:selected {
            background-color: #81c3d7;
        }

        QToolBar {
            background-color: #81c3d7;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: #12303a;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #5faec6;
        }

        QToolButton:checked {
            background-color: #4a98b0;
            color: white;
        }

        QStatusBar {
            background-color: #a9d6e5;
            color: #12303a;
        }
    )");
}

void MainWindow::changeInterfaceGreen()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #cfe0c3;
            color: #243120;
        }

        QTextEdit {
            background-color: #f7fbf4;
            color: #243120;
            border: 1px solid #9ec1a3;
        }

        QMenuBar {
            background-color: #b7d3b0;
            color: #243120;
        }

        QMenuBar::item {
            background: transparent;
            color: #243120;
        }

        QMenuBar::item:selected {
            background-color: #9ec1a3;
        }

        QMenu {
            background-color: #edf5e8;
            color: #243120;
            border: 1px solid #9ec1a3;
        }

        QMenu::item:selected {
            background-color: #9ec1a3;
        }

        QToolBar {
            background-color: #9ec1a3;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: #243120;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #88b08e;
        }

        QToolButton:checked {
            background-color: #6f9a76;
            color: white;
        }

        QStatusBar {
            background-color: #b7d3b0;
            color: #243120;
        }
    )");
}

void MainWindow::changeInterfaceYellow()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #faf0ca;
            color: #4a3b12;
        }

        QTextEdit {
            background-color: #fffdf5;
            color: #4a3b12;
            border: 1px solid #ffef9f;
        }

        QMenuBar {
            background-color: #f4e7a1;
            color: #4a3b12;
        }

        QMenuBar::item {
            background: transparent;
            color: #4a3b12;
        }

        QMenuBar::item:selected {
            background-color: #ffef9f;
        }

        QMenu {
            background-color: #fff9dd;
            color: #4a3b12;
            border: 1px solid #ffef9f;
        }

        QMenu::item:selected {
            background-color: #ffef9f;
        }

        QToolBar {
            background-color: #ffef9f;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: #4a3b12;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #f2dc6d;
        }

        QToolButton:checked {
            background-color: #d9bf3f;
            color: white;
        }

        QStatusBar {
            background-color: #f4e7a1;
            color: #4a3b12;
        }
    )");
}

void MainWindow::changeInterfaceDarkMode()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #1e1e1e;
            color: white;
        }

        QTextEdit {
            background-color: #2b2b2b;
            color: white;
            border: 1px solid #3e3e42;
        }

        QMenuBar {
            background-color: #2d2d30;
            color: white;
        }

        QMenuBar::item {
            background: transparent;
            color: white;
        }

        QMenuBar::item:selected {
            background-color: #3e3e42;
        }

        QMenu {
            background-color: #2d2d30;
            color: white;
            border: 1px solid #3e3e42;
        }

        QMenu::item:selected {
            background-color: #3e3e42;
        }

        QToolBar {
            background-color: #3e3e42;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: white;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #4a4a4f;
        }

        QToolButton:checked {
            background-color: #5a5a60;
        }

        QStatusBar {
            background-color: #2d2d30;
            color: white;
        }
    )");
}

void MainWindow::changeInterfaceLightMode()
{
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #ffffff;
            color: #222222;
        }

        QTextEdit {
            background-color: #ffffff;
            color: #222222;
            border: 1px solid #cfcfcf;
        }

        QMenuBar {
            background-color: #f5f5f5;
            color: #222222;
        }

        QMenuBar::item {
            background: transparent;
            color: #222222;
        }

        QMenuBar::item:selected {
            background-color: #e0e0e0;
        }

        QMenu {
            background-color: #ffffff;
            color: #222222;
            border: 1px solid #cfcfcf;
        }

        QMenu::item:selected {
            background-color: #e0e0e0;
        }

        QToolBar {
            background-color: #f0f0f0;
            border: none;
            spacing: 3px;
        }

        QToolButton {
            background: transparent;
            color: #222222;
            border: none;
            padding: 4px;
        }

        QToolButton:hover {
            background-color: #e0e0e0;
        }

        QToolButton:checked {
            background-color: #d0d0d0;
        }

        QStatusBar {
            background-color: #f5f5f5;
            color: #222222;
        }
    )");
}
