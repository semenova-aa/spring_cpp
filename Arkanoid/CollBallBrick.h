#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Brick.h"
#include "Intersection.h"

using namespace std;
using namespace sf;


void testCollision(Brick& mBrick, Ball& mBall) {
	if (!isIntersecting(mBrick, mBall))
		return;
	mBrick.destroyed = true;

	// в этой функции мы пытаемся как можно более естесвенно задать полет ударившегося шарика

		//тут мы считаем насколько сильно шарик перешел границу с каждой стороны
	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };
	//проверяем окуда "заезд" больше слева или справа и сверху или снизу
	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
	//возвращается то значение, откуда "заезд" больше 
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };
	//провераем где "заезд" шара сильнее по абсциссе или по ординате и меняем его направление 
	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}