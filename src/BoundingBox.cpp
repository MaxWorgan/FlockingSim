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
    mMaxs.x = -MAXFLOAT;
    mMaxs.y = -MAXFLOAT;
}

void BoundingBox::update(const glm::vec2 pos) {
    
    if(pos.x < mMins.x) mMins.x = pos.x;
    else if(pos.x > mMaxs.x) mMaxs.x = pos.x;
    
    if(pos.y < mMins.y) mMins.y = pos.y;
    else if(pos.y > mMaxs.y) mMaxs.y = pos.y;

}
float BoundingBox::boxWidth()  { return mMaxs.x - mMins.x; }
float BoundingBox::boxHeight() { return mMaxs.y - mMins.y; }

glm::vec2 BoundingBox::getCenter() {
    return glm::vec2(mMins.x, mMins.y);
}

void BoundingBox::draw() {
    
    ofEnableDepthTest();
    ofNoFill();
    ofPushMatrix();
    ofTranslate(getCenter());
    ofDrawRectangle(0,0,boxWidth(), boxHeight());
    ofPopMatrix();
    ofFill();
    ofDisableDepthTest();
}
