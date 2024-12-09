#ifndef __CHURCH_SCENE_H__
#define __CHURCH_SCENE_H__

#include "cocos2d.h"

class ChurchScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // Funciones para mostrar y ocultar las im�genes de los objetos en la iglesia
    void showHideScript(Ref* sender);
    void showHideChest(Ref* sender);
    void showHideDialog(Ref* sender);
    void showHideBible(Ref* sender);

    // Funci�n para configurar el listener del teclado (ESC para ocultar im�genes)
    void setupKeyboardListener();

    // Funci�n para configurar el listener de las flechas para cambiar de escena
    void setupArrowKeyListener();

    // Macro de creaci�n
    CREATE_FUNC(ChurchScene);

private:
    // Variables para las im�genes de los objetos en la iglesia
    cocos2d::Sprite* scriptImage;
    cocos2d::Sprite* chestImage;
    cocos2d::Sprite* dialogImage;
    cocos2d::Sprite* bibleImage;

    // Funci�n para crear los botones de interacci�n
    void crearInteractionButtons();
};

#endif // __CHURCH_SCENE_H__

