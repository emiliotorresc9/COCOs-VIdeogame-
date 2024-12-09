#include "BoatScene.h"
#include "CasinoScene.h"  // Incluir CasinoScene para la transición al casino
#include "ClubScene.h"    // Incluir ClubScene para la transición al club
#include "OfficeScene.h"  // Incluir OfficeScene para la transición a la oficina
#include "MapScene.h"  // Incluir MapScene para la transición al mapa
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
    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del barco
    auto background = Sprite::create("boat_scene.png");  // Asegúrate de tener esta imagen
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'boat_scene.png'");
        return false;
    }

    // Ajustar la imagen para que cubra toda la pantalla
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    // Crear el botón de mapa en esta escena
    auto mapButton = MenuItemImage::create(
        "map_button.png",  // Imagen normal del botón
        "map_button.png",  // Imagen cuando el mouse está sobre el botón
        [](Ref* sender) {
            auto mapScene = MapScene::createScene();
            Director::getInstance()->pushScene(mapScene);  // Abre el mapa
        });

    // Ajustar la escala y posición del botón de mapa
    mapButton->setScale(0.45f);  // Ajusta el tamaño del botón
    mapButton->setPosition(1520, 80);  // Ajusta la posición según lo necesites

    // Crear el menú con el botón de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacción para los objetos en el barco
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
    // Botón para abrir el cuadro de diálogo (más pequeño)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo más pequeño
    buttonDialog->setPosition(750, 600);  // Posición del botón en el barco

    // Botón para abrir las noticias (más pequeño)
    auto buttonNews = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideNews, this)
    );
    buttonNews->setScale(0.04f);  // Hacerlo más pequeño
    buttonNews->setPosition(1000, 100);  // Posición del botón en el barco

    // Botón para abrir el teléfono (más pequeño)
    auto buttonPhone = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHidePhone, this)
    );
    buttonPhone->setScale(0.04f);  // Hacerlo más pequeño
    buttonPhone->setPosition(700, 350);  // Posición del botón en el barco

    // Botón para abrir el mapa (más pequeño)
    auto buttonMap = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BoatScene::showHideMap, this)
    );
    buttonMap->setScale(0.04f);  // Hacerlo más pequeño
    buttonMap->setPosition(1100, 580);  // Posición del botón en el barco

    // Crear el menú con los botones
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
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de diálogo al frente
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
        this->addChild(phoneImage, 2);  // Agregar la imagen del teléfono al frente
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
            CCLOG("ESC presionado: Ocultando todas las imágenes");
            // Ocultar todas las imágenes si están visibles
            if (dialogImage) dialogImage->setVisible(false);
            if (newsImage) newsImage->setVisible(false);
            if (phoneImage) phoneImage->setVisible(false);
            if (mapImage) mapImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
