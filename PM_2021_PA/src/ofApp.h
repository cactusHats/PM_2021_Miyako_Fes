/*
 * Tokyo Metropolitan University
 * Code of the projection show at Miyako fest.
 *
 * Code of the slave (PA).
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
#include <unistd.h>

#define PORT_TO_SLAVE 8000
#define PORT_TO_CONTROLLER 7000

#define IP_CONTROLLER "192.168.0.10" //IP address of controller

#define PLAY_ADJUST 10 //frames

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void play();
	void QR_play();
	void fw_play();
	void pause();
	void rewind();
	void screenOff();
	void screenOn();
	void reply();

	ofxOscSender sender;
	ofxOscReceiver receiver;

	ofSoundPlayer sound;
	ofSoundPlayer qr;
	ofSoundPlayer fw;
	ofImage img;

	bool black;
	bool count_start;
	bool pauseFlag;

	int framecount;
	int soundType;
	int width;
	int height;
};
