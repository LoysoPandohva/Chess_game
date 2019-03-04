#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Mause_control {
private:
	Vector2i mause_position;
public:
	Vector2i get_mause_position() {
		return this->mause_position;
	}
	void set_mause_position(RenderWindow &_window) {
		this->mause_position = Mouse::getPosition(_window);
	}
	float get_x_position(RenderWindow &_window) {
		this->set_mause_position(_window);
		if (this->get_mause_position().x > 50 && this->get_mause_position().x <= 450) {
			cout << (float)this->get_mause_position().x << "  ";
			return (float)this->get_mause_position().x;
		}
		else {
			if (this->get_mause_position().x < 50) return 50;
			if (this->get_mause_position().x > 450) return 450;
		}
	}
	float get_y_position(RenderWindow &_window) {
		this->set_mause_position(_window);
		if (this->get_mause_position().y > 50 && this->get_mause_position().x <= 450) {
			cout << (float)this->get_mause_position().y << endl;
			return (float)this->get_mause_position().y;
		}
		else {
			if (this->get_mause_position().y < 50) return 50;
			if (this->get_mause_position().y > 450) return 450;
		}
	}
};