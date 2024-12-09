#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(IntroScene);

private:
    // Declaramos las funciones usadas en el archivo .cpp
    void startImageSequence();
    void changeImage(const std::string& imageName);

    // Nueva función para saltar la introducción
    void skipIntro();

    // Puntero al sprite de la imagen actual
    cocos2d::Sprite* currentImage;

    // ID del audio de la introducción
    int introAudioId;
};

#endif // __INTRO_SCENE_H__
