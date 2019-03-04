#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Pawn {
public:
	bool cell_employment(Pieces_on_board *_obj, int _x, int _y) {
		if (_obj->get_board().get_all_squares(_x, _y).get_employment()) {
			return 0;
		}
		return 1;
	}

	void opportunity_to_move(Pieces_on_board *_obj, int _ch) {//возможный ход
		if (_obj->get_pieces(_ch)->get_life() == 1) {
			if (_obj->get_pieces(_ch)->get_select() == 1) {
				if (_obj->get_pieces(_ch)->get_name_piece() == 0) {
					int i = _obj->get_pieces(_ch)->get_x();
					int j = _obj->get_pieces(_ch)->get_y();
					if (_obj->get_pieces(_ch)->get_color() == 0) {
						if (_obj->get_pieces(_ch)->get_first_move()) {
							if (cell_employment(_obj, i, j + 1)) {
								_obj->get_board().get_all_squares(i, j + 1).on_backlight();
								if (cell_employment(_obj, i, j + 2)) {
									_obj->get_board().get_all_squares(i, j + 2).on_backlight();
								}
							}						
						}
						else {
							if (cell_employment(_obj, i, j + 1)) {
								_obj->get_board().get_all_squares(i, j + 1).on_backlight();
							}
						}
					}
					else {
						if (_obj->get_pieces(_ch)->get_first_move()) {
							if (cell_employment(_obj, i, j - 1)) {
								_obj->get_board().get_all_squares(i, j - 1).on_backlight();
								if (cell_employment(_obj, i, j - 2)) {
									_obj->get_board().get_all_squares(i, j - 2).on_backlight();
								}
							}						
						}
						else {
							if (cell_employment(_obj, i, j - 1)) {
								_obj->get_board().get_all_squares(i, j - 1).on_backlight();
							}
						}
					}
					opportunity_to_eat(_obj, _ch, i, j);
				}
			}
		}
	}

	void opportunity_to_eat(Pieces_on_board *_obj, int _ch, int _i, int _j) {
		if (_obj->get_pieces(_ch)->get_life() == 1) {
			if (_obj->get_pieces(_ch)->get_select() == 1) {
				if (_obj->get_pieces(_ch)->get_name_piece() == 0) {
					if (_obj->get_pieces(_ch)->get_color() == 0) {// для белых пешек
						if (_obj->get_board().get_all_squares(_i + 1, _j + 1).get_employment() == 1) {
							if (_obj->get_board().get_all_squares(_i + 1, _j + 1).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
								_obj->get_board().get_all_squares(_i + 1, _j + 1).on_backlight();
							}
						}
						if (_obj->get_board().get_all_squares(_i - 1, _j + 1).get_employment() == 1) {
							if (_obj->get_board().get_all_squares(_i - 1, _j + 1).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
								_obj->get_board().get_all_squares(_i - 1, _j + 1).on_backlight();
							}
						}
					}
					if (_obj->get_pieces(_ch)->get_color() == 1) {// для черных пешек
						if (_obj->get_board().get_all_squares(_i + 1, _j - 1).get_employment() == 1) {
							if (_obj->get_board().get_all_squares(_i + 1, _j - 1).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
								_obj->get_board().get_all_squares(_i + 1, _j - 1).on_backlight();
							}
						}
						if (_obj->get_board().get_all_squares(_i - 1, _j - 1).get_employment() == 1) {
							if (_obj->get_board().get_all_squares(_i - 1, _j - 1).get_piece_color() != _obj->get_pieces(_ch)->get_color()) {
								_obj->get_board().get_all_squares(_i - 1, _j - 1).on_backlight();
							}
						}
					}

					//for (int f = 0; f < _obj->get_size(); f++) {
					//	if (_obj->get_pieces(_ch)->get_color() == 0) {// для белых пешек
					//		if (_obj->get_pieces(f)->get_x() == _i + 1 && _obj->get_pieces(f)->get_y() == _j + 1) {
					//			if (_obj->get_pieces(f)->get_color() != _obj->get_pieces(_ch)->get_color()) {
					//				_obj->get_board().get_all_squares(_i + 1, _j + 1).on_backlight();
					//			}
					//		}
					//		if (_obj->get_pieces(f)->get_x() == _i - 1 && _obj->get_pieces(f)->get_y() == _j + 1) {
					//			if (_obj->get_pieces(f)->get_color() != _obj->get_pieces(_ch)->get_color()) {
					//				_obj->get_board().get_all_squares(_i - 1, _j + 1).on_backlight();
					//			}
					//		}
					//	}
					//	else if (_obj->get_pieces(_ch)->get_color() == 1) {//для черных пешек
					//		if (_obj->get_pieces(f)->get_x() == _i - 1 && _obj->get_pieces(f)->get_y() == _j - 1) {
					//			if (_obj->get_pieces(f)->get_color() != _obj->get_pieces(_ch)->get_color()) {
					//				_obj->get_board().get_all_squares(_i - 1, _j - 1).on_backlight();
					//			}
					//		}
					//		if (_obj->get_pieces(f)->get_x() == _i + 1 && _obj->get_pieces(f)->get_y() == _j - 1) {
					//			if (_obj->get_pieces(f)->get_color() != _obj->get_pieces(_ch)->get_color()) {
					//				_obj->get_board().get_all_squares(_i + 1, _j - 1).on_backlight();
					//			}
					//		}
					//	}
					//}
				}
			}
		}
	}

	void promotion(RenderWindow &_window, Event _event, Pieces_on_board *_obj, int _ch) {
		if (_obj->get_pieces(_ch)->get_name_piece() == 0) {
			if (_obj->get_pieces(_ch)->get_y() == 7 || _obj->get_pieces(_ch)->get_y() == 0) {
				Font font;
				font.loadFromFile("Font//cour.ttf");
				Text *t[5];
				for (int i = 0; i < 5; i++) {
					t[i] = new Text("", font, 15);
				}
				t[0]->setString(L"Выберите фигуру:");
				t[1]->setString(L"Тура");
				t[2]->setString(L"Конь");
				t[3]->setString(L"Офицер");
				t[4]->setString(L"Ферзь");
				RectangleShape shape(Vector2f(160, 80));
				shape.setFillColor(Color(0, 0, 0, 255));
				shape.setPosition(170, 210);
				for (int i = 0; i < 5; i++) {
					t[i]->setPosition(170 + 4, 210 + i * 14);
					t[i]->setFillColor(Color::White);
				}
				CircleShape triangle(6, 3);
				triangle.setRotation(90);
				triangle.setPosition(170 + 14, 210 + 19);
				triangle.setFillColor(Color::White);
				t[1]->move(13, 0);
				int i = 1;//выбор фигуры
				bool stop = 1;//выход из окна выбора
				while (stop) {
					_window.draw(shape);
					for (int f = 0; f < 5; f++) {
						_window.draw(*t[f]);
					}
					while (_window.pollEvent(_event)) {
						if (_event.type == sf::Event::KeyPressed) {
							if (_event.key.code == sf::Keyboard::S) {
								if (i + 1 <= 4) {
									//t[i]->setFillColor(Color::White);
									t[i]->move(-13, 0);
									i = i + 1;
									//t[i]->setFillColor(Color::Red);
									t[i]->move(13, 0);
									triangle.move(0, 14);
								}
							}
						}
						if (_event.type == sf::Event::KeyPressed) {
							if (_event.key.code == sf::Keyboard::W) {
								if (i - 1 >= 1) {
									//t[i]->setFillColor(Color::White);
									t[i]->move(-13, 0);
									i = i - 1;
									//t[i]->setFillColor(Color::Red);
									t[i]->move(13, 0);
									triangle.move(0, -14);
								}
							}
						}
						if (_event.type == sf::Event::KeyPressed) {
							if (_event.key.code == sf::Keyboard::Enter) {
								stop = 0;
							}
						}
					}
					_window.draw(triangle);
					_window.display();
				}
				int choise_piece = i;
				_obj->get_pieces(_ch)->promotion(choise_piece, _obj->get_pieces(_ch)->get_color());
			}
		}
	}
};