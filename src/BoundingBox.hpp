//
//  BoundingBox.hpp
//  Flocking
//
//  Created by Max Worgan on 11/04/2022.
//

#ifndef BoundingBox_hpp
#define BoundingBox_hpp

#include <stdio.h>
#include <ofMain.h>

class BoundingBox{

public:
    void draw();
    void update(const glm::vec3 pos);
    void reset();

    glm::vec3 mMins;
    glm::vec3 mMaxs;

    float boxWidth();
    float boxHeight();
    float boxDepth();
    
    glm::vec3 getCenter();
    
};

#endif /* BoundingBox_hpp */
