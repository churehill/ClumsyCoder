#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
