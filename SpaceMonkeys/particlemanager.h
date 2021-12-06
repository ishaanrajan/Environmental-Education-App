#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "gamedata.h"
#include "box2d/box2d.h"
#include <vector>
#include <QGraphicsScene>
#include <map>
#include <QTimer>

// Perhaps we can replace this with tighter integration with the model
// Not sure what that is going to look like yet so this is the temp solution
struct ParticleSpawner{
    b2Vec2 pos;
    int quantity; //TODO: decide what this means/howto calculate
    data::Demands type;
    int spawnDelay = 0; // how many ticks between spawns
    int spawnsRemaining = 0; //how many spawns left at this delay
};

struct Particle{
    b2Body* body;
    data::Demands type;
    // in ticks!
    int lifetime = 0;
};

class ParticleManager
{

public:
    ParticleManager();

    QGraphicsScene& getScene();

    void simulate();

    void stopSimulate();

    /**
     * @brief Set the desired amount of time a particle will be alive for (IE, desired to reach its attractor)
     * @param desired
     */
    void setDesiredTTL(int desired);
    /**
     * @brief Set the max amount of time a particle will live for
     * @param max
     */
    void setMaxTTL(int max);

    void setWindVec(float x, float y);

    void addSpawner(data::Demands type, int x, int y, int quantity);

    void setAttractionPoint(data::Demands type, int x, int y);

//    /**
//     * @brief Sets the rectangle that the given demand should be attracted to
//     *
//     * Will cause generated particles for that demand to float towards that point
//     * @param demand
//     * @param x
//     * @param y
//     */
//    void setAttractionBound(data::Demands demand, int x, int y, int w, int h);

    //TODO: some good way of determining
//    /**
//     * @brief Adds a position that particles should spawn from
//     * @param demand
//     * @param x
//     * @param y
//     */
//    void setParticleSpawnPoint(data::Demands demand, int x, int y, int magnitude);

    /**
     * @brief Perform end-of-round particle spawning
     * Particles will follow maximum/desired TTL as defined by the user
     */
    void spawnParticles(/*data?*/);


private:
    bool simulating = false;
    long elapsedSimTicks = 0;
    float timestep = 1.0f/30.0f;

    QGraphicsScene particleScene;
    QTimer* timer;

    //in ms
    //defines about what time we want the particles to reach the attraction bound and despawn
    //controls the strength of the attractive force to try to satisfy this TTL
    int desiredTtl = 5000;
    //in ms
    //maximum amount of time that a particle will live before being forcibly despawned
    int maxTtl = 10000;
    // Radius of particle spawning zone
    int spawnRadius = 5;

    std::vector<ParticleSpawner> spawners;

    b2World* world;
    b2BodyDef particleBodyDef;
    b2CircleShape circle;
    b2FixtureDef fixtureDef;
    b2Vec2 wind = {60.0f, 80.0f}; //TODO: configure

    std::vector<Particle> particles;
    std::map<data::Demands, b2Vec2> demandAttractors;


    /**
     * @brief Performs one tick of updating
     */
    void update();

    void timerTick();
};

#endif // PARTICLEMANAGER_H
