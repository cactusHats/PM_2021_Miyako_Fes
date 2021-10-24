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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofHideCursor(); //win and mac
					//CGDisplayHideCursor(NULL); //mac only

	ofBackground(0, 0, 0);
	ofSetFrameRate(60);

	movie.load("movie1.mov");
	qr.load("movie2.mp4");

	movie.setLoopState(OF_LOOP_NONE);
	qr.setLoopState(OF_LOOP_NONE);

	sender.setup(IP_CONTROLLER, PORT_TO_CONTROLLER);
	receiver.setup(PORT_TO_SLAVE);

	black = false;
	movie_on = false;
	count_start = false;
	pauseFlag = false;
	framecount = 0;
	videoType = 0;

	width = ofGetWidth();
	height = ofGetHeight();

	//-- movie start --
	//count_start = true;
	//videoType = 2;
}

//--------------------------------------------------------------
void ofApp::update() {

	movie.update();
	qr.update();

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		if (m.getAddress() == "/pmap/media/play") {
			count_start = true;
			videoType = 1;
		}
		else if (m.getAddress() == "/pmap/media/QR_play") {
			count_start = true;
			videoType = 2;
		}
		else if (m.getAddress() == "/pmap/media/pause") {
			count_start = true;
			pauseFlag = true;
		}
		else if (m.getAddress() == "/pmap/media/rewind") {
			rewind();
		}
		else if (m.getAddress() == "/pmap/screen/off") {
			screenOff();
		}
		else if (m.getAddress() == "/pmap/screen/on") {
			screenOn();
		}
		else if (m.getAddress() == "/pmap/connection/ask") {
			reply();
		}
	}

	if (count_start) {

		framecount++;

		if (framecount > PLAY_ADJUST) {
			movie_on = true;

			if (pauseFlag == true) {
				pause();
				//cout << "#0 " << endl;
			}
			else if (videoType == 1) {
				play();
				//cout << "#1 " << endl;
			}
			else if (videoType == 2) {
				QR_play();
				//cout << "#2 " << endl;
			}

			count_start = false;
			pauseFlag = false;
			framecount = 0;
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (black == false && movie_on == true) {

		if (videoType == 1) {
			movie.draw(0, 0, width, height);
			//cout << "+1 ";
		}
		else if (videoType == 2) {
			qr.draw(0, 0, width, height);
			//cout << "+2 ";
		}
	}

	//debug
	//cout << count_start << " " << framecount << " " << movie_on << " " << videoType << " " << black << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'q') {
		black = !black;
		cout << "black:" << black << endl;
	}

	/*
	if (key == 'p') {
		count_start = true;
		videoType = 1;
	}
	else if (key == 's') {
		count_start = true;
		pauseFlag = true;
	}
	else if (key == 'r') {
		rewind();
	}
	*/
}

//--------------------------------------------------------------
void ofApp::play() {
	movie.setPaused(false);
	qr.setPaused(true);
	if (movie.getPosition() == 0.0f) {
		movie.play();
	}
	cout << "play" << endl;
}

//--------------------------------------------------------------
void ofApp::QR_play() {
	qr.setPaused(false);
	movie.setPaused(true);
	if (qr.getPosition() == 0.0f) {
		qr.play();
	}
	cout << "qr play" << endl;
}

//--------------------------------------------------------------
void ofApp::pause() {
	movie.setPaused(true);
	qr.setPaused(true);
	framecount = 0;
	cout << "pause" << endl;
}

//--------------------------------------------------------------
void ofApp::rewind() {
	movie.setPaused(true);
	movie.setPosition(0.0);
	qr.setPaused(true);
	qr.setPosition(0.0);
	videoType = 1;
	movie_on = false;
	cout << "rewind" << endl;
}

//--------------------------------------------------------------
void ofApp::screenOff() {
	black = true;
	cout << "screen off" << endl;
}

//--------------------------------------------------------------
void ofApp::screenOn() {
	black = false;
	cout << "screen on" << endl;
}

//--------------------------------------------------------------
void ofApp::reply() {
	// osc message
	ofxOscMessage message;
	message.setAddress("/pmap/connection/responce/A"); //change URL according to device name.

													   //stalling
	for (int i = 0; i < 10000; i++);
	sender.sendMessage(message);

	cout << "replay" << endl;
}