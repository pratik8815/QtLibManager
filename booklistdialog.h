#ifndef BOOKLISTDIALOG_H
#define BOOKLISTDIALOG_H

#include <QDialog>

#include"library.h"

namespace Ui
{
    class BookListDialog;
}

class BookListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookListDialog(QWidget *parent = nullptr);
    ~BookListDialog();

    void showBooks(const QVector<Book> &books);
private:
    Ui::BookListDialog *ui;
};

#endif // BOOKLISTDIALOG_H
