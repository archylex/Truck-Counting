//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_CLOUDDIALOG_H
#define PROJ_ANDROID_CLOUDDIALOG_H

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CloudDialog : public Layer {
public:
    CloudDialog(int num);
    void showMe();
    void hideMe();
    void setDialog(int num);
    void setDialog(string txt);

private:
    Sprite *cDialog;
    Label *cLabel;
};


#endif //PROJ_ANDROID_CLOUDDIALOG_H
