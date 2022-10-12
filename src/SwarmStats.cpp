//
//  SwarmStats.cpp
//  Flocking
//
//  Created by Max Worgan on 12/04/2022.
//

#include "SwarmStats.hpp"


void SwarmStats::tick(vector<Agent> &flock) {
    for( auto f : flock){
        mBoundingBox.update(f.mPosition);
    }
    
    counter++;
}

template <typename T> static float ShannonEntropy(T data[],int elements){
    float entropy=0;
    std::map<T,long> counts;
    typename std::map<T,long>::iterator it;
    //
    for (int dataIndex = 0; dataIndex < elements; ++dataIndex) {
        counts[data[dataIndex]]++;
    }
    //
    it = counts.begin();
    while(it != counts.end()){
        float p_x = (float)it->second/elements;
        if (p_x>0) entropy-=p_x*log(p_x)/log(2);
        it++;
    }
    return entropy;
}

void SwarmStats::reset(){
    counter = 0;
}

