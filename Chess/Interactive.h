#include <SFML/Graphics.hpp>
#include "Mause_control.h"
#include "King.h"
#include <iostream>
#include <list>
#include <vector>
using namespace sf;
using namespace std;

class Interactive {
private:
	int num_king = NULL;
	bool player = 0;//цвет фигур для хода
	CircleShape * cursor;
	bool select_cursor;
	int ch = 0;//индекс выбранной для хода фигуры
	King king;
	
public:
	vector <int> ch_AI;
	vector <int> cell_rand;
	//vector <int> y_rand;

	bool get_player() {
		return this->player;
	}
	void set_player(bool _i) {
		this->player = _i;
	}
	int get_ch() {
		return this->ch;
	}

	Interactive() {
		cursor = new CircleShape(15);
		cursor->setFillColor(Color(80, 0, 0, 60));
		cursor->setPosition(60, 60);
		this->select_cursor = 0;
	}

	void move_cursor(RenderWindow &_window) {
		float speed = 2;
		if (Keyboard::isKeyPressed(Keyboard::LShift)) { speed = 5; }
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			cursor->move(0, -speed);
			if (cursor->getPosition().y + 15 < 50) {
				cursor->move(0, speed);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			cursor->move(speed, 0);
			if (cursor->getPosition().x + 15 > 450) {
				cursor->move(-speed, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			cursor->move(0, speed);
			if (cursor->getPosition().y + 15 > 450) {
				cursor->move(0, -speed);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			cursor->move(-speed, 0);
			if (cursor->getPosition().x + 15 < 50) {
				cursor->move(speed, 0);
			}
		}
	}

	void set_cursor(RenderWindow  &_window, float _x, float _y) {
		this->cursor->setPosition(_x - 15, _y - 15);
	}

	void AI(RenderWindow &_window, Pieces_on_board &_obj, list <Game_moves> &_game_moves, Event _event, Mause_control _mause_control, int &_end) {
		int move = 1;
		int st1 = 0;//для отмены приоритета съедания 
		if (_end == 0) {
			if (player == 0) {
				ch_AI.erase(ch_AI.begin(), ch_AI.end());
				while (move == 1) {
					
					srand(time(0));
					bool g = 1;
					while (g) {
						if (st1 == 1) {
							ch = 4;
							break;
						}
						ch = rand() % 16;
						auto s = find(ch_AI.begin(), ch_AI.end(), ch);
						if (s == ch_AI.end()) {
							ch_AI.push_back(ch);
							break;
						}
					}

					if (_obj.get_pieces(ch)->get_life() == 1) {
						_obj.get_pieces(ch)->select_piece();
						this->select_cursor = 1;
						std::cout << "Take!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
						cursor->setFillColor(Color(0, 80, 0, 60));
						_obj.delete_backlight(&_obj);
						/*int i_1 = rand() % 8;
						int j_1 = rand() % 8;
						while (_obj.get_board().get_all_squares(i_1, j_1).get_backlight() != 1) {
							i_1 = rand() % 8;
							j_1 = rand() % 8;
						}*/
						cell_rand.erase(cell_rand.begin(), cell_rand.end());
						
						int i = 7;
						int j = 7;
						/*for (int i = 7; i > -1; i--) {
							for (int j = 7; j > -1; j--) {*/
								king.pawn.opportunity_to_move(&_obj, ch);
								king.rook.opportunity_to_move(&_obj, ch);
								king.bishop.opportunity_to_move(&_obj, ch);
								king.knight.opportunity_to_move(&_obj, ch);
								king.opportunity_to_move(&_obj, ch);
								king.queen.opportunity_to_move(&_obj, ch);

								int st = 0;
								
								for (int x = 7; x > -1; x--) {
									for (int y = 7; y > -1; y--) {										
										if (_obj.get_board().get_all_squares(x, y).get_backlight() == 1) {
											cell_rand.push_back(x);
											cell_rand.push_back(y); 
											if (_obj.get_board().get_all_squares(x, y).get_employment() == 1) {
												i = x;
												j = y;
												st = 1;
												break;
											}
										}
									}
									if (st) break;
								}
								if (st == 0 || st1 == 1) {
									if (cell_rand.size() != 0) {
										int r = rand() % cell_rand.size();
										if (r % 2 == 1) r = r - 1;
										i = cell_rand[r];
										j = cell_rand[r + 1];
									}
								}								

								/*king.pawn.opportunity_to_move(&_obj, ch);
								king.rook.opportunity_to_move(&_obj, ch);
								king.bishop.opportunity_to_move(&_obj, ch);
								king.knight.opportunity_to_move(&_obj, ch);
								king.opportunity_to_move(&_obj, ch);
								king.queen.opportunity_to_move(&_obj, ch);*/
								/*int i = i_1;
								int j = j_1;*/
								if (_obj.get_board().get_all_squares(i, j).get_backlight() == 1) {
									if (castling(&_obj, _window, _event, _mause_control, _game_moves, ch)) {
										if (error_eat(&_obj, i * 50 + 60, j * 50 + 51, ch)) {
											_obj.get_pieces(ch)->leave_piece();
											this->select_cursor = 0;
											_obj.get_board().get_all_squares(_obj.get_pieces(ch)->get_x(), _obj.get_pieces(ch)->get_y()).cell_free();
											_obj.get_pieces(ch)->change_position(i * 50 + 60, j * 50 + 51);
											_obj.get_board().get_all_squares(_obj.get_pieces(ch)->get_x(), _obj.get_pieces(ch)->get_y()).cell_employment(_obj.get_pieces(ch)->get_color());

											cursor->setFillColor(Color(80, 0, 0, 60));
											std::cout << "Drop!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
											eat_enemy(&_obj, i * 50 + 60, j * 50 + 51, _game_moves, ch);
											_obj.get_pieces(ch)->make_the_first_move();
											_obj.delete_backlight(&_obj);
											king.pawn.promotion(_window, _event, &_obj, ch);
											player = !player;
											num_king = king.check(&_obj, 1);
											_obj.set_player(player);
											_game_moves.push_back(_obj);
											bool move_back = 1;
											if (move_back == 1) {
												if (num_king != 0) {
													if (player != _obj.get_pieces(ch)->get_color()) {
														if (_obj.get_pieces(num_king)->get_color() == _obj.get_pieces(ch)->get_color()) {
															if (_game_moves.back().delete_last_move(_obj, _game_moves)) {
																player = !player;
																move_back = 0;
																_obj.get_pieces(ch)->select_piece();
																this->select_cursor = 1;
																continue;
																//AI(_window, _obj, _game_moves, _event, _mause_control, _end, i, j);
															}
														}
													}
												}
											}
											if (move_back == 1) {
												if (_obj.get_pieces(num_king)->get_sum_shah() >= 2) {
													if (_game_moves.back().delete_last_move(_obj, _game_moves)) {
														if (st == 1) {
															if (ch == 4) {
																st1 = 1;
															}
														}
														player = !player;
														move_back = 0;
														_obj.get_pieces(ch)->select_piece();
														this->select_cursor = 1;
														continue;
														//AI(_window, _obj, _game_moves, _event, _mause_control, _end, i, j);
													}
												}
											}
											if (move_back == 1) {
												if (king.dont_eat_the_king(_obj, _game_moves, 1)) {
													player = !player;
													move_back = 0;
													continue;
													//AI(_window, _obj, _game_moves, _event, _mause_control, _end, i, j);
												}
											}
											if (move_back == 1) {
												if (king.check_kings_position(_obj, _game_moves)) {
													player = !player;
													move_back = 0;
													continue;
													//AI(_window, _obj, _game_moves, _event, _mause_control, _end, i, j);
												}
											}
											_obj.delete_backlight(&_obj);

											//checkmate(_window, &_obj, _event, _game_moves, _mause_control, _end);
											move = 0;
										}
									}
								}
						
					}
				}
			}
		}
	}

	void choise_of_shapes(RenderWindow &_window, Pieces_on_board &_obj, Event _event, Mause_control &_mause_control, list <Game_moves> &_game_moves, int &_end) {//выбор фигуры для хода
		//AI(_window, _obj, _game_moves, _event, _mause_control, _end);
		if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == sf::Keyboard::Space || _event.key.code == Mouse::Right) {
				if (_event.type == sf::Event::MouseButtonPressed) {
					if (_event.key.code == Mouse::Right) {
						this->set_cursor(_window, _mause_control.get_x_position(_window), _mause_control.get_y_position(_window));
					}
				}
				if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::MouseButtonPressed) {//для отмены взятия фигуры
					if (_event.key.code == sf::Keyboard::Space || _event.key.code == Mouse::Right) {
						if (_obj.get_pieces(ch)->get_select() == 1 && this->select_cursor == 1) {
							_obj.get_pieces(ch)->leave_piece();
							this->select_cursor = 0;
							//std::cout << "Drop" << endl;
							cursor->setFillColor(Color(80, 0, 0, 60));
							_obj.delete_backlight(&_obj);
							return;
						}
					}
				}
				for (int i = 0; i < _obj.get_size(); i++) {
					if (cursor->getPosition().x + 15 >= _obj.get_pieces(i)->get_x_position() - 10 &&
						cursor->getPosition().x + 15 <= _obj.get_pieces(i)->get_x_position() + 40 &&
						cursor->getPosition().y + 15 >= _obj.get_pieces(i)->get_y_position() &&
						cursor->getPosition().y + 15 <= _obj.get_pieces(i)->get_y_position() + 48) {
						ch = i;
						if (_obj.get_pieces(ch)->get_select() == 0 && this->select_cursor == 0) {
							if (_obj.get_pieces(ch)->get_color() == player) {
								_obj.get_pieces(ch)->select_piece();
								this->select_cursor = 1;
								//std::cout << "Take" << endl;
								cursor->setFillColor(Color(0, 80, 0, 60));
								king.pawn.opportunity_to_move(&_obj, ch);
								king.rook.opportunity_to_move(&_obj, ch);
								king.bishop.opportunity_to_move(&_obj, ch);
								king.knight.opportunity_to_move(&_obj, ch);
								king.opportunity_to_move(&_obj, ch);
								king.queen.opportunity_to_move(&_obj, ch);
								return;
							}
						}
					}
				}
			}
		}
	}

	int x_alignment_in_the_squere(RenderWindow &_window, Event _event, Mause_control _mause_control) {//центровка фигуры в клетке после хода (выбор x координаты)
		if (_event.type == Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left || _event.key.code == Mouse::Right) {
				this->set_cursor(_window, _mause_control.get_x_position(_window), _mause_control.get_y_position(_window));
			}
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (cursor->getPosition().x + 15 >= i * 50 &&
					cursor->getPosition().x + 15 <= (i + 1) * 50 &&
					cursor->getPosition().y + 15 >= j * 50 &&
					cursor->getPosition().y + 15 <= (j + 1) * 50) {
					return 10 + i * 50;
				}
			}
		}
	}
	int y_alignment_in_the_squere(RenderWindow &_window, Event _event, Mause_control _mause_control) {//центровка фигуры в клетке после хода (выбор y координаты)
		if (_event.type == Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left || _event.key.code == Mouse::Right) {
				this->set_cursor(_window, _mause_control.get_x_position(_window), _mause_control.get_y_position(_window));
			}
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (cursor->getPosition().x + 15 >= i * 50 &&
					cursor->getPosition().x + 15 <= (i + 1) * 50 &&
					cursor->getPosition().y + 15 >= j * 50 &&
					cursor->getPosition().y + 15 <= (j + 1) * 50) {
					return 1 + j * 50;
				}
			}
		}
	}

	void eat_enemy(Pieces_on_board *_obj, float _x, float _y, list <Game_moves> &_game_moves, int _ch) {//ем фигуру врага
		for (int i = 0; i < _obj->get_size(); i++) {
			if (_obj->get_pieces(i)->get_x_position() == _x &&
				_obj->get_pieces(i)->get_y_position() == _y) {
				if (_obj->get_pieces(i)->get_color() != _obj->get_pieces(_ch)->get_color()) {
					_obj->get_pieces(i)->dead_piece();
					/*if (ch > i) {
						ch = ch - 1;
					}*/
					_obj->get_pieces(i)->change_position(0, 0);
					/*for (int j = i; j < _obj->get_size(); j++) {
						_obj->set_pieces(j, _obj->get_pieces(j + 1));
					}
					_obj->set_size(_obj->get_size() - 1);*/
					_obj->delete_backlight(_obj);
				}
			}

		}
	}

	bool error_eat(Pieces_on_board *_obj, float _x, float _y, int _ch) {//невозможность есть свои фигуры
		for (int i = 0; i < _obj->get_size(); i++) {
			if (_obj->get_pieces(i)->get_x_position() == _x &&
				_obj->get_pieces(i)->get_y_position() == _y) {
				if (_obj->get_pieces(i)->get_color() == _obj->get_pieces(_ch)->get_color()) {
					cout << "Странная затея есть свои фигуры." << endl;
					return 0;
				}
				return 1;
			}
		}
	}

	bool castling(Pieces_on_board *_obj, RenderWindow &_window, Event _event, Mause_control _mause_control, list <Game_moves> &_game_moves, int _ch) {
		int i = king.opportunity_to_castling(_obj, _ch);
		if (i) {
			if (_obj->get_pieces(i)->get_x_position() == x_alignment_in_the_squere(_window, _event, _mause_control) &&
				_obj->get_pieces(i)->get_y_position() == y_alignment_in_the_squere(_window, _event, _mause_control)) {
				_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_free();
				_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x(), _obj->get_pieces(i)->get_y()).cell_free();
				if (i < ch) {
					_obj->get_pieces(i)->change_position(_obj->get_pieces(i)->get_x_position() + 150, _obj->get_pieces(i)->get_y_position());
					_obj->get_pieces(ch)->change_position(_obj->get_pieces(_ch)->get_x_position() - 100, _obj->get_pieces(_ch)->get_y_position());
					_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x(), _obj->get_pieces(i)->get_y()).cell_employment(_obj->get_pieces(i)->get_color());
					_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(ch)->get_y()).cell_employment(_obj->get_pieces(_ch)->get_color());
				}
				else {
					_obj->get_pieces(i)->change_position(_obj->get_pieces(i)->get_x_position() - 100, _obj->get_pieces(i)->get_y_position());
					_obj->get_pieces(_ch)->change_position(_obj->get_pieces(_ch)->get_x_position() + 100, _obj->get_pieces(_ch)->get_y_position());
					_obj->get_board().get_all_squares(_obj->get_pieces(i)->get_x(), _obj->get_pieces(i)->get_y()).cell_employment(_obj->get_pieces(i)->get_color());
					_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_employment(_obj->get_pieces(_ch)->get_color());
				}
				_obj->get_pieces(_ch)->leave_piece();
				this->select_cursor = 0;
				cursor->setFillColor(Color(80, 0, 0, 60));
				_obj->delete_backlight(_obj);
				_obj->get_pieces(i)->make_the_first_move();
				_obj->get_pieces(_ch)->make_the_first_move();
				player = !player;
				_game_moves.push_back(*_obj);
				return 0;
			}
		}
		return 1;
	}

	void change_position(RenderWindow &_window, Pieces_on_board *_obj, Event _event, list <Game_moves> &_game_moves, float _x, float _y, int _ch, bool press, Mause_control _mause_control, int &_end) {//ход фигуры
		if (press == 1) {
			bool next = 0;
			if (_event.type == Event::KeyPressed) {
				if (_event.key.code == Keyboard::Enter) {
					next = 1;
				}
			}
			if (_event.type == Event::MouseButtonPressed) { 
				if (_event.key.code == Mouse::Left) {
					next = 1;
				}
			}
			if (next == 1) {
				if (_obj->get_pieces(_ch)->get_select() == 1 && this->select_cursor == 1) {
					if (_obj->get_board().get_all_squares((x_alignment_in_the_squere(_window, _event, _mause_control) - 60) / 50, (y_alignment_in_the_squere(_window, _event, _mause_control) - 51) / 50).get_backlight() == 1) {
						if (castling(_obj, _window, _event, _mause_control, _game_moves, _ch)) {
							if (error_eat(_obj, _x, _y, _ch)) {
								_obj->get_pieces(_ch)->leave_piece();
								this->select_cursor = 0;
								_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_free();
								_obj->get_pieces(_ch)->change_position(_x, _y);
								_obj->get_board().get_all_squares(_obj->get_pieces(ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_employment(_obj->get_pieces(ch)->get_color());

								/*for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++) {
										cout << _obj->board.all_squares[j][i].get_employment() << " ";
									}
									cout << endl;
								}
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++) {
										cout << _obj->board.all_squares[j][i].get_piece_color() << " ";
									}
									cout << endl;
								}*/

								cursor->setFillColor(Color(80, 0, 0, 60));
								//std::cout << "Drop" << endl;
								eat_enemy(_obj, _x, _y, _game_moves, _ch);
								_obj->get_pieces(_ch)->make_the_first_move();
								_obj->delete_backlight(_obj);
								king.pawn.promotion(_window, _event, _obj, _ch);
								player = !player;
								num_king = king.check(_obj, 1);
								_obj->set_player(player);
								_game_moves.push_back(*_obj);
								bool move_back = 1;
								if (move_back == 1) {
									if (num_king != 0) {
										if (player != _obj->get_pieces(_ch)->get_color()) {
											if (_obj->get_pieces(num_king)->get_color() == _obj->get_pieces(_ch)->get_color()) {
												if (_game_moves.back().delete_last_move(*_obj, _game_moves)) {
													player = !player;
													move_back = 0;
												}
											}
										}
									}
								}
								if (move_back == 1) {
									if (_obj->get_pieces(num_king)->get_sum_shah() >= 2) {
										if (_game_moves.back().delete_last_move(*_obj, _game_moves)) {
											player = !player;
											move_back = 0;
										}
									}
								}
								if (move_back == 1) {
									if (king.dont_eat_the_king(*_obj, _game_moves, 1)) {
										player = !player;
										move_back = 0;
									}
								}
								if (move_back == 1) {
									if (king.check_kings_position(*_obj, _game_moves)) {
										player = !player;
										move_back = 0;
									}
								}
								checkmate(_window, _obj, _event, _game_moves, _mause_control, _end);
							}
						}
					}
				}
			}
		}
		else {
			_game_moves.push_back(*_obj);
			if (error_eat(_obj, _x, _y, _ch)) {
				_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_free();
				_obj->get_pieces(_ch)->change_position(_x, _y);
				_obj->get_board().get_all_squares(_obj->get_pieces(_ch)->get_x(), _obj->get_pieces(_ch)->get_y()).cell_employment(_obj->get_pieces(_ch)->get_color());
				_obj->get_pieces(_ch)->leave_piece();
				//std::cout << "Drop" << endl;
				eat_enemy(_obj, _x, _y, _game_moves, _ch);
				_obj->delete_backlight(_obj);
				player = !player;
				_obj->set_player(player);
				if (king.dont_eat_the_king(*_obj, _game_moves, 0)) {
					player = !player;
				}
			}
		}
	}

	void move_back(Pieces_on_board &_obj, Event _event, list <Game_moves> &_game_moves) {
		if (Keyboard::isKeyPressed(Keyboard::LControl)) {
			if (_event.type == sf::Event::KeyPressed) {
				if (_event.key.code == sf::Keyboard::Z) {
					if (_game_moves.back().delete_last_move(_obj, _game_moves)) {
						player = !player;
					}
				}
			}
		}
	}

	void checkmate(RenderWindow &_window, Pieces_on_board *_obj, Event _event, list <Game_moves> &_game_moves, Mause_control _mause_control, int &_end) {
		bool save_backlight[8][8];//сохраняю все вохможные ходы каждой фигуры (т.к. в процессе хода подцветка клеток удаляется)
		const int dangerous_checkmate = king.check(_obj, 0);//номер короля, для которого возможен мат
		bool you_can_save = 0;
		if (dangerous_checkmate) {
			for (int chert = 0; chert < _obj->get_size(); chert++) {
				if (_obj->get_pieces(chert)->get_life() == 1) {
					if (_obj->get_pieces(chert)->get_color() == _obj->get_pieces(dangerous_checkmate)->get_color()) {

						_obj->get_pieces(chert)->select_piece();
						king.pawn.opportunity_to_eat(_obj, chert, _obj->get_pieces(chert)->get_x(), _obj->get_pieces(chert)->get_y());
						king.pawn.opportunity_to_move(_obj, chert);
						king.rook.opportunity_to_move(_obj, chert);
						king.bishop.opportunity_to_move(_obj, chert);
						king.knight.opportunity_to_move(_obj, chert);
						king.queen.opportunity_to_move(_obj, chert);
						king.opportunity_to_move(_obj, chert);
						_obj->get_pieces(chert)->leave_piece();
						
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								save_backlight[i][j] = _obj->get_board().get_all_squares(i, j).get_backlight();
							}
						}

						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								if (save_backlight[i][j] == 1) {
									_obj->get_pieces(chert)->select_piece();
									change_position(_window, _obj, _event, _game_moves, 60 + i * 50, 51 + j * 50, chert, 0, _mause_control, _end);
									int zxc = king.check(_obj, 0);
									if (_obj->get_pieces(dangerous_checkmate)->get_color() == 0) {
										if (zxc == dangerous_checkmate) {
											_obj->delete_backlight(_obj);
										}
										else if (zxc == 0) {
											you_can_save = 1;
											_obj->delete_backlight(_obj);
											//cout << "This is not checkmate for white" << endl;
										}
									}
									if (_obj->get_pieces(dangerous_checkmate)->get_color() == 1) {
										if (zxc == dangerous_checkmate) {
											_obj->delete_backlight(_obj);
										}
										else if (zxc == 0) {
											you_can_save = 1;
											_obj->delete_backlight(_obj);
											//cout << "This is not checkmate for black" << endl;
										}
									}
									if (_game_moves.back().delete_last_move(*_obj, _game_moves)) {
										player = !player;
									}
								}
							}
						}
						_obj->delete_backlight(_obj);
					}
				}
			}
			if (you_can_save == 0) {
				_obj->delete_backlight(_obj);
				if (_obj->get_pieces(dangerous_checkmate)->get_color() == 0) {
					cout << "White lose" << endl;
					_end = 1;
					return;
				}
				else {
					cout << "Black lose" << endl;
					_end = 2;
					return;
				}
			}
		}
		return;
	}

	void draw_cursor(RenderWindow  &_window) {
		move_cursor(_window);
		_window.draw(*cursor);
	}
};