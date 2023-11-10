#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QString currentFile = "";
    QTextEdit * text_edit;
    QVBoxLayout * vertical_layout;
    QMenuBar *menuBar;

    QMenu * file_Menu;
    QMenu *edit_Menu;
    QMenu *view_Menu;

    QAction *newAction;
    QAction *openAction;
    QAction *exitAction;
    QAction *saveAction;

    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *undoAction;
    QAction *redoAction;

    void setTextEdit();
    void setMenuBar();
    void connect_function();
    void setIcon();
public slots:
    void slots_newAction();
    void slots_openAction();
    void slots_saveAction();
    void slots_cutAction();
    void slots_copyAction();
    void slots_pasteAction();
    void slots_undoAction();
    void slots_redoAction();
};
#endif // WIDGET_H
