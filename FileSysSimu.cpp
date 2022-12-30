#include <bits/stdc++.h>
#include <src/fauc++.h>
const std::string gg_NORMAL_START_DIR = "$env:WORK_ENV";
std::filesystem::path curDir = gg_NORMAL_START_DIR;
fau::status_t change_dir(std::string strDestDir = gg_NORMAL_START_DIR) {
    if (!std::filesystem::exists(strDestDir)) return fau::code::NOT_EXISTS;
    std::string strTempDir = "cd " + strDestDir;
    curDir = strDestDir;
    return system(strTempDir.data());
}
fau::status_t open_file(std::string strDest = "") {
    return system(strDest.data());
}