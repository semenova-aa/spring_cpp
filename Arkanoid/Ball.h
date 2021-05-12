#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 600 };
constexpr float ballRadius{ 10.f }, ballVelocity{ 6.f };

struct Ball {
	// CircleShape это класс, который задает отрисовываемый круг
	CircleShape shape;
	// вектор, хранящий инвормацию о скорости шара
	Vector2f velocity{ -ballVelocity, -ballVelocity };
	bool destroyed{ false };
	//создаем конструктор для нашего Шара
	//mX - начальная координата икс
	//mY - начальная координата игрек
	Ball(float mX, float mY) {
		// добавляем позицию, радиус, цвет и начало 
		//для CircleShape 'shape'
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::White);
		shape.setOrigin(ballRadius, ballRadius);
	}
	//обновляем шар: передвигая его относительно изменений его скорости
	void update() {
		shape.move(velocity);
		if (left() < 0)
			velocity.x = ballVelocity;
		else if (right() > windowWidth)
			velocity.x = -ballVelocity;
		if (top() < 0)
			velocity.y = ballVelocity;
		else if (bottom() > windowHeight) {
			velocity.y = -ballVelocity;
		}

	}
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }
};
