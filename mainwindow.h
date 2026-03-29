#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void selectFont();
    void setFontBold(bool bold);
    void setFontUnderline(bool underline);
    void setFontItalic(bool italic);
    void changeInterfacePink();
    void changeInterfaceBlue();
    void changeInterfaceGreen();
    void changeInterfaceYellow();
    void changeInterfaceDarkMode();
    void changeInterfaceLightMode();

private:
    Ui::MainWindow *ui;
    QString m_currentFile;
};
#endif // MAINWINDOW_H
