#include <SFML/Graphics.hpp>
using namespace sf;

class Bishop {
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

	void opportunity_to_move(Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_life() == 1) {
			if (_obj->get_pieces(_ch)->get_select() == 1) {
				if (_obj->get_pieces(_ch)->get_name_piece() == 3) {
					int i = _obj->get_pieces(_ch)->get_x();
					int j = _obj->get_pieces(_ch)->get_y();
					int s = 1;
					while (1) { //ход слона вниз-вправо								
						if (i + s >= 8) {
							break;
						}
						if (j + s >= 8) {
							break;
						}
						if (cell_employment(_obj, i + s, j + s, _ch)) {
							break;
						}
						_obj->get_board().get_all_squares(i + s, j + s).on_backlight();
						s++;
					}
					s = 1;
					while (1) {//ход слона вниз-влево								
						if (i + s >= 8) {
							break;
						}
						if (j - s <= -1) {
							break;
						}
						if (cell_employment(_obj, i + s, j - s, _ch)) {
							break;
						}
						_obj->get_board().get_all_squares(i + s, j - s).on_backlight();
						s++;
					}
					s = 1;
					while (1) {//ход слона вверх-влево								
						if (i - s <= -1) {
							break;
						}
						if (j - s <= -1) {
							break;
						}
						if (cell_employment(_obj, i - s, j - s, _ch)) {
							break;
						}
						_obj->get_board().get_all_squares(i - s, j - s).on_backlight();
						s++;
					}
					s = 1;
					while (1) {//ход слона вверх-вправо								
						if (i - s <= -1) {
							break;
						}
						if (j + s >= 8) {
							break;
						}
						if (cell_employment(_obj, i - s, j + s, _ch)) {
							break;
						}
						_obj->get_board().get_all_squares(i - s, j + s).on_backlight();
						s++;
					}
				}
			}
		}
	}
};