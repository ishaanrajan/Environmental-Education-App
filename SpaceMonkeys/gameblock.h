#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

#include <QListWidgetItem>

class GameBlock : public QListWidgetItem
{
public:
    GameBlock();

    std::string type;

    int enviornment;
    int food;
    int energy;
    int ammenity;
    int housing;

    void setType(std::string name);
    std::string getType();
};

#endif // GAMEBLOCK_H
