#ifndef SYSTEMM_H
#define SYSTEMM_H
#include<QVector>
#include<QString>
#include <algorithm>
#include"student.h"

class systemm {
private:
  QVector<student>s;//学生数组
public:

    void addstudent(QString &id,QString &name,double &scores);//添加学生信息
    void deletestudent(QString &id);//删除学生信息
    student* findstudent(QString &id);//找到学生
    QVector<student>  display();//显示
    void csort();//按成绩排序
    double total();//计算总分
    double totalaver();//计算平均分
    //操作文件
    bool savefile(const QString &filename);
    bool loadfile(const QString &filename);
    //辅助函数
    bool findhs(QString& id)
    {
        for (int i = 0;i < s.size();i++)
        {
            if (s[i].getid() == id) {
                return true;
            }
        }
        return false;
    }

    //找到学生
    int zxh(QString id)
    {
        for (int i = 0;i < s.size();i++)
        {
            if (s[i].getid() == id)
            {
                return i;
            }
        }
        return -1;
    }
};


#endif // SYSTEMM_H
