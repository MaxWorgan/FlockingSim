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
    Agent(glm::vec3 position);
    
    void applyForce(glm::vec3 force);
    void updatePosition();
    void setPosition(glm::vec3 pos);
    void draw();
    
    glm::vec3 mPosition;
    glm::vec3 mVelocity;
    glm::vec3 mAcceleration;
    
    float mMass;
    float mMaxSpeed;

};

#endif /* agent_hpp */
