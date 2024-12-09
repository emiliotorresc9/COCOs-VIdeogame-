#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 800);  // Resolución de diseño

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

void AppDelegate::initGLContextAttrs()
{
    // Configuración de los atributos del contexto OpenGL (esto es opcional, dependiendo de tu proyecto)
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Inicializar el director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) {
        glview = GLViewImpl::createWithRect("ProyectoProgramacion", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
        director->setOpenGLView(glview);
    }

    // Establecer FPS
    director->setAnimationInterval(1.0f / 60);

    // Establecer la resolución de diseño
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // Crear la escena de HelloWorld (la que solo contiene la imagen de fondo)
    auto scene = HelloWorld::createScene();

    // Ejecutar la escena
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    // Detener la animación cuando la aplicación entra en segundo plano
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    // Reanudar la animación cuando la aplicación regresa al primer plano
    Director::getInstance()->startAnimation();
}
