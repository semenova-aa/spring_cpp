#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

using namespace std;
using namespace sf;


void testCollision(Paddle& mPaddle, Ball& mBall) {
	if (!isIntersecting(mPaddle, mBall))
		return;
	mBall.velocity.y = -ballVelocity;
	if (mBall.x() < mPaddle.x())
		mBall.velocity.x = -ballVelocity;
	else
		mBall.velocity.x = ballVelocity;
}