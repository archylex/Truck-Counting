//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_BACKGROUND_H
#define PROJ_ANDROID_BACKGROUND_H

#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

class Background : public Layer {
public:
    Background();
    void update(float delta);
    void createCloud(float delta);

private:
    Size visibleSize;
    Vector<Sprite*> clouds;
    Vector<Sprite*> deleteClouds;

};


#endif //PROJ_ANDROID_BACKGROUND_H
