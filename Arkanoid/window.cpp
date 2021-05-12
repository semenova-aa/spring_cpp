#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 600 };

int main() {
	RenderWindow window{ {windowWidth,windowHeight}, "Arkanoid" };
	window.setFramerateLimit(60);

	while (true) {
		//������� ���� �� ���������� ����������� ����
		window.clear(Color::Black);

		//���� ������ esc ������� �� �����
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			break;

		//���������� ���������� ���� 
		window.display();
	}
	return 0;
}
