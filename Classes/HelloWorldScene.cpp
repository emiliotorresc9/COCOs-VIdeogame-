#include "HelloWorldScene.h"
#include "IntroScene.h"  // Incluir IntroScene
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    } 

    // Cargar la imagen de fondo
    auto background = Sprite::create("menu_background.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Ajustar la imagen de fondo al tamaño de la pantalla
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    // Reproducir la música de fondo en bucle
    AudioEngine::play2d("tense_music.mp3", true);
     
    // Crear el botón "Play"
    auto playButton = MenuItemImage::create(
        "play_button_deactivated.png",
        "play_button_activated.png",
        CC_CALLBACK_1(HelloWorld::playButtonCallback, this));

    float scaleFactor = 0.55f;
    playButton->setScale(scaleFactor);
    playButton->setPosition(800, 120);
    auto menu = Menu::create(playButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void HelloWorld::playButtonCallback(Ref* pSender)
{
    CCLOG("Botón Play presionado");

    // Cambiar a IntroScene
    auto introScene = IntroScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, introScene));
}
