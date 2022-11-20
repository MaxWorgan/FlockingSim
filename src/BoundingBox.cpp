//
//  BoundingBox.cpp
//  Flocking
//
//  Created by Max Worgan on 11/04/2022.
//

#include "BoundingBox.hpp"

void BoundingBox::reset() {
    mMins.x = MAXFLOAT;
    mMins.y = MAXFLOAT;
    mMins.z = MAXFLOAT;
    mMaxs.x = -MAXFLOAT;
    mMaxs.y = -MAXFLOAT;
    mMaxs.z = -MAXFLOAT;
}

void BoundingBox::update(const glm::vec3 pos) {
    
    if(pos.x < mMins.x) mMins.x = pos.x;
    else if(pos.x > mMaxs.x) mMaxs.x = pos.x;
    
    if(pos.y < mMins.y) mMins.y = pos.y;
    else if(pos.y > mMaxs.y) mMaxs.y = pos.y;
    
    if(pos.z < mMins.z) mMins.z = pos.z;
    else if(pos.z > mMaxs.z) mMaxs.z = pos.z;

}
float BoundingBox::boxWidth()  { return mMaxs.x - mMins.x; }
float BoundingBox::boxHeight() { return mMaxs.y - mMins.y; }
float BoundingBox::boxDepth()  { return mMaxs.z - mMins.z; }

glm::vec3 BoundingBox::getCenter() {
    return glm::vec3(mMins.x + boxWidth()/2.0f,
                     mMins.y + boxHeight()/2.0f,
                     mMins.z + boxDepth()/2.0f);
}

void BoundingBox::draw() {
    
    ofEnableDepthTest();
    ofNoFill();
    ofPushMatrix();
    ofTranslate(getCenter());
    ofDrawBox(boxWidth(), boxHeight(), boxDepth());
    ofPopMatrix();
    ofFill();
    ofDisableDepthTest();
}
