/*
 * ofApp.cpp
 *
 * Project: Creative coding using openFrameworks - Workshop: Simple Object Detection using OpenCV
 *
 * Author: Nico Reski
 * Web: http://reski.nicoversity.com
 * Twitter: @nicoversity
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::debugCameraDevices()
{
    // create a collection holding information about all available camera sources
    vector< ofVideoDevice > devices = cameraInput.listDevices();
    
    // iterate through camera source collection and print info for each item
    for(int i = 0; i < devices.size(); i++) {
        cout <<
        "Device ID: " << devices[i].id <<
        " Device Name: " << devices[i].deviceName <<
        " Hardware Name: " << devices[i].hardwareName <<
        " Is Available: " << devices[i].bAvailable <<
        endl;
    }
}


//--------------------------------------------------------------
void ofApp::setup()
{
    // initialize image properties
    imgWidth  = 320;
    imgHeight = 240;
    
    // initialize OpenCV image instances
    // (manual memory allocation required)
    originalInputImg.allocate(imgWidth, imgHeight);
    
    // initialize camera instance
    debugCameraDevices();   // print information about available camera sources
    cameraInput.setDeviceID(0);     // 0 -> default if at least once camera is available (get device id of other camera sources from running debugCameraDevices() )
    cameraInput.initGrabber(imgWidth, imgHeight, true); // enable bTexture flag for setting up a texture and displaying the video on screen
    
    // initialize helper values
    labelPosDelta = 14;
}

//--------------------------------------------------------------
void ofApp::update()
{
    // update (read) input from camera feed
    cameraInput.update();
    
    // check if a new frame from the camera source was received
    if (cameraInput.isFrameNew())
    {
        // read (new) pixels from camera input and write them to original input image instance
        originalInputImg.setFromPixels(cameraInput.getPixels(), imgWidth, imgHeight);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // reset color for drawing
    ofSetHexColor(0xffffffff);  // set color "white" in hexadicimal representation
    
    // draw original input image as received from camera source
    originalInputImg.draw(0 * imgWidth, 0 * imgHeight);
    
    // draw image caption
    ofSetColor(236, 50, 135);   // set color: OF pink
    ofDrawBitmapString("Original", labelPosDelta + 0 * imgWidth, labelPosDelta + 0 * imgHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
