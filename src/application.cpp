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


	// Code pour la sphere texturé avec custom shader
    ofLoadImage(sphereTexture, "textures/grey-texture2.jpg");

    texturedSphere.setRadius(100);
    texturedSphere.setResolution(48);
    texturedSphere.mapTexCoordsFromTexture(sphereTexture);


	// Code pour la sphere texturé sans shader (le shader de base de openFrameworks)
    sphereNoShaderTexture.load("textures/grey-texture2.jpg");

    sphereNoShader.setRadius(100);
    sphereNoShader.setResolution(48);
    sphereNoShader.mapTexCoordsFromTexture(sphereNoShaderTexture.getTexture());

}

void Application::update() {
    rotationSpeed += 0.5f;
}

void Application::draw() {
    //ofBackground(20);
    cam.begin();

    // ----------------------------------------------------------------
    // LIGHT SETUP (shared by both objects that use the custom shader)
    // ----------------------------------------------------------------
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

    // --------------------------------------
    // PENGUIN DRAWING
    // --------------------------------------
    if (texturedMesh.getNumVertices() > 0) {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, model.getPosition());
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationSpeed), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(200.0f));

        shader.begin();
        shader.setUniformTexture("tex0", penguinTexture.getTexture(), 0);
        shader.setUniform3f("lightDir", lightWorldDir);
        shader.setUniform3f("lightColor", lightColor);
        shader.setUniform3f("ambientColor", ambientColor);
        shader.setUniform3f("viewPos", cam.getPosition());
        shader.setUniformMatrix4f("modelMatrix", modelMatrix);

        ofPushMatrix();
        ofTranslate(model.getPosition());
        ofRotateDeg(rotationSpeed, 0, 1, 0);
        ofRotateDeg(180, 0, 1, 0);
        ofRotateDeg(90, 1, 0, 0);
        ofScale(200.0f, 200.0f, 200.0f);
        texturedMesh.draw();
        ofPopMatrix();

        shader.end();
    }

    // -------------------------------------------
    // TEXTURED SPHERE DRAWING WITH CUSTOM SHADER
    // 

	// Le model matrix est une matrice 4 x 4 qui sert à transformer les coordonnées de l'objet de l'espace local à l'espace monde. (local space to world space)

	glm::mat4 sphereModelMatrix = glm::mat4(1.0f); // Matrice d'identité (aucune transformation appliquée)

    sphereModelMatrix = glm::translate(sphereModelMatrix, spherePosition); // Applique une translation pour positionner la sphère à l’endroit désiré

    sphereModelMatrix = glm::rotate(sphereModelMatrix, glm::radians(rotationSpeed), glm::vec3(0, 1, 0)); // Applique une rotation autour de l’axe Y pour faire tourner la sphère (comme le pingouin)

    sphereModelMatrix = glm::scale(sphereModelMatrix, glm::vec3(1.0f)); // Applique un facteur d’échelle uniforme de 1.0 (laisse la sphère à sa taille originale)


    shader.begin();
	shader.setUniformTexture("tex0", sphereTexture, 0); // On passe la texture au shader
    shader.setUniform3f("lightDir", lightWorldDir);
    shader.setUniform3f("lightColor", lightColor);
    shader.setUniform3f("ambientColor", ambientColor);
    shader.setUniform3f("viewPos", cam.getPosition());
	shader.setUniformMatrix4f("modelMatrix", sphereModelMatrix); // On passe la matrice de transformation au shader pour que les ombres, la lumière et les reflets soient appliqués correctement sur la sphère

    ofPushMatrix();
	ofTranslate(spherePosition); // à la droite du pingouin
    ofRotateDeg(rotationSpeed, 0, 1, 0);
    texturedSphere.draw();
    ofPopMatrix();

    shader.end();


    // --------------------------------------
	// SPHERE WITH NO SHADER, NO LIGHTING 
    // Le lighting ne marchera pas sur cette sphere vu qu'il utilise le shader de base de openFrameworks. 
    // Donc pour avoir de la lumière avec le shader de base il faudrait utiliser ofLight 
    // Je pense que dans notre projet on vas utiliser le custom shader, faque on n'utilisera pas ce code.
    // --------------------------------------
    ofPushMatrix();
	ofTranslate(sphereNoShaderPos); // à la gauche du pingouin
    ofRotateDeg(rotationSpeed, 0, 1, 0);
    sphereNoShaderTexture.bind();
    sphereNoShader.draw();
    sphereNoShaderTexture.unbind();
    ofPopMatrix();


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
