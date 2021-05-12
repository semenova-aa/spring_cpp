
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "MovingPaddle.h"
#include "Intersection.h"

using namespace std;
using namespace sf;

void testCollision(MovingPaddle& mPaddle, Ball& mBall) {
	if (!isIntersecting(mPaddle, mBall))
		return;
    mPaddle.destroyed = true;
	mBall.velocity.y = -ballVelocity;
	if (mBall.x() < mPaddle.x())
		mBall.velocity.x = -ballVelocity;
	else
		mBall.velocity.x = ballVelocity;
}