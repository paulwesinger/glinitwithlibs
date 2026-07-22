#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <string>
#include </usr/include/SDL2/SDL.h>

#include <logger.h>
#include "textdraw.h"
#include "vartypes.h"

typedef enum{
    SDL_CONTEXT_OK = 0,
    SDL_CONTEXT_FAILED,
    SDL_WINDOWCREATE_OK,
    SDL_WINDOWCREATE_FAILED,

    SDL_ADD_CONTROL_OK,
    SDL_ADD_CONTROL_FAILED,
    SDL_STATE_UNDEFINED

}INIT_STATES;


enum ShaderType {
    COLOR_SHADER = 0,
    TEXTURE_SHADER,
    LIGHT_SHADER,
    LIGHT_COLOR_SHADER,
    LIGHT_TEXTURE_SHADER,
    GLASS_SHADER
};



class TestEngine
{
public:
    TestEngine(int resx,int resy);
    ~TestEngine();
    virtual void DestroySDL();

    bool InitEngine();
    void PrintData();
    INIT_STATES getInitState();

    bool InitSDL();
    void Run();

    void PrintDisplayModes();
    void PrintOpenGLData();

    bool AddTextDisplay();

protected:
    // ***********************************
    // Display data
    // ***********************************
    SDL_DisplayMode getCurrentDisplayMode();
    string getCurrentDisplayModeAsString();

    void Prepare2D();
    void Restore3D();

    void InitShaders();

    SDL_Window * CreateGLWindow(bool fullscreen = false,string caption = "GLEngine");
    bool HandleMessage();
    void sdl_die(string msg);

    std::vector<TextDraw*> _Displays;

    SDL_GLContext glContext;
    SDL_Window * GLWindow =  nullptr;

    SDL_DisplayMode DesktopDisplayMode;

    int _ResX;
    int _ResY;
    bool _Quit;

    Shader * _Shader;
    ShaderType _CurrentShader;

    glm::mat4 projection;

    SDL_Event _Event;
    float4 _ClearColor;

    INIT_STATES sdlstate;

private:
    Logger log;

};

#endif // TESTENGINE_H
