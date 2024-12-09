#include "OfficeScene.h"
#include "MapScene.h"
#include "BoatScene.h"
#include "ChurchScene.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* OfficeScene::createScene()
{
    return OfficeScene::create();
}

bool OfficeScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Tamaño visible de la pantalla
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Cargar la imagen de fondo de la oficina
    auto background = Sprite::create("mansion_room.png");
    if (background == nullptr) {
        CCLOG("Error: No se pudo cargar 'mansion_room.png'");
        return false;
    }

    // Ajustar la imagen para que cubra toda la pantalla
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    // Crear los botones de interacción para los objetos en la oficina
    crearInteractionButtons();

    // Inicializar las variables para las imágenes
    safeImage = nullptr;
    computerImage = nullptr;
    bookImage = nullptr;
    papersImage = nullptr;

    // Estado de desbloqueo
    isSafeUnlocked = false;
    isComputerUnlocked = false;

    // Inicializar variables del cronómetro
    cronometroLabel = nullptr;
    tiempoTranscurrido = 0;

    // Crear el botón de mapa en esta escena
    auto mapButton = MenuItemImage::create(
        "map_button.png",
        "map_button.png",
        [](Ref* sender) {
            auto mapScene = MapScene::createScene();
            Director::getInstance()->pushScene(mapScene);
        });

    mapButton->setScale(0.45f);
    mapButton->setPosition(1520, 80);

    auto menu = Menu::create(mapButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Configurar los listeners de teclado
    setupKeyboardListener();
    setupArrowKeyListener();

    // Iniciar el cronómetro
    iniciarCronometro();

    // Programar la aparición de la pregunta final después de 5 minutos (300 segundos)
    scheduleOnce([=](float) { mostrarPreguntaFinal(); }, 300.0f, "PreguntaFinal");

    return true;
}

void OfficeScene::crearInteractionButtons()
{
    auto buttonSafe = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(OfficeScene::showHideSafe, this)
    );
    buttonSafe->setScale(0.04f);
    buttonSafe->setPosition(660, 440);

    auto buttonComputer = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(OfficeScene::showHideComputer, this)
    );
    buttonComputer->setScale(0.04f);
    buttonComputer->setPosition(1080, 360);

    auto buttonPapers = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(OfficeScene::showHidePapers, this)
    );
    buttonPapers->setScale(0.04f);
    buttonPapers->setPosition(800, 30);

    auto buttonBook = MenuItemImage::create(
        "general_button.png",
        "general_button_pressed.png",
        CC_CALLBACK_1(OfficeScene::showHideBook, this)
    );
    buttonBook->setScale(0.04f);
    buttonBook->setPosition(950, 500);

    auto menu = Menu::create(buttonSafe, buttonComputer, buttonPapers, buttonBook, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void OfficeScene::iniciarCronometro()
{
    // Etiqueta para el cronómetro
    cronometroLabel = Label::createWithTTF("Tiempo: 00:00", "fonts/Marker Felt.ttf", 24);
    cronometroLabel->setPosition(Vec2(100, Director::getInstance()->getVisibleSize().height - 50)); // Esquina superior izquierda
    this->addChild(cronometroLabel, 5);

    // Tiempo inicial
    tiempoTranscurrido = 0;

    // Programar la actualización del cronómetro cada segundo
    this->schedule([=](float) mutable {
        tiempoTranscurrido++;
        int minutos = tiempoTranscurrido / 60;
        int segundos = tiempoTranscurrido % 60;

        // Actualizar el texto del cronómetro
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Tiempo: %02d:%02d", minutos, segundos);
        cronometroLabel->setString(buffer);
        }, 1.0f, "ActualizarCronometro");
}

void OfficeScene::mostrarPreguntaFinal()
{
    // Crear la etiqueta para la pregunta
    auto labelPregunta = Label::createWithTTF("¿Quién asesinó al millonario?", "fonts/Marker Felt.ttf", 36);
    labelPregunta->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
        Director::getInstance()->getVisibleSize().height / 2 + 50));
    this->addChild(labelPregunta, 3);

    // Crear un botón para responder "El Capitán"
    auto botonCapitan = ui::Button::create("general_button.png", "general_button_pressed.png");
    botonCapitan->setScale(0.1f);
    botonCapitan->setTitleText("Capitan");
    botonCapitan->setTitleFontSize(24);
    botonCapitan->setPosition(Vec2(labelPregunta->getPositionX(), labelPregunta->getPositionY() - 100));
    this->addChild(botonCapitan, 4);

    // Listener para el botón "El Capitán"
    botonCapitan->addClickEventListener([=](Ref* sender) {
        CCLOG("¡Respuesta correcta! Resolviste el caso.");
        auto resultado = Label::createWithTTF("¡Correcto! Resolviste el caso.", "fonts/Marker Felt.ttf", 30);
        resultado->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
            Director::getInstance()->getVisibleSize().height / 2 - 50));
        this->addChild(resultado, 5);
        botonCapitan->removeFromParent();
        labelPregunta->removeFromParent();
        });
}

void OfficeScene::showHideSafe(Ref* sender)
{
    if (!safeImage)
    {
        safeImage = Sprite::create("office_safe.png");
        safeImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(safeImage, 2);
    }

    if (isSafeUnlocked)
    {
        safeImage->setVisible(!safeImage->isVisible());
        return;
    }

    if (!safeTextFieldBackground)
    {
        safeTextFieldBackground = Sprite::create();
        safeTextFieldBackground->setTextureRect(Rect(0, 0, 220, 50));
        safeTextFieldBackground->setColor(Color3B::WHITE);
        safeTextFieldBackground->setOpacity(200);
        safeTextFieldBackground->setPosition(Vec2(safeImage->getPositionX(), safeImage->getPositionY() + 100));
        this->addChild(safeTextFieldBackground, 3);
    }

    if (!safeTextField)
    {
        safeTextField = ui::TextField::create("Enter code", "Arial", 20);
        safeTextField->setPosition(safeTextFieldBackground->getPosition());
        safeTextField->setMaxLength(6);
        safeTextField->setMaxLengthEnabled(true);
        safeTextField->setTextColor(Color4B::BLACK);
        safeTextField->setPlaceHolderColor(Color4B::GRAY);
        safeTextField->setCursorEnabled(true);
        this->addChild(safeTextField, 4);
    }

    if (!safeVerifyButton)
    {
        safeVerifyButton = ui::Button::create("general_button.png", "general_button_pressed.png");
        safeVerifyButton->setScale(0.04f);
        safeVerifyButton->setTitleText("Verify");
        safeVerifyButton->setTitleFontSize(15);
        safeVerifyButton->setPosition(Vec2(safeTextField->getPositionX() + safeTextFieldBackground->getContentSize().width / 2 + 30,
            safeTextField->getPositionY()));
        this->addChild(safeVerifyButton, 4);

        safeVerifyButton->addClickEventListener([=](Ref* sender) {
            std::string userInput = safeTextField->getString();
            std::string correctCode = "1234";

            if (userInput == correctCode)
            {
                CCLOG("¡Contraseña correcta! Caja fuerte abierta.");
                safeImage->setTexture("office_safe_opened.png");
                isSafeUnlocked = true;

                safeTextField->removeFromParent();
                safeTextFieldBackground->removeFromParent();
                safeVerifyButton->removeFromParent();
                safeTextField = nullptr;
                safeTextFieldBackground = nullptr;
                safeVerifyButton = nullptr;
            }
            else
            {
                CCLOG("Contraseña incorrecta. Intenta nuevamente.");
                safeTextField->setString("");
            }
            });
    }

    safeImage->setVisible(true);
}

void OfficeScene::showHideComputer(Ref* sender)
{
    if (!computerImage)
    {
        computerImage = Sprite::create("office_computer.png");
        computerImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(computerImage, 2);
    }

    if (isComputerUnlocked)
    {
        computerImage->setVisible(!computerImage->isVisible());
        return;
    }

    if (!computerTextFieldBackground)
    {
        computerTextFieldBackground = Sprite::create();
        computerTextFieldBackground->setTextureRect(Rect(0, 0, 220, 50));
        computerTextFieldBackground->setColor(Color3B::WHITE);
        computerTextFieldBackground->setOpacity(200);
        computerTextFieldBackground->setPosition(Vec2(computerImage->getPositionX(), computerImage->getPositionY() - 50));
        this->addChild(computerTextFieldBackground, 3);
    }

    if (!computerTextField)
    {
        computerTextField = ui::TextField::create("Enter password", "Arial", 20);
        computerTextField->setPosition(computerTextFieldBackground->getPosition());
        computerTextField->setMaxLength(10);
        computerTextField->setMaxLengthEnabled(true);
        computerTextField->setTextColor(Color4B::BLACK);
        computerTextField->setPlaceHolderColor(Color4B::GRAY);
        computerTextField->setCursorEnabled(true);
        this->addChild(computerTextField, 4);
    }

    if (!computerVerifyButton)
    {
        computerVerifyButton = ui::Button::create("general_button.png", "general_button_pressed.png");
        computerVerifyButton->setScale(0.04f);
        computerVerifyButton->setTitleText("Verify");
        computerVerifyButton->setTitleFontSize(15);
        computerVerifyButton->setPosition(Vec2(computerTextField->getPositionX() + computerTextFieldBackground->getContentSize().width / 2 + 30,
            computerTextField->getPositionY()));
        this->addChild(computerVerifyButton, 4);

        computerVerifyButton->addClickEventListener([=](Ref* sender) {
            std::string userInput = computerTextField->getString();
            std::string correctCode = "secure123";

            if (userInput == correctCode)
            {
                CCLOG("¡Contraseña correcta! Computadora desbloqueada.");
                computerImage->setTexture("office_computer_unlocked.png");
                isComputerUnlocked = true;

                computerTextField->removeFromParent();
                computerTextFieldBackground->removeFromParent();
                computerVerifyButton->removeFromParent();
                computerTextField = nullptr;
                computerTextFieldBackground = nullptr;
                computerVerifyButton = nullptr;
            }
            else
            {
                CCLOG("Contraseña incorrecta. Intenta nuevamente.");
                computerTextField->setString("");
            }
            });
    }

    computerImage->setVisible(true);
}

void OfficeScene::showHidePapers(Ref* sender)
{
    if (!papersImage)
    {
        papersImage = Sprite::create("office_papers.png");
        papersImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(papersImage, 2);
    }
    else
    {
        papersImage->setVisible(!papersImage->isVisible());
    }
}

void OfficeScene::showHideBook(Ref* sender)
{
    if (!bookImage)
    {
        bookImage = Sprite::create("office_book.png");
        bookImage->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(bookImage, 2);
    }
    else
    {
        bookImage->setVisible(!bookImage->isVisible());
    }
}

void OfficeScene::setupKeyboardListener()
{
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            CCLOG("ESC presionado: Ocultando todas las imágenes y elementos interactivos");

            if (safeImage) safeImage->setVisible(false);
            if (computerImage) computerImage->setVisible(false);
            if (papersImage) papersImage->setVisible(false);
            if (bookImage) bookImage->setVisible(false);

            if (safeTextField) {
                safeTextField->removeFromParent();
                safeTextField = nullptr;
            }
            if (safeTextFieldBackground) {
                safeTextFieldBackground->removeFromParent();
                safeTextFieldBackground = nullptr;
            }
            if (safeVerifyButton) {
                safeVerifyButton->removeFromParent();
                safeVerifyButton = nullptr;
            }

            if (computerTextField) {
                computerTextField->removeFromParent();
                computerTextField = nullptr;
            }
            if (computerTextFieldBackground) {
                computerTextFieldBackground->removeFromParent();
                computerTextFieldBackground = nullptr;
            }
            if (computerVerifyButton) {
                computerVerifyButton->removeFromParent();
                computerVerifyButton = nullptr;
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void OfficeScene::setupArrowKeyListener()
{
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            auto boatScene = BoatScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, boatScene));
        }

        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            auto churchScene = ChurchScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, churchScene));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
