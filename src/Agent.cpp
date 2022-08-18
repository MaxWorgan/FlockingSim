//
//  agent.cpp
//  Flocking
//
//  Created by Max Worgan on 17/09/2021.
//

#include "Agent.hpp"


Agent::Agent(glm::vec3 position) {
    
    mPosition = position;
    
    mVelocity.x = ofRandomuf();
    mVelocity.y = ofRandomuf();
    mVelocity.z = ofRandomuf();
    
    mAcceleration.x = 0;
    mAcceleration.y = 0;
    mAcceleration.z = 0;
    
    mMass = ofRandom(2.0,3.5);
    mMaxSpeed = 2.0f + ofRandom(2.0f);
    
}

void Agent::applyForce(const glm::vec3 force){
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

void Agent::draw(){
    ofDrawSphere(mPosition,mMass);
}


void Agent::setPosition(const glm::vec3 pos){
    mPosition = pos;
}
