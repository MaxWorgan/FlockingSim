//
//  Scaler.hpp
//  Flocking
//
//  Created by Max Worgan on 08/08/2022.
//

#ifndef Scaler_hpp
#define Scaler_hpp

#include <stdio.h>

class Scaler {
    void load();

public:
    float min;
    float max;
    Scaler(float min, float max);
    float scale(const float input);
};

#endif /* Scaler_hpp */
