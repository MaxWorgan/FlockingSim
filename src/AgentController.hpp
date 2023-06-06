//
//  AgentController.hpp
//  Flocking
//
//  Created by Max Worgan on 18/09/2021.
//

#ifndef AgentController_hpp
#define AgentController_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Agent.hpp"
#include "ofxSharedMemory.hpp"
#include "BoundingBox.hpp"
#include "SwarmStats.hpp"
#include "ofxGui.h"
#include "GuiApp.hpp"

class AgentController {
    
public:
    AgentController(size_t numAgents, shared_ptr<GuiApp> guiWindow);
    void draw(bool drawAttractors);
    void applyFlocking();
    void attract(Agent &agent, const glm::vec2 &pos, const float strength, const float minDistance);
    void applyWind(Agent &agent, const float windAmount);
    void applyCenterPull(Agent &agent, const glm::vec2 &center);
    void applyForces();
    void updateAgents();
    void updateAgent(int index, float x, float y);
    
    void setHigherThreshold(float& f);
    void setLowerThreshold(float& f);
    
    void createRandomAttractor();
    void clearAttractors();
    void createRandomRepulsor();
    void clearRepulsors();
    void wrapAround(Agent &agent);
    
    void toggleDrawNeighbourhood(bool& value);
    void toggleDrawBoundingBox(bool& value);
    void toggleAutoAttractor(bool& value);
    void toggleCenterPull(bool& value);
    void toggleSpaceWrap(bool& value);
    
    string getAllPositions();

    glm::vec2 mWorldDimensions;
    
    shared_ptr<GuiApp> gui;

    vector<Agent> flock;
    vector<glm::vec2> mAllPositions;
    
    SwarmStats mSwarmStats;

    vector<glm::vec2> attractors;
    vector<unsigned int> attractorTimers;
    vector<glm::vec2> repulsors;
    vector<unsigned int> repulsorTimers;
    
    bool bDrawNeighbourhood,bDrawBoundingBox,bEnableWrapAround,bEnableCenterPull;
    
    ofxSharedMemory<glm::vec2*> mSharedPositionData;

};

#endif /* AgentController_hpp */
