#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <glframework.h>
#include <logger.h>
#include <rendertext.h>


class TestEngine : public GLFrameWork
{
public:
    TestEngine(int resx,int resy);
    ~TestEngine();
    virtual void DestroySDL() override;

    bool InitEngine();

    void PrintData();

protected:

    RenderText * text;
private:
    Logger log;

};

#endif // TESTENGINE_H
