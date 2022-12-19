#include <iostream>
using namespace std;
int len = 5;
struct teacher {
    string id, name, sex, depart, job;
    int salary;
} t[1001] = {{"201901", "刘明", "男", "化工学院", "副教授", 12000},
             {"201904", "张小小", "女", "环保学院", "助教", 6900},
             {"201503", "蔡琳", "女", "化工学院", "讲师", 6900},
             {"201805", "李晓红", "女", "化工学院", "助教", 7200},
             {"201902", "王爱华", "男", "环保学院", "讲师", 7900}};
void infOut(teacher a) {
    cout << a.id << ' ' << a.name << ' ' << a.sex << ' ' << a.depart << ' '
         << a.job << ' ' << a.salary << endl;
}
void infIn(teacher a) {
    cin >> a.id >> a.name >> a.sex >> a.depart >> a.job >> a.salary;
}
void inq(char type) {
    string tmp, tmp1, tmp2, dep;
    int maxn = 0, minn = len - 1;
    switch (type) {
        case 'A': //显示全部教师信息
            for (int i = 0; i < len; i++) infOut(t[i]);
            break;
        case 'B': //按部门查询教师信息
            cout << "输入查询部门：" << endl;
            cin >> dep;
            for (int i = 0; i < len; i++)
                if (dep == t[i].depart) infOut(t[i]);
            break;
        case 'C': //查询月薪>=8000的教师信息
            for (int i = 0; i < len; i++)
                if (t[i].salary >= 8000) infOut(t[i]);
            break;
        case 'D': //查询部门最高与最低月薪
            cout << "输入查询部门：" << endl;
            cin >> dep;
            //此处用于记录下标
            for (int i = 0; i < len; i++) {
                if (t[i].salary > t[maxn].salary && t[i].depart == dep)
                    maxn = i;
                if (t[i].salary < t[minn].salary && t[i].depart == dep)
                    minn = i;
            }
            infOut(t[maxn]);
            infOut(t[minn]);
            break;
        case 'E':
            cout << "输入修改信息：" << endl;
            cin >> tmp >> tmp1 >> tmp2;
            for (int i = 0; i < len; i++)
                if (tmp == t[i].id) {
                    t[i].depart = tmp1;
                    t[i].salary = atoi(tmp2.c_str());
                }
            break;
    }
}
int main() {
    char choice;
    while (cin >> choice) switch (choice) {
            case 'A': inq('A'); break;
            case 'B': inq('B'); break;
            case 'C': inq('C'); break;
            case 'D': inq('D'); break;
            case 'E': inq('E'); break;
            case 'Q': return 0; break;
        }

    return 0;
}
