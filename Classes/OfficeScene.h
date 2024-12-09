#ifndef __OFFICE_SCENE_H__
#define __OFFICE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OfficeScene : public cocos2d::Scene
{
public:
    // Crear la escena
    static cocos2d::Scene* createScene();

    // Inicialización de la escena
    virtual bool init();

    // Macro para el método create()
    CREATE_FUNC(OfficeScene);

private:
    // Métodos privados
    void crearInteractionButtons();          // Crear botones de interacción
    void iniciarCronometro();                // Iniciar el cronómetro
    void mostrarPreguntaFinal();             // Mostrar la pregunta final después de 5 minutos
    void showHideSafe(cocos2d::Ref* sender); // Mostrar/ocultar la caja fuerte
    void showHideComputer(cocos2d::Ref* sender); // Mostrar/ocultar la computadora
    void showHidePapers(cocos2d::Ref* sender);   // Mostrar/ocultar los papeles
    void showHideBook(cocos2d::Ref* sender);     // Mostrar/ocultar el libro
    void setupKeyboardListener();            // Configurar el listener para teclas
    void setupArrowKeyListener();            // Configurar el listener para teclas de flecha

    // Variables de la escena
    cocos2d::Sprite* safeImage;              // Imagen de la caja fuerte
    cocos2d::Sprite* computerImage;          // Imagen de la computadora
    cocos2d::Sprite* bookImage;              // Imagen del libro
    cocos2d::Sprite* papersImage;            // Imagen de los papeles

    // Elementos interactivos de la caja fuerte
    cocos2d::ui::TextField* safeTextField = nullptr;       // Cuadro de texto de la caja fuerte
    cocos2d::Sprite* safeTextFieldBackground = nullptr;    // Fondo del cuadro de texto de la caja fuerte
    cocos2d::ui::Button* safeVerifyButton = nullptr;       // Botón de verificación de la caja fuerte

    // Elementos interactivos de la computadora
    cocos2d::ui::TextField* computerTextField = nullptr;       // Cuadro de texto de la computadora
    cocos2d::Sprite* computerTextFieldBackground = nullptr;    // Fondo del cuadro de texto de la computadora
    cocos2d::ui::Button* computerVerifyButton = nullptr;       // Botón de verificación de la computadora

    // Estado de desbloqueo
    bool isSafeUnlocked;          // Estado de desbloqueo de la caja fuerte
    bool isComputerUnlocked;      // Estado de desbloqueo de la computadora

    // Variables para el cronómetro
    cocos2d::Label* cronometroLabel;  // Etiqueta del cronómetro
    int tiempoTranscurrido;           // Tiempo transcurrido en segundos
};

#endif // __OFFICE_SCENE_H__
