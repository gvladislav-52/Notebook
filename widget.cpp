#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("Notebook");
    setTextEdit();
    setMenuBar();
    setIcon();
    connect_function();
}

void Widget::setTextEdit()
{
    vertical_layout = new QVBoxLayout(this);
    vertical_layout->setContentsMargins(0,0,0,0);
    vertical_layout->setSpacing(0);
    text_edit = new QTextEdit();
    vertical_layout->addWidget(text_edit);

}

void Widget::connect_function()
{
    QObject::connect(newAction, &QAction::triggered, this, &Widget::slots_newAction);
    QObject::connect(openAction, &QAction::triggered, this, &Widget::slots_openAction);
    QObject::connect(saveAction, &QAction::triggered, this, &Widget::slots_saveAction);
    QObject::connect(exitAction, &QAction::triggered, this, &exit);
    QObject::connect(cutAction, &QAction::triggered, this, &Widget::slots_cutAction);
    QObject::connect(copyAction, &QAction::triggered, this, &Widget::slots_copyAction);
    QObject::connect(undoAction, &QAction::triggered, this, &Widget::slots_undoAction);
    QObject::connect(pasteAction, &QAction::triggered, this, &Widget::slots_pasteAction);
    QObject::connect(redoAction, &QAction::triggered, this, &Widget::slots_redoAction);
}
void Widget::setIcon()
{
        setWindowIcon(QIcon(":/img/notebook.png"));
        saveAction->setIcon(QIcon(":/img/save.png"));
        newAction->setIcon(QIcon(":/img/plus.png"));
        openAction->setIcon(QIcon(":/img/open.png"));
        exitAction->setIcon(QIcon(":/img/delete.png"));
}

void Widget::setMenuBar()
{
    menuBar = new QMenuBar(this);
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    file_Menu = menuBar->addMenu("&Файл");
    edit_Menu = menuBar->addMenu("&Изменить");
    view_Menu = menuBar->addMenu("&Просмотр");


    newAction = file_Menu->addAction(tr("&Стереть"));
    openAction = file_Menu->addAction(tr("&Открыть"));
    saveAction = file_Menu->addAction(tr("&Сохранить"));
    file_Menu->addSeparator();
    exitAction = file_Menu->addAction(tr("&Выйти"));

    copyAction = edit_Menu->addAction(tr("&Копировать"));
    cutAction = edit_Menu->addAction(tr("&Вырезать"));
    pasteAction = edit_Menu->addAction(tr("&Вставить"));
    undoAction = edit_Menu->addAction(tr("&Шаг назад"));
    redoAction = edit_Menu->addAction(tr("&Шаг вперед"));
    this->setLayout(new QVBoxLayout);
    this->layout()->setMenuBar(menuBar);
}

void Widget::slots_newAction()
{
    text_edit->clear();
    text_edit->setText(QString());
}

void Widget::slots_openAction()
{
    QString filename = QFileDialog::getOpenFileName(this,"Открыть файл");
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Внимание!", "Данный файл не удалось открыть: " + file.errorString());
        return;
    }
    setWindowTitle(QFileInfo(filename).fileName());
    QTextStream in(&file);
    QString text = in.readAll();
    text_edit->setText(text);
    file.close();


}

void Widget::slots_saveAction()
{

    QString filename = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt)");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Внимание!", "Данный файл не удалось записать: " + file.errorString());
        return;
    }
    setWindowTitle(QFileInfo(file).fileName());
    QTextStream out(&file);
    QString text = text_edit->toPlainText();
    out << text;
    file.close();
}

void Widget::slots_cutAction()
{
    text_edit->cut();
}

void Widget::slots_copyAction()
{
    text_edit->copy();
}

void Widget::slots_pasteAction()
{
    text_edit->paste();
}

void Widget::slots_undoAction()
{
    text_edit->undo();
}

void Widget::slots_redoAction()
{
    text_edit->redo();
}


Widget::~Widget()
{

}

