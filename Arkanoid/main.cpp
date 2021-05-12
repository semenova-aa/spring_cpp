#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "CollBallBrick.h"
#include "CollBallPaddle.h"
#include "Intersection.h"
#include "MovingPaddle.h"
#include "CollMovPadWall.h"
#include "CollMovPadBall.h"
#include "ifBricksDestroed.h"
#include "iostream"

using namespace std;
using namespace sf;

int main() {
	//создадим шар расположенный в середине
	Ball ball{ windowWidth / 2, windowHeight / 2 };
	Paddle paddle{ windowWidth / 2, windowHeight - 50 };
	vector<Brick> bricks;
	vector<Brick> unbreakableBricks;
	vector<Brick> bonusBricks;
	vector<Ball> bonusBall;
	vector<Brick> speedBricks;
	vector<Brick> fewHitBricks;
	vector<int> hitCounter;
	vector<Brick> ballBricks;
	Ball newBall{ -windowWidth / 2, -windowHeight / 2 };
	vector<Brick> paddleBricks;
	MovingPaddle newPaddle{ -windowWidth / 2, -windowHeight / 2 };

	newBall.shape.setFillColor(Color::Red);
	int countUnb = -1, countBon = -1, countSp = -1,  stopSpeed = 0, countFH = -1, countNB = -1,  countPB = -1;
	int speedCheck = 0, newBallcheck = 0, newPaddlecheck = 0, collNewPad = 0;
	bool isSecondBallIn = false, isSecondPaddleIn = false;

	for (int iX = 0; iX < countBlocksX; ++iX)
		for (int iY = 0; iY < countBlocksY; ++iY) {
			int type = rand() % 7;
			switch (type) {
			case 0:
				bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				break;
			case 1:
				countUnb++;
				unbreakableBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				unbreakableBricks[countUnb].shape.setFillColor(Color::Red);
				break;
			
			case 2:
				countSp++;
				speedBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				speedBricks[countSp].shape.setFillColor(Color::Green);
				break;
			case 3:
				countBon++;	
				bonusBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
                bonusBall.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				bonusBall[countBon].shape.setFillColor(Color::Yellow);
				bonusBricks[countBon].shape.setFillColor(Color::Cyan);
				break;

			case 4:
				countFH++;
				fewHitBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				fewHitBricks[countFH].shape.setFillColor(Color::Magenta);
				hitCounter.push_back(2);
				break;

			case 5:
				countNB++;
				ballBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				ballBricks[countNB].shape.setFillColor(Color::Blue);
				break;
			case 6:
				countPB++;
				paddleBricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
				paddleBricks[countPB].shape.setFillColor(Color::White);
				break;
			}
		}

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
		int check = ifBricksDestr(bricks, bonusBricks, speedBricks, fewHitBricks, ballBricks, paddleBricks);
		if (check == 0) {
			window.clear(Color::Black);
			lblScore.setPosition({ windowWidth / 2, windowHeight / 2});
			ball.velocity.y = 0;
			ball.velocity.x = 0;
			if (score >= 0) {
				ssScore.str("");
				ssScore << "You won! Score: " << score;
				lblScore.setString(ssScore.str());
			}
			else {
				ssScore.str("");
				ssScore << "You lost! Score: " << score;
				lblScore.setString(ssScore.str());
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				break;
		}

		//каждую итерацию обновл€ем информацию о шаре
		if (speedCheck == 0)
			ball.update();
		else {
			ball.update();
			ball.update();
			stopSpeed++;
			if (stopSpeed >= 100) {
				speedCheck = 0;
				stopSpeed = 0;
			}
		}

		for (auto& ball : bonusBall) { 
			if (ball.destroyed) {
				ball.velocity.x = 0;
				ball.velocity.y = ballVelocity;
				ball.update();
			}
		}

		newBallcheck++;
		if (newBallcheck >= 500) {
			newBall.shape.setPosition(-windowWidth , -windowHeight);
			newBallcheck = 0;
			isSecondBallIn = false;
		}
		else
			if (isSecondBallIn)
				newBall.update();

		if (isSecondPaddleIn) {
				newPaddle.update();
				testCollision(newPaddle);				
		}
		paddle.update();
		testCollision(paddle, ball);
		testCollision(paddle, newBall);
		testCollision(newPaddle, ball);
		//удалем платформу с экрана и начисл€ем баллы, если о нее ударились 3 раза (любой из м€чей)
		if (newPaddle.destroyed) {
			if (collNewPad >= 3) {
				newPaddle.shape.setPosition(-windowWidth, -windowHeight);
				isSecondPaddleIn = false;
				collNewPad = 0;
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
			else 
				if (isSecondPaddleIn) {
					newPaddle.destroyed = false;
					collNewPad++;
				}
				
		}
		testCollision(newPaddle, newBall);
		if (newPaddle.destroyed) {
			if (collNewPad >= 3) {
				newPaddle.shape.setPosition(-windowWidth, -windowHeight);
				isSecondPaddleIn = false;
				collNewPad = 0;
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
			else 
				if (isSecondPaddleIn) {
					newPaddle.destroyed = false;
					collNewPad++;
			    }
		}
		//cтолкновение с обчным блоком
		for (auto& brick : bricks) {
			testCollision(brick, ball);
			testCollision(brick, newBall);
			if (brick.destroyed) {
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		//cтолкновение с создающим каретку блоком
		for (auto& brick : paddleBricks) {
			testCollision(brick, ball);
			testCollision(brick, newBall);
			if (brick.destroyed) {
				if (!isSecondPaddleIn) {
					newPaddle.shape.setPosition(windowWidth + 1, windowHeight - 150);
					isSecondPaddleIn = true;
				}
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		//cтолкновение с вызывающим шар блоком
		for (auto& brick : ballBricks) {
			testCollision(brick, ball);
			testCollision(brick, newBall);
			if (brick.destroyed) {
				if (!isSecondBallIn) {
					newBall.shape.setPosition(windowWidth / 2, windowHeight / 2);
					isSecondBallIn = true;
				}
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		//столкновение с несломаемым блоком
		for (auto& brick : unbreakableBricks) {
			testCollision(brick, ball);
			testCollision(brick, newBall);
		}

		//столкновение с ускор€ющим блоком
		for (auto& brick : speedBricks) {
			testCollision(brick, ball);
			testCollision(brick, newBall);
			if (brick.destroyed) {
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
				speedCheck = 1;
			}
		}
		//столкновение с несразу разбиваемым блоком
		for (int i = 0; i < size(fewHitBricks); i++) {
			testCollision(fewHitBricks[i], ball);
			testCollision(fewHitBricks[i], newBall);
			if (fewHitBricks[i].destroyed) {
				if (hitCounter[i] == 2) {
					fewHitBricks[i].destroyed = false;
					hitCounter[i]--;
				}
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		//столкновение с бонусным блоком
		for (int i = 0; i < size(bonusBricks); i++) {
			testCollision(bonusBricks[i], ball);
			testCollision(bonusBricks[i], newBall);
			if (bonusBricks[i].destroyed) {
				bonusBall[i].destroyed = true;
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
				//bonusBall[i].shape.setPosition(bonusBricks[i].x(),bonusBricks[i].y());
			}
		}
		//bonusBall.erase(remove_if(begin(bonusBall), end(bonusBall), [](const Ball& mBall) {return mBall.destroyed; }), end(bonusBall));
		bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(bricks));
		bonusBricks.erase(remove_if(begin(bonusBricks), end(bonusBricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(bonusBricks));
		speedBricks.erase(remove_if(begin(speedBricks), end(speedBricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(speedBricks));
		fewHitBricks.erase(remove_if(begin(fewHitBricks), end(fewHitBricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(fewHitBricks));
		ballBricks.erase(remove_if(begin(ballBricks), end(ballBricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(ballBricks));
		paddleBricks.erase(remove_if(begin(paddleBricks), end(paddleBricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(paddleBricks));
		
		//проверка нет ли удара о дно
		if (ball.bottom() >= windowHeight || newBall.bottom() >= windowHeight) {
			score -= 2;
			ssScore.str("");
			ssScore << "Score: " << score;
			lblScore.setString(ssScore.str());
		}

		for (auto& balls : bonusBall) {
			if (isIntersecting(balls, ball) && balls.y() > 150) {
				balls.shape.setPosition(-windowWidth, -windowHeight);
				bonusBall.erase(remove_if(begin(bonusBall), end(bonusBall), [](const Ball& mBall) {return mBall.destroyed; }), end(bonusBall));
				score += 2;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
			if (isIntersecting(balls, newBall) && balls.y() > 150) {
				balls.shape.setPosition(-windowWidth, -windowHeight);
				bonusBall.erase(remove_if(begin(bonusBall), end(bonusBall), [](const Ball& mBall) {return mBall.destroyed; }), end(bonusBall));
				score += 2;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		//выводим все на экран
		if (check > 0) {
			window.draw(lblScore);
			window.draw(ball.shape);
			window.draw(paddle.shape);
			window.draw(newBall.shape);
			window.draw(newPaddle.shape);
			for (auto& brick : bricks)
				window.draw(brick.shape);
			for (auto& brick : unbreakableBricks)
				window.draw(brick.shape);
			for (auto& brick : bonusBricks)
				window.draw(brick.shape);
			for (auto& brick : speedBricks)
				window.draw(brick.shape);
			for (auto& brick : fewHitBricks)
				window.draw(brick.shape);
			for (auto& brick : ballBricks)
				window.draw(brick.shape);
			for (auto& brick : paddleBricks)
				window.draw(brick.shape);
			for (auto& ball : bonusBall)
				window.draw(ball.shape);
			window.display();
		}
		else {
			window.draw(lblScore);
			window.display();
		}
			
	}
	return 0;
}