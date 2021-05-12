#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 600 };

int main() {
	RenderWindow window{ {windowWidth,windowHeight}, "Arkanoid" };
	window.setFramerateLimit(60);

	while (true) {
		//очищает окно от оставшихся графических штук
		window.clear(Color::Black);

		//если нажали esc выходим из цикла
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			break;

		//показывает содержимое окна 
		window.display();
	}
	return 0;
}
