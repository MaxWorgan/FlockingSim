//
//  agent.cpp
//  Flocking
//
//  Created by Max Worgan on 17/09/2021.
//

#include "Agent.hpp"


Agent::Agent(glm::vec2 position) {
    
    mPosition = position;
    
    mVelocity.x = ofRandomuf();
    mVelocity.y = ofRandomuf();
    
    mAcceleration.x = 0;
    mAcceleration.y = 0;
    
    mMass = ofRandom(2.0,3.5);
    mMaxSpeed = 5.0f + ofRandom(2.0f);
    
}

void Agent::applyForce(const glm::vec2 force){
    mAcceleration += force / mMass;
}

void Agent::updatePosition(){
    mVelocity += mAcceleration;
    if(glm::length(mVelocity) > mMaxSpeed) {
        mVelocity = glm::normalize(mVelocity) * mMaxSpeed;
    }
    mPosition += mVelocity;
    mAcceleration *= 0.0f;

}
void Agent::setMaxSpeed(float ms){
  mMaxSpeed = ms + ofRandom(ms*0.25);
}

void Agent::draw(){
    ofDrawCircle(mPosition,mMass);
}


void Agent::setPosition(const glm::vec2 pos){
    mPosition = pos;
}
