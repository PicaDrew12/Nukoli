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
#include "Utils.h"
#include "Maisi.h"
#include "Debug.h"
#include "Map.h"


void init();
void exec(Game& game);
void run(Game& game);

