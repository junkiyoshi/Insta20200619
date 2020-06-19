#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < 3; i++) {

		if (ofGetFrameNum() % 10 == 0) {

			auto noise_location = glm::vec2(
				ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 120, ofGetWidth() - 120),
				ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 120, ofGetHeight() - 120)
			);

			auto ripple = Ripple();
			ripple.location = noise_location;
			ripple.radius = 1;

			this->ripple_list.push_back(ripple);
		}
	}

	for (int i = this->ripple_list.size() - 1; i >= 0; i--) {

		if (this->ripple_list[i].radius < 70) {

			this->ripple_list[i].radius += 1;
		}
		else {

			this->ripple_list.erase(this->ripple_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& ripple : this->ripple_list) {

		if (ripple.radius > 50) {

			ofSetColor(ofMap(ripple.radius, 50, 70, 39, 239));
		}
		else {

			ofSetColor(39);
		}

		ofBeginShape();
		for (int deg = 0; deg < 360; deg += 5) {

			ofVertex(ripple.location + glm::vec2(ripple.radius * cos(deg * DEG_TO_RAD), ripple.radius * sin(deg * DEG_TO_RAD)));
		}
		ofEndShape(true);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
