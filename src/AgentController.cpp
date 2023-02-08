//
//  AgentController.cpp
//  Flocking
//
//  Created by Max Worgan on 18/09/2021.
//

#include "AgentController.hpp"
#include "range.hpp"
#include <glm/gtc/random.hpp>

using util::lang::indices;

AgentController::AgentController(size_t numAgents,shared_ptr<GuiApp> guiWindow){
    for(size_t i = 0; i < numAgents; ++i){
        flock.push_back(Agent(glm::vec2(ofRandomWidth() - (ofGetWidth() * 0.5),ofRandomHeight() - (ofGetHeight() * 0.5))));
        mAllPositions.push_back(flock[i].mPosition);
    }
    int size = (int) mAllPositions.size() * sizeof(glm::vec2);
    mSharedPositionData.setup(size);
    bool isConnected = mSharedPositionData.connect();
    ofLog() << "Memory was mapped? " << isConnected;
    ofLog() << "&mAllPositions[0] " << &mAllPositions[0];
    ofLog() << "Size: " << size;
    gui = guiWindow;
    
    //GUI stuff
    gui->bAddRandomAttractor.addListener(this, &AgentController::createRandomAttractor);
    
    gui->bClearAttractors.addListener(this, &AgentController::clearAttractors);
    
    gui->bAddRandomRepulsor.addListener(this, &AgentController::createRandomRepulsor);

    
    gui->bClearRepulsors.addListener(this, &AgentController::clearRepulsors);
    
    gui->bDrawNeighbourhoodDistance.addListener(this, &AgentController::toggleDrawNeighbourhood);
    bDrawNeighbourhood = gui->bDrawNeighbourhoodDistance;
    
    gui->bDrawBoundingBox.addListener(this, &AgentController::toggleDrawBoundingBox);
    
    gui->mLowerThreshold.addListener(this, &AgentController::setLowerThreshold);
    gui->mHigherThreshold.addListener(this, &AgentController::setHigherThreshold);
    

}


void AgentController::applyFlocking() {
    auto neighbourhoodDistanceSq = gui->mNeighbourhoodDistance * gui->mNeighbourhoodDistance;
    
    for(auto it1 = std::begin(flock); it1 != std::end(flock); ++it1) {
        for(auto it2 = std::next(it1); it2 != std::end(flock); ++it2) {
            auto dir = it1->mPosition - it2->mPosition;
            float distSq = glm::length2(dir);

            if(distSq <= neighbourhoodDistanceSq){ //We're in the neighbourhood of it1
                float percent = distSq / neighbourhoodDistanceSq; // what percentage into our neighbourhood zone are we?
                if(percent < gui->mLowerThreshold){ //SEPERATE
                    float F = (gui->mLowerThreshold/percent - 1.0f) * gui->mSeperateStrength;
                    dir = glm::normalize(dir) * F;
                    it1->applyForce(dir);
                    it2->applyForce(dir * -1.0f);
                } else if (percent < gui->mHigherThreshold) { //ALIGNMENT
                    float thresholdDelta = gui->mHigherThreshold - gui->mLowerThreshold;
                    float adjustedPercent = (percent - gui->mLowerThreshold) / thresholdDelta;
                    float F = (1.0f - (cos(adjustedPercent * TWO_PI) * 0.5f + 0.5f)) * gui->mAlignStrength;
                    it1->applyForce(glm::normalize(it2->mVelocity) * F);
                    it2->applyForce(glm::normalize(it1->mVelocity) * F);
                } else { // COHESION
                    float thresholdDelta = 1.0f - gui->mHigherThreshold;
                    float adjustedPercent = (percent - gui->mHigherThreshold) / thresholdDelta;
                    float F = (1.0f - (cos(adjustedPercent * TWO_PI) * -0.5f + 0.5f)) * gui->mCohesionStrength;
                    dir = glm::normalize(dir);
                    it1->applyForce(dir * F * -1.0f);
                    it2->applyForce(dir * F);
                }
            }
        }
    }
}
void AgentController::createRandomRepulsor(){
    repulsors.push_back(glm::ballRand(1000.0f));
    repulsorTimers.push_back(ofGetUnixTime() + 10);
}

void AgentController::createRandomAttractor(){
    attractors.push_back(glm::ballRand(1000.0f));
    attractorTimers.push_back(ofGetUnixTime() + 10);
}
void AgentController::clearAttractors(){
    attractors.clear();
}
void AgentController::clearRepulsors(){
    repulsors.clear();
}

void AgentController::toggleDrawNeighbourhood(bool& b){
    bDrawNeighbourhood = b;
}

void AgentController::toggleDrawBoundingBox(bool& b){
    bDrawBoundingBox = b;
}

void AgentController::attract(Agent &agent, const glm::vec2 &pos, const float strength, const float minDistance){
    glm::vec2 direction = pos - agent.mPosition;
    float distance = glm::length(direction);
    if(distance > minDistance){
        agent.applyForce(glm::normalize(direction) * (1/distance) * strength);
    }
}

void AgentController::applyCenterPull(Agent &agent,const glm::vec2 &center) {
    glm::vec2 direction = center - agent.mPosition;
    float distance = glm::length(direction);
    if(distance > gui->mMaxCenterDistanceSq){
        agent.applyForce(glm::normalize(direction) * (distance - gui->mMaxCenterDistanceSq) * gui->mCenterPullStrength.get());
    }
}

void AgentController::applyWind(Agent &agent, const float windAmount){
    float x = ofSignedNoise(agent.mPosition.x*gui->mWindMult);
    float y = ofSignedNoise(agent.mPosition.y*gui->mWindMult);
    agent.applyForce(glm::vec2(x,y) * windAmount);
    
}

void AgentController::applyForces(){
    for(Agent &agent: flock){
        //attractors
        for(auto attractor: attractors) attract(agent, attractor, gui->mAttractorStrength, gui->mAttractorMinDistance);
        //repulsors
        for(auto repulsor: repulsors) attract(agent, repulsor, -gui->mRepulsorStrength, gui->mRepulsorMinDistance);
        //wind
        applyWind(agent, gui->mWindAmount);
        //centerpull
        applyCenterPull(agent, glm::vec2(0,0));
    }
    if(attractorTimers.size() > 0){
      if(attractorTimers.front() <= ofGetUnixTime()){
        attractors.erase(attractors.begin());
        attractorTimers.erase(attractorTimers.begin());
      }
    }
    if(repulsorTimers.size() > 0){
      if(repulsorTimers.front() <= ofGetUnixTime()){
        repulsors.erase(repulsors.begin());
        repulsorTimers.erase(repulsorTimers.begin());
      }
    }

}

void AgentController::updateAgents(){
    for( auto i: indices(flock)){
        flock[i].updatePosition();
        mAllPositions[i] = flock[i].mPosition;
    }
    mSwarmStats.tick(flock);
    mSharedPositionData.setData(&mAllPositions[0]);
}

void AgentController::updateAgent(int index, float x, float y){
    flock.at(index).setPosition(glm::vec2(x,y));
}

void AgentController::draw(bool drawAttractors) {

    if(drawAttractors) {
        ofPushStyle();
        ofSetColor(ofColor::white);
        for(auto &a : attractors) {
            ofDrawCircle(a,15);
        }
        ofSetColor(ofColor::indianRed);
        for(auto &a : repulsors) {
            ofDrawCircle(a,15);
        }
        ofPopStyle();
    }
    if(gui->bDrawNeighbourhoodDistance){
        for(auto &a : flock){
            float s = gui->mNeighbourhoodDistance;
            float s1 =  s * gui->mLowerThreshold;
            float s2 =  s * gui->mHigherThreshold;
            float s3 =  s;
            ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            //draw cohesion sphere
            ofSetColor(ofColor::lightBlue,gui->mCohesionStrength * 100.0f);
            ofDrawCircle(a.mPosition,s3);
            //draw allignment sphere
            ofSetColor(ofColor::lightYellow,gui->mAlignStrength * 100.0f);
            ofDrawCircle(a.mPosition,s2);
            //draw seperate sphere
            ofSetColor(ofColor::paleVioletRed,gui->mSeperateStrength * 100.0f);
            ofDrawCircle(a.mPosition,s1);
            ofPopStyle();
            a.draw();
        }
    } else {
        for(auto &a : flock) a.draw();
    }
    if(gui->bDrawBoundingBox){
        mSwarmStats.mBoundingBox.draw();
    }

}

string AgentController::getAllPositions(){
    string output = "";
    bool first = true;
    for(auto a : flock){
        if(first) { first = false; } else { output += ", "; }
        output += ofToString(a.mPosition);
    }
    return output;
}


void AgentController::setHigherThreshold(float& f){
    if(f < gui->mLowerThreshold){
        gui->mLowerThreshold = f;
    }
}

void AgentController::setLowerThreshold(float& f){
    if(f > gui->mHigherThreshold){
        gui->mHigherThreshold = f;
    }
}
