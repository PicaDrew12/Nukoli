#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint> // Required for std::uint8_t
#include <optional>
#include "Color.h"
#include "Game.h"
#include "Global.h"
#include "Koge.h"
#include "Rendering.h"
#include "Saisa.h"
#include "Maisi.h"


void init();
void run(Game& game);

