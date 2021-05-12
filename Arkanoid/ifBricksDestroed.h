#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include <iostream>

using namespace std;
using namespace sf;
int ifBricksDestr(vector<Brick> bricks,vector<Brick> bonusBricks,vector<Brick> speedBricks,
vector<Brick> fewHitBricks,vector<Brick> ballBricks,vector<Brick> paddleBricks) {
	int counter = 0;
	for (auto& brick : bricks)
		if (!brick.destroyed)
			counter++;
	for (auto& brick : bonusBricks)
		if (!brick.destroyed)
			counter++;
	for (auto& brick : speedBricks)
		if (!brick.destroyed)
			counter++;
	for (auto& brick : fewHitBricks)
		if (!brick.destroyed)
			counter++;
	for (auto& brick : ballBricks)
		if (!brick.destroyed)
			counter++;
	for (auto& brick : paddleBricks)
		if (!brick.destroyed)
			counter++;
	return counter;
}