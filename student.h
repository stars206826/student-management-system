#ifndef STUDENT_H
#define STUDENT_H
#include<qstring.h>
class student {
private :
    QString name;//成员：姓名，成绩，学号

    double scores;
     QString id;
public:
    student(  QString sid,   QString  sname, double sscores)
        : id(sid), name(sname), scores(sscores) {
    }

     QString  getname()const;//姓名
    double getscores()const;//成绩
     QString  getid()const;//学号
    //文件读取赋值
    void set(  QString & sid,   QString & sname, double& sscorses)
    {
        id = sid;
        name = sname;
        scores = sscorses;


    }
};
#endif // STUDENT_H
