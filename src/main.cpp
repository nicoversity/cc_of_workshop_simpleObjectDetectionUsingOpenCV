/*
 * main.cpp
 *
 * Project: Creative coding using openFrameworks - Workshop: Simple Object Detection using OpenCV
 *
 * Supported openFrameworks version: 0.9.6
 *
 * Author: Nico Reski
 * Web: http://reski.nicoversity.com
 * Twitter: @nicoversity
 */

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // updated application window size: space for a grid of 3x3 images of size 320x240 each
	ofSetupOpenGL(960,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
