#include "HospitalScene.h"
#include "ChurchScene.h"  // Incluir ChurchScene para la transición al regreso
#include "BankScene.h"    // Incluir BankScene para la transición al banco
#include "MapScene.h"  // Incluir MapScene para la transición al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* HospitalScene::createScene()
{
    return HospitalScene::create();
}

bool HospitalScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo del hospital
    auto background = Sprite::create("hospital_scene.png");
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'hospital_scene.png'");
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

    // Escalar y posicionar el botón de mapa
    mapButton->setScale(0.45f);  // Ajusta el tamaño del botón
    mapButton->setPosition(1520, 80);  // Ajusta la posición según lo necesites

    // Crear el menú con el botón de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacción para los objetos en el hospital
    crearInteractionButtons();

    // Inicializar las variables para las imágenes
    dialogImage = nullptr;
    clockImage = nullptr;
    medicineImage = nullptr;
    recordImage = nullptr;
    computerImage = nullptr;

    // Configurar el listener del teclado
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void HospitalScene::crearInteractionButtons()
{
    // Botón para abrir el cuadro de diálogo
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(HospitalScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo más pequeño
    buttonDialog->setPosition(770, 430);  // Posición del botón en el hospital

    // Botón para abrir el reloj
    auto buttonClock = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(HospitalScene::showHideClock, this)
    );
    buttonClock->setScale(0.04f);
    buttonClock->setPosition(882, 630);  // Posición del botón en el hospital

    // Botón para abrir la medicina
    auto buttonMedicine = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(HospitalScene::showHideMedicine, this)
    );
    buttonMedicine->setScale(0.04f);
    buttonMedicine->setPosition(270, 480);

    // Botón para abrir el expediente
    auto buttonRecord = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(HospitalScene::showHideRecord, this)
    );
    buttonRecord->setScale(0.04f);
    buttonRecord->setPosition(620, 40);

    // Botón para abrir la computadora
    auto buttonComputer = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(HospitalScene::showHideComputer, this)
    );
    buttonComputer->setScale(0.04f);
    buttonComputer->setPosition(1020, 390);

    // Crear el menú con los botones
    auto menu = Menu::create(buttonDialog, buttonClock, buttonMedicine, buttonRecord, buttonComputer, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Funciones para mostrar u ocultar las imágenes (el mismo patrón para cada función)

void HospitalScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("hospital_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());
    }
}

void HospitalScene::showHideClock(Ref* sender)
{
    if (!clockImage)
    {
        clockImage = Sprite::create("hospital_clock.png");
        clockImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(clockImage, 2);
    }
    else
    {
        clockImage->setVisible(!clockImage->isVisible());
    }
}

void HospitalScene::showHideMedicine(Ref* sender)
{
    if (!medicineImage)
    {
        medicineImage = Sprite::create("hospital_medicine.png");
        medicineImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(medicineImage, 2);
    }
    else
    {
        medicineImage->setVisible(!medicineImage->isVisible());
    }
}

void HospitalScene::showHideRecord(Ref* sender)
{
    if (!recordImage)
    {
        recordImage = Sprite::create("hospital_record.png");
        recordImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(recordImage, 2);
    }
    else
    {
        recordImage->setVisible(!recordImage->isVisible());
    }
}

void HospitalScene::showHideComputer(Ref* sender)
{
    if (!computerImage)
    {
        computerImage = Sprite::create("hospital_computer.png");
        computerImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(computerImage, 2);
    }
    else
    {
        computerImage->setVisible(!computerImage->isVisible());
    }
}

// Configurar el listener del teclado para ocultar las imágenes con ESC
void HospitalScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las imágenes");
            // Ocultar todas las imágenes si están visibles
            if (dialogImage) dialogImage->setVisible(false);
            if (clockImage) clockImage->setVisible(false);
            if (medicineImage) medicineImage->setVisible(false);
            if (recordImage) recordImage->setVisible(false);
            if (computerImage) computerImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Configurar el listener del teclado para cambiar entre escenas con las flechas
void HospitalScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a ChurchScene");
            // Cambiar a la escena de la iglesia
            auto churchScene = ChurchScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, churchScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a BankScene");
            // Cambiar a la escena del banco
            auto bankScene = BankScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, bankScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
