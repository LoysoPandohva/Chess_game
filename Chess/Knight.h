#include <SFML/Graphics.hpp>
using namespace sf;

class Knight {
public:
	bool cell_employment(Pieces_on_board *_obj, int _x, int _y, int _ch) {
		if (_obj->get_board().get_all_squares(_x, _y).get_employment()) {
			if (_obj->get_board().get_all_squares(_x, _y).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
				_obj->get_board().get_all_squares(_x, _y).on_backlight();
			}	
			return 1;
		}
		return 0;
	}

	void knight_move(Pieces_on_board *_obj, int _x, int _y, int _ch, int _i, int _j) {
		bool can = 1;
		if (_i == 1) {
			if (_x + _i >= 8) {
				can = 0;
			}
		}
		if (_i == -1) {
			if (_x + _i <= -1) {
				can = 0;
			}
		}
		if (_j == -2) {
			if (_y + _j <= -1) {
				can = 0;
			}
		}
		if (_j == 2) {
			if (_y + _j >= 8) {
				can = 0;
			}
		}
		if (_i == 2) {
			if (_x + _i >= 8) {
				can = 0;
			}
		}
		if (_i == -2) {
			if (_x + _i <= -1) {
				can = 0;
			}
		}
		if (_j == -1) {
			if (_y + _j <= -1) {
				can = 0;
			}
		}
		if (_j == 1) {
			if (_y + _j >= 8) {
				can = 0;
			}
		}
		if (can) {
			if (cell_employment(_obj, _x + _i, _y + _j, _ch)) {
				can = 0;
			}
		}
		if (can) {
			_obj->get_board().get_all_squares(_x + _i, _y + _j).on_backlight();
		}
	}

	void opportunity_to_move(Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_life() == 1) {
			if (_obj->get_pieces(_ch)->get_select() == 1) {
				if (_obj->get_pieces(_ch)->get_name_piece() == 2) {
					int i = _obj->get_pieces(_ch)->get_x();
					int j = _obj->get_pieces(_ch)->get_y();
					knight_move(_obj, i, j, _ch, 1, 2);
					knight_move(_obj, i, j, _ch, 2, 1);
					knight_move(_obj, i, j, _ch, -1, 2);
					knight_move(_obj, i, j, _ch, -2, 1);
					knight_move(_obj, i, j, _ch, 1, -2);
					knight_move(_obj, i, j, _ch, 2, -1);
					knight_move(_obj, i, j, _ch, -1, -2);
					knight_move(_obj, i, j, _ch, -2, -1);
				}
			}
		}
	}
};