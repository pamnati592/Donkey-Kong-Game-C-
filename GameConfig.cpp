#include "GameConfig.h"

bool GameConfig::isValidKey(char ch) {
    switch (ch) {
    case static_cast<char>(eKeys::UP):
    case static_cast<char>(eKeys::DOWN):
    case static_cast<char>(eKeys::LEFT):
    case static_cast<char>(eKeys::RIGHT):
    case static_cast<char>(eKeys::STAY):
    case static_cast<char>(eKeys::ATTACK):
    case static_cast<char>(eKeys::ESC):
    case static_cast<char>(eKeys::START):
    case static_cast<char>(eKeys::STAGE):
    case static_cast<char>(eKeys::INST):
    case static_cast<char>(eKeys::EXIT):
        return true;
    default:
        return false;
    }
}
