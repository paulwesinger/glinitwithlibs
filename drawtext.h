/*
 * Änderung an Stelle des bisherigen codes in Voxel und co:
 * Class Drawtext von Base2d ableiten
 * Shader aus datei einlesen ?
 * Mehr Fonts ?
 */


#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;

const string GNU_DEFAULT_FONT = "/usr/share/fonts/gnu-free/FreeSans.ttf";
const string GNU_DEFAULT_FONT_BOLD = "/usr/share/fonts/gnu-free/FreeSansBold.ttf";

const string GNU_DEFAULT_OBLIQUE_FONT = "/usr/share/fonts/gnu-free/FreeSansOblique.ttf";
const string GNU_DEFAULT_OBLIQUE_FONT_BOLD = "/usr/share/fonts/gnu-free/FreeSansBoldOblique.ttf";

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    FT_Pos     Advance;    // Offset to advance to next glyph
    GLuint     Height;
};

struct sTextfeld{
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};


class DrawText
{
public:
    DrawText();


};

#endif // DRAWTEXT_H
