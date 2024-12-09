#include "MapScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
    return MapScene::create();
}

bool MapScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Configurar la imagen de fondo del mapa
    auto background = Sprite::create("city_map.png");
    if (!background)
    {
        CCLOG("Error: No se pudo cargar 'city_map.png'");
        return false;
    }

    // Ajustar la imagen al tamaño de la pantalla
    background->setPosition(visibleSize / 2);
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    // Crear el botón de salida para cerrar el mapa
    auto exitButton = MenuItemImage::create(
        "exit_button.png",          // Imagen normal del botón
        "exit_button.png",          // Imagen cuando el mouse está sobre el botón
        [](Ref* sender) {
            CCLOG("Saliendo del mapa...");
            // Salir del mapa y regresar a la escena activa
            Director::getInstance()->popScene();  // Regresa a la escena anterior (la que estaba activa)
        });

    if (!exitButton)
    {
        CCLOG("Error: No se pudo cargar 'exit_button.png'");
        return false;
    }

    // Ajustar el tamaño del botón y su posición
    exitButton->setScale(0.25f);  // Ajusta el tamaño si es necesario
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - 80, origin.y + 80));  // Esquina inferior derecha

    // Crear el menú con el botón de salida
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
