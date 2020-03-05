//
// Created by alec on 29.10.19.
//

#include "UILayer.h"
#include "GameScene.h"

UILayer::UILayer() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    goButton = Button::create("go.png", "go.png", "go.png", Widget::TextureResType::PLIST);
    goButton->setPosition(Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.15f));
    this->addChild(goButton, 1);

    goButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto scene = (GameScene*) this->getParent();
                scene->Go();
                break;
        }
    });

    auto closeButton = Button::create("close.png", "close.png", "close.png", Widget::TextureResType::PLIST);
    closeButton->setPosition(Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f));
    this->addChild(closeButton, 1);

    closeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->end();
                #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    exit(0);
                #endif
                break;
        }
    });

    Color4B wColor(250, 250, 255, 255);
    number = Label::createWithBMFont("font.fnt", "1");
    number->enableGlow(wColor);
    number->setScale(1.2f);
    number->setPosition(Vec2(visibleSize.width * 0.7f, visibleSize.height/2));
    this->addChild(number);
    showNumber(false);
}

void UILayer::onGoButton(bool enabled) {
    goButton->setTouchEnabled(enabled);
    goButton->setEnabled(enabled);
}

void UILayer::showNumber(bool isShow) {
    number->setVisible(isShow);
}

void UILayer::setNumber(int number) {
    this->number->setString(to_string(number));
}