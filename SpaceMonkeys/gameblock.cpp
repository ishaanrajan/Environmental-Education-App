#include "gameblock.h"
#include <QListWidgetItem>

#include <iostream>

GameBlock::GameBlock() : QListWidgetItem()
{

}

void GameBlock::setType(std::string name)
{
    type = name;
}

std::string GameBlock::getType()
{
    return type;
}
