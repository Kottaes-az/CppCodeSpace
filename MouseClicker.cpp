#include <bits/stdc++.h>
#include <windows.h>
#define pause_key VK_INSERT        // 暂停连点按键
const char *pause_name = "Insert"; // 修改连点名称
ssize_t speedArg;
// 下面可以不用修改，除非你知道你在干什么
bool destKeyDown(short destKeyName) { return (GetAsyncKeyState(destKeyName)); }
void showUpWindow(bool show) {
    ShowWindow(GetConsoleWindow(), show ? SW_SHOW : SW_HIDE);
}
void hideCursor() { // 隐藏光标
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
}
void sizeWindow(int r, int c) {
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, r, c, SWP_NOMOVE);
} // 设置窗口大小
void colorizeText(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
} // 改变字的颜色
void clickSimu() {
    mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
} // 模拟点击
void clickInit() {
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
    SetWindowLong(GetConsoleWindow(), GWL_STYLE,
                  GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_CAPTION);
}
void clickSpeedConfig() {
    system("cls"), sizeWindow(250, 85);
    printf("请输入速度参数\n越小越快, (默认1e7)\n: ");
    double tempArg_double;
    speedArg = (scanf("%lf", &tempArg_double) != 1) ? 1e7 : round(tempArg_double);
}
void clickPause() {
    system("cls"), sizeWindow(250, 85);
    colorizeText(0x04);
    printf("||连点器暂停中||");
    colorizeText(0x07);
    printf("\n当前速度参数: %lld\n短按 %s键 开始/暂停连点\n长按 1 秒 %s键 "
           "改变参数",
           speedArg, pause_name, pause_name);
    hideCursor();
}
void clickResume() {
    system("cls"), sizeWindow(200, 35), colorizeText(0x02);
    printf("||连点器已开启||");
    colorizeText(0x07);
    hideCursor();
}
int main() {
    clickInit();
    showUpWindow(true);
    register bool state, flag;
    clickSpeedConfig();
    state = false, clickPause();
    while (!destKeyDown(pause_key)) Sleep(10);
    state = true, clickResume();
    while (true) {
        flag = false;
        while (state) {
            clickSimu();
            for (ssize_t i = 1; i <= speedArg; ++i)
                if (!(i & 0x1ffffff) && destKeyDown(pause_key)) {
                    clickPause(), flag = true;
                    break;
                }
            if (destKeyDown(pause_key)) {
                clickPause(), flag = true;
                break;
            }
        }
        if (!state) Sleep(10);
        if (destKeyDown(pause_key) || flag) {
            clock_t timeCnt = clock();
            while (destKeyDown(pause_key)) Sleep(10);
            if (clock() - timeCnt >= 1000)
                clickSpeedConfig(), clickPause(), state = false;
            else
                state ^= 1, state ? clickResume() : clickPause();
        }
    }
    return 0;
}
