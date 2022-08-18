//
//  Scaler.cpp
//  Flocking
//
//  Created by Max Worgan on 08/08/2022.
//

#include "Scaler.hpp"
#include "ofMain.h"


Scaler::Scaler(float _min, float _max){
    min = _min;
    max = _max;
}

float Scaler::scale(const float input) {
    if(input < min){
        ofLog() << "Min was " << min << endl;
        ofLog() << "Min mow " << input << endl;
        min = input;
    }
    else if (input > max){
        ofLog() << "Max was " << max << endl;
        ofLog() << "Max mow " << input << endl;
        max = input;
    }
    ofMap(input, min, max, 0.0, 1.0);
}
