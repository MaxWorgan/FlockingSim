//
//  agent.hpp
//  Flocking
//
//  Created by Max Worgan on 17/09/2021.
//

#ifndef agent_hpp
#define agent_hpp

#include <stdio.h>
#include "ofMain.h"

class Agent{
    

public:
    Agent(glm::vec2 position);
    
    void applyForce(glm::vec2 force);
    void updatePosition();
    void setPosition(glm::vec2 pos);
    void draw();
    void setMaxSpeed(float ms);
    
    glm::vec2 mPosition;
    glm::vec2 mVelocity;
    glm::vec2 mAcceleration;
    
    float mMass;
    float mMaxSpeed;

};

#endif /* agent_hpp */
