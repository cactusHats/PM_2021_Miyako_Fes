/*
 * Tokyo Metropolitan University
 * Code of the projection show at Miyako fest.
 *
 * Code of the controller.
 * Written by Masashi Seki
 *
 * 2019.10.26 Sat.
 *
 * -----
 * Set IP address of slaves in ofApp.h
 * Put in the font data "VerdanaRef.ttf" in "data" folder
 * -----
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define IP_PROJECTOR_A1 "192.168.11.2"
#define IP_PROJECTOR_B1 "192.168.11.3"
#define IP_PROJECTOR_B2 "192.168.11.4"
#define IP_PROJECTOR_C1 "192.168.11.5"
#define IP_PA			"192.168.11.6"

#define PORT_TO_SLAVE 8000
#define PORT_TO_CONTROLLER 7000

#define TIMEOUT 50

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	void connectionCheck();
	void allPlay();
	void allPause();
	void allRewind();
	void allScreenOff();
	void allScreenOn();
	void getTime();
	void allQR_Play();

	ofxOscSender projector_A1, projector_B1, projector_B2, projector_C1, pa;
	ofxOscReceiver receiver;

	bool connectionState;
	bool black;

	string time;
	ofTrueTypeFont verdana;

	int width;
	int height;

	int cnState_A1;
	int cnState_B1;
	int cnState_B2;
	int cnState_C1;
	int cnState_PA;

	string s, m, h;
	string then_s, then_m, then_h;

	int frameCount;

	int betweenLines;
	int margin;
	int fontSize;
};

