//
// Created by alec on 29.10.19.
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define VELOCITY 350
#define TRUCK_LINE 5
#define BASKET_LINE 3

float rad(float deg) {
    return deg * 3.14f / 180.0f;
}

Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spritecache = SpriteFrameCache::getInstance();

    isGo = false;
    lpart = -1;
    questNumber = 0;
    calc = false;
    isMovingAnimation = false;
    animatedElement = 0;
    bx = by = sx = sy = radius = 0.0f;

    srand(time(0));

    gLayer = Layer::create();
    gLayer->setPosition(Vec2(0.0f, 0.0f));
    this->addChild(gLayer);

    background = new Background();
    gLayer->addChild(background, 0);

    truck = new Truck();
    gLayer->addChild(truck, 2);

    auto girl = Sprite::create();
    girl->setSpriteFrame(spritecache->getSpriteFrameByName("girl.png"));
    girl->setAnchorPoint(Vec2(0.5f, 0.0f));
    girl->setPosition(Vec2(visibleSize.width * 0.77f, visibleSize.height * 0.05f));
    gLayer->addChild(girl, 4);

    basket = Sprite::create();
    basket->setSpriteFrame(spritecache->getSpriteFrameByName("basket.png"));
    basket->setAnchorPoint(Vec2(0.5f, 0.0f));
    basket->setPosition(Vec2(visibleSize.width * 0.65f, visibleSize.height * 0.03f));
    gLayer->addChild(basket, 6);

    auto tree_left = Sprite::create();
    tree_left->setSpriteFrame(spritecache->getSpriteFrameByName("tree_left.png"));
    tree_left->setAnchorPoint(Vec2(0.0f, 0.0f));
    tree_left->setPosition(Vec2(-visibleSize.width - tree_left->getContentSize().width*0.1f, 0.0f));
    gLayer->addChild(tree_left, 8);

    auto tree_right = Sprite::create();
    tree_right->setSpriteFrame(spritecache->getSpriteFrameByName("tree_right.png"));
    tree_right->setAnchorPoint(Vec2(1.0f, 0.0f));
    tree_right->setPosition(Vec2(visibleSize.width, 0.0f));
    gLayer->addChild(tree_right, 8);

    auto fg0 = Sprite::create();
    fg0->setSpriteFrame(spritecache->getSpriteFrameByName("foreground_0.png"));
    fg0->setAnchorPoint(Vec2(0.0f, 0.0f));
    fg0->setPosition(Vec2(-visibleSize.width, 0.0f));
    gLayer->addChild(fg0, 10);

    auto fg1 = Sprite::create();
    fg1->setSpriteFrame(spritecache->getSpriteFrameByName("foreground_1.png"));
    fg1->setAnchorPoint(Vec2(0.0f, 0.0f));
    fg1->setPosition(Vec2(0.0f, 0.0f));
    gLayer->addChild(fg1, 10);

    cloudDialog = new CloudDialog(1);
    gLayer->addChild(cloudDialog, 12);

    for (int a = 0; a < 12; a++) {
        Fruit* fruit = new Fruit();
        fruit->setStartPosition(visibleSize.width * (rand()%53 + 10) / 100.0f - visibleSize.width,
                                visibleSize.height * (rand()%25 + 65) / 100.0f);
        gLayer->addChild(fruit, 9);
        fruits.pushBack(fruit);
    }

    uiLayer = new UILayer();
    this->addChild(uiLayer);

    this->scheduleUpdate();

    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnd, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    newQuest();

    return true;
}

void GameScene::update(float dt) {
    background->update(dt);
    truck->update(dt);
    moveFruit(dt);

    for (auto fruit : fruitsInTruck) {
        fruit->update(dt);
    }

    if (isGo) {
        gLayer->setPositionX(gLayer->getPositionX() + VELOCITY * lpart * dt);

        if (gLayer->getPositionX() >= visibleSize.width || gLayer->getPositionX() <= 0) {
            isGo = false;
            truck->setVelocity(0.0f);

            for (auto fruit : fruitsInTruck) {
                fruit->setVelocity(0.0f);
                fruit->setMyPosition(Vec2(fruit->getMyPosition().x - truck->getDeltaPos() * (1 + lpart), fruit->getMyPosition().y));
            }

            if (lpart == 1) {
                truck->turnMe();
                uiLayer->onGoButton(true);
                uiLayer->setNumber(questNumber);
                uiLayer->showNumber(true);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MyUtils::intToAudioName(questNumber));
            } else {
                if (questNumber == fruitsInTruck.size()) {
                    char* ok[] = { "well.mp3", "right.mp3" };
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ok[rand()%2]);
                    this->schedule([&](float dt){
                        this->unschedule("schedulerKey");
                        isMovingAnimation = true;
                    }, 0.f, 0, 2.0f, "schedulerKey");
                } else {
                    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                        AdMob::showInterstitial();
                    #endif
                    uiLayer->onGoButton(true);
                    if (questNumber > fruitsInTruck.size())
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("small.mp3");
                    else
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("big.mp3");
                }
            }
        }

        if (fruitsInBasket.size() > 0 && gLayer->getPositionX() >= visibleSize.width * 0.4f) {
            for (auto fruit : fruitsInBasket) {
                fruit->resetToStartPosition();
                fruit->setLocalZOrder(9);
            }
            fruitsInBasket.clear();
        }
    }
}

void GameScene::Go() {
    lpart *= -1;
    if (lpart == 1)
        truck->turnMe();
    else
        uiLayer->showNumber(false);

    for (auto fruit : fruitsInTruck) {
        fruit->setVelocity(-VELOCITY * lpart);
        fruit->setMyPosition(Vec2(fruit->getMyPosition().x + truck->getDeltaPos() * (1 + lpart), fruit->getMyPosition().y));
    }

    truck->setVelocity(-VELOCITY * lpart);
    isGo = true;
    uiLayer->onGoButton(false);
    cloudDialog->hideMe();
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    Point touchLoc = touch->getLocation();

    if (lpart == 1) {
        for (auto fruit : fruits) {
            if (fruit->isSelected(Point(touchLoc.x - visibleSize.width, touchLoc.y))) {
                selectedFruit = fruit;
                selectedFruitLastPosition = selectedFruit->getMyPosition();
                selectedFruit->setMyPosition(touchLoc);
                return true;
            }
        }
    }

    return false;
}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    if (selectedFruit != nullptr)
        selectedFruit->setMyPosition(touch->getLocation());
}

bool GameScene::onTouchEnd(Touch *touch, Event *event) {
    Point touchLoc = touch->getLocation();

    if (truck->isSelected(Point(touchLoc.x - visibleSize.width, touchLoc.y))) {
        if (fruitsInTruck.find(selectedFruit) == fruitsInTruck.end()) {
            fruitsInTruck.pushBack(selectedFruit);
            selectedFruit->setLocalZOrder(1);
            refreshCargo();
        } else {
            selectedFruit->setMyPosition(selectedFruitLastPosition);
        }

        return true;
    } else {
        if (fruitsInTruck.find(selectedFruit) != fruitsInTruck.end()) {
            selectedFruit->setLocalZOrder(9);
            fruitsInTruck.eraseObject(selectedFruit);
            refreshCargo();
        }

        selectedFruit->resetToStartPosition();
        selectedFruit = nullptr;
    }

    return false;
}

void GameScene::refreshCargo()
{
    for (int a = 0; a < fruitsInTruck.size(); a++) {
        fruitsInTruck.at(fruitsInTruck.size() - a - 1)->setMyPosition(
                truck->getMyPos().x + truck->getMySize().width * 0.48f - (a % TRUCK_LINE) * fruitsInTruck.at(fruitsInTruck.size() - a - 1)->getMySize().width / 2,
                truck->getMyPos().y + truck->getMySize().height * 0.59f + (a / TRUCK_LINE) * fruitsInTruck.at(fruitsInTruck.size() - a - 1)->getMySize().height / 2);
    }
}

void GameScene::refreshBasket()
{
    for (int a = 0; a < fruitsInBasket.size(); a++) {
        fruitsInBasket.at(fruitsInBasket.size() - a - 1)->setMyPosition(
                basket->getPositionX() + basket->getContentSize().width * 0.37f - (fruitsInBasket.at(fruitsInBasket.size() - a - 1)->getMySize().width / 2) * (1 + (a % BASKET_LINE)),
                basket->getPositionY() + basket->getContentSize().height * 1.0f + (a / BASKET_LINE) * fruitsInBasket.at(fruitsInBasket.size() - a - 1)->getMySize().height / 2);
    }
}

void GameScene::moveFruit(float dt) {
    if (isMovingAnimation) {
        if (!calc) {
            animated_angle = -90.0f;
            fruitStartPos = fruitsInTruck.at(animatedElement)->getMyPosition();
            bx = basket->getPositionX() + basket->getContentSize().width * 0.37f - (fruitsInTruck.at(animatedElement)->getMySize().width / 2) * (1 + (animatedElement % BASKET_LINE)) ;
            by = basket->getPositionY() + basket->getContentSize().height * 1.0f + (animatedElement / BASKET_LINE) * fruitsInTruck.at(animatedElement)->getMySize().height / 2;
            sx = (bx - fruitStartPos.x);
            sy = (by - fruitStartPos.y);
            dAngle = atan(sy/sx);
            radius = sqrt(pow(sx, 2) + pow(sy, 2)) / 2;
            calc = true;

            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MyUtils::intToAudioName(animatedElement + 1));
        }

        fruitsInTruck.at(animatedElement)->setMyPosition(
                bx - sx/2 + radius * sin(rad(animated_angle)-dAngle),
                by - sy/2 + radius * cos(rad(animated_angle)-dAngle));

        animated_angle += 100 * dt;

        if (animated_angle >= 90.0f) {
            fruitsInBasket.pushBack(fruitsInTruck.at(animatedElement));
            animatedElement++;
            if (animatedElement == fruitsInTruck.size()) {
                animatedElement = 0;
                isMovingAnimation = false;
                fruitsInTruck.clear();

                newQuest();
                uiLayer->onGoButton(true);
            }
            calc = false;
            refreshBasket();
        }
    }
}

void GameScene::newQuest() {
    questNumber = rand() % 9 + 1;
    cloudDialog->setDialog(questNumber);
    cloudDialog->showMe();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MyUtils::intToAudioName(questNumber));

    auto seq = Sequence::create(
        CallFunc::create([this] {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bring.mp3");
        }),
        DelayTime::create(1.1f),
        CallFunc::create([this] {
            if (questNumber == 1)
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("1s.mp3");
            else
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MyUtils::intToAudioName(questNumber));
        }),
        DelayTime::create(0.9f),
        CallFunc::create([this] {
            if (questNumber == 1)
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("apple.mp3");
            else if (questNumber > 1 && questNumber < 5)
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("apples.mp3");
            else
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("apples2.mp3");
        }),
        nullptr
    );
    this->runAction(seq);
}