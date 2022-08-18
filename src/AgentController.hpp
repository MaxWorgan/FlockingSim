//
//  AgentController.hpp
//  Flocking
//
//  Created by Max Worgan on 18/09/2021.
//

#ifndef AgentController_hpp
#define AgentController_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Agent.hpp"
#include "ofxSharedMemory.hpp"
#include "BoundingBox.hpp"
#include "SwarmStats.hpp"
#include "ofxGui.h"

class AgentController {
    
public:
    AgentController(size_t numAgents);
    void applyFlocking();
    void attract(Agent &agent, const glm::vec3 &pos, const float strength, const float minDistance);
    void applyWind(Agent &agent, const float windAmount);
    void applyCenterPull(Agent &agent, const glm::vec3 &center);
    void applyForces();
    void updateAgents();
    void updateAgent(int index, float x, float y, float z);
    void createRandomAttractor();
    void clearAttractors();
    void createRandomRepulsor();
    void clearRepulsors();
    void draw(bool drawAttractors);
    string getAllPositions();

    //GUI
    ofParameter<float> mSeperateStrength{ "Seperation Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mAlignStrength{ "Align Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mCohesionStrength{ "Cohesion Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mCenterPullStrength{"Center Pull Strength", 0.001f,0.0f,0.01f};
    ofParameter<float> mMaxCenterDistanceSq{"Center Size", 100.f,10.f,100000.f};
    ofParameter<float> mNeighbourhoodDistance{"Neighbourhood distance", 100.0f, 10.f, 500.0f };
    ofParameter<float> mLowerThreshold{"Lower Threshold", 0.4, 0.0, 1.0};
    ofParameter<float> mHigherThreshold{"Higher Threshold", 0.76, 0 , 1.0 };
    ofParameter<float> mAttractorStrength{"Attractor Strength", 10.f, 0.f, 100.f};
    ofParameter<float> mAttractorMinDistance{"Attractor Min Distance", 10.f, 0.f, 100.f};
    ofParameter<float> mRepulsorStrength{"Repulsor Strength", 10.f, 0.f, 100.f};
    ofParameter<float> mRepulsorMinDistance{"Repulsor Min Distance", 10.f, 0.f, 100.f};
    ofParameter<float> mWindAmount{"Wind Amount", 0.0f, 0.0f, 10.0f};
    ofParameter<float> mWindMult{"Wind Mult", 0.001f, 0.0f, 0.01f};
    
    ofxButton bAddRandomAttractor;
    ofxButton bClearAttractors;
    ofxButton bAddRandomRepulsor;
    ofxButton bClearRepulsors;

    ofParameterGroup centerPullParams{"Center Pull",
        mCenterPullStrength,
        mMaxCenterDistanceSq,
    };
    
    ofParameterGroup repulsorParams{"Repulsors",
        mRepulsorStrength,
        mRepulsorMinDistance,
        bAddRandomRepulsor.getParameter(),
        bClearRepulsors.getParameter()
    };
    
    ofParameterGroup attractorParams{"Attractors",
        mAttractorStrength,
        mAttractorMinDistance,
        bAddRandomAttractor.getParameter(),
        bClearAttractors.getParameter(),
    };
    
    ofParameterGroup flockingParams{ "Flocking Parameters",
        mSeperateStrength,
        mAlignStrength,
        mCohesionStrength,
        mNeighbourhoodDistance
    };
    
    ofParameterGroup windParams{ "Wind Parameters",
        mWindAmount,
        mWindMult
    };
    
    vector<Agent> flock;
    vector<glm::vec3> mAllPositions;
    BoundingBox mBoundingBox;
    SwarmStats mSwarmStats;
    
    
    vector<glm::vec3> attractors;
    vector<glm::vec3> repulsors;
    
    float mRatio, mPrevRatio, mRatioDT;
    float mBBArea, mPrevBBArea, mBBAreaDT;
    glm::vec3 mDirection, mPrevDirection;
    float mDirectionDT;


    ofxSharedMemory<glm::vec3*> mSharedPositionData;
    


};

#endif /* AgentController_hpp */
