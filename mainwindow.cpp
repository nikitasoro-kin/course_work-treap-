#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->keyEdit->setValidator(new QIntValidator(0, 9999, this));

    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);

    ui->treeWidget->setTreap(&treap);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "C:\\", "Text Files (*.txt);");
    if (filename.isEmpty()) return;

    std::ifstream file(filename.toStdString());
    if (!file) {
        QMessageBox::critical(this, "Error", "Cannot open file");
        return;
    }

    treap.clear();
    int key;
    while (file >> key) {
        treap.insert(key);
    }
    updateTreeView();
}

void MainWindow::onInsertClicked() {
    int key = ui->keyEdit->text().toInt();
    treap.insert(key);
    updateTreeView();
}

void MainWindow::onRemoveClicked() {
    bool ok;
    int key = ui->keyEdit->text().toInt(&ok);

    if (ok) {
        treap.remove(key);
        updateTreeView();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите корректный ключ!");
    }
}

void MainWindow::updateTreeView() {
    ui->treeWidget->update();
}
