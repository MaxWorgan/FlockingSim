//
//  GuiApp.hpp
//  Flocking
//
//  Created by Max Worgan on 12/10/2022.
//

#ifndef GuiApp_hpp
#define GuiApp_hpp

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp: public ofBaseApp {
public:
    void setup();
    void draw();
    
    ofxPanel gui;


    ofParameter<float> mSeperateStrength{ "Seperation Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mAlignStrength{ "Align Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mCohesionStrength{ "Cohesion Strength", 0.001f, 0.00001f, 0.1f };
    ofParameter<float> mCenterPullStrength{"Center Pull Strength", 0.001f,0.0f,0.01f};
    ofParameter<float> mMaxCenterDistanceSq{"Center Size", 100.f,10.f,10000.f};
    ofParameter<float> mNeighbourhoodDistance{"Neighbourhood distance", 100.0f, 10.f, 500.0f };
    ofParameter<float> mLowerThreshold{"Lower Threshold", 0.4, 0.0, 1.0};
    ofParameter<float> mHigherThreshold{"Higher Threshold", 0.76, 0 , 1.0 };
    ofParameter<float> mAttractorStrength{"Attractor Strength", 10.f, 0.f, 1000.f};
    ofParameter<float> mAttractorMinDistance{"Attractor Min Distance", 10.f, 0.f, 1000.f};
    ofParameter<float> mRepulsorStrength{"Repulsor Strength", 10.f, 0.f, 1000.f};
    ofParameter<float> mRepulsorMinDistance{"Repulsor Min Distance", 10.f, 0.f, 1000.f};
    ofParameter<float> mWindAmount{"Wind Amount", 0.0f, 0.0f, 1.0f};
    ofParameter<float> mWindMult{"Wind Mult", 0.001f, 0.0f, 0.001f};
    
    ofParameter<int> mCameraDistance{"Distance", 1000, -5000, 5000};
    ofParameter<int> mCameraFov{"FOV", 60, 5, 360};
    
    ofxButton bAddRandomAttractor;
    ofxButton bClearAttractors;
    ofxButton bAddRandomRepulsor;
    ofxButton bClearRepulsors;
    
    ofParameter<bool> bDrawNeighbourhoodDistance;
    ofParameter<bool> bDrawBoundingBox;
    ofParameter<bool> bFollowCamera;
    ofParameter<bool> bCameraOrtho;
    
    
    
    ofParameterGroup cameraParams{"Camera Controls",
        bFollowCamera,
        mCameraDistance,
        mCameraFov,
        bCameraOrtho
    };

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
        bClearAttractors.getParameter()
    };
    
    ofParameterGroup flockingParams{ "Flocking Parameters",
        mLowerThreshold,
        mHigherThreshold,
        mSeperateStrength,
        mAlignStrength,
        mCohesionStrength,
        mNeighbourhoodDistance,
        bDrawNeighbourhoodDistance,
        bDrawBoundingBox
    };
    
    ofParameterGroup windParams{ "Wind Parameters",
        mWindAmount,
        mWindMult
    };
};

#endif /* GuiApp_hpp */
