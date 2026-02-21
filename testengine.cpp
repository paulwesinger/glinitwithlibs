#include <string>
#include <iostream>
#include "testengine.h"
#include "imageloader.h"


TestEngine::TestEngine():
    GLFrameWork(){

}

TestEngine::~TestEngine(){

}

void TestEngine::DestroySDL(){
    GLFrameWork::DestroySDL();

    // ************************************************************
    // Hier noch weitere release gschichten..
    // ************************************************************
}


// ****************************************************************
// Init. der engine-> Images, renderer, usw laden
// ****************************************************************
bool TestEngine::InitEngine(){

    log.loginfo("Starte initialisierung der engine","TestEngine::IniEngine");
    log.loginfo(getCurrentDisplayModeAsString(),"TestEngine::InitEngine");
    log.logEmptyLine(1);
    log.loginfo("Teste Imageloading...");

    SDL_Surface* surf = ImageLoader::getSurface(IMG_ERROR);
    if (surf)
        log.loginfo("Standard SDL Surface geladen");
    else
       log.logError("Kein surface geladen");

    log.loginfo("Stelle auf andere Hintergrundfarbe um: GRAU ");
    setClearColor(0.8f,0.8f,1.0f,1.0f);


    return true;
}


void TestEngine::PrintData(){
    std::string log = Log();
    PrintDisplayModes();
    PrintOpenGLData();
    log = Log();
    std::cout << log ;
}
