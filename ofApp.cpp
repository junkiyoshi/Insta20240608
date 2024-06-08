#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);

	auto ico_sphere = ofIcoSpherePrimitive(250, 6);
	this->base_mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh.clear();

	vector<ofColor> color_list = { ofColor(0, 255, 255), ofColor(255, 0, 255), ofColor(255, 255, 0)};

	auto noise_seed = ofRandom(1000);
	for (int k = 0; k < color_list.size(); k++) {

		noise_seed += ofRandom(1000);
		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 10; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed + ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed + ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed + ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
			}

			this->draw_mesh.addVertex(v);
			this->draw_mesh.addColor(color_list[k]);
		}
	}

	for (auto& vertex : this->draw_mesh.getVertices()) {

		vertex.x = vertex.x < -135 ? -135 : vertex.x > 135 ? 135 : vertex.x;
		vertex.y = vertex.y < -135 ? -135 : vertex.y > 135 ? 135 : vertex.y;
		vertex.z = vertex.z < -135 ? -135 : vertex.z > 135 ? 135 : vertex.z;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.66666666666666);
	ofRotateX(ofGetFrameNum() * 1.22222222222222);

	this->draw_mesh.drawVertices();

	this->cam.end();

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}