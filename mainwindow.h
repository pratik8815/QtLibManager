#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "library.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void button1();
    void button2();
    void button3();

    void button4();

private:
    Ui::MainWindow *ui;
    Library m_library;
    void updateStats();

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
