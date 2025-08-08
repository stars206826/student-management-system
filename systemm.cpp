#include "systemm.h"
#include"student.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
bool compare(student& a, student& b)
{
    return a.getscores() > b.getscores();
}
void systemm::addstudent(QString &id,QString &name,double &scores)
{

    if (findhs(id))
    {
        qDebug()<<"该ID已存在！";
            return ;
    }


    s.emplace_back(id, name, scores);


}
//识别学生
student* systemm::findstudent(QString &id)
{    for(int i=0;i<s.size();i++)
    {
        if(s[i].getid()==id)
        {
            return &s[i];
        }
    }}
//删除学生
void systemm::deletestudent(QString &id)
{

    for(int i=0;i<s.size();i++)
    {
        if(s[i].getid()==id)
        {
            s.remove(i);
        }
    }
}
//显示学生
QVector<student> systemm::display()
{
    return s;
}
//计算总分
double systemm::total()
{
    double total=0;
    for (int i = 0;i < s.size();i++)
    {
        total += s[i].getscores();
    }
   return total;
}
//计算平均分
double systemm::totalaver()
{

    double total = 0;
    for (int i = 0;i < s.size();i++)
    {
        total += s[i].getscores();
    }
   return (total / s.size());
}
//排序
void systemm::csort()
{
    std::sort(s.begin(), s.end(), compare);


}
//读取文件
bool systemm::loadfile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    s.clear();
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();  // 读取整行并去除两端空白
        if (line.isEmpty()) continue;           // 跳过空行

        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() != 3) continue;        // 格式不正确则跳过

        QString id = parts[0];
        QString name = parts[1];
        bool ok;
        double scores = parts[2].toDouble(&ok);
        if (!ok) continue;                     // 成绩转换失败则跳过

        addstudent(id, name, scores);
    }

    file.close();
    return true;
}
//写入文件
bool systemm::savefile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    for (const auto &student : s) {
        out << student.getid() << " "
            << student.getname() << " "
            << student.getscores() << "\n";
    }

    file.close();
    return true;
}
