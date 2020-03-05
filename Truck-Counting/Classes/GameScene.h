//
// Created by alec on 29.10.19.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cocos2d.h"
#include "Background.h"
#include "Truck.h"
#include "Fruit.h"
#include "UILayer.h"
#include "CloudDialog.h"
#include "AdMob.h"
#include "MyUtils.h"

using namespace cocos2d;

class GameScene : public Scene {
public:
    static Scene* createScene();
    virtual bool init();
    void Go();

private:
    Layer* gLayer;
    Background* background;
    Truck* truck;
    UILayer* uiLayer;
    CloudDialog* cloudDialog;
    Sprite* basket;
    bool isGo;
    Size visibleSize;
    int lpart;
    Vector<Fruit*> fruits;
    Vector<Fruit*> fruitsInTruck;
    Vector<Fruit*> fruitsInBasket;
    Fruit* selectedFruit;
    Vec2 selectedFruitLastPosition;
    bool calc;
    float bx, by, sx, sy, radius, animated_angle;
    int animatedElement;
    bool isMovingAnimation;
    Vec2 fruitStartPos;
    float dAngle;
    int questNumber;

    void update(float dt);
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    bool onTouchEnd(Touch *touch, Event *event);
    void refreshCargo();
    void moveFruit(float dt);
    void refreshBasket();
    void newQuest();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

};


#endif //PROJ_ANDROID_GAMESCENE_H
