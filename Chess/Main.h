#include <SFML/Graphics.hpp>
using namespace sf;

class Main {
public:
	void text(RenderWindow &_window) {
		setlocale(LC_ALL, "rus");
		Font font;
		font.loadFromFile("Font//cour.ttf");
		Text *t[8];
		for (int i = 0; i < 8; i++) {
			t[i] = new Text("", font, 40);
			
		}
		t[0]->setString(L"Шахматы");
		t[1]->setString(L"Управление:");
		t[2]->setString(L"Вверх        - W");
		t[3]->setString(L"Вправо       - D");
		t[4]->setString(L"Вниз         - S");
		t[5]->setString(L"Влево        - A");
		t[6]->setString(L"Выбор фигуры - Space");
		t[7]->setString(L"Сделать ход  - Enter");

		RectangleShape *shape = new RectangleShape(Vector2f(480, 235));
		shape->setFillColor(Color(200, 200, 200));
		shape->setOutlineThickness(2);
		shape->setOutlineColor(sf::Color(0, 0, 0));
		shape->setPosition(10, 92);
		_window.draw(*shape);

		for (int i = 0; i < 8; i++) {
			t[i]->setPosition(10, i * 40);
			t[i]->setFillColor(Color::Black);
			if (i == 0) {
				t[i]->setPosition(155, i * 35);
				t[i]->setStyle(Text::Bold);
			}
			_window.draw(*t[i]);
		}
		Text start("", font, 20);
		start.setString(L"Для начала нажмите пробел");
		start.setPosition(90, 450);
		start.setFillColor(Color::Black);
		_window.draw(start);
	}

	void instruction(RenderWindow &_window, Event _event, int &_i) {		
		while (_i == 0) {
			while (_window.pollEvent(_event)) {
				if (_event.type == Event::Closed)
					_window.close();
				if (_event.type == sf::Event::KeyPressed) {
					if (_event.key.code == sf::Keyboard::Space) {
						_i = 1;
					}
				}
			}
			_window.clear(Color(200, 200, 200));
			text(_window);
			_window.display();
		}
	}

	void is_chekmate(RenderWindow &_window, Event _event, int _end) {
		Font font;
		font.loadFromFile("Font//cour.ttf");
		Text text("", font, 60);
		text.setFillColor(Color::Black);
		text.setPosition(65, 190);
		text.setStyle(Text::Bold);
		//while (_end != 0) {
			while (_window.pollEvent(_event)) {
				if (_event.type == sf::Event::KeyPressed) {
					if (_event.key.code == sf::Keyboard::Space) {
						_window.close();
					}
				}
			}
			//_window.clear(Color(200, 200, 200));			
			if (_end == 1) {
				text.setString("White lose");
			}
			if (_end == 2) {
				text.setString("Black lose");
			}
			_window.draw(text);
			//_window.display();
		//}
	}
};