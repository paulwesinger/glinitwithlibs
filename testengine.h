#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <glframework.h>
#include <logger.h>

class TestEngine : public GLFrameWork
{
public:
    TestEngine();
    ~TestEngine();
    virtual void DestroySDL() override;

    bool InitEngine();

    void PrintData();

private:
    Logger log;

};

#endif // TESTENGINE_H
