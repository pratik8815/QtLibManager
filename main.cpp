#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QMainWindow { background-color: #1e1e2e; }"
        "QWidget#centralwidget { background-color: #1e1e2e; }"
        "QFrame#frame { background-color: #282838; border: 1px solid #3a3a4d; border-radius: 12px; }"
        "QLabel { color: #e0e0e8; background: transparent; font-size: 10pt; }"
        "QLineEdit { padding: 6px 10px; border: 1px solid #44445a; border-radius: 6px; background: #1e1e2e; color: #e0e0e8; }"
        "QLineEdit:focus { border: 1px solid #7f8cff; }"
        "QPushButton { padding: 10px 14px; border-radius: 8px; font-weight: 500; }"
        "QPushButton#pushButton { background-color: #3b5b8c; border: 1px solid #5a89c9; color: #dbe9ff; }"
        "QPushButton#pushButton:hover { background-color: #4a6fa8; }"
        "QPushButton#pushButtonReturn { background-color: #8a5f26; border: 1px solid #c98d3f; color: #ffe9c7; }"
        "QPushButton#pushButtonReturn:hover { background-color: #a3722f; }"
        "QPushButton#pushButtonAdd { background-color: #3d7a2e; border: 1px solid #64ab4a; color: #dcf3cf; }"
        "QPushButton#pushButtonAdd:hover { background-color: #4a9236; }"
        "QPushButton#pushButtonShow { background-color: #3a3a4d; border: 1px solid #55556e; color: #e0e0e8; }"
        "QPushButton#pushButtonShow:hover { background-color: #48485e; }"
        "QDialog { background-color: #1e1e2e; }"
        "QMessageBox { background-color: #1e1e2e; }"
        "QPushButton { color: #e0e0e8; background-color: #2f2f42; border: 1px solid #44445a; }"
        );

    MainWindow w;
    w.show();
    return QApplication::exec();


}
