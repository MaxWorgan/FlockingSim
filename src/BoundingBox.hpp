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
    void update(const glm::vec2 pos);
    void reset();

    glm::vec2 mMins;
    glm::vec2 mMaxs;

    float boxWidth();
    float boxHeight();
    
    glm::vec2 getCenter();
    
};

#endif /* BoundingBox_hpp */
