#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr float movingPaddleWidth{ 60.f }, movingPaddleHeight{ 20.f }, movingPaddleVelocity{ 6.f };

struct MovingPaddle {
	RectangleShape shape;
	Vector2f velocity;
	bool destroyed{ false };

	MovingPaddle(float mX, float mY) {
		shape.setPosition(mX, mY);
		shape.setSize({ movingPaddleWidth, movingPaddleHeight });
		shape.setFillColor(Color::White);
		shape.setOrigin(movingPaddleWidth / 2.f, movingPaddleHeight / 2.f);
	}

	void update() {
		shape.move(velocity);
		if (left() < 0)
			velocity.x = movingPaddleVelocity;
		else if (right() > windowWidth)
			velocity.x = -movingPaddleVelocity;
	
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
};
