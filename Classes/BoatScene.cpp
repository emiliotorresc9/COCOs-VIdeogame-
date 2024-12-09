#include "BoatScene.h"
#include "CasinoScene.h"  // Incluir CasinoScene para la transici�n al casino
#include "ClubScene.h"    // Incluir ClubScene para la transici�n al club
#include "OfficeScene.h"  // Incluir OfficeScene para la transici�n a la oficina
#include "MapScene.h"  // Incluir MapScene para la transici�n al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* BoatScene::createScene()
{
    return BoatScene::create();
}

bool BoatScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // Tama�o visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del barco
    auto background = Sprite::create("boat_scene.png");  // Aseg�rate de tener esta imagen
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'boat_scene.png'");
        return false;
    }

    // Ajustar la imagen para que cubra toda la pantalla
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    // Crear el bot�n de mapa en esta escena
    auto mapButton = MenuItemImage::create(
        "map_button.png",  // Imagen normal del bot�n
        "map_button.png",  // Imagen cuando el mouse est� sobre el bot�n
        [](Ref* sender) {
            auto mapScene = MapScene::createScene();
            Director::getInstance()->pushScene(mapScene);  // Abre el mapa
        });

    // Ajustar la escala y posici�n del bot�n de mapa
    mapButton->setScale(0.45f);  // Ajusta el tama�o del bot�n
    mapButton->setPosition(1520, 80);  // Ajusta la posici�n seg�n lo necesites

    // Crear el men� con el bot�n de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacci�n para los objetos en el barco
    crearInteractionButtons();

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void BoatScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a ClubScene");
            // Cambiar a la escena del club
            auto clubScene = ClubScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, clubScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a OfficeScene");
            // Cambiar a la escena de la oficina
            auto officeScene = OfficeScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, officeScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BoatScene::crearInteractionButtons()
{
    // Bot�n para abrir el cuadro de di�logo (m�s peque�o)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonDialog->setPosition(750, 600);  // Posici�n del bot�n en el barco

    // Bot�n para abrir las noticias (m�s peque�o)
    auto buttonNews = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideNews, this)
    );
    buttonNews->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonNews->setPosition(1000, 100);  // Posici�n del bot�n en el barco

    // Bot�n para abrir el tel�fono (m�s peque�o)
    auto buttonPhone = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHidePhone, this)
    );
    buttonPhone->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonPhone->setPosition(700, 350);  // Posici�n del bot�n en el barco

    // Bot�n para abrir el mapa (m�s peque�o)
    auto buttonMap = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideMap, this)
    );
    buttonMap->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonMap->setPosition(1100, 580);  // Posici�n del bot�n en el barco

    // Crear el men� con los botones
    auto menu = Menu::create(buttonDialog, buttonNews, buttonPhone, buttonMap, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void BoatScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("boat_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de di�logo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

void BoatScene::showHideNews(Ref* sender)
{
    if (!newsImage)
    {
        newsImage = Sprite::create("boat_news.png");
        newsImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(newsImage, 2);  // Agregar la imagen de las noticias al frente
    }
    else
    {
        newsImage->setVisible(!newsImage->isVisible());  // Alternar visibilidad
    }
}

void BoatScene::showHidePhone(Ref* sender)
{
    if (!phoneImage)
    {
        phoneImage = Sprite::create("boat_phone.png");
        phoneImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(phoneImage, 2);  // Agregar la imagen del tel�fono al frente
    }
    else
    {
        phoneImage->setVisible(!phoneImage->isVisible());  // Alternar visibilidad
    }
}

void BoatScene::showHideMap(Ref* sender)
{
    if (!mapImage)
    {
        mapImage = Sprite::create("boat_map.png");
        mapImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(mapImage, 2);  // Agregar la imagen del mapa al frente
    }
    else
    {
        mapImage->setVisible(!mapImage->isVisible());  // Alternar visibilidad
    }
}

void BoatScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las im�genes");
            // Ocultar todas las im�genes si est�n visibles
            if (dialogImage) dialogImage->setVisible(false);
            if (newsImage) newsImage->setVisible(false);
            if (phoneImage) phoneImage->setVisible(false);
            if (mapImage) mapImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
