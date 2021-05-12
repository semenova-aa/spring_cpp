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

	// � ���� ������� �� �������� ��� ����� ����� ���������� ������ ����� ������������ ������

		//��� �� ������� ��������� ������ ����� ������� ������� � ������ �������
	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };
	//��������� ����� "�����" ������ ����� ��� ������ � ������ ��� �����
	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
	//������������ �� ��������, ������ "�����" ������ 
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };
	//��������� ��� "�����" ���� ������� �� �������� ��� �� �������� � ������ ��� ����������� 
	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}