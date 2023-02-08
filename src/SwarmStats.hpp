//
//  SwarmStats.hpp
//  Flocking
//
//  Created by Max Worgan on 12/04/2022.
//

#ifndef SwarmStats_hpp
#define SwarmStats_hpp

#include <stdio.h>
#include <ofMain.h>
#include "Agent.hpp"
#include "BoundingBox.hpp"


// Unused
class SwarmStats {

public:
    void tick(vector<Agent> &flock);
    void reset();
    
    float mRatio, mRatioDT;
    glm::vec2 mAvgVelocity, mAvgVelocityDT;
    glm::vec2 mCenterOfMass;
    float mBoundingBoxArea;
    float mEntropy;
    int counter = 0;
    BoundingBox mBoundingBox;
    
};


#endif /* SwarmStats_hpp */
