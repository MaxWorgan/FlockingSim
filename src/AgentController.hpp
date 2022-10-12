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
    void applyFlocking();
    void attract(Agent &agent, const glm::vec3 &pos, const float strength, const float minDistance);
    void applyWind(Agent &agent, const float windAmount);
    void applyCenterPull(Agent &agent, const glm::vec3 &center);
    void applyForces();
    void updateAgents();
    void updateAgent(int index, float x, float y, float z);
    void createRandomAttractor();
    void clearAttractors();
    void createRandomRepulsor();
    void clearRepulsors();
    void draw(bool drawAttractors);
    string getAllPositions();
    
    shared_ptr<GuiApp> gui;

    vector<Agent> flock;
    vector<glm::vec3> mAllPositions;
    
    SwarmStats mSwarmStats;
    
    
    vector<glm::vec3> attractors;
    vector<unsigned int> attractorTimers;
    vector<glm::vec3> repulsors;
    vector<unsigned int> repulsorTimers;
    
    float mRatio, mPrevRatio, mRatioDT;
    float mBBArea, mPrevBBArea, mBBAreaDT;
    glm::vec3 mDirection, mPrevDirection;
    float mDirectionDT;


    ofxSharedMemory<glm::vec3*> mSharedPositionData;
    


};

#endif /* AgentController_hpp */
