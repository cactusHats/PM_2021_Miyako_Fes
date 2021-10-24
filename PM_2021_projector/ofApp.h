/*
 * Tokyo Metropolitan University
 * Code of the projection show at Miyako fest.
 *
 * Code of the slave (projector).
 * Written by Masashi Seki
 *
 * 2019.10.12 Sat.
 *
 * -----
 * Set IP address of controller in ofApp.h
 * Change the device name of URL of function reply() in ofApp.cpp
 * -----
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT_TO_SLAVE 8000
#define PORT_TO_CONTROLLER 7000

#define IP_CONTROLLER "192.168.11.1" //IP address of controller

#define PLAY_ADJUST 0 //frames

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void play();
	void pause();
	void rewind();
	void screenOff();
	void screenOn();
	void reply();
	void QR_play();

	ofxOscSender sender;
	ofxOscReceiver receiver;

	ofVideoPlayer movie;
	ofVideoPlayer qr;

	bool black;
	bool count_start;
	bool movie_on;
	bool pauseFlag;
	
	int framecount;
	int videoType;
	int width;
	int height;
};
