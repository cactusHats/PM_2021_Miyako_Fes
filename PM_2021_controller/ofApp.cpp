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

#include "ofApp.h"

 //--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0, 0, 0); //background
	ofSetFrameRate(30); //30frames per sec

	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);
	verdana.load("VerdanaRef.ttf", 50);
	verdana.setLineHeight(24);
	verdana.setLetterSpacing(1.0);

	// osc setting
	projector_A1.setup(IP_PROJECTOR_A1, PORT_TO_SLAVE);
	projector_B1.setup(IP_PROJECTOR_B1, PORT_TO_SLAVE);
	projector_B2.setup(IP_PROJECTOR_B2, PORT_TO_SLAVE);
	projector_C1.setup(IP_PROJECTOR_C1, PORT_TO_SLAVE);
	pa.setup(IP_PA, PORT_TO_SLAVE);

	receiver.setup(PORT_TO_CONTROLLER);

	cnState_A1 = 2; //0:..., 1:success, 2:failed
	cnState_B1 = 2;
	cnState_B2 = 2;
	cnState_C1 = 2;
	cnState_PA = 2;

	connectionState = false;
	frameCount = 0;
	black = false;
	margin = 50;
}

//--------------------------------------------------------------
void ofApp::update() {

	getTime();

	width = ofGetWidth();
	height = ofGetHeight();
	betweenLines = height / 17.0;
	fontSize = height * 0.035;
			
	if (connectionState == true) {
		frameCount++;

		while (receiver.hasWaitingMessages()) {
			ofxOscMessage m;
			receiver.getNextMessage(&m);

			if (m.getAddress() == "/pmap/connection/responce/A") { cnState_A1 = 1; }
			else if (m.getAddress() == "/pmap/connection/responce/B1") { cnState_B1 = 1; }
			else if (m.getAddress() == "/pmap/connection/responce/B2") { cnState_B2 = 1; }
			else if (m.getAddress() == "/pmap/connection/responce/C") { cnState_C1 = 1; }
			else if (m.getAddress() == "/pmap/connection/responce/PA") { cnState_PA = 1; }
			else;
		}

		if (frameCount > TIMEOUT) {
			if (cnState_A1 == 0) cnState_A1 = 2;
			if (cnState_B1 == 0) cnState_B1 = 2;
			if (cnState_B2 == 0) cnState_B2 = 2;
			if (cnState_C1 == 0) cnState_C1 = 2;
			if (cnState_PA == 0) cnState_PA = 2;

			connectionState = false;
		}

		if (cnState_A1 == 1 && cnState_B1 == 1 && cnState_B2 == 1 && cnState_C1 == 1 && cnState_PA == 1) connectionState = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize);
	verdana.drawString(time, 500, margin);

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize * 1.4);
	verdana.drawString("Media & Screen", 50, margin + betweenLines*2);

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize);
	verdana.drawString("+ Media Play", 90, margin + betweenLines * 3); verdana.drawString("'   '", 480, margin + betweenLines * 3);
	verdana.drawString("+ Media Pause", 90, margin + betweenLines * 4); verdana.drawString("' p '", 480, margin + betweenLines * 4);
	verdana.drawString("+ Media Rewind", 90, margin + betweenLines * 5); verdana.drawString("' r '", 480, margin + betweenLines * 5);
	verdana.drawString("+ Screen Blind", 90, margin + betweenLines * 6); verdana.drawString("' q '", 480, margin + betweenLines * 6);
	verdana.drawString("+ QR code play", 90, margin + betweenLines * 7); verdana.drawString("' g '", 480, margin + betweenLines * 7);

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize * 1.4);
	verdana.drawString("Connection", 50, margin + betweenLines * 9);

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize);
	verdana.drawString("+ Connection Check", 90, margin + betweenLines * 10); verdana.drawString("' c '", 480, margin + betweenLines * 10);

	ofSetColor(30, 200, 200);
	verdana.load("VerdanaRef.ttf", fontSize);
	verdana.drawString("- Projector A", 150, margin + betweenLines * 11);
	verdana.drawString("- Projector B1", 150, margin + betweenLines * 12);
	verdana.drawString("- Projector B2", 150, margin + betweenLines * 13);
	verdana.drawString("- Projector C", 150, margin + betweenLines * 14);
	verdana.drawString("- PA", 150, margin + betweenLines * 15);

	verdana.load("VerdanaRef.ttf", fontSize);
	if (cnState_A1 == 1) { ofSetColor(0, 200, 100); verdana.drawString("success", 455, margin + betweenLines * 11); }
	else if (cnState_A1 == 2) { ofSetColor(200, 100, 0); verdana.drawString("failed", 470, margin + betweenLines * 11); }
	else if (cnState_A1 == 0) { ofSetColor(30, 200, 200); verdana.drawString("connecting...", 440, margin + betweenLines * 11); }

	if (cnState_B1 == 1) { ofSetColor(0, 200, 100); verdana.drawString("success", 455, margin + betweenLines * 12); }
	else if (cnState_B1 == 2) { ofSetColor(200, 100, 0); verdana.drawString("failed", 470, margin + betweenLines * 12); }
	else if (cnState_B1 == 0) { ofSetColor(30, 200, 200); verdana.drawString("connecting...", 440, margin + betweenLines * 12); }

	if (cnState_B2 == 1) { ofSetColor(0, 200, 100); verdana.drawString("success", 455, margin + betweenLines * 13); }
	else if (cnState_B2 == 2) { ofSetColor(200, 100, 0); verdana.drawString("failed", 470, margin + betweenLines * 13); }
	else if (cnState_B2 == 0) { ofSetColor(30, 200, 200); verdana.drawString("connecting...", 440, margin + betweenLines * 13); }

	if (cnState_C1 == 1) { ofSetColor(0, 200, 100); verdana.drawString("success", 455, margin + betweenLines * 14); }
	else if (cnState_C1 == 2) { ofSetColor(200, 100, 0); verdana.drawString("failed", 470, margin + betweenLines * 14); }
	else if (cnState_C1 == 0) { ofSetColor(30, 200, 200); verdana.drawString("connecting...", 440, margin + betweenLines * 14); }

	if (cnState_PA == 1) { ofSetColor(0, 200, 100); verdana.drawString("success", 455, margin + betweenLines * 15); }
	else if (cnState_PA == 2) { ofSetColor(200, 100, 0); verdana.drawString("failed", 470, margin + betweenLines * 15); }
	else if (cnState_PA == 0) { ofSetColor(30, 200, 200); verdana.drawString("connecting...", 440, margin + betweenLines * 15); }
}

//--------------------------------------------------------------
void ofApp::getTime() {

	if (ofGetSeconds() < 10)
		s = "0" + ofToString(ofGetSeconds(), 0);
	else
		s = ofToString(ofGetSeconds(), 0);
	if (ofGetMinutes() < 10)
		m = "0" + ofToString(ofGetMinutes(), 0);
	else
		m = ofToString(ofGetMinutes(), 0);

	if (ofGetHours() < 10)
		h = "0" + ofToString(ofGetHours(), 0);
	else
		h = ofToString(ofGetHours(), 0);

	time = h + ":" + m + ":" + s;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'c':
		connectionCheck();
		break;

	case ' ':
		allPlay();
		break;

	case 'p':
		allPause();
		break;

	case 'r':
		allRewind();
		break;

	case 'q':
		black = (!black);
		if (black == false) allScreenOn();
		else if (black == true) allScreenOff();
		else;
		break;

	case 'g':
		allQR_Play();
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------

void ofApp::connectionCheck() {

	cnState_A1 = 0;
	cnState_B1 = 0;
	cnState_B2 = 0;
	cnState_C1 = 0;
	cnState_PA = 0;

	// osc message
	ofxOscMessage message;
	message.setAddress("/pmap/connection/ask");

	//sendmessages
	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);

	connectionState = true;
	frameCount = 0;
}

//--------------------------------------------------------------
void ofApp::allPlay() {

	ofxOscMessage message;
	message.setAddress("/pmap/media/play");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::allPause() {

	ofxOscMessage message;
	message.setAddress("/pmap/media/pause");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::allRewind() {

	ofxOscMessage message;
	message.setAddress("/pmap/media/rewind");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::allScreenOff() {

	ofxOscMessage message;
	message.setAddress("/pmap/screen/off");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::allScreenOn() {

	ofxOscMessage message;
	message.setAddress("/pmap/screen/on");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::allQR_Play() {

	ofxOscMessage message;
	message.setAddress("/pmap/media/QR_play");

	projector_A1.sendMessage(message);
	projector_B1.sendMessage(message);
	projector_B2.sendMessage(message);
	projector_C1.sendMessage(message);
	pa.sendMessage(message);
}
