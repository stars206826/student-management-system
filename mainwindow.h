#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemm.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
private slots:
    void onAddStudent();
    void onDeleteStudent();
    void onFindStudent();
    void onSortStudents();
    void onCalculateTotal();
    void onCalculateAverage();
    void onSaveToFile();
    void onLoadFromFile();
    void updateStudentTable();
private:
    Ui::MainWindow *ui;
    systemm maner;
};
#endif // MAINWINDOW_H
