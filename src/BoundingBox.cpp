//
//  BoundingBox.cpp
//  Flocking
//
//  Created by Max Worgan on 11/04/2022.
//

#include "BoundingBox.hpp"

void BoundingBox::reset() {
    mMins.x = 1000;
    mMins.y = 1000;
    mMins.z = 1000;
    mMaxs.x = -1000;
    mMaxs.y = -1000;
    mMaxs.z = -1000;
}

void BoundingBox::update(const glm::vec3 pos) {
    
    if(pos.x < mMins.x) mMins.x = pos.x;
    else if(pos.x > mMaxs.x) mMaxs.x = pos.x;
    
    if(pos.y < mMins.y) mMins.y = pos.y;
    else if(pos.y > mMaxs.y) mMaxs.y = pos.y;
    
    if(pos.z < mMins.z) mMins.z = pos.z;
    else if(pos.z > mMaxs.z) mMaxs.z = pos.z;

}

glm::vec3 BoundingBox::getCenter() {
    return mMaxs - mMins;
}

void BoundingBox::draw() {
    
    ofEnableDepthTest();
    ofNoFill();
    ofPushMatrix();
    ofTranslate(glm::vec3(width()/2.0f, height()/2.0f,depth()/2.0f));
    ofDrawBox(mMins.x,mMins.y,mMins.z,width(), height(), depth());
    ofPopMatrix();
    ofFill();
    ofDisableDepthTest();
}
