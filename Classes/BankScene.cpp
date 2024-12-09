#include "BankScene.h"
#include "HospitalScene.h"  // Incluir HospitalScene para la transici�n de regreso
#include "CasinoScene.h"    // Incluir CasinoScene para la transici�n al casino
#include "MapScene.h"  // Incluir MapScene para la transici�n al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* BankScene::createScene()
{
    return BankScene::create();
}

bool BankScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tama�o visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del banco
    auto background = Sprite::create("bank_scene.png");
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'bank_scene.png'");
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
    mapButton->setPosition(1520, 80);  // Ajusta el tama�o de la posici�n del bot�n

    // Crear el men� con el bot�n de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacci�n para los objetos en el banco
    crearInteractionButtons();

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void BankScene::crearInteractionButtons()
{
    // Bot�n para abrir la caja fuerte (m�s peque�o)
    auto buttonSafe = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideSafe, this)
    );
    buttonSafe->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonSafe->setPosition(770, 540);  // Posici�n del bot�n en el banco

    // Bot�n para abrir el cheque (m�s peque�o)
    auto buttonCheck = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideCheck, this)
    );
    buttonCheck->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonCheck->setPosition(450, 80);  // Posici�n del bot�n en el banco

    // Bot�n para abrir la computadora (m�s peque�o)
    auto buttonComputer = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideComputer, this)
    );
    buttonComputer->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonComputer->setPosition(1050, 450);  // Posici�n del bot�n en el banco

    // Bot�n para abrir el cuadro de di�logo (m�s peque�o)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonDialog->setPosition(1250, 400);  // Posici�n del bot�n en el banco

    // Crear el men� con los botones
    auto menu = Menu::create(buttonSafe, buttonCheck, buttonComputer, buttonDialog, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Funci�n para mostrar u ocultar la imagen de la caja fuerte
void BankScene::showHideSafe(Ref* sender)
{
    if (!safeImage)
    {
        safeImage = Sprite::create("bank_safe.png");
        safeImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(safeImage, 2);  // Agregar la imagen de la caja fuerte al frente
    }
    else
    {
        safeImage->setVisible(!safeImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen del cheque
void BankScene::showHideCheck(Ref* sender)
{
    if (!checkImage)
    {
        checkImage = Sprite::create("bank_check.png");
        checkImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(checkImage, 2);  // Agregar la imagen del cheque al frente
    }
    else
    {
        checkImage->setVisible(!checkImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen de la computadora
void BankScene::showHideComputer(Ref* sender)
{
    if (!computerImage)
    {
        computerImage = Sprite::create("bank_computer.png");
        computerImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(computerImage, 2);  // Agregar la imagen de la computadora al frente
    }
    else
    {
        computerImage->setVisible(!computerImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen del cuadro de di�logo
void BankScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("bank_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de di�logo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

// Configurar el listener del teclado para ocultar las im�genes con ESC
void BankScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las im�genes");
            // Ocultar todas las im�genes si est�n visibles
            if (safeImage) safeImage->setVisible(false);
            if (checkImage) checkImage->setVisible(false);
            if (computerImage) computerImage->setVisible(false);
            if (dialogImage) dialogImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Configurar el listener del teclado para cambiar entre escenas con las flechas
void BankScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a HospitalScene");
            // Cambiar a la escena del hospital
            auto hospitalScene = HospitalScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, hospitalScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a CasinoScene");
            // Cambiar a la escena del casino
            auto casinoScene = CasinoScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, casinoScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
