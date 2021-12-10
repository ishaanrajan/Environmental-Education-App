#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "gamedata.h"
#include "box2d/box2d.h"
#include <vector>
#include <QGraphicsScene>
#include <map>
#include <QTimer>
#include <QAbstractGraphicsShapeItem>
#include <QVector2D>

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
    int randSize = 4 + ( std::rand() % ( 12 - 4 + 1 ) );
};

struct AttractorRect{
    b2Vec2 attractionPoint;
    float x;
    float y;
    float w;
    float h;

    //AttractorRect(b2Vec2 p, float x, float y, float w, float h) : attractionPoint(p), x(x), y(y), w(w), h(h){}
};

class ParticleManager
{

public:
    ParticleManager();

    QGraphicsScene& getScene();

    void simulate();

    void resetSim();

    void gridParams(int startX, int startY, int gridWidth, int gridSpacing);

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

    /**
     * @brief Sets the rectangle that the given demand should be attracted to
     *
     * Will cause generated particles for that demand to float towards that point
     * @param demand
     * @param x
     * @param y
     */
    void setAttractionBound(data::Demands demand, float x, float y, float w, float h);

    /**
     * @brief Perform end-of-round particle spawning
     * Particles will follow maximum/desired TTL as defined by the user
     */
    void spawnParticles();

    void addTile(std::string buildingType, /*std::vector<int> costs,*/ int gridX, int gridY);

private:
    bool simulating = false;
    long elapsedSimTicks = 0;
    // Simulation timestep
    float timestep = 1.0f/30.0f;

    // Scene that particles are drawn to
    QGraphicsScene particleScene;
    QTimer* timer;

    // In ms
    // Defines about what time we want the particles to reach the attraction bound and despawn
    // Controls the strength of the attractive force to try to satisfy this TTL
    int desiredTtl = 5000;
    // In ms
    // Maximum amount of time that a particle will live before being forcibly despawned
    int maxTtl = 30000;
    // Radius of particle spawning zone
    int spawnRadius = 15;

    QPoint gridStart;
    int gridTileWidth;
    int gridTileSpacing;

    std::vector<ParticleSpawner> spawners;

    // Box2D vars
    b2World* world;
    b2BodyDef particleBodyDef;
    b2CircleShape circle;
    b2FixtureDef fixtureDef;
    b2Vec2 wind = {400.0f, -20.0f};

    std::vector<Particle> particles;
    std::map<data::Demands, AttractorRect> demandAttractors;
    std::map<data::Demands, QColor> demandColors;

    // TODO: we should unify the process from city --> here
    // For now, simply using vector indexed on the Demand for the impact it has
    std::map<std::string, std::vector<int>> spawnerTemplates;
    std::map<std::string, QVector2D> tileOffsetMap;


    /**
     * @brief Performs one tick of updating
     */
    void update();

    void timerTick();
    void updateScene();

    inline bool hitAttractor(Particle& particle);
};

#endif // PARTICLEMANAGER_H
