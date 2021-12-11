#include "particlemanager.h"
#include <random>
#include <QObject>
#include <QTimer>
#include <box2d/box2d.h>
#include <vector>
#include <QGraphicsRectItem>
#include <QDebug>
#include <iostream>

using data::Demands;
using std::vector;

ParticleManager::ParticleManager(QObject * parent)
{
    timer = new QTimer();

    world = new b2World(wind);
    // Configure body def
    particleBodyDef.type = b2_dynamicBody;
    particleBodyDef.fixedRotation = true;
    particleBodyDef.position.Set(0.0f, 0.0f);
    particleBodyDef.linearDamping = 0.0f;

    // Configure fixture def
    circle.m_radius = 2.0f;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.1f;
    fixtureDef.restitution = 1.0f;

    // Init colors
    demandColors[data::Demands::CLIMATE] = QColor(100,100,100,175);
    demandColors[data::Demands::FOOD] = QColor(0,175,0,255);
    demandColors[data::Demands::HOUSING] = QColor(0,0,175,255);
    demandColors[data::Demands::AMMENITIES] = QColor(175,0,175,255);
    demandColors[data::Demands::ENERGY] = QColor(0,175,175,255);

    // Init spawner templates
    spawnerTemplates["coalplant"] = {0, 0, 0, 4, 2};
    spawnerTemplates["factory2"] = {0, 0, 0, 4, 2};
    spawnerTemplates["highdensityhousing"] = {0, 2, 0, 1, 0};
    spawnerTemplates["neighborhood"] = {0, 2, 0, 2, 0};
    spawnerTemplates["nuclear"] = {0, 0, 0, 1, 5};
    spawnerTemplates["solar"] = {0, 0, 0, 0, 2};
    spawnerTemplates["windfarm"] = {0, 0, 0, 0, 3};
    spawnerTemplates["drivein"] = {2, 2, 2, 2, 2};
    spawnerTemplates["stadium"] = {0,0,3,1,0};
    spawnerTemplates["park"] = {0,0,1,0,0};
    spawnerTemplates["cowfactory"] = {3,0,1,3,0};
    spawnerTemplates["plantFarm"] = {2,0,0,0,0};

    tileOffsetMap["coalplant"] = {50,10};
    tileOffsetMap["factory2"] = {50,0};
    tileOffsetMap["highdensityhousing"] = {50,0};
    tileOffsetMap["neighborhood"] = {50,50};
    tileOffsetMap["nuclear"] = {50,30};
    tileOffsetMap["solar"] = {50,60};
    tileOffsetMap["windfarm"] = {50,10};
    tileOffsetMap["drivein"] = {50,50};
    tileOffsetMap["stadium"] = {50,35};
    tileOffsetMap["park"] = {50,50};
    tileOffsetMap["cowfactory"] = {50,45};
    tileOffsetMap["plantFarm"] = {50,50};

    totalSpawns = {0,0,0,0,0};
    receivedSpawns = {0,0,0,0,0};

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
    update();
    world->Step(timestep, 1, 1);
    world->ClearForces();
    // Box2D is evidently actually super fast, the problem is drawing to the screen which takes forever with a lot of particles
    if(elapsedSimTicks % 2 == 0){
        updateScene();
    }

    // Occasionally notify what current proportions are
    if(elapsedSimTicks % 5 == 0){
        vector<float> percentages;
        for(int i = 0; i < (int)totalSpawns.size(); i++){
            percentages.push_back(totalSpawns[i] > 0 ? ((float)receivedSpawns[i])/totalSpawns[i] : 0);
        }
        emit particlesReached(percentages);
    }
}

void ParticleManager::updateScene()
{

    particleScene.clear();
    for(size_t i = 0; i < particles.size(); i++){
        Particle& particle = particles[i];
        QColor& color = demandColors[particle.type];

        float buffer = 15.0f;
        // If out of bounds, don't draw
        // Necessary due to QGraphicsScene slowness when drawing out of bounds
        if(particle.body->GetPosition().x + buffer > particleScene.width()
                || particle.body->GetPosition().x - buffer < 0
                || particle.body->GetPosition().y + buffer > particleScene.height()
                || particle.body->GetPosition().y - buffer < 0){
            continue;
        }

        // Draw appropriate particle shape
        if(particle.type != data::CLIMATE){
            particleScene.addEllipse(particle.body->GetPosition().x, particle.body->GetPosition().y, 6, 6, color, color);
        } else {
            particleScene.addRect(particle.body->GetPosition().x, particle.body->GetPosition().y, particle.randSize, particle.randSize, color, color);
        }
    }

    // DEBUG: Attraction draw
//    particleScene.addEllipse(demandAttractors[Demands::CLIMATE].attractionPoint.x, demandAttractors[Demands::CLIMATE].attractionPoint.y, 5, 5, QColor(255, 0, 0, 255), QColor(255, 0, 0, 255));
//    particleScene.addRect(demandAttractors[Demands::FOOD].attractionPoint.x, demandAttractors[Demands::FOOD].attractionPoint.y, 5, 5, QColor(255, 0, 0, 255), QColor(0, 255, 0, 255));
//    particleScene.addRect(demandAttractors[Demands::HOUSING].attractionPoint.x, demandAttractors[Demands::HOUSING].attractionPoint.y, 5, 5, QColor(255, 0, 0, 255), QColor(0, 0, 255, 255));
//    particleScene.addRect(demandAttractors[Demands::AMMENITIES].attractionPoint.x, demandAttractors[Demands::AMMENITIES].attractionPoint.y, 5, 5, QColor(255, 0, 0, 255), QColor(255, 0, 255, 255));
//    particleScene.addRect(demandAttractors[Demands::ENERGY].attractionPoint.x, demandAttractors[Demands::ENERGY].attractionPoint.y, 5, 5, QColor(255, 0, 0, 255), QColor(0, 255, 255, 255));

    particleScene.update();
}

bool ParticleManager::hitAttractor(Particle &particle)
{
    AttractorRect& rect = demandAttractors[particle.type];

    float x = particle.body->GetPosition().x;
    float y = particle.body->GetPosition().y;

    return rect.x <= x
            && x <= rect.x+rect.w
            && rect.y <= y
            && y <= rect.y+rect.h;
}

void ParticleManager::simulate()
{
    simulating = true;
    elapsedSimTicks = 0;

    timer->start(timestep*50);
}

void ParticleManager::resetSim()
{
    timer->stop();

    // Clear all
    particleScene.clear();
    delete world;
    spawners.clear();
    particles.clear();
    totalSpawns = {0,0,0,0,0};
    receivedSpawns = {0,0,0,0,0};
    world = new b2World(wind);
    elapsedSimTicks = 0;

    simulating = false;
}

void ParticleManager::gridParams(int startX, int startY, int gridWidth, int gridSpacing)
{
    gridStart = {startX, startY};
    gridTileWidth = gridWidth;
    gridTileSpacing = gridSpacing;
}

void ParticleManager::setWindVec(float x, float y)
{
    wind.Set(x, y);
    world->SetGravity(wind);
}

void ParticleManager::addSpawner(data::Demands type, int x, int y, int quantity)
{
    ParticleSpawner spawner;
    spawner.pos = b2Vec2(x, y);
    spawner.quantity = quantity;
    spawner.type = type;

    if(!simulating){
        switch(type){
        case data::FOOD:
        case data::HOUSING:
        case data::AMMENITIES:
        case data::ENERGY:
            spawner.spawnDelay = 30;
            spawner.spawnsRemaining = 4;
            break;
        case data::CLIMATE:
            spawner.spawnDelay = 40;
            spawner.spawnsRemaining = 15;
            break;
        }
        totalSpawns[type] += spawner.spawnsRemaining * quantity;
        spawners.push_back(spawner);
    }
}

void ParticleManager::setAttractionBound(data::Demands demand, float x, float y, float w, float h)
{
    if(!simulating){
        b2Vec2 center(x+w/2, y+h/2);
        AttractorRect r;
        r.attractionPoint = center;
        r.x = x;
        r.y = y;
        r.w = w;
        r.h = h;
        demandAttractors[demand] = r;
    }
}

void ParticleManager::spawnParticles()
{
    for(ParticleSpawner& spawner : spawners){
        if(spawner.spawnsRemaining < 1 || elapsedSimTicks % spawner.spawnDelay != 0){
            continue;
        }
        spawner.spawnsRemaining--;

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

void ParticleManager::addTile(std::string buildingType, int gridX, int gridY)
{
    int x = gridStart.x() + (gridTileWidth + gridTileSpacing) * (gridX - 1);
    int y = gridStart.y() + (gridTileWidth + gridTileSpacing) * (gridY - 1);
    vector<int> prodVals = spawnerTemplates[buildingType];
    for(int demand = 0; demand < prodVals.size(); demand++){
        QVector2D& offset = tileOffsetMap[buildingType];
        if(prodVals[demand] != 0){
            addSpawner(static_cast<data::Demands>(demand), x+offset.x(), y+offset.y(), prodVals[demand]);
        }
    }
}

void ParticleManager::update()
{
    vector<size_t> deleteParticles;

    // Apply attracting force to relevant particles
    for(size_t i = 0; i < particles.size(); i++){
        Particle& particle = particles[i];
        if(((float)particle.lifetime * timestep * 1000.0f) > maxTtl){// || hitAttractor(particle)){
            // Delete this particle
            deleteParticles.push_back(i);
            continue;
        }

        b2Vec2& attractorPos = demandAttractors[particle.type].attractionPoint;

        // apply a force to the particle to move it towards its attractor
        b2Vec2 deltaX = attractorPos - particle.body->GetPosition();

        //int ttl = particle.type == data::Demands::CLIMATE ? desiredTtl : (desiredTtl / 2);
        //in s
        float deltaT = abs(((float)desiredTtl/1000.0f - particle.lifetime*timestep));

        //if deltaT is near 0, it should be inside the bar, so delete
        // prevent blowback, but blowback looks cool
//        if(abs(deltaT) < timestep){
//            //particle.body->GetFixtureList()->SetSensor(true);

//            deleteParticles.push_back(i);
//            continue;
//        }

        // Count particles when received
        if(hitAttractor(particle) && !particle.received){
            receivedSpawns[particle.type]++;
            particle.received = true;
            //qDebug() << particle.type << " " << receivedSpawns[particle.type] << "/" << totalSpawns[particle.type];
        }

        b2Vec2 currV = particle.body->GetLinearVelocity();
        b2Vec2 nextV = deltaX;
        nextV *= 1.0f/deltaT;

        b2Vec2 accel = nextV;// - currV;
        b2Vec2 attractForce = accel; //m = 1, so ma = a

        //particle.body->ApplyForceToCenter(attractForce, true);
        particle.body->ApplyLinearImpulseToCenter(attractForce, true);

//        deltaX.Normalize();
//        float strength = 800.0f;//particle.type == data::Demands::CLIMATE ? 400.0f : 5000000.0f;
//        deltaX *= strength;

//        //particle.body->ApplyForceToCenter(deltaX, true);
//        particle.body->ApplyLinearImpulseToCenter(deltaX, true);

        particle.lifetime++;
    }

    for(size_t del : deleteParticles){
//        world->DestroyBody(particles[del].body);
        // Move to end and pop for efficient removal
        std::swap(particles[del], particles.back());
        particles.pop_back();
    }
}


