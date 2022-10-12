#pragma once

#include "ofMain.h"
#include "Agent.hpp"
#include "AgentController.hpp"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxSparkline.h"
#include "GuiApp.hpp"


class ofApp : public ofBaseApp{
    

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);

        shared_ptr<GuiApp> guiWindow;
        ofEasyCam mCam;
    
        AgentController *mAgentController;

        ofFile mDataFile;
    
        bool bWriteData;
        bool bSendStats;
        bool bEnableSimulation;
        bool bDrawAttractors;
        bool bDrawSparkLines;

        ofxOscReceiver mOscReceiver;
        ofxOscSender mOscSender;
    
        //draw PCA data in these sparkLines
        vector<ofxSparkline> sparkLines;
};
