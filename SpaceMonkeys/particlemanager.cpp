#include "particlemanager.h"
#include <random>
#include <QObject>
#include <QTimer>
#include <box2d/box2d.h>


#include <iostream>

using data::Demands;

ParticleManager::ParticleManager()
{
    timer = new QTimer();

    world = new b2World(wind);

    // Configure body def
    particleBodyDef.type = b2_dynamicBody;
    particleBodyDef.fixedRotation = true;
    particleBodyDef.position.Set(0.0f, 0.0f);

    // Configure fixture def
    circle.m_radius = 0.5f;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;

    QObject::connect(timer, &QTimer::timeout, [this](){
        timerTick();
    });
}

QGraphicsScene &ParticleManager::getScene()
{
    return particleScene;
}

void ParticleManager::timerTick()
{
    elapsedSimTicks++;
    spawnParticles();
    //update(); //temp disable to test without attractors
    world->Step(timestep, 2, 1);
    world->ClearForces();

    // Update scene
    particleScene.clear();
    for(b2Body* b = world->GetBodyList(); b; b = b->GetNext()){
        particleScene.addRect(b->GetPosition().x,b->GetPosition().y, 4, 4, QColor(100, 100, 100, 175), QColor(100, 100, 100, 175));
    }

    particleScene.addEllipse(demandAttractors[Demands::CLIMATE].x, demandAttractors[Demands::CLIMATE].y, 5, 5, QColor(255, 0, 0, 255), QColor(255, 0, 0, 255));

    particleScene.update();
}

void ParticleManager::simulate()
{
    //must stop simulation before add/retrieve
        //check flag; if simulating, prevent call
    simulating = true;
    elapsedSimTicks = 0;

    timer->start(timestep);
}

void ParticleManager::stopSimulate()
{
    timer->stop();
    simulating = false;
    //TODO: clear everything
        //delete all particles
        //reset remaining spawns
    //etc
}

void ParticleManager::setWindVec(float x, float y)
{
    wind.Set(x, y);
    world->SetGravity(wind);
}

void ParticleManager::addSpawner(data::Demands type, int x, int y, int quantity)
{
    if(!simulating){
        ParticleSpawner spawner;
        spawner.pos = b2Vec2(x, y);
        spawner.quantity = quantity;
        //TODO: setup spawnsRemaining and spawnDelay for all by some calculation (?)
        spawner.spawnDelay = 25; //temp
        spawner.spawnsRemaining = 20;
        spawner.type = type;

        spawners.push_back(spawner);
    }
}

void ParticleManager::setAttractionPoint(data::Demands type, int x, int y)
{
    if(!simulating){
        demandAttractors[type] = b2Vec2(x,y);
    }
}

void ParticleManager::spawnParticles()
{
    for(ParticleSpawner& spawner : spawners){
        if(spawner.spawnsRemaining < 1 || elapsedSimTicks % spawner.spawnDelay != 0){
            continue;
        }
        spawner.spawnsRemaining--;
        std::cout << spawner.spawnsRemaining << std::endl;

        // Spawn 'quantity' particles
        for(int i = 0; i < spawner.quantity; i++){
            Particle p;
            p.type = spawner.type;
            p.body = world->CreateBody(&particleBodyDef);
            p.body->CreateFixture(&fixtureDef);

            double randMin = -spawnRadius;
            double randMax = spawnRadius;

            // Spawn in radius around desired position
            double randX = spawner.pos.x + randMin + ((double)rand() / RAND_MAX) * (randMax - randMin);
            double randY = spawner.pos.y + randMin + ((double)rand() / RAND_MAX) * (randMax - randMin);

            b2Vec2 spawnPos(randX,randY);

            p.body->SetTransform(spawnPos, 0.0f);
            // Only smoke should have gravity
            if(spawner.type != Demands::CLIMATE){
                p.body->SetGravityScale(0.0f);
            }

            // Add particle to list of particles
            particles.push_back(p);
        }
    }
}

void ParticleManager::update()
{

    //TODO: create remove queue and pop them all if lifetime > maxTTL

    // This approximation sucks. Try something better

    // Apply attracting force to relevant particles
    for(Particle& particle : particles){
        b2Vec2& attractorPos = demandAttractors[particle.type];

        // apply a force to the particle to move it towards its attractor
        b2Vec2 deltaX = attractorPos - particle.body->GetPosition();
        float deltaT = (float)(desiredTtl - particle.lifetime)/1000.0f;
        b2Vec2 currV = particle.body->GetLinearVelocity();
        b2Vec2 nextV = deltaX;
        nextV *= 1.0f/deltaT;

        b2Vec2 accel = nextV - currV;
        b2Vec2 attractForce = accel; //m = 1, so ma = a

        particle.body->ApplyForceToCenter(attractForce, true);

        particle.lifetime++;
    }
}


