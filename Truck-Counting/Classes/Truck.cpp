//
// Created by alec on 29.10.19.
//

#include "Truck.h"


Truck::Truck() {
    visibleSize = Director::getInstance()->getVisibleSize();
    auto spritecache = SpriteFrameCache::getInstance();

    truck = Sprite::create();
    truck->setSpriteFrame(spritecache->getSpriteFrameByName("truck.png"));
    truck->setAnchorPoint(Vec2(0.0f, 0.0f));
    truck->setPosition((Vec2(visibleSize.width * 0.15f, visibleSize.height * 0.08f)));
    this->addChild(truck);

    for (int a = 0; a < 2; a++) {
        auto wheel = Sprite::create();
        wheel->setSpriteFrame(spritecache->getSpriteFrameByName("wheel.png"));
        wheel->setAnchorPoint(Vec2(0.5f, 0.5f));
        wheel->setPosition(Vec2(
            truck->getContentSize().width * 0.175f + a * truck->getContentSize().width * 0.54f,
            truck->getContentSize().height * 0.008f));
        truck->addChild(wheel);
        wheels.pushBack(wheel);
    }

    velocity = 0.0f;
}

void Truck::setVelocity(float velocity) {
    this->velocity = velocity;
}

Size Truck::getMySize() {
    return truck->getContentSize();
}

Vec2 Truck::getMyPos() {
    return truck->getPosition();
}

bool Truck::isSelected(Point _point) {
    return truck->getBoundingBox().containsPoint(_point);
}

void Truck::update(float dt) {
    truck->setPositionX(truck->getPositionX() + velocity * dt);

    for (auto wheel : wheels) {
        if (wheel != nullptr) {
            wheel->setRotation(wheel->getRotation() + 1 * velocity * dt);
        }
    }
}

float Truck::getDeltaPos() {
    return truck->getContentSize().width * 0.1f;
}

void Truck::turnMe() {
    if (!truck->isFlippedX()) {
        truck->setFlippedX(true);
        for (auto wheel : wheels) {
            wheel->setPositionX(wheel->getPositionX() + getDeltaPos());
        }
    } else {
        truck->setFlippedX(false);
        for (auto wheel : wheels) {
            wheel->setPositionX(wheel->getPositionX() - getDeltaPos());
        }
    }
}