#include "drawtext.h"

RenderText::RenderText() {}

RenderText::RenderText(int resx, int resy,Shader * sh){

}
RenderText::RenderText(const RenderText& orig){

}

bool RenderText::Init(int resx, int resy){
    _ResX = resx;
    _ResY = resy;
    // _RenderBottom = false;
    // _RenderHeader = false;
    // _HasBackground = false;
    // _HasTexture = false;
    // _AlignRight = false;
    _BackgroundColor = glm::vec4(0.0f,0.0f,0.8f,0.3f);
    _TextColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    _Scale = 1.0f;
    _Pixelsize = 16;
    _MarginLeft = 5.0f;
    _MarginRight= 5.0f;
    _MarginY = 5.0f;

    // ---------------------------------------
    //  Freetype2 init.
    // ---------------------------------------
    if (FT_Init_FreeType(&ft))
        log.logwarn("Konnte Freetype nicht initialisieren !!","TextRender::Init");
    else
        log.loginfo("Freetype2 initialisiert ","TextRender::Init");


    if (FT_New_Face(ft, _Font.c_str(), 0, &face)) {
        log.logwarn("Konnte Freetype2 Face nicht initialisieren","RenderText::Init");
        return false;
    }
    else
        log.loginfo("Freetype2 Face initialisiert ... ");


    // FT_Set_Pixel_Sizes(face, 0, _Pixelsize);

    // //if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    // //    logwarn("Char X konnte nicht geladen werden !","TextRender::Init");
    // //else
    // //    loginfo("Char X geladen ","TextRender::Init");

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    // // Char 0 .. 127 einlesen
    // glActiveTexture(GL_TEXTURE0);

    return true;
}
