#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "CollBallPaddle.h"
#include "CollBallBrick.h"

using namespace std;
using namespace sf;

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

int main() {
	//создадим шар расположенный в середине
	Ball ball{ windowWidth / 2, windowHeight / 2 };
	Paddle paddle{ windowWidth / 2, windowHeight - 50 };
	vector<Brick> bricks;
	for (int iX = 0; iX < countBlocksX; ++iX)
		for (int iY = 0; iY < countBlocksY; ++iY)
			bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
	RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
	window.setFramerateLimit(60);

	//—чет 
	int score = 0;
	Font arial;
	arial.loadFromFile("arial.ttf");
	ostringstream ssScore;
	ssScore << "Score: " << score;

	Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 10, 560 });
	lblScore.setFont(arial);
	lblScore.setString(ssScore.str());

	while (true) {
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			break;

		//каждую итерацию обновл€ем информацию о шаре
		ball.update();
		paddle.update();
		testCollision(paddle, ball);

		for (auto& brick : bricks) testCollision(brick, ball);
		bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick) { return mBrick.destroyed;}), end(bricks));

		for (auto& brick : bricks)
			if (brick.destroyed) {
				score += 5;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore);
			}

		//выводим его на экран
		//window.draw(lblScore);
		window.draw(ball.shape);
		window.draw(paddle.shape);

		for (auto& brick : bricks)
			window.draw(brick.shape);
		window.display();
	}
	return 0;
}