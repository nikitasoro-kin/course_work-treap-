#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "treap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFromFile();
    void onInsertClicked();
    void onRemoveClicked();
    void updateTreeView();

private:
    Ui::MainWindow *ui;
    Treap treap;
    QScrollArea *treeScrollArea;  
};
#endif // MAINWINDOW_H
