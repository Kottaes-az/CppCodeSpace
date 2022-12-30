#include <bits/stdc++.h>
bool g_PAUSE_STATUS = false;
struct docu_t {
    std::string strID, strName, strSex, strDepart, strJob;
    int nSalary;
};
struct docu_cmp {
    bool operator()(docu_t &docu1, docu_t &docu2) const {
        return docu1.nSalary > docu2.nSalary;
    }
};
typedef std::set<docu_t, docu_cmp> depart_t;
typedef std::unordered_map<std::string, depart_t> docudata_t;
docudata_t docuData;
void departInit() {
    docuData["化工学院"] = {
        {"201901", "刘明", "男", "化工学院", "副教授", 12000},
        {"201805", "李晓红", "女", "化工学院", "助教", 7200},
        {"201503", "蔡琳", "女", "化工学院", "讲师", 6900}};
    docuData["环保学院"] = {
        {"201904", "张小小", "女", "环保学院", "助教", 6900},
        {"201902", "王爱华", "男", "环保学院", "讲师", 7900}};
}
void docuOut(depart_t::iterator docuDest) {
    std::cout << docuDest->strID << ' ' << docuDest->strName << ' '
              << docuDest->strSex << ' ' << docuDest->strDepart << ' '
              << docuDest->strJob << ' ' << docuDest->nSalary << std::endl;
}
void docuModify(depart_t::iterator docuDest) {
    std::string strTempName = docuDest->strDepart;
    docuData[strTempName].erase(docuDest);
    docu_t docuTmp;
    std::cin >> docuTmp.strName >> docuTmp.strSex >> docuTmp.strDepart >>
        docuTmp.strJob >> docuTmp.nSalary;
    docuData[docuTmp.strDepart].insert(docuTmp);
}
void docuNew() {
    docu_t *docuTmp = (docu_t *)malloc(sizeof(docu_t));
    std::cin >> docuTmp->strName >> docuTmp->strSex >> docuTmp->strDepart >>
        docuTmp->strJob >> docuTmp->nSalary;
    docuData[docuTmp->strDepart].insert(*docuTmp);
}
void QuestIn(void) {
    char chChoice;
    std::string strTempID, strTempDepart;
    int nTempSalary;
    std::cin >> chChoice;
    depart_t::iterator tcIter;
    switch (chChoice) {
        case 'A': // 显示全部教师信息
            for (docudata_t::iterator tcJter = docuData.begin();
                 tcJter != docuData.end(); tcJter++)
                for (tcIter = tcJter->second.begin();
                     tcIter != tcJter->second.end(); tcIter++)
                    docuOut(tcIter);
            break;
        case 'B': // 按部门查询教师信息
            std::cout << "输入查询部门：" << std::endl;
            std::cin >> strTempDepart;
            for (tcIter = docuData[strTempDepart].begin();
                 tcIter != docuData[strTempDepart].end(); tcIter++)
                docuOut(tcIter);
            break;
        case 'C': // 查询月薪>=8000的教师信息
            for (docudata_t::iterator tcJter = docuData.begin();
                 tcJter != docuData.end(); tcJter++)
                for (tcIter = tcJter->second.begin();
                     tcIter != tcJter->second.end(); tcIter++)
                    if (tcIter->nSalary >= 8000)
                        docuOut(tcIter);
                    else
                        break;
            break;
        case 'D': // 查询部门最高与最低月薪
            std::cout << "输入查询部门：" << std::endl;
            std::cin >> strTempDepart;
            depart_t *departTemp = &docuData[strTempDepart];
            depart_t::iterator tcSalaryMax = departTemp->begin(),
                               tcSalaryMin =
                                   departTemp->end(); // 此处用于记录下标
            docuOut(tcSalaryMax);
            docuOut(tcSalaryMin);
            break;
        case 'E':
            std::cout << "输入修改信息：" << std::endl;
            docu_t *docuTmp = (docu_t *)malloc(sizeof(docu_t));
            std::cin >> docuTmp->strDepart >> docuTmp->strID;
            depart_t *departTemp = &docuData[docuTmp->strDepart];
            for (depart_t::iterator iter = departTemp->begin();
                 iter != departTemp->end(); iter++)
                if (docuTmp->strID == iter->strID) {
                    docuModify(iter);
                    break;
                }
            break;
        case 'Q': g_PAUSE_STATUS |= 1; break;
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    char chChoice;
    while (std::cin >> chChoice && g_PAUSE_STATUS) QuestIn();
    return 0;
}
