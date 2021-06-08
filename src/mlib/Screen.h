#ifndef SREEN_H_
#define SREEN_H_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Screen.h"
#include "ShowGrid.h"
#include "ShowPixel.h"
#include "UserButton.h"
#include "UserZone.h"
#include "logic.h"
#include "Settings.h"
#include <iostream>

void CloseWindow(sf::RenderWindow& window);

void Screen();

#endif