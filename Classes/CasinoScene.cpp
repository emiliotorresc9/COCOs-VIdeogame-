#include "CasinoScene.h"
#include "BankScene.h"  // Incluir BankScene para la transición al banco
#include "ClubScene.h"  // Incluir ClubScene para la transición al club
#include "MapScene.h"  // Incluir MapScene para la transición al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* CasinoScene::createScene()
{
    return CasinoScene::create();
}

bool CasinoScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del casino
    auto background = Sprite::create("casino_scene.png");
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'casino_scene.png'");
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

    // Crear los botones de interacción para los objetos en el casino
    crearInteractionButtons();

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void CasinoScene::crearInteractionButtons()
{
    // Botón para abrir el cuadro de diálogo (más pequeño)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(CasinoScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo más pequeño
    buttonDialog->setPosition(800, 600);  // Posición del botón en el casino

    // Botón para abrir las cartas (más pequeño)
    auto buttonCards = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(CasinoScene::showHideCards, this)
    );
    buttonCards->setScale(0.04f);  // Hacerlo más pequeño
    buttonCards->setPosition(850, 70);  // Posición del botón en el casino

    // Botón para abrir el papel (más pequeño)
    auto buttonPaper = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(CasinoScene::showHidePaper, this)
    );
    buttonPaper->setScale(0.04f);  // Hacerlo más pequeño
    buttonPaper->setPosition(1000, 100);  // Posición del botón en el casino

    // Botón para abrir el tequila (más pequeño)
    auto buttonTequila = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(CasinoScene::showHideTequila, this)
    );
    buttonTequila->setScale(0.04f);  // Hacerlo más pequeño
    buttonTequila->setPosition(350, 300);  // Posición del botón en el casino

    // Crear el menú con los botones
    auto menu = Menu::create(buttonDialog, buttonCards, buttonPaper, buttonTequila, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Función para mostrar u ocultar la imagen del cuadro de diálogo
void CasinoScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("casino_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de diálogo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen de las cartas
void CasinoScene::showHideCards(Ref* sender)
{
    if (!cardsImage)
    {
        cardsImage = Sprite::create("casino_cards.png");
        cardsImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(cardsImage, 2);  // Agregar la imagen de las cartas al frente
    }
    else
    {
        cardsImage->setVisible(!cardsImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen del papel
void CasinoScene::showHidePaper(Ref* sender)
{
    if (!paperImage)
    {
        paperImage = Sprite::create("casino_paper.png");
        paperImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(paperImage, 2);  // Agregar la imagen del papel al frente
    }
    else
    {
        paperImage->setVisible(!paperImage->isVisible());  // Alternar visibilidad
    }
}

// Función para mostrar u ocultar la imagen del tequila
void CasinoScene::showHideTequila(Ref* sender)
{
    if (!tequilaImage)
    {
        tequilaImage = Sprite::create("casino_tequila.png");
        tequilaImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(tequilaImage, 2);  // Agregar la imagen del tequila al frente
    }
    else
    {
        tequilaImage->setVisible(!tequilaImage->isVisible());  // Alternar visibilidad
    }
}

// Configurar el listener del teclado para ocultar las imágenes con ESC
void CasinoScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las imágenes");
            // Ocultar todas las imágenes si están visibles
            if (dialogImage) dialogImage->setVisible(false);
            if (cardsImage) cardsImage->setVisible(false);
            if (paperImage) paperImage->setVisible(false);
            if (tequilaImage) tequilaImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Configurar el listener del teclado para cambiar entre escenas con las flechas
void CasinoScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a BankScene");
            // Cambiar a la escena del banco
            auto bankScene = BankScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, bankScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a ClubScene");
            // Cambiar a la escena del club
            auto clubScene = ClubScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, clubScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
