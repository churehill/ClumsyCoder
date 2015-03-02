#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTextStream>
#include <QKeyEvent>
#include <QDialog>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_O_triggered();

    void on_action_T_triggered();

private:
    QString text;
    unsigned int pos;
    int speed;
    int blanks;

    QString get_filename();
    void get_text();
    void keyPressEvent(QKeyEvent *k);
    void showSome();
    Ui::MainWindow *ui;
    Dialog *dialog;
};

#endif // MAINWINDOW_H
