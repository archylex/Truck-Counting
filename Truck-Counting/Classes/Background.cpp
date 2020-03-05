//
// Created by alec on 29.10.19.
//

#include "Background.h"

Background::Background() {
    visibleSize = Director::getInstance()->getVisibleSize();

    auto spritecache = SpriteFrameCache::getInstance();

    Color4B nColor(71, 203, 241, 255);
    Color4B wColor(250, 250, 255, 255);

    for (int a = 0; a < 2; a++) {
        auto sky = LayerGradient::create(wColor, nColor);
        sky->setAnchorPoint(Vec2(0.0f, 0.0f));
        sky->setPosition(Vec2(0.0f - visibleSize.width * a, 0.0f));
        sky->setVector(Point(0, 1));
        this->addChild(sky, 0);
    }

    auto bg0 = Sprite::create();
    bg0->setSpriteFrame(spritecache->getSpriteFrameByName("background_main_0.png"));
    bg0->setAnchorPoint(Vec2(0.0f, 0.0f));
    bg0->setPosition(Vec2(-visibleSize.width, 0.0f));
    this->addChild(bg0, 2);

    auto bg1 = Sprite::create();
    bg1->setSpriteFrame(spritecache->getSpriteFrameByName("background_main_1.png"));
    bg1->setAnchorPoint(Vec2(0.0f, 0.0f));
    bg1->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(bg1, 2);

    this->schedule(schedule_selector(Background::createCloud), 15);
}

void Background::createCloud(float delta) {
    auto spritecache = SpriteFrameCache::getInstance();
    auto cloud = Sprite::create();
    cloud->setSpriteFrame(spritecache->getSpriteFrameByName("cloud.png"));

    if (cloud != nullptr) {
        cloud->setAnchorPoint(Vec2(0.0f, 0.5f));
        cloud->setPosition(Vec2(visibleSize.width, visibleSize.height - rand()%(int)visibleSize.height/2));
        cloud->setScale((rand()%30 + 70)/100.0f);
        this->addChild(cloud, 1);
        clouds.pushBack(cloud);
    }
}

void Background::update(float delta) {
    for (auto cloud : clouds) {
        cloud->setPositionX(cloud->getPositionX() - 39 * delta);
        if (cloud->getPositionX() + cloud->getContentSize().width < -visibleSize.width)
            deleteClouds.pushBack(cloud);
    }

    for (auto cloud : deleteClouds) {
        clouds.eraseObject(cloud);
        this->removeChild(cloud, true);
    }

    deleteClouds.clear();
}
