#include "application.h"

void Application::setup() {
    ofEnableDepthTest();

    ofDisableArbTex();

    penguinTexture.load("textures/Penguin_Diffuse_Color.png");
    model.loadModel("models/PenguinBaseMesh.fbx");
    model.setScaleNormalization(false);
    model.setPosition(0, 0, 0);

    if (model.getMeshCount() > 0) {
        texturedMesh = model.getMesh(0);
    }

    shader.load("shaders/shader");
}

void Application::update() {
    penguinRotation += 0.5f;
}

void Application::draw() {
    ofBackground(20);
    cam.begin();

    // Create model matrix manually
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, model.getPosition());
    modelMatrix = glm::rotate(modelMatrix, glm::radians(penguinRotation), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(200.0f));

    if (texturedMesh.getNumVertices() > 0) {

        glm::vec3 lightColor = glm::vec3(1.5);
        glm::vec3 ambientColor = glm::vec3(0.2);

        glm::vec3 lightWorldDir = glm::normalize(glm::vec3(1.0, -1.0, 0.0));
        glm::vec3 lightStart = glm::vec3(500, 400, 0);

        glm::vec3 penguinCenter = model.getPosition();
        glm::vec3 arrowDir = glm::normalize(penguinCenter - lightStart);
        glm::vec3 lightEnd = lightStart + arrowDir * 100.0f;

        ofPushStyle();
        ofSetColor(255, 255, 100);
        ofDrawArrow(lightStart, lightEnd, 10.0f);
        ofPopStyle();

        // Shader + lighting
        shader.begin();
        shader.setUniformTexture("tex0", penguinTexture.getTexture(), 0);
        shader.setUniform3f("lightDir", lightWorldDir);
        shader.setUniform3f("lightColor", lightColor);
        shader.setUniform3f("ambientColor", ambientColor);
        shader.setUniform3f("viewPos", cam.getPosition());
        shader.setUniformMatrix4f("modelMatrix", modelMatrix);

        // Draw the penguin
        ofPushMatrix();
        ofTranslate(model.getPosition());
        ofRotateDeg(penguinRotation, 0, 1, 0);
        ofRotateDeg(180, 0, 1, 0);
        ofRotateDeg(90, 1, 0, 0);
        ofScale(200.0f, 200.0f, 200.0f);
        texturedMesh.draw();
        ofPopMatrix();

        shader.end();
    }

    cam.end();
}

//--------------------------------------------------------------
void Application::keyPressed(int key){

}

//--------------------------------------------------------------
void Application::keyReleased(int key){

}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Application::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo){

}
