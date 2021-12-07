#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

#include <QListWidgetItem>

class GameBlock : public QListWidgetItem
{
public:
    GameBlock();

    char type;

    int enviornment;
    int food;
    int energy;
    int ammenity;
    int housing;
};

#endif // GAMEBLOCK_H
