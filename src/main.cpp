#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"
#include "GuiApp.hpp"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(1, 2);  // Programmable pipeline
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.setSize(220,500);
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<GuiApp> guiApp(new GuiApp);
    mainApp->guiWindow = guiApp;

    ofRunApp(guiWindow, guiApp);
    ofRunApp(mainWindow, mainApp);

    ofRunMainLoop();

}
