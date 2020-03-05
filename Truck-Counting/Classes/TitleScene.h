//
// Created by alec on 28.10.19.
//

#ifndef PROJ_ANDROID_TITLESCENE_H
#define PROJ_ANDROID_TITLESCENE_H

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MyUtils.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

class TitleScene : public Scene {
public:
    static Scene* createScene();
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);
    void changePicButton();

private:
    Button* langButton;
    int numlang;
    string langs[2] = { "audio-ru", "audio-en" };
    string langpic[2] = { "ru.png", "en.png" };

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);

};


#endif //PROJ_ANDROID_TITLESCENE_H
