#include <SFML/Graphics.hpp>
using namespace sf;
#pragma warning(default:4716)

class Piece {
private:
	bool life;
	bool color;
	float x_fragment;//координаты нужной фигуры в спрайте по X(не изменяется)
	float y_fragment;//координаты нужной фигуры в спрайте по Y(не изменяется)
	float x_position;//координаты расположения фигуры по X
	float y_position;//координаты расположения фигуры по Y
	Texture texture;//(не изменяется, кроме пешек)
	Sprite sprite;//(не изменяетсяб кроме пешек)
	bool select = 0;
	int name_piece = 0;
	bool first_move = 1;

	bool first_shah = 1;
	int sum_shah = 0;
public:
	float get_x_fragment() {
		return this->x_fragment;
	}
	void set_x_fragment(float _x) {
		this->x_fragment = _x;
	}
	float get_y_fragment() {
		return this->y_fragment;
	}
	void set_y_fragment(float _y) {
		this->y_fragment = _y;
	}
	void set_color(bool _color) {
		this->color = _color;
	}
	Sprite get_sprite() {
		return this->sprite;
	}
	float get_x_position() {
		return this->x_position;
	}
	float get_y_position() {
		return this->y_position;
	}
	int get_x() {
		return (int)(this->get_x_position() - 10 - 50) / 50;
	}
	int get_y() {
		return (int)(this->get_y_position() - 1 - 50) / 50;
	}
	void select_piece() {//выбор фигуры
		this->select = 1;
	}
	void leave_piece() {
		this->select = 0;
	}
	bool get_select() {
		return this->select;
	}
	void set_sprite_position(float _x, float _y) {
		this->sprite.setPosition(_x, _y);
	}
	void change_position(float _x, float _y) {
		this->x_position = _x;
		this->y_position = _y;
		this->set_sprite_position(_x, _y);
	}
	bool get_color() {
		return this->color;
	}
	void dead_piece() {
		this->life = 0;
	}
	int get_name_piece() {
		return this->name_piece;
	}
	void set_name_piece(int _name_piece) {
		this->name_piece = _name_piece;
	}

	void set_sprite(Sprite _sprite) {
		this->sprite = _sprite;
	}
	bool get_first_move() {
		return this->first_move;
	}
	void make_the_first_move() {
		this->first_move = 0;
	}
	void make_first_shah() {
		this->first_shah = 0;
	}
	bool get_first_shah() {
		return this->first_shah;
	}
	void make_shah() {
		this->sum_shah = this->sum_shah + 1;
	}
	int get_sum_shah() {
		return this->sum_shah;
	}
	bool get_life() {
		return this->life;
	}

	void set_life(bool _i) {
		this->life = _i;
	}
	void set_first_move(bool _i) {
		this->first_move = _i;
	}
	void set_first_shah(bool _i) {
		this->first_shah = _i;
	}
	void set_sum_shah(int _i) {
		this->sum_shah = _i;
	}

	void promotion(int _i, int _color) {
		if (_color == 0) {
			switch (_i) {
			case 1:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(30, 0, 30, 48));
				break;
			case 2:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(60, 0, 30, 48));
				break;
			case 3:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(90, 0, 30, 48));
				break;
			case 4:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(120, 0, 30, 48));
				break;
			default:
				break;
			}
		}
		else {
			switch (_i) {
			case 1:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(120, 50, 30, 48));
				break;
			case 2:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(90, 50, 30, 48));
				break;
			case 3:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(60, 50, 30, 48));
				break;
			case 4:
				this->name_piece = _i;
				this->sprite.setTextureRect(IntRect(30, 50, 30, 48));
				break;
			default:
				break;
			}
		}
	}

	Piece() { ; }

	Piece(RenderWindow  &_window, float _x_fragment, float _y_fragment, float _x_position, float _y_position, bool _color, int _name_piece) {
		this->name_piece = _name_piece;
		this->select = 0;
		this->life = 1;
		this->color = _color;
		this->x_fragment = _x_fragment;
		this->y_fragment = _y_fragment;
		this->x_position = _x_position;
		this->y_position = _y_position;
		this->texture.loadFromFile("Images//Pieces.png");
		this->sprite.setTexture(texture);
		this->sprite.setTextureRect(IntRect(_x_fragment, _y_fragment, 30, 48));
		this->sprite.setPosition(_x_position, _y_position);
	}

	void draw_piece(RenderWindow  &_window) {
		if (this->get_life() != 0) {
		_window.draw(this->sprite);
		}
	}

	Piece operator = (Piece _obj) {
		this->name_piece = _obj.name_piece;
		this->select = _obj.select;
		this->color = _obj.color;
		this->x_fragment = _obj.x_fragment;
		this->y_fragment = _obj.y_fragment;
		this->x_position = _obj.x_position;
		this->y_position = _obj.y_position;
		this->texture.loadFromFile("Images//Pieces.png");
		this->sprite.setTexture(texture);
		this->sprite.setTextureRect(IntRect(x_fragment, y_fragment, 30, 48));
		this->sprite.setPosition(_obj.x_position, _obj.y_position);
	}

	Piece(const Piece &_obj) {
		this->name_piece = _obj.name_piece;
		this->select = _obj.select;
		this->color = _obj.color;
		this->x_fragment = _obj.x_fragment;
		this->y_fragment = _obj.y_fragment;
		this->x_position = _obj.x_position;
		this->y_position = _obj.y_position;
		this->texture.loadFromFile("Images//Pieces.png");
		this->sprite.setTexture(texture);
		this->sprite.setTextureRect(IntRect(x_fragment, y_fragment, 30, 48));
		this->sprite.setPosition(_obj.x_position, _obj.y_position);
	}
};