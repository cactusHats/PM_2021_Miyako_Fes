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

#include "ofMain.h"
#include "ofApp.h"

int main() {
	ofSetupOpenGL(670, 700, OF_WINDOW);
	ofRunApp(new ofApp());
}
