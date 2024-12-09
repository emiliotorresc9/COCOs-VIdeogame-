#include "ChurchScene.h"
#include "OfficeScene.h"  // Incluir OfficeScene para la transici�n
#include "HospitalScene.h"  // Incluir HospitalScene para la transici�n
#include "MapScene.h"  // Incluir MapScene para la transici�n al mapa
#include "cocos2d.h"

USING_NS_CC;

Scene* ChurchScene::createScene()
{
    return ChurchScene::create();
}

bool ChurchScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tama�o visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo de la iglesia
    auto background = Sprite::create("church_scene.png");
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'church_scene.png'");
        return false;
    }

    // Ajustar la imagen para que cubra toda la pantalla
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    // Crear el bot�n de mapa en esta escena
    auto mapButton = MenuItemImage::create(
        "map_button.png",         // Imagen normal del bot�n
        "map_button.png",         // Imagen cuando el mouse est� sobre el bot�n
        [](Ref* sender) {
            auto mapScene = MapScene::createScene();
            Director::getInstance()->pushScene(mapScene);  // Abre el mapa
        });

    // Ajustar la escala y posici�n del bot�n de mapa
    mapButton->setScale(0.45f);  // Cambia el valor si es necesario
    mapButton->setPosition(1520, 80);  // Ajusta la posici�n seg�n lo necesites

    // Crear el men� con el bot�n de mapa
    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Crear los botones de interacci�n para los objetos en la iglesia
    crearInteractionButtons();

    // Inicializar las variables para las im�genes
    scriptImage = nullptr;
    chestImage = nullptr;
    dialogImage = nullptr;
    bibleImage = nullptr;

    // Configurar el listener del teclado para ESC
    setupKeyboardListener();

    // Configurar el listener del teclado para las flechas
    setupArrowKeyListener();

    return true;
}

void ChurchScene::crearInteractionButtons()
{
    // Bot�n para abrir el script (m�s peque�o)
    auto buttonScript = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ChurchScene::showHideScript, this)
    );
    buttonScript->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonScript->setPosition(480, 80);  // Posici�n del bot�n en la iglesia

    // Bot�n para abrir el cofre (m�s peque�o)
    auto buttonChest = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ChurchScene::showHideChest, this)
    );
    buttonChest->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonChest->setPosition(650, 420);  // Posici�n del bot�n en la iglesia

    // Bot�n para abrir el cuadro de di�logo (m�s peque�o)
    auto buttonDialog = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ChurchScene::showHideDialog, this)
    );
    buttonDialog->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonDialog->setPosition(1280, 300);  // Posici�n del bot�n en la iglesia

    // Bot�n para abrir la biblia (m�s peque�o)
    auto buttonBible = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(ChurchScene::showHideBible, this)
    );
    buttonBible->setScale(0.04f);  // Hacerlo m�s peque�o
    buttonBible->setPosition(1065, 320);  // Posici�n del bot�n en la iglesia

    // Crear el men� con los botones
    auto menu = Menu::create(buttonScript, buttonChest, buttonDialog, buttonBible, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

// Funci�n para mostrar u ocultar la imagen del script
void ChurchScene::showHideScript(Ref* sender)
{
    if (!scriptImage)
    {
        scriptImage = Sprite::create("church_script.png");
        scriptImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(scriptImage, 2);  // Agregar la imagen del script al frente
    }
    else
    {
        scriptImage->setVisible(!scriptImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen del cofre
void ChurchScene::showHideChest(Ref* sender)
{
    if (!chestImage)
    {
        chestImage = Sprite::create("church_chest.png");
        chestImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(chestImage, 2);  // Agregar la imagen del cofre al frente
    }
    else
    {
        chestImage->setVisible(!chestImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen del cuadro de di�logo
void ChurchScene::showHideDialog(Ref* sender)
{
    if (!dialogImage)
    {
        dialogImage = Sprite::create("church_dialog.png");
        dialogImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(dialogImage, 2);  // Agregar la imagen del cuadro de di�logo al frente
    }
    else
    {
        dialogImage->setVisible(!dialogImage->isVisible());  // Alternar visibilidad
    }
}

// Funci�n para mostrar u ocultar la imagen de la biblia
void ChurchScene::showHideBible(Ref* sender)
{
    if (!bibleImage)
    {
        bibleImage = Sprite::create("church_bible.png");
        bibleImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(bibleImage, 2);  // Agregar la imagen de la biblia al frente
    }
    else
    {
        bibleImage->setVisible(!bibleImage->isVisible());  // Alternar visibilidad
    }
}

// Configurar el listener del teclado para ocultar las im�genes con ESC
void ChurchScene::setupKeyboardListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las im�genes");
            // Ocultar todas las im�genes si est�n visibles
            if (scriptImage) scriptImage->setVisible(false);
            if (chestImage) chestImage->setVisible(false);
            if (dialogImage) dialogImage->setVisible(false);
            if (bibleImage) bibleImage->setVisible(false);
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Configurar el listener del teclado para cambiar entre escenas con las flechas
void ChurchScene::setupArrowKeyListener()
{
    // Crear el listener de teclado
    auto listener = EventListenerKeyboard::create();

    // Definir lo que sucede cuando una tecla es presionada
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            CCLOG("Flecha izquierda: Regresando a OfficeScene");
            // Cambiar a la escena de la oficina
            auto officeScene = OfficeScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, officeScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            CCLOG("Flecha derecha: Cambiando a HospitalScene");
            // Cambiar a la escena del hospital
            auto hospitalScene = HospitalScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, hospitalScene));
        }
        };

    // Registrar el listener con la escena
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
