#ifndef __HOSPITAL_SCENE_H__
#define __HOSPITAL_SCENE_H__

#include "cocos2d.h"

class HospitalScene : public cocos2d::Scene
{
public:
    // Funci�n para crear la escena
    static cocos2d::Scene* createScene();

    // Funci�n de inicializaci�n
    virtual bool init();

    // Funciones de callback para mostrar/ocultar las im�genes
    void showHideDialog(Ref* sender);
    void showHideClock(Ref* sender);
    void showHideMedicine(Ref* sender);
    void showHideRecord(Ref* sender);
    void showHideComputer(Ref* sender);

    // Funci�n para configurar el listener del teclado
    void setupKeyboardListener();

    // Funci�n para configurar el listener de las flechas para cambiar de escenas
    void setupArrowKeyListener();

    // Macro de creaci�n
    CREATE_FUNC(HospitalScene);

private:
    // Punteros a las im�genes
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* clockImage;
    cocos2d::Sprite* medicineImage;
    cocos2d::Sprite* recordImage;
    cocos2d::Sprite* computerImage;

    // Funci�n para crear los botones
    void crearInteractionButtons();
};

#endif // __HOSPITAL_SCENE_H__
