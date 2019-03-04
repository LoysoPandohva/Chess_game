#include <SFML/Graphics.hpp>
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
using namespace sf;

class King {
private:
	int white_king;
	int black_king;
public:
	Pawn pawn;
	Rook rook;
	Bishop bishop;
	Knight knight;
	Queen queen;

	bool cell_employment(Pieces_on_board *_obj, int _x, int _y, int _ch) {
		if (_obj->get_board().get_all_squares(_x, _y).get_employment()) {
			if (_obj->get_board().get_all_squares(_x, _y).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
				_obj->get_board().get_all_squares(_x, _y).on_backlight();
			}
			return 1;
		}
		return 0;
	}

	void king_move(Pieces_on_board *_obj, int _x, int _y, int _ch, int _i, int _j) {
		bool can = 1;
		if (_j == 1) {
			if ( _y + 1 >= 8) {
				can = 0;
			}
		}
		if (_i == 1) {
			if (_x + 1 >= 8) {
				can = 0;
			}
		}
		if (_j == -1) {
			if ( _y - 1 <= -1) {
				can = 0;
			}
		}
		if (_i == -1) {
			if (_x - 1 <= -1) {
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

	int opportunity_to_castling(Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_name_piece() == 5) {
			if (_obj->get_pieces(_ch)->get_first_move()) {
				if (_obj->get_pieces(_ch)->get_first_shah()) {
					for (int i = 0; i < _obj->get_size(); i++) {
						if (_obj->get_pieces(i)->get_name_piece() == 1) {
							if (_obj->get_pieces(i)->get_first_move()) {
								if (_obj->get_pieces(i)->get_color() == _obj->get_pieces(_ch)->get_color()) {
									bool free = 0;//если между королем и турой свободные клетки
									if (i < _ch) {//если тура до короля (т.е. тура слева от короля)
										if (!(_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x() + 1, _obj->get_pieces(i)->get_y()).get_employment() ||
											_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x() + 2, _obj->get_pieces(i)->get_y()).get_employment() ||
											_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x() + 3, _obj->get_pieces(i)->get_y()).get_employment())) {
											free = 1;
										}
									}
									else {
										if (!(_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x() + 1, _obj->get_pieces(_ch)->get_y()).get_employment() ||
											_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x() + 2, _obj->get_pieces(_ch)->get_y()).get_employment())) {
											free = 1;
										}
									}
									if (free) {
										_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x(), _obj->get_pieces(i)->get_y()).on_backlight();
										return i;
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
		
	void opportunity_to_move(Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_select() == 1) {
			if (_obj->get_pieces(_ch)->get_name_piece() == 5) {
				int i = _obj->get_pieces(_ch)->get_x();
				int j = _obj->get_pieces(_ch)->get_y();
				king_move(_obj, i, j, _ch, 1, 1);
				king_move(_obj, i, j, _ch, 1, -1);
				king_move(_obj, i, j, _ch, -1, 1);
				king_move(_obj, i, j, _ch, -1, -1);
				king_move(_obj, i, j, _ch, 1, 0);
				king_move(_obj, i, j, _ch, 0, -1);
				king_move(_obj, i, j, _ch, -1, 0);
				king_move(_obj, i, j, _ch, 0, 1);
				opportunity_to_castling(_obj, _ch);
			}
		}
	}

	int check(Pieces_on_board *_obj, bool _remember_check) {
		for (int i = 0; i < _obj->get_size(); i++) {
			if (_obj->get_pieces(i)->get_name_piece() == 5) {
				if (_obj->get_pieces(i)->get_color() == 0) {
					white_king = i;
				}
				if (_obj->get_pieces(i)->get_color() == 1) {
					black_king = i;
				}
			}
		}
		
		for (int i = _obj->get_size() - 1; i > -1; i--) {
			_obj->get_pieces(i)->select_piece();
			pawn.opportunity_to_eat(_obj, i, _obj->get_pieces(i)->get_x(), _obj->get_pieces(i)->get_y());
			rook.opportunity_to_move(_obj, i);
			bishop.opportunity_to_move(_obj, i);
			knight.opportunity_to_move(_obj, i);
			queen.opportunity_to_move(_obj, i);
			if (_obj->get_board().get_all_squares(_obj->get_pieces(white_king)->get_x(), _obj->get_pieces(white_king)->get_y()).get_backlight() == 1) {
				if (_remember_check) {
					cout << "check for white" << endl;
					_obj->get_pieces(white_king)->make_first_shah();
					_obj->get_pieces(white_king)->make_shah();
				}
				_obj->get_pieces(i)->leave_piece();
				_obj->delete_backlight(_obj);
				return white_king;
			}
			if (_obj->get_board().get_all_squares(_obj->get_pieces(black_king)->get_x(), _obj->get_pieces(black_king)->get_y()).get_backlight() == 1) {
				if (_remember_check) {
					cout << "check for black" << endl;
					_obj->get_pieces(black_king)->make_first_shah();
					_obj->get_pieces(black_king)->make_shah();
				}
				_obj->get_pieces(i)->leave_piece();
				_obj->delete_backlight(_obj);
				return black_king;
			}
			_obj->get_pieces(i)->leave_piece();
			_obj->delete_backlight(_obj);
		}
		_obj->get_pieces(white_king)->set_sum_shah(0);
		_obj->get_pieces(black_king)->set_sum_shah(0);
		return 0;
	}

	bool dont_eat_the_king(Pieces_on_board &_obj, list <Game_moves> &_game_moves, bool _checkmate) {
		if (_checkmate) {
			for (int i = 0; i < _obj.get_size(); i++) {
				if (_obj.get_pieces(i)->get_name_piece() == 5) {
					if (_obj.get_pieces(i)->get_x_position() == 0) {
						return _game_moves.back().delete_last_move(_obj, _game_moves);
					}
				}
			}
		}
		return 0;
	}

	bool check_kings_position(Pieces_on_board &_obj, list <Game_moves> &_game_moves) {
		if (_obj.get_pieces(4)->get_x() + 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() + 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() - 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() + 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() + 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() + 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() - 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() - 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() - 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() - 1 == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() + 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() == _obj.get_pieces(20)->get_y() ||
			_obj.get_pieces(4)->get_x() - 1 == _obj.get_pieces(20)->get_x() && _obj.get_pieces(4)->get_y() == _obj.get_pieces(20)->get_y()) {
			return _game_moves.back().delete_last_move(_obj, _game_moves);
		}
		else return 0;
	}
};