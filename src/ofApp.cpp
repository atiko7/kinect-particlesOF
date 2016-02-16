#include "ofApp.h"
ofColor gColor = ofColor(0, 255, 255);

int steps =20;
int maxPS = 307200/steps;
int numPart = 4;
bool useKinect = false;

int lifeDec1 = 20;
int lifeDec2 = 50;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetWindowTitle("Atiko7 Kinect Particles");
    ofDisableArbTex();
    spriteImg.load("sprite.png");
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    gui.setup();
    gui.add(guiLife1.setup("Life1", 18, 0, 50));
    gui.add(guiSize1.setup("Size1", 7, 1, 30));
//    gui.add(guiLife2.setup("Life2", 18, 0, 50));
//    gui.add(guiSize2.setup("Size2", 7, 1, 30));
    
    for(int i=0; i<maxPS; i++){
        ps.push_back(ParticleSystem(1, lifeDec1));
    }
    indices.assign(maxPS, 0);
    
    int a = 0;
    for (int i = 0; i < indices.size(); i++) {
        a +=steps+ ofRandom(0, 10);
        indices[i]=a;
        mesh.addColor(gColor);
        mesh.addVertex(ofVec3f(ps[i].particles[0].pos.x, ps[i].particles[0].pos.y, 0));
    }

    if (useKinect){
        niContext.setup();
        niDepthGenerator.setup( &niContext );
        niImageGenerator.setup( &niContext );
        niUserGenerator.setup( &niContext );
        niUserGenerator.setUseMaskPixels(true);
        niUserGenerator.setUseCloudPoints(true);
        niContext.setMirror(true);
        niContext.registerViewport();
    }
    userpixels.allocate(640, 480, 1);
    myImage.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    myImage2.allocate(640, 480, OF_IMAGE_COLOR);

}

//--------------------------------------------------------------
void ofApp::update(){
    if (useKinect){
        niContext.update();
        niDepthGenerator.update();
        niImageGenerator.update();
        niUserGenerator.update();
        userpixels.setFromExternalPixels(niUserGenerator.getUserPixels(0), 640, 480, 1);
        myImage.setFromPixels(userpixels);
        myImage.update();
        for (int i=0; i<640; i++) {
            for (int j=0; j<480; j++) {
                if(myImage.getColor(i, j) == ofColor(255)){
                    myImage2.setColor(i, j, ofColor(255, 255, 255));
                }
                else{
                    myImage2.setColor(i, j, ofColor(0, 0, 0));
                }
            }
        }
        myImage2.update();
    }
    for(int i = 0; i < ps.size(); i++){
        ps[i].update();
        ps[i].updatePartSizeref(guiSize1);
        ps[i].updateLifedec(guiLife1);
    }
    for(unsigned int i = 0; i < ps.size(); i++){
        ofVec3f vert = mesh.getVertex(i);
        vert.x = ps[i].particles[0].pos.x;
        vert.y = ps[i].particles[0].pos.y;
        vert.z = ps[i].particles[0].pos.z;
        mesh.setVertex(i, vert);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    //myImage2.draw(0, 0);
    ofEnableBlendMode ( OF_BLENDMODE_ADD ) ;
    if(useKinect){
        for(int i = 0; i<ps.size(); i++){
            int ind = indices[i];
            if (myImage2.getColor(int(ind%640), int(ind/480)) == ofColor(255, 255, 255)) {
                ps[i].setEmitter(int(ind%640), int(ind/480));
                ps[i].setColor(gColor);
                mesh.setColor(i, gColor);
            }
            else{
                ps[i].setEmitter(int(ind%640+ofRandom(-4, 4)), int(ind/480 + ofRandom(-4, 4)));
                ps[i].setColor(ofColor(0));
                mesh.setColor(i, ofColor(0));
            }
            ps[i].draw();
        }
    }
    else{
        for(int i = 0; i<ps.size(); i++){
            ps[i].setEmitter(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
            ps[i].draw();
        }
    }
    //drawPointCloud();
    gui.draw();
    ofSetColor(255);
    ofDrawBitmapString("FPS: " + ofToString( ofGetFrameRate()), ofGetWidth()-100, 15);
    ofDrawBitmapString("Particulas: " + ofToString(ps.size()), ofGetWidth()-200, 30);
    ofDrawBitmapString("Num Pixels: " + ofToString(indices.size()), ofGetWidth()-200, 45);
    ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::drawPointCloud() {
    meshPoints = mesh.getNumVertices();
    glPointSize(20);
    ofEnableAlphaBlending();
    ofEnablePointSprites();
    spriteImg.getTexture().bind();
    mesh.drawVertices();
    ofDisablePointSprites();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case '1':
            changeColor(ofColor(255));
            break;
        case '2':
            changeColor(ofColor(255, 180, 0));
            break;
        case '3':
            changeColor(ofColor(15, 80, 255));
            break;
        case '4':
            changeColor(ofColor(100, 100, 100));
            break;
        default:
            break;
    }
    
}


//--------------------------------------------------------------
void ofApp::changeColor(ofColor col){
    gColor = col;
//    for(unsigned int i = 0; i < ps.size(); i++){
//        ps[i].setColor(col);
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}