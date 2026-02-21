#include <testengine.h>
#include<iostream>

int main(int argc, char *argv[])
{
    TestEngine * testengine = new TestEngine();
    if (testengine->InitSDL())
    {
        cout<<"OpenGL Context und Fenster erzeugt " << std::endl;
        testengine->PrintData();

        if (testengine->InitEngine()){

           testengine->Run();
        }
    }
    else{

        INIT_STATES state = testengine->getInitState();

        switch(state){

        case INIT_STATES::SDL_WINDOWCREATE_FAILED:
                cout<<"OpenGL Fenster konnte nicht erzeugt werden -> Abbruch" << std::endl;
            break;

            case INIT_STATES::SDL_CONTEXT_FAILED:
                cout<<"OpenGL Context konnte nicht erzeugt werden -> Abbruch" << std::endl;
            break;
            default:
                 cout<<"Unbekannter Feher" << std::endl;
        }




    }
   // QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    testengine->DestroySDL();
    return 0;// a.exec();
}
