#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
using namespace sf;

class Dangmen_eggs {
private:
	bool start = 0;
	Texture texture;
	Sprite sprite;
	float speed = 2;
	int sum = 0;
	int health = 100;
	vector <char> s;
public:
	Texture get_texture() {
		return this->texture;
	}
	Sprite get_sprite() {
		return this->sprite;
	}

	void move_hero(RenderWindow &_window) {
		float speed = 2;
		if (Keyboard::isKeyPressed(Keyboard::LShift)) { speed = 5; }
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			sprite.move(0, -speed);
			if (sprite.getPosition().y + 10 < 50) {
				sprite.move(0, speed);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			sprite.move(speed, 0);
			if (sprite.getPosition().x + 40 > 450) {
				sprite.move(-speed, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			sprite.move(0, speed);
			if (sprite.getPosition().y + 40 > 450) {
				sprite.move(0, -speed);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			sprite.move(-speed, 0);
			if (sprite.getPosition().x + 10 < 50) {
				sprite.move(speed, 0);
			}
		}
	}

	bool dead(Pieces_on_board &_obj) {
		cout << (int)_obj.get_pieces(4)->get_x_position() - 10 << "    " << sprite.getPosition().x << endl;
		cout << (int)_obj.get_pieces(4)->get_y_position() - 1 << "    " << sprite.getPosition().y << endl;
		if (_obj.get_pieces(4)->get_x_position() + 10 <= sprite.getPosition().x + 25&&
			_obj.get_pieces(4)->get_x_position() + 40 >= sprite.getPosition().x + 25&&
			_obj.get_pieces(4)->get_y_position() + 10 <= sprite.getPosition().y + 25&&
			_obj.get_pieces(4)->get_y_position() + 40 >= sprite.getPosition().y + 25) {
			health = health - 5;
		}
		if (health < 0) {
			this->texture.loadFromFile("Images//Death.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(IntRect(0, 0, 64, 64));
			this->sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			cout << "DEATH!";
			return 0;
		}
		return 1;
	}

	bool find_egg(Event _event, Pieces_on_board &_obj, list <Game_moves> &_all_moves) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::D) {
				s.push_back('d');
			}
			if (_event.key.code == sf::Keyboard::A) {
				s.push_back('a');
			}
			if (_event.key.code == sf::Keyboard::N) {
				s.push_back('n');
			}
			if (_event.key.code == sf::Keyboard::G) {
				s.push_back('g');
			}
			if (_event.key.code == sf::Keyboard::M) {
				s.push_back('m');
			}
			if (_event.key.code == sf::Keyboard::E) {
				s.push_back('e');
			}
		}
		if (s.size() >= 7) {
			if (s[s.size() - 1] == 'n') {
				if (s[s.size() - 2] == 'e') {
					if (s[s.size() - 3] == 'm') {
						if (s[s.size() - 4] == 'g') {
							if (s[s.size() - 5] == 'n') {
								if (s[s.size() - 6] == 'a') {
									if (s[s.size() - 7] == 'd') {
										_all_moves.push_back(_obj);
										this->start = 1;
										return 1;
									}
								}
							}
						}
					}
				}
			}
		}
		return 0;
	}

	bool you_find_it(RenderWindow &_window, Event _event, Pieces_on_board &_obj, list <Game_moves> &_all_moves) {
		if (start == 0) {
			find_egg(_event, _obj, _all_moves);
		}
		if (start == 1) {
			this->texture.loadFromFile("Images//Dangmen.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(IntRect(0, 0, 50, 50));
			this->sprite.setPosition(225, 225);
			int stop = 1;
			while (stop) {
				while (_window.pollEvent(_event)) {
					if (_event.type == Event::Closed)
						_window.close();
					if (_event.type == sf::Event::KeyPressed) {
						if (_event.key.code == sf::Keyboard::Space) {
							stop = 1;
						}
					}
				}
				for (int i = 0; i < _obj.get_size(); i++) {
					for (int i = 0; i < _obj.get_size(); i++) {
						float distance = sqrt(_obj.get_pieces(i)->get_x_position() * _obj.get_pieces(i)->get_x_position() + _obj.get_pieces(i)->get_y_position()*_obj.get_pieces(i)->get_y_position());
						float dx = (this->sprite.getPosition().x + 10 - _obj.get_pieces(i)->get_x_position()) / distance;
						float dy = (this->sprite.getPosition().y + 1 - _obj.get_pieces(i)->get_y_position()) / distance;
						_obj.get_pieces(i)->change_position(_obj.get_pieces(i)->get_x_position() + dx, _obj.get_pieces(i)->get_y_position() + dy);
					}
				}
				if (dead(_obj)) {
					move_hero(_window);
				}
				else return 0;
				_obj.draw_pieces(_window);
				_window.draw(this->sprite);
				_window.display();
			}
		}
		return 1;
	}
};