/*
 * ofApp.h
 *
 * Project: Creative coding using openFrameworks - Workshop: Simple Object Detection using OpenCV
 *
 * Author: Nico Reski
 * Web: http://reski.nicoversity.com
 * Twitter: @nicoversity
 */

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"  // make functionalities of OpenCV addon available

class ofApp : public ofBaseApp{

    private:
        void debugCameraDevices();  // helper method to print information about available camera sources to the console
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // image propeties
        int imgWidth;
        int imgHeight;
    
        // image instances (managed by OpenCV)
        ofxCvColorImage originalInputImg;   // original image as received from camera source
    
        // camera instance
        ofVideoGrabber cameraInput;
    
        // helper values
        int labelPosDelta;
};
