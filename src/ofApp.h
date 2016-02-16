#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "ofxGui.h"
#include "ofxOpenNI.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void drawPointCloud();
    void resetParticles();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOpenNIContext                niContext;
    ofxDepthGenerator               niDepthGenerator;
    ofxImageGenerator               niImageGenerator;
    ofxUserGenerator                niUserGenerator;
    ofPixels userpixels;
    
    void trackUser();
    
    void changeColor(ofColor col);
    ofImage myImage;
    ofImage myImage2;
    ofEasyCam                cam;
    
    ofMesh mesh;
    ofImage spriteImg;
    
    int meshPoints;
    int userPixels;
    ParticleSystem* ps1;
    vector <ParticleSystem> ps;
    vector <int> indices;
    
    ofxPanel gui;
    ofxIntSlider guiLife1;
    ofxIntSlider guiSize1;
    ofxIntSlider guiLife2;
    ofxIntSlider guiSize2;

};