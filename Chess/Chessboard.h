#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <iostream>
using namespace sf;
using namespace std;
#pragma warning(default:4716)


class Chessboard {
private:	
	Cell all_squares[8][8];
public:
	Cell &get_all_squares(int _i, int _j) {
		return this->all_squares[_i][_j];
	}
	
	void draw_board(RenderWindow &_window) {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(i * 50.0, j * 50);
				if ((i + j) % 2 == 1) all_squares[i - 1][j - 1].set_actuality_color(all_squares[i - 1][j - 1].get_white());
				else all_squares[i - 1][j - 1].set_actuality_color(all_squares[i - 1][j - 1].get_black());
				all_squares[i - 1][j - 1].get_square()->setFillColor(all_squares[i - 1][j - 1].get_actuality_color());
				_window.draw(*all_squares[i - 1][j - 1].get_square());
			}
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_backlight() == 1) {
					RectangleShape square_light(Vector2f(50, 50));
					square_light.setPosition(i * 50, j * 50);
					all_squares[i - 1][j - 1].set_actuality_color(all_squares[i - 1][j - 1].get_green());
				}
				all_squares[i - 1][j - 1].get_square()->setFillColor(all_squares[i - 1][j - 1].get_actuality_color());
				_window.draw(*all_squares[i - 1][j - 1].get_square());
			}
		}
		Font font;
		font.loadFromFile("Font//cour.ttf");
		Text *t[16];
		for (int i = 0; i < 16; i++) {
			t[i] = new Text("", font, 35);

		}
		t[0]->setString(L"1");
		t[1]->setString(L"2");
		t[2]->setString(L"3");
		t[3]->setString(L"4");
		t[4]->setString(L"5");
		t[5]->setString(L"6");
		t[6]->setString(L"7");
		t[7]->setString(L"8");
		t[8]->setString(L"À");
		t[9]->setString(L"Á");
		t[10]->setString(L"Â");
		t[11]->setString(L"Ã");
		t[12]->setString(L"Ä");
		t[13]->setString(L"Å");
		t[14]->setString(L"Æ");
		t[15]->setString(L"Ç");
		for (int i = 0; i < 8; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition(10, i * 50 + 50);
			_window.draw(*t[i]);
			t[i]->setPosition(460, i * 50 + 50);
			_window.draw(*t[i]);
		}
		for (int i = 8; i < 16; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition((i-8) * 50 + 60, 1);
			_window.draw(*t[i]);
			t[i]->setPosition((i-8) * 50 + 60, 451);
			_window.draw(*t[i]);
		}
	}	

	Chessboard operator = (Chessboard _obj) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				this->all_squares[i][j] = _obj.get_all_squares(i, j);
			}
		}
	}
};