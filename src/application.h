#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Application : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxAssimpModelLoader model;
		ofEasyCam cam;
		ofShader shader;
		
		float rotationSpeed = 0.0f;

		// Pour le model 3D du pingouin
		ofMesh texturedMesh;
		ofImage penguinTexture;


		// Pour la sphere texturé
		ofSpherePrimitive texturedSphere;
		ofTexture sphereTexture; // J'utilise ofTexture ici juste pour montrer qu'on peut utiliser soit ofImage ou ofTexture. Les deux marche.
		glm::vec3 spherePosition = glm::vec3(400, 0, 0); // On positionne la sphere à droite du pingouin


		// Pour un autre sphere texturé en utilisant le shader de base de openFrameworks
		ofSpherePrimitive sphereNoShader;
		ofImage sphereNoShaderTexture;
		glm::vec3 sphereNoShaderPos = glm::vec3(-400, 0, 0); // On positionne la sphere à la gauche du pingouin
	
};
