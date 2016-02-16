#include "ParticleSystem.h"

//------------------------------------------------------------------
ParticleSystem::ParticleSystem(int n){
    nParticles = n;
    particles.assign(nParticles, Particle());
}

//------------------------------------------------------------------
ParticleSystem::ParticleSystem(int n, float ld){
    nParticles = n;
    particles.assign(nParticles, Particle(ld));
}

//------------------------------------------------------------------
void ParticleSystem::update(){
    for(int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
}

//------------------------------------------------------------------
void ParticleSystem::updateLifedec(float ld){
    for(int i = 0; i < particles.size(); i++){
        particles[i].updateLifedec(ld);
    }
}

//------------------------------------------------------------------
void ParticleSystem::updatePartSizeref(float ps){
    for(int i = 0; i < particles.size(); i++){
        particles[i].updatePartSizeref(ps);
    }
}

//------------------------------------------------------------------
void ParticleSystem::setEmitter(float x, float y){
    for(int i = 0; i < particles.size(); i++){
        if(particles[i].isDead()){
            particles[i].rebirth(x, y);
        }
    }
}

//------------------------------------------------------------------
void ParticleSystem::setColor(ofColor col){
    if(col == ofColor(0)){
        for(int i = 0; i < particles.size(); i++){
            if(particles[i].lifespan<20){
                particles[i].setColor(col);
                particles[i].setbColor(col);
            }
        }
    }
    else{
        for(int i = 0; i < particles.size(); i++){
            
            particles[i].setColor(col);
            particles[i].setbColor(ofColor(255));

        }
    }
}


//------------------------------------------------------------------
void ParticleSystem::draw(){
    for(int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
}
