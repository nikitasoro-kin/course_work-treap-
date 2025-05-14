#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <QDebug>
#include <QScrollArea>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->keyEdit->setValidator(new QIntValidator(0, 9999, this));

    ui->treeWidget->setTreap(&treap);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(ui->treeWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    ui->treeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(new QLabel("Ключ:"));
    controlsLayout->addWidget(ui->keyEdit);
    controlsLayout->addWidget(ui->loadButton);
    controlsLayout->addWidget(ui->insertButton);
    controlsLayout->addWidget(ui->removeButton);
    controlsLayout->addStretch();

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(scrollArea);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);

    QString appStyle =
        "QLabel {"
        "   font-size: 14px;"
        "   margin-right: 10px;"
        "}"
        "QLineEdit {"
        "   border-radius: 4px;"
        "   border: 1px solid #ccc;"
        "   padding: 5px;"
        "   min-width: 100px;"
        "}"
        "QPushButton {"
        "   padding: 5px 10px;"
        "   min-width: 150px;"
        "}"
        "QPushButton:hover {"
        "   background: #e0e0e0;"
        "}"
        "QScrollArea { "
            "background: transparent;"
        "}"
        "treeWidget { "
            "background-color: #a2ff94;"
        "}";
    qApp->setStyleSheet(appStyle);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onLoadFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
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

void MainWindow::onInsertClicked()
{
    bool ok;
    int key = ui->keyEdit->text().toInt(&ok);

    if (ok) {
        treap.insert(key);
        updateTreeView();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите корректное число!");
    }
    ui->keyEdit->clear();
}

void MainWindow::onRemoveClicked()
{
    bool ok;
    int key = ui->keyEdit->text().toInt(&ok);

    if (ok) {
        treap.remove(key);
        updateTreeView();
    } else {
        QMessageBox::warning(this, "Ошибка", "Введите корректный ключ!");
    }
    ui->keyEdit->clear();
}

void MainWindow::updateTreeView()
{
    ui->treeWidget->adjustSize();

    ui->treeWidget->update();

    qDebug() << "TreeWidget size:" << ui->treeWidget->size()
             << "Min size:" << ui->treeWidget->minimumSize();
}

