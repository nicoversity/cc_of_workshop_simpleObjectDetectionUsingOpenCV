/*
 * ofApp.cpp
 *
 * Project: Creative coding using openFrameworks - Workshop: Simple Object Detection using OpenCV
 *
 * Supported openFrameworks version: 0.9.0
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
    detectedObjectMax  = 10;    // maximum of 10 detected object at a time
    contourMinArea     = 40;    // detect a wide range of different sized objects
    contourMaxArea     = (imgWidth * imgHeight) / 3;
    
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
    // cameraInput.initGrabber(imgWidth, imgHeight, true); // OF version 0.8.4; enable bTexture flag for setting up a texture and displaying the video on screen
    cameraInput.initGrabber(imgWidth, imgHeight); // OF version 0.9.0
    
    // initialize helper values
    labelPosDelta     = 14;
    blobOverlayRadius = 10;
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
        //originalInputImg.setFromPixels(cameraInput.getPixels(), imgWidth, imgHeight);    // OF version 0.8.4
        originalInputImg.setFromPixels(cameraInput.getPixels());    // OF version 0.9.0
        
        // create HCV color space image based on original (RGB) received camera input image
        hsvImg = originalInputImg;
        hsvImg.convertRgbToHsv();
        
        // extract HSV color space channels into separate image instances
        hsvImg.convertToGrayscalePlanarImages(hueImg, saturationImg, valueImg);
        
        // take the absolute value of the difference between the registered background image and the updated saturation color channel image in order to determine the image parts that have changed
        bckgrndSatDiffImg.absDiff(backgroundImg, saturationImg);
        
        // increase the contrast of the image
        bckgrndSatDiffImg.threshold(detectionThreshold);
        
        // apply object detection via OpenCV contour finder class
        contourFinder.findContours(bckgrndSatDiffImg, contourMinArea, contourMaxArea, detectedObjectMax, false);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // reset color for drawing
    ofSetHexColor(0xffffffff);  // set color "white" in hexadecimal representation
    
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
    saturationImg.draw(0 * imgWidth, 2 * imgHeight);    // copy of saturation image in order to put colored circles on detection objects in the scene
    bckgrndSatDiffImg.draw(1 * imgWidth, 2 * imgHeight);
    
    
    // visualize object detection
    // draw detected objects ("blobs") individually
    for (int i = 0; i < contourFinder.nBlobs; i++) {
        // access current blob
        contourFinder.blobs[i].draw(2 * imgWidth, 2 * imgHeight);   // draw current blob in bottom right image grid
        
        // extract RGB color from the center of the current blob based on original input image
        //
        
        // get pixel reference of original input image
        //ofPixels originalInputImagePxls = originalInputImg.getPixelsRef();    // OF version 0.8.4
        ofPixels originalInputImagePxls = originalInputImg.getPixels(); // OF version 0.9.0
        
        // get point reference to the center of the current detected blob
        ofPoint blobCenterPnt = contourFinder.blobs[i].centroid;
        
        // get color of pixel in the center of the detected blob
        ofColor detectedBlobClr = originalInputImagePxls.getColor(blobCenterPnt.x, blobCenterPnt.y);
        
        // apply detected color for drawing circle overlay
        ofSetColor(detectedBlobClr);
        ofFill();
        
        // draw circle overlay in bottom left image of the grid (ontop of a copy of the saturation image)
        // OF version 0.8.4
        /*ofCircle(blobCenterPnt.x + 0 * imgWidth,
         blobCenterPnt.y + 2 * imgHeight,
         blobOverlayRadius); */
        // OF version 0.9.0
        ofDrawCircle(blobCenterPnt.x + 0 * imgWidth,
                     blobCenterPnt.y + 2 * imgHeight,
                     blobOverlayRadius);
    }

    
    // draw image captions
    ofSetColor(236, 50, 135);   // set color: OF pink
    ofDrawBitmapString("Original", labelPosDelta + 0 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("HSV", labelPosDelta + 1 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("Registered Background", labelPosDelta + 2 * imgWidth, labelPosDelta + 0 * imgHeight);
    ofDrawBitmapString("Hue", labelPosDelta + 0 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Saturation", labelPosDelta + 1 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Value", labelPosDelta + 2 * imgWidth, labelPosDelta + 1 * imgHeight);
    ofDrawBitmapString("Color Detection", labelPosDelta + 0 * imgWidth, labelPosDelta + 2 * imgHeight);
    ofDrawBitmapString("Bckgrnd-Sat-Difference", labelPosDelta + 1 * imgWidth, labelPosDelta + 2 * imgHeight);
    ofDrawBitmapString("Object Detection", labelPosDelta + 2 * imgWidth, labelPosDelta + 2 * imgHeight);
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
