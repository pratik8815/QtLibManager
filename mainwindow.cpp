 // #include "mainwindow.h"
// #include "ui_mainwindow.h"
// #include "booklistdialog.h"

// #include <QMessageBox>

// #include <QDebug>
// #include <QDir>

// #include<QCloseEvent>
// #include<QTableWidgetItem>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);

//     //qDebug() << "Working directory:" << QDir::currentPath();

//     m_library.loadFromCsv("books.csv");
//     //m_library.addBook(Book("H_Potter", 101));
//     //m_library.addBook(Book("C_Programming",202));
//     //m_library.addBook(Book("Math",303));

//     connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(button1()));
//     connect(ui->pushButtonReturn, SIGNAL(clicked()), this, SLOT(button2()));
//     connect(ui->pushButtonShow, SIGNAL(clicked()), this, SLOT(button3()));


// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

// void MainWindow::button1()
// {
//     // Book database
//     //QString book[] = {"H_Potter", "C_Programming", "Math"};
//     //int rollNo[] = {101, 203, 304};

//     // Number of elements in the array
//     //int size = sizeof(rollNo) / sizeof(rollNo[0]);

//     // User input
//     //QString uBook = ui->lineEdit_2->text().trimmed();
//     int uBookId = ui->lineEditBookID->text().toInt();
//     int uRollNo = ui->lineEdit->text().toInt();

//     //qDebug() << "You entered book : " << uBook << "| roll no: " << uRollNo;

//     bool success = m_library.issuedBook(uBookId, uRollNo);

//     if(success)
//     {
//         QMessageBox::information(this, "LIBRARY MANAGEMENT", "BOOK ID: " + QString::number(uBookId) + "\nIssued to student roll no : " + QString::number(uRollNo));
//     }
//     else
//     {
//         QMessageBox::warning(this, "ERROR", "Book is Unavailable");
//     }

//     // bool found = false;

//     // // Search for matching record
//     // for(int i = 0; i < size; i++)
//     // {
//     //     if(uRollNo == rollNo[i] && uBook == book[i])
//     //     {
//     //         found = true;

//     //         QMessageBox::information(
//     //             this,
//     //             "LIBRARY MANAGEMENT",
//     //             "BOOK : " + book[i] +
//     //                 "\nIssued To Student Roll No : " + QString::number(uRollNo)
//     //             );

//     //         break;
//     //     }
//     // }

//     // // Show error only after checking all records
//     // if(!found)
//     // {
//     //     QMessageBox::warning(
//     //         this,
//     //         "Error",
//     //         "Book is unavailable or Roll Number is incorrect."
//     //         );
//     // }
// }

// void MainWindow::closeEvent(QCloseEvent *event)
// {
//     m_library.saveToCsv("books.csv");
//     event->accept();
// }
// void MainWindow::button2()
// {
//     //QString uBook = ui->lineEdit_2->text().trimmed();
//     int uBookId = ui->lineEditBookID->text().toInt();
//     int uRollNo = ui->lineEdit->text().toInt();

//     bool success = m_library.returnBook(uBookId,uRollNo);

//     if(success)
//     {
//         QMessageBox::information(this, "LIBRARY MANAGEMENT", "BOOK : " + QString::number(uBookId) + "\nReturned by student roll no : " + QString::number(uRollNo));
//     }
//     else
//     {
//         QMessageBox::warning(this, "ERROR", "Book Was Not Issued");
//     }


// }


// void MainWindow::button3()
// {
//     BookListDialog dialog(this);
//     dialog.showBooks(m_library.allBooks());
//     dialog.exec();

// }

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "booklistdialog.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QTableWidgetItem>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);  //loads everyting designed in QT Designer

    //m_library.loadFromCsv("books.csv");

    m_library.openDatabase("library.db");
    m_library.loadFromDb();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(button1()));
    connect(ui->pushButtonReturn, SIGNAL(clicked()), this, SLOT(button2()));
    connect(ui->pushButtonShow, SIGNAL(clicked()), this, SLOT(button3()));
    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(button4()));
    updateStats();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStats()
{
    ui->labelTotalBooks->setText("Total Books: " + QString::number(m_library.totalCopiesCount()));
    ui->labelIssuedBooks->setText("Issued Books: " + QString::number(m_library.issuedCopiesCount()));
}

void MainWindow::button1()
{
    int uBookId = ui->lineEditBookID->text().toInt();
    int uRollNo = ui->lineEdit->text().toInt();

    Book *book = m_library.findBook(uBookId);
    bool success = m_library.issuedBook(uBookId);

    if(success)
    {
        QMessageBox::information(this,"LIBRARY MANAGEMENT","Book: " + book->title() +   "\nBook ID: " + QString::number(uBookId) +
                "\nIssued to student roll no: " + QString::number(uRollNo) + "\nAvailable copies left: " + QString::number(book->availableCopies()));
    }
    else
    {
        QMessageBox::warning(this, "ERROR", "no copies left");
    }

    updateStats();
}

void MainWindow::button2()
{
    int uBookId = ui->lineEditBookID->text().toInt();
    int uRollNo = ui->lineEdit->text().toInt();

    Book *book = m_library.findBook(uBookId);
    bool success = m_library.returnBook(uBookId);

    if(success)
    {
        QMessageBox::information(this,"LIBRARY MANAGEMENT","Book: " + book->title() + "\nBook ID: " + QString::number(uBookId) +
                "\nReturned by student roll no: " + QString::number(uRollNo) +
                "\nAvailable copies now: " + QString::number(book->availableCopies()));
    }
    else
    {
        QMessageBox::warning(this, "ERROR", "no copies were issued");
    }

    updateStats();
}

void MainWindow::button3()
{
    BookListDialog dialog(this);
    dialog.showBooks(m_library.allBooks());
    dialog.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //m_library.saveToCsv("books.csv");
    m_library.saveToDb();
    event->accept();
}

void MainWindow::button4()
{
    bool flag;
    QString title = QInputDialog::getText(this, "Add Book", "Book Title:", QLineEdit::Normal, "", &flag);

    if(!flag || title.isEmpty())
    {
        return;
    }

    int id = QInputDialog::getInt(this, "Add Book", "Book ID:", 0, 0, 999999, 1,&flag);
    if(!flag)
    {
        return;
    }

    int total = QInputDialog::getInt(this, "Add Book", "Total Copies:", 1, 1, 1000, 1, &flag);
    if(!flag)
    {
        return;
    }

    m_library.addBook(Book(title, id, total, 0));
    m_library.saveToDb();
    updateStats();

    QMessageBox::information(this, "Success", "Book added");
}

