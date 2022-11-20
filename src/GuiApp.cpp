//
//  GuiApp.cpp
//  Flocking
//
//  Created by Max Worgan on 12/10/2022.
//
#define SETTINGS_FILE "settings.xml"

#include "GuiApp.hpp"


void GuiApp::setup(){
    ofSetDataPathRoot("../Resources/data/");

    gui.setup();
    //GUI stuff
    bAddRandomAttractor.setup("Add Random Attractor");
    bClearAttractors.setup("Clear Attractors");
    bAddRandomRepulsor.setup("Add Random Repulsor");
    bClearRepulsors.setup("Clear Repulsors");
    bDrawNeighbourhoodDistance.setName("Draw Neighbourhood Dist");
    bDrawBoundingBox.setName("Draw Bounding Box");
    bFollowCamera.setName("Camera Follow");
    bCameraOrtho.setName("Orthographic");

    gui.add(cameraParams);
    gui.add(flockingParams);
    gui.add(centerPullParams);
    gui.add(attractorParams);
    gui.add(repulsorParams);
    gui.add(windParams);
    
    gui.loadFromFile(SETTINGS_FILE);
    
    
}

void GuiApp::draw(){
    gui.draw();
}
