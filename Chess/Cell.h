#include <SFML/Graphics.hpp>
using namespace sf;


class Cell {
private:
	const Color black = Color(80, 80, 80);
	const Color white = Color(222, 222, 222);
	const Color green = Color(0, 100, 0, 80);
	bool backlight = 0;
	bool employment = 0;
	bool piece_color;
	RectangleShape *square = new RectangleShape(Vector2f(50, 50));
	Color actuality_color;
public:
	Cell() { ; }

	RectangleShape *get_square() {
		return this->square;
	}

	Color get_black() {
		return this->black;
	}
	Color get_white() {
		return this->white;
	}
	Color get_green() {
		return this->green;
	}

	Color get_actuality_color() {
		return this->actuality_color;
	}
	void set_actuality_color(Color _new_color) {
		this->actuality_color = _new_color;
	}
	void change_actualite_color(Cell *_obj) {
		_obj->actuality_color = _obj->green;
	}
	void set_position(float _x, float _y) {
		this->square->setPosition(_x, _y);
	}
	void on_backlight() {
		this->backlight = 1;
	}
	void off_backlight() {
		this->backlight = 0;
	}
	bool get_backlight() {
		return this->backlight;
	}
	void cell_employment(bool _i) {

		this->employment = 1;
		this->piece_color = _i;
	}
	void cell_free() {
		this->employment = 0;
	}
	bool get_employment() {
		return this->employment;
	}
	bool get_piece_color() {
		return this->piece_color;
	}
	void set_employment(bool _i) {
		this->employment = _i;
	}
	void set_piece_color(bool _i) {
		this->piece_color = _i;
	}

	Cell operator = (Cell _obj) {
		this->backlight = _obj.backlight;
		this->employment = _obj.employment;
		this->piece_color = _obj.piece_color;
		this->square = _obj.square;
		this->actuality_color = _obj.actuality_color;
	}
};