#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->textEdit->setTextColor(QColor(0,255,0));
    //ui->textEdit->setTextBackgroundColor(QColor(0,0,0));
    ui->textEdit->setStyleSheet("background:#000000;color:#00FF00");
    ui->textEdit->setReadOnly(1);
    //text = get_text();
    pos = 0;
    speed = 3;
    blanks = 5;
    ui->textEdit->insertPlainText(QString(blanks,'\n'));

    dialog = new Dialog();


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_filename()
{
    QFileDialog fileDialog(this,tr("打开代码"),QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                           ,tr("code sources (*.txt *.cpp *.c *.h *.py *.java *.sh *.js *.html *.htm *.css *.php)"));
    //fileDialog.selectMimeTypeFilter("text/plain");
    //QStringList mimelist;
    //mimelist<<"text/plain";
    //fileDialog.setMimeTypeFilters(mimelist);
    if(fileDialog.exec())
        return fileDialog.selectedFiles().at(0);
    else
        return QString();
}

void MainWindow::get_text()
{
    QString filename = get_filename();
    if(filename.isEmpty())
        return;
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this,"读取文件",tr("%1\n读取失败").arg(filename));
        return;
    }
    setWindowTitle(QFileInfo(file).fileName() + " - GVIM");
    QTextStream filestream(&file);
    text = filestream.readAll();
    pos = 0;
    ui->textEdit->clear();
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if((k->key()>=Qt::Key_Space && k->key()<=Qt::Key_AsciiTilde) || k->key() == Qt::Key_Return)
        showSome();
}


void MainWindow::showSome()
{
    if(pos < text.length())
    {
        /*QString sub = text.left(pos+3);
        pos = sub.length();
        ui->textEdit->setText(sub+"\n\n\n\n\n");
        ui->textEdit->moveCursor(QTextCursor::End);*/
        QString sub = text.mid(pos,speed);
        pos += sub.length();
        ui->textEdit->moveCursor(QTextCursor::End);
        QTextCursor cursor = ui->textEdit->textCursor();
        for(int i=0;i<blanks;i++) cursor.deletePreviousChar();
        ui->textEdit->insertPlainText(sub+QString(blanks,'\n'));
        ui->textEdit->moveCursor(QTextCursor::End);
    }
}

void MainWindow::on_action_O_triggered()
{
    get_text();
}

void MainWindow::on_action_T_triggered()
{
    dialog->ui->speed->setText(tr("%1").arg(speed));
    dialog->ui->blanks->setText(tr("%1").arg(blanks));
    if(dialog->exec())
    {
        bool ok;
        int temp = dialog->ui->speed->text().toInt(&ok);
        if(ok&&temp>=1&&temp<=10)
            speed = temp;
        temp = dialog->ui->blanks->text().toInt(&ok);
        if(ok&&temp>=0&&temp<=10)
        {
            QTextCursor cursor = ui->textEdit->textCursor();
            for(int i=0;i<blanks;i++) cursor.deletePreviousChar();
            blanks = temp;
            ui->textEdit->insertPlainText(QString(blanks,'\n'));
            ui->textEdit->moveCursor(QTextCursor::End);
        }
    }
}
