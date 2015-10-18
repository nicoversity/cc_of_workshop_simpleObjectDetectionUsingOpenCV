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
    
    // initialize object detection properties
    detectionThreshold = 70;    // very high contrast
    
    // initialize OpenCV image instances
    // (manual memory allocation required)
    originalInputImg.allocate(imgWidth, imgHeight);
    hsvImg.allocate(imgWidth, imgHeight);
    hueImg.allocate(imgWidth, imgHeight);
    saturationImg.allocate(imgWidth, imgHeight);
    valueImg.allocate(imgWidth, imgHeight);
    backgroundImg.allocate(imgWidth, imgHeight);
    bckgrndSatDiffImg.allocate(imgWidth, imgHeight);
    
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
        
        // create HCV color space image based on original (RGB) received camera input image
        hsvImg = originalInputImg;
        hsvImg.convertRgbToHsv();
        
        // extract HSV color space channels into separate image instances
        hsvImg.convertToGrayscalePlanarImages(hueImg, saturationImg, valueImg);
        
        // take the absolute value of the difference between the registered background image and the updated saturation color channel image in order to determine the image parts that have changed
        bckgrndSatDiffImg.absDiff(backgroundImg, saturationImg);
        
        // increase the contrast of the image
        bckgrndSatDiffImg.threshold(detectionThreshold);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // reset color for drawing
    ofSetHexColor(0xffffffff);  // set color "white" in hexadicimal representation
    
    // draw grid of images
    //
    
    // row 1
    originalInputImg.draw(0 * imgWidth, 0 * imgHeight); // draw original input image as received from camera source
    hsvImg.draw(1 * imgWidth, 0 * imgHeight);   // original input image in HSV color space representation
    backgroundImg.draw(2 * imgWidth, 0 * imgHeight);   // registred background image
    
    // row 2
    hueImg.draw(0 * imgWidth, 1 * imgHeight);
    saturationImg.draw(1 * imgWidth, 1 * imgHeight);
    valueImg.draw(2 * imgWidth, 1 * imgHeight);
    
    // row 3
    bckgrndSatDiffImg.draw(1 * imgWidth, 2 * imgHeight);
    
    // draw image captions
    ofSetColor(236, 50, 135);   // set color: OF pink
    ofDrawBitmapString("Original", labelPosDelta + 0 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("HSV", labelPosDelta + 1 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("Registered Background", labelPosDelta + 2 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("Hue", labelPosDelta + 0 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Saturation", labelPosDelta + 1 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Value", labelPosDelta + 2 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Bckgrnd-Sat-Difference", labelPosDelta + 1 * imgWidth, labelPosDelta + 2 * imgHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // press spacebar (key code == 32): learn background
    if (key == 32) {
        // copy information of current saturation color channel image into background image reference
        backgroundImg = saturationImg;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
