#include "ClubScene.h"
#include "CasinoScene.h"  // Incluir CasinoScene para la transición al regreso
#include "BoatScene.h"    // Incluir BoatScene para la transición al barco
#include "MapScene.h"  // Incluir MapScene para la transición al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* ClubScene::createScene()
{
    return ClubScene::create();
}

bool ClubScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del club
    auto background = Sprite::create("club_scene.png");  // Asegúrate de tener esta imagen
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'club_scene.png'");
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

    // Configurar los botones de interacción para los objetos en el club
    crearInteractionButtons();

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void ClubScene::crearInteractionButtons()
{
    // Botón para abrir el cuadro de diálogo (más pequeño)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ClubScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo más pequeño
    buttonDialog->setPosition(800, 500);  // Posición del botón en el club

    // Botón para abrir el libro (más pequeño)
    auto buttonBook = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ClubScene::showHideBook, this)
    );
    buttonBook->setScale(0.04f);  // Hacerlo más pequeño
    buttonBook->setPosition(400, 70);  // Posición del botón en el club

    // Botón para abrir la bolsa (más pequeño)
    auto buttonBag = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ClubScene::showHideBag, this)
    );
    buttonBag->setScale(0.04f);  // Hacerlo más pequeño
    buttonBag->setPosition(450, 200);  // Posición del botón en el club

    // Botón para abrir el contrato (más pequeño)
    auto buttonContract = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ClubScene::showHideContract, this)
    );
    buttonContract->setScale(0.04f);  // Hacerlo más pequeño
    buttonContract->setPosition(900, 100);  // Posición del botón en el club

    // Crear el menú con los botones
    auto menu = Menu::create(buttonDialog, buttonBook, buttonBag, buttonContract, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Función para mostrar u ocultar la imagen del cuadro de diálogo
void ClubScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("club_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de diálogo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen del libro
void ClubScene::showHideBook(Ref* sender)
{
    if (!bookImage)
    {
        bookImage = Sprite::create("club_book.png");
        bookImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(bookImage, 2);  // Agregar la imagen del libro al frente
    }
    else
    {
        bookImage->setVisible(!bookImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen de la bolsa
void ClubScene::showHideBag(Ref* sender)
{
    if (!bagImage)
    {
        bagImage = Sprite::create("club_bag.png");
        bagImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(bagImage, 2);  // Agregar la imagen de la bolsa al frente
    }
    else
    {
        bagImage->setVisible(!bagImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen del contrato
void ClubScene::showHideContract(Ref* sender)
{
    if (!contractImage)
    {
        contractImage = Sprite::create("club_contract.png");
        contractImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(contractImage, 2);  // Agregar la imagen del contrato al frente
    }
    else
    {
        contractImage->setVisible(!contractImage->isVisible());  // Alternar visibilidad
    }
}

// Configurar el listener del teclado para ocultar las imágenes con ESC
void ClubScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las imágenes");
            // Ocultar todas las imágenes si están visibles
            if (dialogImage) dialogImage->setVisible(false);
            if (bookImage) bookImage->setVisible(false);
            if (bagImage) bagImage->setVisible(false);
            if (contractImage) contractImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Configurar el listener del teclado para cambiar entre escenas con las flechas
void ClubScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a CasinoScene");
            // Cambiar a la escena del casino
            auto casinoScene = CasinoScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, casinoScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a BoatScene");
            // Cambiar a la escena del barco
            auto boatScene = BoatScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, boatScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
