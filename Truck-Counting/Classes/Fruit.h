//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_FRUIT_H
#define PROJ_ANDROID_FRUIT_H

#include "cocos2d.h"

using namespace cocos2d;

class Fruit : public Layer {
public:
    Fruit();
    bool isSelected(Point _point);
    Size getMySize();
    Vec2 getMyPosition();
    void setMyPosition(float _x, float _y);
    void setMyPosition(Point _point);
    void setStartPosition(float x, float y);
    void resetToStartPosition();
    void setVelocity(float velocity);
    void update(float dt);

private:
    Sprite *sprite;
    Vec2 start_position;
    float velocity;

};


#endif //PROJ_ANDROID_FRUIT_H
