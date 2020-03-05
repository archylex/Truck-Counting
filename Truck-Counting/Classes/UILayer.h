//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_UILAYER_H
#define PROJ_ANDROID_UILAYER_H


#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class UILayer : public Layer{
public:
    UILayer();
    void onGoButton(bool enabled);
    void showNumber(bool isShow);
    void setNumber(int number);

private:
    Button* goButton;
    Label* number;

};


#endif //PROJ_ANDROID_UILAYER_H
