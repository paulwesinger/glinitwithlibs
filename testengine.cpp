#include <string>
#include <iostream>
#include "testengine.h"
#include "imageloader.h"


#include <glew.h>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>

TestEngine::TestEngine(int resx, int resy){
    _ResX = resx;
    _ResY = resy;
}

TestEngine::~TestEngine(){
    DestroySDL();
    if (_Shader)
        delete _Shader;
    for (TextDraw* elem: _Displays)
        delete elem;

    _Displays.clear();

}

void TestEngine::Prepare2D() {
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);


    //projection =  glm::ortho(0.0f,static_cast<GLfloat>(_ResX), static_cast<GLfloat>(_ResY) , 0.0f);   //,  -1.0f, 1.0f);
    //projection =  glm::orthoRH(0.0f,static_cast<GLfloat>(_ResX), static_cast<GLfloat>(_ResY), 0.0f,  -100.0f, 100.0f);
}

void TestEngine::InitProjection(){
    projection = new Projection(0,_ResX,0,_ResY,0.01f,1000.0f);
    if (projection != nullptr) {
        log.loginfo("Created Procjection Class","InitGL::InitMatrices");
    }
    else{
        log.logwarn("Creating Projection failed");
    }
}
void TestEngine::InitShaders() {
    //================================================================
    //Test für CustomShader
    log.loginfo("===========================");
    log.loginfo("Erstelle Shaders...........");
    log.loginfo("===========================");
    _Shader = new Shader();
    _CurrentShader = ShaderType::LIGHT_SHADER;
    // ========================================================================
}

void TestEngine::Restore3D() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glDepthMask(1);   
}

SDL_DisplayMode TestEngine::getCurrentDisplayMode(){
    return DesktopDisplayMode;
}

string TestEngine::getCurrentDisplayModeAsString(){
    stringstream stream;

    stream  <<"Aktueller Display- Modus:\n" <<
        to_string(DesktopDisplayMode.w) << " x " << to_string(DesktopDisplayMode.h)  <<
        " Format: " << DesktopDisplayMode.format;

    return stream.str();
}

// ****************************************************************
// Init. der engine-> Images, renderer, usw laden
// ****************************************************************
bool TestEngine::InitEngine(){

    log.loginfo("####################################");
    log.loginfo("Init Shaders","TestEngine::IniEngine");
    log.loginfo("####################################");
    log.logEmptyLine(1);

    InitShaders();
    InitProjection();


    log.loginfo("Starte initialisierung der engine","TestEngine::IniEngine");
    log.loginfo(getCurrentDisplayModeAsString(),"TestEngine::InitEngine");
    log.logEmptyLine(1);
    log.loginfo("Teste Imageloading...");

    _Quit = false;

    SDL_Surface* surf = ImageLoader::getSurface(IMG_ERROR);
    if (surf)
        log.loginfo("Standard SDL Surface geladen");
    else
       log.logError("Kein surface geladen");


    // *******************
    // Standard Farbe Grau
    // *******************

    log.loginfo("TestEngine:: Background nach Grau");

    // **************************
    // Standard grau
    // **************************
    _ClearColor.x = 0.5f;
    _ClearColor.y = 0.5f;
    _ClearColor.z = 0.5f;
    _ClearColor.w = 1.0f;
    glClearColor(_ClearColor.x, _ClearColor.y, _ClearColor.z, _ClearColor.w);

    if (AddTextDisplay()) {

        _Displays[0]->SetText("Neues Fenster");
        log.loginfo("Text Display erstellt");

        log.loginfo(_Displays[0]->GetText());
        return true;
    }
    else{
        log.logwarn("Kein Textfenster erstellt !");
    }



    return true;
}

bool TestEngine::InitSDL(){

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret != 0)
        return ret;

    atexit(SDL_Quit);
    log.loginfo("SDL Init  success");
    // Attribute
    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // **********************************
    // SDL Window init:
    // **********************************

    GLWindow = CreateGLWindow();
    return GLWindow != nullptr;
}

bool TestEngine::AddTextDisplay(){
    sPoint p(10,10);
    TextDraw * t = new TextDraw(_ResX,_ResY,p,_Shader);

    _Displays.push_back(t);

    //  string sCount = std::to_string( _Displays.size());
    return true;
}


SDL_Window * TestEngine::CreateGLWindow(bool fullscreen,std::string caption){
    if ( fullscreen) {
        GLWindow = SDL_CreateWindow(
            caption.c_str(),
            0, //SDL_WINDOWPOS_UNDEFINED,
            0, //SDL_WINDOWPOS_UNDEFINED,
            _ResX,_ResY,
            //SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL
            SDL_WINDOW_OPENGL
            );
        SDL_SetWindowFullscreen(GLWindow,SDL_WINDOW_FULLSCREEN);

    }
    else {

        GLWindow = SDL_CreateWindow(
            caption.c_str(),
            0,
            0,
            _ResX,_ResY,
            SDL_WINDOW_OPENGL);
    }
    glViewport(0,0,_ResX, _ResY);

    if ( GLWindow == nullptr)  {
        sdlstate = INIT_STATES::SDL_WINDOWCREATE_FAILED;
        sdl_die("Konnte Fenster nicht erzeugen");
        return nullptr;
    }

    glContext = SDL_GL_CreateContext(GLWindow);
    if ( ! glContext) {
        sdlstate = INIT_STATES::SDL_CONTEXT_FAILED;
        sdl_die (" Konnte Context nicht erzeugen ");
        return nullptr;
    }

    glewExperimental = GL_TRUE;
    glewInit();

    SDL_GL_SetSwapInterval(1);


    DesktopDisplayMode.w = _ResX;
    DesktopDisplayMode.h = _ResY;
    DesktopDisplayMode.format = SDL_PIXELFORMAT_RGBA8888;
    SDL_SetWindowDisplayMode(GLWindow,&DesktopDisplayMode);

    sdlstate = INIT_STATES::SDL_CONTEXT_OK;
    return GLWindow;
}

INIT_STATES TestEngine::getInitState(){
    return sdlstate;
}

// **********************************************
// event handling
// **********************************************
bool TestEngine::HandleMessage(){


    while (SDL_PollEvent(&_Event))
    {
        switch(_Event.type) {
        case SDL_KEYDOWN:
            switch(_Event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _Quit =true;
                break;
            }
            break;
        case SDL_KEYUP:
            break;
        default:
            break;
        }
    }
    return true;
}

void TestEngine::Run(){

    glEnable(GL_DEPTH_TEST);

    while (! _Quit) {

        HandleMessage();

        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor( _ClearColor.x, _ClearColor.y, _ClearColor.z, _ClearColor.w);

        Prepare2D();

        for(TextDraw* elems: _Displays) {
            elems->Draw();
        }


        Restore3D();

        SDL_GL_SwapWindow(GLWindow);
        //_Quit =true;
    }
}


void TestEngine::DestroySDL(){
    if(GLWindow != nullptr)
        SDL_DestroyWindow(GLWindow);

}

void TestEngine::sdl_die(std::string msg){
    log.loginfo( msg + "\n");
}


void TestEngine::PrintDisplayModes(){

    int numDisplaymodes = SDL_GetNumDisplayModes(0);
    log.logimage("Num Display modes: " + std::to_string(numDisplaymodes));

    // Alle Display modes auflisten:

    for(int j = 0; j < SDL_GetNumVideoDisplays(); j++)
    {
        for (int i = 0; i < numDisplaymodes; i++ ) {
            SDL_DisplayMode dpm;
            SDL_GetDisplayMode(j,i,&dpm);
            std::string w = std::to_string(dpm.w);
            std::string h = std::to_string(dpm.h);
            std::string index = std::to_string(i);
            try {

                // todo: Pixelformat auswerten
                log.loginfo("Display : " + std::to_string(j) + " Resolution Mode[" + index+ "] : " + w + "x" + h + "\n");
            }
            catch ( ...) {
                log.loginfo("Konnte Display Mode[" + index + "] nicht ermitteln\n");
            }

        }
    }
}

void TestEngine::PrintOpenGLData(){

    printf("Vendor :  %s\n",glGetString(GL_VENDOR));
    printf("Renderer  %s\n",glGetString(GL_RENDERER));
    printf("Version   %s\n",glGetString(GL_VERSION));
}
void TestEngine::PrintData(){    
    PrintDisplayModes();
    PrintOpenGLData(); 

}
