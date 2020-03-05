//
// Created by alec on 29.10.19.
//

#include "CloudDialog.h"

CloudDialog::CloudDialog(int num) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto spritecache = SpriteFrameCache::getInstance();

    cDialog = Sprite::create();
    cDialog->setSpriteFrame(spritecache->getSpriteFrameByName("dialog.png"));
    cDialog->setAnchorPoint(Vec2(1.0f, 0.0f));
    cDialog->setPosition(Vec2(visibleSize.width * 0.76f, visibleSize.height * 0.43f));
    this->addChild(cDialog);

    cLabel = Label::createWithBMFont("font.fnt", to_string(num));
    cLabel->setPosition(Vec2(cDialog->getContentSize().width * 0.45f, cDialog->getContentSize().height * 0.6f));
    cDialog->addChild(cLabel);

    cDialog->setScale(0.0f);
}

void CloudDialog::showMe() {
    auto scale = ScaleTo::create(1.0f, 1.0f);
    cDialog->runAction(scale);
}

void CloudDialog::hideMe() {
    auto scale = ScaleTo::create(1.0f, 0.0f);
    cDialog->runAction(scale);
}

void CloudDialog::setDialog(int num) {
    cLabel->setString(to_string(num));
}

void CloudDialog::setDialog(string txt) {
    cLabel->setString(txt);
}