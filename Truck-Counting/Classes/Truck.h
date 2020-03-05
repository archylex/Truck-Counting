//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_TRUCK_H
#define PROJ_ANDROID_TRUCK_H

#include "cocos2d.h"

using namespace cocos2d;

class Truck : public Layer {
public:
    Truck();
    void update(float dt);
    void setVelocity(float velocity);
    bool isSelected(Point _point);
    Size getMySize();
    Vec2 getMyPos();
    void turnMe();
    float getDeltaPos();

private:
    Sprite *truck;
    Vector <Sprite*> wheels;
    float velocity;
    Size visibleSize;

};


#endif //PROJ_ANDROID_TRUCK_H
