#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

ui->tablestudent->setColumnCount(3);
ui->tablestudent->setHorizontalHeaderLabels({"学号", "姓名", "成绩"});
connect(ui->btnadd, &QPushButton::clicked, this, &MainWindow::onAddStudent);
connect(ui->btndelete, &QPushButton::clicked, this, &MainWindow::onDeleteStudent);
connect(ui->btnfind, &QPushButton::clicked, this, &MainWindow::onFindStudent);
connect(ui->btnsort, &QPushButton::clicked, this, &MainWindow::onSortStudents);
connect(ui->btntotal, &QPushButton::clicked, this, &MainWindow::onCalculateTotal);
connect(ui->btnaver, &QPushButton::clicked, this, &MainWindow::onCalculateAverage);
connect(ui->btnsave, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
connect(ui->btnload, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    // 设置背景
this->setStyleSheet(
    "MainWindow {"
    "   background-image: url(:/images/background.jpg);"
    "   background-position: center;"
    "   background-repeat: no-repeat;"
    "   background-attachment: fixed;"
    "}"

    "QTableView {"
    "   background-color: rgba(255, 255, 255, 180);"  // 半透明白色背景
    "   border: 1px solid #cccccc;"
    "}"

    "QGroupBox {"
    "   background-color: rgba(255, 255, 255, 200);"
    "   border: 1px solid #aaaaaa;"
    "   border-radius: 5px;"
    "   margin-top: 10px;"
    "}"

    "QLineEdit, QPushButton {"
    "   background-color: white;"
    "}"
    );
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onAddStudent() {
    QString id = ui->editID->text();
    QString name = ui->editName->text();
    double scores = ui->editscores->text().toDouble();

    maner.addstudent(id, name, scores);
    updateStudentTable();

    ui->editID->clear();
    ui->editName->clear();
    ui->editscores->clear();
}
void MainWindow::onDeleteStudent() {
    QString id = ui->editID->text();
    maner.deletestudent(id);
    updateStudentTable();
}
void MainWindow::onFindStudent() {
    QString id = ui->editID->text();
    student* student = maner.findstudent(id);

    if (student) {
        QMessageBox::information(this, "查询结果",
                                 QString("学号: %1\n姓名: %2\n成绩: %3")
                                     .arg(student->getid())
                                     .arg(student->getname())
                                     .arg(student->getscores()));
    } else {
        QMessageBox::warning(this, "查询结果", "未找到该学生");
    }
}
void MainWindow::onSortStudents() {
    maner.csort();
    updateStudentTable();
}
void MainWindow::onCalculateTotal() {
    double total = maner.total();
    QMessageBox::information(this, "总分", QString("总成绩: %1").arg(total));
}
void MainWindow::onCalculateAverage() {
    double average = maner.totalaver();
    QMessageBox::information(this, "平均分", QString("平均成绩: %1").arg(average));
}

void MainWindow::onSaveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt)");
    if (!filename.isEmpty()) {
        if (maner.savefile(filename)) {
            QMessageBox::information(this, "成功", "文件保存成功");
        } else {
            QMessageBox::warning(this, "错误", "文件保存失败");
        }
    }
}
void MainWindow::onLoadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", "", "文本文件 (*.txt)");
    if (!filename.isEmpty()) {
        if (maner.loadfile(filename)) {
            updateStudentTable();
            QMessageBox::information(this, "成功", "文件加载成功");
        } else {
            QMessageBox::warning(this, "错误", "文件加载失败");
        }
    }
}
void MainWindow::updateStudentTable() {
    ui->tablestudent->setRowCount(0);
    QVector<student> students = maner.display();

    for (const auto &student : students) {
        int row = ui->tablestudent->rowCount();
        ui->tablestudent->insertRow(row);

        ui->tablestudent->setItem(row, 0, new QTableWidgetItem(student.getid()));
        ui->tablestudent->setItem(row, 1, new QTableWidgetItem(student.getname()));
        ui->tablestudent->setItem(row, 2, new QTableWidgetItem(QString::number(student.getscores())));
    }
}

