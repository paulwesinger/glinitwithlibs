#include <string>
#include <iostream>
#include "testengine.h"
#include "imageloader.h"


TestEngine::TestEngine(int resx, int resy):
    GLFrameWork(resx,resy){

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


    // *******************
    // Standard Farbe Grau
    // *******************
    setClearColor(0.5f,0.5f,0.5f,0.5f);

    log.loginfo("TestEngine:: Background nach Grau");
    log.loginfo(Log());

    Logtext = "";

    if (AddTextDisplay()) {

        _Texts[0]->SetText("Neues Fenster");
        log.loginfo("Text Display erstellt");


        log.loginfo(_Texts[0]->GetText());
        return true;
    }

    log.logwarn("Text Display NICHT erstellt");
    return false;
}

void TestEngine::PrintData(){
    std::string log = Log();
    PrintDisplayModes();
    PrintOpenGLData();
    std::cout << Log() ;
    Logtext = "";

}
