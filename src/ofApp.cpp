#include "ofApp.h"
#define OSC_TARGET_HOST "127.0.0.1"
#define OSC_TARGET_PORT 7779
#define SETTINGS_FILE "settings.xml"
#define gradScale 0.5

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetBackgroundColor(0);
    ofSetDataPathRoot("…/Resources/data/");
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    mCam.setNearClip(0.1);
    mCam.setFarClip(200000);
    mCam.setDistance(500);
    mAgentController = new AgentController(300);
    gui.setup();

    gui.add(mAgentController->flockingParams);
    gui.add(mAgentController->centerPullParams);
    gui.add(mAgentController->attractorParams);
    gui.add(mAgentController->repulsorParams);
    gui.add(mAgentController->windParams);

    mDataFile.open("data.csv",ofFile::WriteOnly);
    mWriteData = false;
    mEnableSimulation = true;
    
    receiver.setup(PORT);
    
    mOscSender.setup(OSC_TARGET_HOST, OSC_TARGET_PORT);

    mSendPositions = false;
    mSendStats = false;
    bDrawGui = true;
    bDrawAttractors = true;

    gui.loadFromFile(SETTINGS_FILE);
    
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
       
    if(mEnableSimulation){
        mAgentController->applyFlocking();
        mAgentController->applyForces();
        mAgentController->updateAgents();
    }
        while(receiver.hasWaitingMessages()){
            ofxOscMessage m;
            receiver.getNextMessage(m);
            if(m.getAddress() == "/flock/position"){
                int index = m.getArgAsInt(0);
                float x = m.getArgAsFloat(1);
                float y = m.getArgAsFloat(2);
                float z = m.getArgAsFloat(3);
                mAgentController->updateAgent(index,x,y,z);
            }
            if(m.getAddress() == "/flock/pca"){
                if(m.getNumArgs() != 10) {
                    ofLog() << "Invalid pca data recieved - expected 10 elements" << endl;
                } else {
                    sparkLines[0].push_back(ofMap(m.getArgAsFloat(0),-0.15, 0.6,0.0,1.0));
                    sparkLines[1].push_back(ofMap(m.getArgAsFloat(1),-3.3784764,-2.42,0.0,1.0));
                    sparkLines[2].push_back(ofMap(m.getArgAsFloat(2),-0.035293266,1.7924565,0.0,1.0));
                    sparkLines[3].push_back(ofMap(m.getArgAsFloat(3),-0.45, 0.41,0.0,1.0));
                    sparkLines[4].push_back(ofMap(m.getArgAsFloat(4),-0.57,0.6638429,0.0,1.0));
                    sparkLines[5].push_back(ofMap(m.getArgAsFloat(5),0.24,0.74080515,0.0,1.0));
                    sparkLines[6].push_back(ofMap(m.getArgAsFloat(6),-0.28176856,0.12020865,0.0,1.0));
                    sparkLines[7].push_back(ofMap(m.getArgAsFloat(7),-0.0076161358,0.134,0.0,1.0));
                    sparkLines[8].push_back(ofMap(m.getArgAsFloat(8),-0.0275,0.11274521,0.0,1.0));
                    sparkLines[9].push_back(ofMap(m.getArgAsFloat(9),-0.2963,-0.15,0.0,1.0));
                }
                
                
            }
        }
//    }
    if(mWriteData){
        mDataFile << mAgentController->getAllPositions() << "\n";
    }
    if(mSendStats) {
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
    for(size_t i = 0; i < sparkLines.size(); ++i) {
        sparkLines[i].draw(0,(ofGetHeight()-500) + i*50);
    }
    if(bDrawGui) gui.draw();
    // fisheye effect begin
    mCam.begin();
    mAgentController->draw(bDrawAttractors);
    mCam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'w'){
        mWriteData = !mWriteData;
        if(mWriteData) ofLog() << "Writing Data...";
        else ofLog() << "Finished Writing Data";
    } else if(key == 's'){
        mEnableSimulation = !mEnableSimulation;
    } else if(key == 'b'){
        mSendStats = !mSendStats;
    } else if(key == 'd') {
        bDrawGui = !bDrawGui;
    } else if(key == 'a') {
        bDrawAttractors = !bDrawAttractors;
    } else if(key == 'f') {
        static bool f = true;
        ofSetFullscreen(f);
        f = !f;
    }
        
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit(){
    mAgentController->mSharedPositionData.close();
}
