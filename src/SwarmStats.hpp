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

class SwarmStats {
    float mRatio, mRatioDT;
    glm::vec3 mAvgVelocity, mAvgVelocityDT;
    glm::vec3 mCenterOfMass;
    float mBoundingBoxArea;
    float mEntropy;
    int counter = 0;
    BoundingBox mBoundingBox;
    
public:
    void tick(vector<Agent> &flock);
    void reset();
    
};


#endif /* SwarmStats_hpp */
