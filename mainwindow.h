#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "treap.h"
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFromFile();
    void onInsertClicked();
    void onRemoveClicked();

private:
    Ui::MainWindow *ui;
    Treap treap;
    void updateTreeView();
};

#endif // MAINWINDOW_H
