#include "BankScene.h"
#include "HospitalScene.h"  // Incluir HospitalScene para la transición de regreso
#include "CasinoScene.h"    // Incluir CasinoScene para la transición al casino
#include "MapScene.h"  // Incluir MapScene para la transición al mapa
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

    // Tamaño visible de la pantalla
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
    mapButton->setPosition(1520, 80);  // Ajusta el tamaño de la posición del botón

    // Crear el menú con el botón de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacción para los objetos en el banco
    crearInteractionButtons();

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void BankScene::crearInteractionButtons()
{
    // Botón para abrir la caja fuerte (más pequeño)
    auto buttonSafe = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideSafe, this)
    );
    buttonSafe->setScale(0.04f);  // Hacerlo más pequeño
    buttonSafe->setPosition(770, 540);  // Posición del botón en el banco

    // Botón para abrir el cheque (más pequeño)
    auto buttonCheck = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideCheck, this)
    );
    buttonCheck->setScale(0.04f);  // Hacerlo más pequeño
    buttonCheck->setPosition(450, 80);  // Posición del botón en el banco

    // Botón para abrir la computadora (más pequeño)
    auto buttonComputer = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideComputer, this)
    );
    buttonComputer->setScale(0.04f);  // Hacerlo más pequeño
    buttonComputer->setPosition(1050, 450);  // Posición del botón en el banco

    // Botón para abrir el cuadro de diálogo (más pequeño)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(BankScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo más pequeño
    buttonDialog->setPosition(1250, 400);  // Posición del botón en el banco

    // Crear el menú con los botones
    auto menu = Menu::create(buttonSafe, buttonCheck, buttonComputer, buttonDialog, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Función para mostrar u ocultar la imagen de la caja fuerte
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

// Función para mostrar u ocultar la imagen del cheque
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

// Función para mostrar u ocultar la imagen de la computadora
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

// Función para mostrar u ocultar la imagen del cuadro de diálogo
void BankScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("bank_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de diálogo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

// Configurar el listener del teclado para ocultar las imágenes con ESC
void BankScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las imágenes");
            // Ocultar todas las imágenes si están visibles
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
