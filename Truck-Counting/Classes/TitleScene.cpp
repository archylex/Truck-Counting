//
// Created by alec on 28.10.19.
//

#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* TitleScene::createScene() {
    return TitleScene::create();
}

bool TitleScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    numlang = 0;

    auto spritecache = SpriteFrameCache::getInstance();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create();
    sprite->setSpriteFrame(spritecache->getSpriteFrameByName("theme.png"));
    if (sprite != nullptr) {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    }

    auto label = Label::createWithBMFont("font.fnt", "TOUCH TO START");
    if (label != nullptr) {
        label->setScale(0.33f);
        label->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.2f + origin.y));
        this->addChild(label);
    }

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

    langButton = Button::create(langpic[numlang], langpic[numlang], langpic[numlang], Widget::TextureResType::PLIST);
    langButton->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.1f));
    this->addChild(langButton, 1);

    langButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::MOVED:
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            case ui::Widget::TouchEventType::ENDED:
                numlang++;
                if (numlang >= (sizeof(langs)/sizeof(*langs)))
                    numlang = 0;
                changePicButton();
                break;
        }
    });

    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void TitleScene::changePicButton() {
    langButton->loadTextures(langpic[numlang], langpic[numlang], langpic[numlang], Widget::TextureResType::PLIST);
}

bool TitleScene::onTouchBegan(Touch *touch, Event *event) {
    auto paths = FileUtils::getInstance()->getSearchPaths();
    paths.push_back(langs[numlang]);
    FileUtils::getInstance()->setSearchPaths(paths);

    // Loading sounds
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    for (int a = 1; a <= 10; a++) {
        audioEngine->preloadEffect(MyUtils::intToAudioName(a));
    }
    audioEngine->preloadEffect("well.mp3");
    audioEngine->preloadEffect("right.mp3");
    audioEngine->preloadEffect("small.mp3");
    audioEngine->preloadEffect("big.mp3");
    audioEngine->preloadEffect("bring.mp3");
    audioEngine->preloadEffect("apple.mp3");
    audioEngine->preloadEffect("apples.mp3");
    audioEngine->preloadEffect("apples2.mp3");

    Scene *mScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mScene, Color3B(0, 0, 0)));
    return false;
}
