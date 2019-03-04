#include <SFML/Graphics.hpp>
using namespace sf;

class Queen {
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

	bool queen_move(Pieces_on_board *_obj, int _x, int _y, int _ch, int _i, int _j) {
		if (_i > 0) {
			if (_x + _i >= 8) {
				return 1;
			}
		}
		if (_i < 0) {
			if (_x + _i <= -1) {
				return 1;
			}
		}
		if (_j > 0) {
			if (_y + _j >= 8) {
				return 1;
			}
		}
		if (_j < 0) {
			if (_y + _j <= -1) {
				return 1;
			}
		}
		if (cell_employment(_obj, _x + _i, _y + _j, _ch)) {
			return 1;
		}
		_obj->get_board().get_all_squares(_x + _i, _y + _j).on_backlight();
		return 0;
	}

	void opportunity_to_move(Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_life() == 1) {
			if (_obj->get_pieces(_ch)->get_select() == 1) {
				if (_obj->get_pieces(_ch)->get_name_piece() == 4) {
					int i = _obj->get_pieces(_ch)->get_x();
					int j = _obj->get_pieces(_ch)->get_y();
					int s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, s, s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, -s, s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, s, -s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, -s, -s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, 0, s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, s, 0)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, 0, -s)) {
							break;
						}
						s++;
					}
					s = 1;
					while (1) {
						if (queen_move(_obj, i, j, _ch, -s, 0)) {
							break;
						}
						s++;
					}
				}
			}
		}
	}
};