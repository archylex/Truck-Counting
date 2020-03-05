//
// Created by alec on 29.10.19.
//

#include "Fruit.h"

Fruit::Fruit() {
    auto spritecache = SpriteFrameCache::getInstance();
    sprite = Sprite::create();
    sprite->setSpriteFrame(spritecache->getSpriteFrameByName("apple.png"));
    sprite->setAnchorPoint(Vec2 (0.5f, 0.5f));
    this->addChild(sprite);
    velocity = 0.0f;
}

bool Fruit::isSelected(Point _point) {
    return sprite->getBoundingBox().containsPoint(_point);
}

Size Fruit::getMySize() {
    return sprite->getContentSize();
}

Vec2 Fruit::getMyPosition() {
    return sprite->getPosition();
}

void Fruit::setMyPosition(float _x, float _y) {
    sprite->setPosition(Vec2(_x, _y));
}

void Fruit::setMyPosition(Point _point) {
    sprite->setPosition(_point);
}

void Fruit::setStartPosition(float x, float y) {
    start_position = Vec2(x, y);
    resetToStartPosition();
}

void Fruit::resetToStartPosition() {
    sprite->setPosition(start_position);
}

void Fruit::setVelocity(float velocity) {
    this->velocity = velocity;
}

void Fruit::update(float dt) {
    sprite->setPositionX(sprite->getPositionX() + velocity * dt);
}