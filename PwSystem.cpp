#include "PwSource.h"
#include <iostream>
using namespace std;
// at break of day,in hope we rise
enum codeType { BASE64_CODE = 1, AES_CODE };
class pwModule {
  private:
    struct {
        codeType currentCode = BASE64_CODE;
        string inputLine, destLine, existSignal = "-1";
        bool oprType;
    } Pw;

  public:
    int existFlag = 0;
    void init(), pwInput(), pwOut();
};
void pwModule::pwInput() {
    getline(cin, Pw.inputLine);
    if (Pw.existSignal == Pw.inputLine) {
        existFlag |= 1;
        return;
    }
    cin >> Pw.oprType;
}
void pwModule::init(void) {
    if (Pw.oprType) {
        if (Pw.currentCode == BASE64_CODE)
            Pw.destLine =
                EncryptionBase64(Pw.inputLine.c_str(), Pw.inputLine.size());
        if (Pw.currentCode == AES_CODE)
            Pw.destLine = EncryptionAES(Pw.inputLine);
    }
    else {
        if (Pw.currentCode == BASE64_CODE)
            Pw.destLine = DecryptionBase64(Pw.inputLine);
        if (Pw.currentCode == AES_CODE)
            Pw.destLine = DecryptionAES(Pw.inputLine);
    }
}
void pwModule::pwOut() {
    cout << (Pw.oprType ? "->Encoded:" : "->Decoded: ") << Pw.destLine << endl;
}
int main(int argc, char *argv[], char **env) {
    pwModule PwObj;
    PwObj.pwInput();
    PwObj.init();
    PwObj.pwOut();
    return 0;
}