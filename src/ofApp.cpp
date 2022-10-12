#include "ofApp.h"

#define OSC_TARGET_HOST "127.0.0.1"
#define OSC_TARGET_PORT 7779
#define OSC_RECEIVE_PORT 12345
#define SETTINGS_FILE "settings.xml"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    mCam.setNearClip(0.1);
    mCam.setFarClip(200000);
    mCam.setDistance(1200);
    
    mAgentController = new AgentController(300,guiWindow);


    bWriteData        = false;
    bEnableSimulation = true;
    bSendStats        = false;
    bDrawAttractors   = true;
    bDrawSparkLines   = true;
    
    mOscReceiver.setup(OSC_RECEIVE_PORT);
    mOscSender.setup(OSC_TARGET_HOST, OSC_TARGET_PORT);


    ofxSparkline::Settings settings = ofxSparkline::Settings();
    settings.width = ofGetWidth();
    settings.height = 50;
    settings.annotations.label.precision = 5;

    for(auto i = 0; i < 10; ++i){
        settings.styles.curve.line.color = ofColor(255,0,i*25);
        sparkLines.push_back(ofxSparkline(settings,ofGetWidth()));
    }
}

void ofApp::update(){
    
    if(bEnableSimulation){
        mAgentController->applyFlocking();
        mAgentController->applyForces();
        mAgentController->updateAgents();
    }
    while(mOscReceiver.hasWaitingMessages()){
        ofxOscMessage m;
        mOscReceiver.getNextMessage(m);
        if(m.getAddress() == "/flock/event"){
            mAgentController->createRandomAttractor();
            mAgentController->createRandomRepulsor();
        } else if(m.getAddress() == "/flock/position"){
            int index = m.getArgAsInt(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float z = m.getArgAsFloat(3);
            mAgentController->updateAgent(index,x,y,z);
        } else if(m.getAddress() == "/flock/pca"){
            if(m.getNumArgs() != 10) {
                ofLog() << "Invalid pca data recieved - expected 10 elements" << endl;
            } else {
                sparkLines[0].push_back(ofMap(m.getArgAsFloat(0),-0.061, 1.0,0.0,1.0));
                sparkLines[1].push_back(ofMap(m.getArgAsFloat(1),1.51,3.0,0.0,1.0));
                sparkLines[2].push_back(ofMap(m.getArgAsFloat(2),0.6,6.0,0.0,1.0));
                sparkLines[3].push_back(ofMap(m.getArgAsFloat(3),-0.45, 0.74,0.0,1.0));
                sparkLines[4].push_back(ofMap(m.getArgAsFloat(4),0.24,1.63,0.0,1.0));
                sparkLines[5].push_back(ofMap(m.getArgAsFloat(5),-0.66,0.087,0.0,1.0));
                sparkLines[6].push_back(ofMap(m.getArgAsFloat(6),0.13,1.91,0.0,1.0));
                sparkLines[7].push_back(ofMap(m.getArgAsFloat(7),-0.13,0.28,0.0,1.0));
                sparkLines[8].push_back(ofMap(m.getArgAsFloat(8),0.141,0.468,0.0,1.0));
                sparkLines[9].push_back(ofMap(m.getArgAsFloat(9),-0.56,-0.125,0.0,1.0));
            }
            
            
        }
    }
    if(bWriteData){
        if(!mDataFile.is_open()) mDataFile.open("data.csv",ofFile::WriteOnly);
        mDataFile << mAgentController->getAllPositions() << "\n";
    }
    //Used for now
    if(bSendStats) {
        ofxOscMessage m;
        m.setAddress("/flock/stats");
        m.addFloatArg(mAgentController->mBBArea);
        m.addFloatArg(mAgentController->mBBAreaDT);
        m.addFloatArg(mAgentController->mRatio);
        m.addFloatArg(mAgentController->mRatioDT);
        m.addFloatArg(mAgentController->mDirectionDT);
        mOscSender.sendMessage(m, false);
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(bDrawSparkLines){
      for(size_t i = 0; i < sparkLines.size(); ++i) {
        sparkLines[i].draw(0,(ofGetHeight()-500) + i*50);
      }
    }
    mCam.begin();
    mAgentController->draw(bDrawAttractors);
    mCam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'w'){
        bWriteData = !bWriteData;
        if(bWriteData) ofLog() << "Writing Data...";
        else ofLog() << "Finished Writing Data";
    } else if(key == 's'){
      bDrawSparkLines = !bDrawSparkLines;
    } else if(key == 'b'){
        bSendStats = !bSendStats;
    } else if(key == 'a') {
        bDrawAttractors = !bDrawAttractors;
    } else if(key == 'f') {
        static bool f = true;
        ofSetFullscreen(f);
        f = !f;
    }
        
}

void ofApp::exit(){
    mAgentController->mSharedPositionData.close();
}
