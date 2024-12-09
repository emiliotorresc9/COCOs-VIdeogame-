#include "IntroScene.h"
#include "OfficeScene.h"  // Cambiar a OfficeScene al final de la intro
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
    return IntroScene::create();
}

bool IntroScene::init()
{
    if (!Scene::init())
    {
        CCLOG("Error: No se pudo inicializar la escena de introducción.");
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    currentImage = Sprite::create("town_intro.png");
    currentImage->setPosition(visibleSize / 2);
    currentImage->setScale(visibleSize.width / currentImage->getContentSize().width,
        visibleSize.height / currentImage->getContentSize().height);
    this->addChild(currentImage);

    auto initialZoom = ScaleBy::create(6.5f, 1.1f);
    currentImage->runAction(initialZoom);

    // Retrasar el inicio del audio por 2 segundos
    this->runAction(Sequence::create(
        DelayTime::create(1.5f),
        CallFunc::create([this]() {
            introAudioId = AudioEngine::play2d("intro_audio.mp3", false);
            }),
        nullptr
    ));

    startImageSequence();

    // Agregar el texto en la esquina inferior derecha
    auto skipLabel = Label::createWithTTF("Press [ESC] to skip intro", "fonts/Arial.ttf", 22);
    skipLabel->setAnchorPoint(Vec2(1, 0));  // Ancla en la esquina inferior derecha
    skipLabel->setPosition(Vec2(visibleSize.width + origin.x - 10, origin.y + 10));  // Posición en la esquina inferior derecha con margen
    skipLabel->setTextColor(Color4B::WHITE);  // Color blanco para el texto
    this->addChild(skipLabel, 1);  // Añadir el texto a la escena

    // Agregar listener para la tecla ESC
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            skipIntro();  // Llama a la función para saltar la introducción
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void IntroScene::startImageSequence()
{
    this->schedule([=](float) { changeImage("office_intro.png"); }, 6.5f, "changeImage1");
    this->schedule([=](float) { changeImage("mansion_intro.png"); }, 13.0f, "changeImage2");
    this->schedule([=](float) { changeImage("detective_intro.png"); }, 19.5f, "changeImage3");
    this->schedule([=](float) { changeImage("pinboard_intro.png"); }, 26.0f, "changeImage4");

    this->scheduleOnce([=](float) {
        skipIntro();  // Llama a skipIntro al finalizar la secuencia
        }, 32.5f, "endIntro");
}

void IntroScene::changeImage(const std::string& imageName)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto fadeOut = FadeOut::create(0.5f);
    currentImage->runAction(Sequence::create(fadeOut, CallFunc::create([=]() {
        currentImage->setTexture(imageName);
        currentImage->setOpacity(0);
        currentImage->setScale(visibleSize.width / currentImage->getContentSize().width,
            visibleSize.height / currentImage->getContentSize().height);

        auto fadeIn = FadeIn::create(0.5f);
        currentImage->runAction(fadeIn);

        auto zoomIn = ScaleBy::create(6.5f, 1.1f);
        currentImage->runAction(zoomIn);
        }), nullptr));
}

void IntroScene::skipIntro()
{
    // Detener el audio de la introducción
    AudioEngine::stop(introAudioId);

    // Transición inmediata a OfficeScene
    auto officeScene = OfficeScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, officeScene));
}
