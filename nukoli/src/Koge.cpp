#include "Koge.h"

bool isKeyPressed(Key keyToCheck) {

    sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(keyToCheck);
    if (sf::Keyboard::isKeyPressed(key)) {
        return true;
    }
    else {
        return false;
    }

}