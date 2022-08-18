#pragma once

#include "ofMain.h"
#include "Agent.hpp"
#include "AgentController.hpp"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "OctaveNoise.h"
#include "ofxSparkline.h"
#include "Scaler.hpp"

#define PORT 12345

class ofApp : public ofBaseApp{
    

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void renderCurl(ofFbo &fbo, ofFloatImage &data, ofFloatImage &draw);
        void imgMinMax(ofFloatImage &img);
        void setupNoise();
        void updateNoise();
        void genCurl();
    
        ofParameter<int> mNumOctaves{ "Number of Octaves", 1, 1, 8 };
        ofParameter<float> mNoiseAlpha{ "Noise Alpha", 2.0f, 0.1f, 8.0f };
        ofParameter<float> mNoiseBeta{ "Noise Beta", 2.0f, 0.1f, 8.0f };
        ofParameter<bool> mNoiseSigned{ "Noise Signed", false, true, false};

        ofEasyCam mCam;
        AgentController *mAgentController;
        ofxPanel gui;
        ofxButton bAddRandomAttractor;
        ofxButton bAddRandomRepulsor;
    

        ofFile mDataFile;
        bool mWriteData;
        bool mSendPositions;
        bool mSendStats;
        
        bool mEnableSimulation;
        bool bNoiseDirty;
        bool bDrawGui;
        bool bDrawAttractors;

        ofxOscReceiver receiver;
        ofxOscSender mOscSender;
    
        //draw PCA data in these sparkLines
        vector<ofxSparkline> sparkLines;
        vector<Scaler> scalers;
    
//    //Curl stuff
//    
//    ofFbo curlTargetXY, curlTargetXZ, curlTargetYZ;
//    ofFloatImage noiseImageXY, noiseImageXZ, noiseImageYZ;
//    ofFloatImage curlDrawXY, curlDrawXZ, curlDrawYZ;
//    OctaveNoise noiseGen;
//    ofShader curl;
//    ofShader advectShader;
//    
    

};
