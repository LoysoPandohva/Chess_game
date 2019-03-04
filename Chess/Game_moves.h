#include <SFML/Graphics.hpp>
#include <list>
#include "Pieces_on_board.h"
using namespace sf;

class Game_moves {
private:
	bool life[32];
	float x_position[32];
	float y_position[32];
	bool first_move[32];
	bool first_shah[32];
	int sum_shah[32];
	bool color[32];
	float x_fragment[32];
	float y_fragment[32];
	int name_piece[32];
	Sprite sprite[32];


	bool employment[8][8];
	bool piece_color[8][8];

	bool player;

public:
	Sprite get_sprite(int _i) {
		return this->sprite[_i];
	}
	int get_name_piece(int _i) {
		return this->name_piece[_i];
	}
	float get_x_fragment(int _i) {
		return this->x_fragment[_i];
	}
	float get_y_fragment(int _i) {
		return this->y_fragment[_i];
	}
	float get_x_position(int _i) {
		return this->x_position[_i];
	}
	float get_y_position(int _i) {
		return this->y_position[_i];
	}
	bool get_color(int _i) {
		return this->color[_i];
	}
	bool get_first_move(int _i) {
		return this->first_move[_i];
	}
	bool get_first_shah(int _i) {
		return this->first_shah[_i];
	}
	int get_sum_shah(int _i) {
		return this->sum_shah[_i];
	}
	bool get_life(int _i) {
		return this->life[_i];
	}

	Game_moves(Pieces_on_board _obj) {
		this->player = _obj.get_player();

		for (int i = 0; i < _obj.get_size(); i++) {
			this->life[i] = _obj.get_pieces(i)->get_life();
			this->x_position[i] = _obj.get_pieces(i)->get_x_position();
			this->y_position[i] = _obj.get_pieces(i)->get_y_position();
			this->first_move[i] = _obj.get_pieces(i)->get_first_move();
			this->first_shah[i] = _obj.get_pieces(i)->get_first_shah();
			this->sum_shah[i] = _obj.get_pieces(i)->get_sum_shah();
			this->color[i] = _obj.get_pieces(i)->get_color();
			this->x_fragment[i] = _obj.get_pieces(i)->get_x_fragment();
			this->y_fragment[i] = _obj.get_pieces(i)->get_y_fragment();
			this->name_piece[i] = _obj.get_pieces(i)->get_name_piece();
			this->sprite[i] = _obj.get_pieces(i)->get_sprite();
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				this->employment[i][j] = _obj.get_board().get_all_squares(i, j).get_employment();
				this->piece_color[i][j] = _obj.get_board().get_all_squares(i, j).get_piece_color();
			}
		}
	}

	bool delete_last_move(Pieces_on_board &_obj, list <Game_moves> &_all_moves) {
		if (_all_moves.size() != 1) {
			_all_moves.pop_back();
			for (int i = 0; i < _obj.get_size(); i++) {
				_obj.get_pieces(i)->set_life(_all_moves.back().get_life(i));
				_obj.get_pieces(i)->change_position(_all_moves.back().get_x_position(i), _all_moves.back().get_y_position(i));
				_obj.get_pieces(i)->set_first_move(_all_moves.back().get_first_move(i));
				_obj.get_pieces(i)->set_first_shah(_all_moves.back().get_first_shah(i));
				_obj.get_pieces(i)->set_sum_shah(_all_moves.back().get_sum_shah(i));
				_obj.get_pieces(i)->set_color(_all_moves.back().get_color(i));
				_obj.get_pieces(i)->set_x_fragment(_all_moves.back().get_x_fragment(i));
				_obj.get_pieces(i)->set_y_fragment(_all_moves.back().get_y_fragment(i));
				_obj.get_pieces(i)->set_name_piece(_all_moves.back().get_name_piece(i));
				_obj.get_pieces(i)->set_sprite(_all_moves.back().get_sprite(i));
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					_obj.get_board().get_all_squares(i, j).set_employment(_all_moves.back().employment[i][j]);
					_obj.get_board().get_all_squares(i, j).set_piece_color(_all_moves.back().piece_color[i][j]);
				}
			}
		}
		return 1;
	}
};