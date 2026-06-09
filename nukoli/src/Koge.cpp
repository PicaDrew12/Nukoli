#include "Koge.h"

 std::vector<Key> pressedKeys;
 std::vector<Key> pressedKeysLastFrame;
bool isKeyHeld(Key keyToCheck) {

    sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(keyToCheck);
    if (sf::Keyboard::isKeyPressed(key)) {
        return true;
    }
    else {
        return false;
    }

}

void poolKeys() {
    pressedKeysLastFrame.clear();
    pressedKeysLastFrame.swap(pressedKeys);
    for (int i = static_cast<int>(Key::A); i <= static_cast<int>(Key::Pause); i++) {
        Key k = static_cast<Key>(i);
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k))) {
            pressedKeys.push_back(k);
        }

    }
}

bool isKeyPressed(Key keyToCheck) {
    if (isKeyHeld(keyToCheck) && !(std::find(pressedKeysLastFrame.begin(), pressedKeysLastFrame.end(), keyToCheck) != pressedKeysLastFrame.end())) {
        return true;
    }
    else {
        return false;
    }
}

bool isKeyUp(Key keyToCheck) {
    return !isKeyHeld(keyToCheck);
}
bool isKeyReleased(Key keyToCheck) {
    if ((std::find(pressedKeysLastFrame.begin(), pressedKeysLastFrame.end(), keyToCheck) != pressedKeysLastFrame.end() && isKeyUp(keyToCheck))) {
        return true;
    }

    else {
        return false;
    }
    
}