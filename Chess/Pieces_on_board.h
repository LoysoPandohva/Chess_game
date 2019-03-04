#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Chessboard.h"
using namespace sf;
#pragma warning(default:4716)

class Pieces_on_board {
private:
	const int size = 32;// количество фигур на доске
	Piece *pieces[32];//вектор хранящий все фигруы
	Chessboard board;
	bool player = 0;
public:	
	void set_player(bool _i) {
		this->player = _i;
	}
	bool get_player() {
		return this->player;
	}
	int get_size() {
		return this->size;
	}
	/*void set_size(int _i) {
		this->size = _i;
	}*/
	Chessboard &get_board() {
		return this->board;
	}
	void set_board(Chessboard _obj) {
		this->board = _obj;
	}
	Piece *get_pieces(int _i) {
		return this->pieces[_i];
	}
	void set_pieces(int _i, Piece _pieces[]) {
		this->pieces[_i] = _pieces;
	}

	void draw_start_game(RenderWindow &_window) {
		for (int i = 1; i <= 8; i++) {//Белые фигуры
			if (i <= 5) pieces[i - 1] = new Piece(_window, i * 30, 0, 10 + i * 50, 51, 0, i);
			else pieces[i - 1] = new Piece(_window, (9 - i) * 30, 0, 10 + i * 50, 51, 0, 9 - i);
			board.get_all_squares(i - 1, 0).cell_employment(0);
		}

		for (int i = 8; i <= 15; i++) {//Белые пешки
			pieces[i] = new Piece(_window, 0, 0, 10 + (i - 7) * 50, 101, 0, 0);
			board.get_all_squares(i - 8, 1).cell_employment(0);
		}

		for (int i = 16; i <= 23; i++) {// Черные фигуры
			if (i <= 19) pieces[i] = new Piece(_window, (20 - i) * 30, 50, 10 + (i - 15) * 50, 401, 1, i - 15);
			else if (i == 20) pieces[i] = new Piece(_window, 0, 50, 10 + (i - 15) * 50, 401, 1, i - 15);
			else pieces[i] = new Piece(_window, (i - 19) * 30, 50, 10 + (i - 15) * 50, 401, 1, 24 - i);
			board.get_all_squares(i - 16, 7).cell_employment(1);
		}

		for (int i = 24; i <= 31; i++) {// Черные пешки
			pieces[i] = new Piece(_window, 150, 50, 10 + (i - 23) * 50, 351, 1, 0);
			board.get_all_squares(i - 24, 6).cell_employment(1);
		}
	}
   
	Pieces_on_board() { ; }

	Pieces_on_board(RenderWindow &_window) {
		board.draw_board(_window);//рисую доску
		draw_start_game(_window);//расставляю фигуры
	};

	void draw_pieces(RenderWindow &_window) {//функция рисования поля с фигурами
		board.draw_board(_window);//рисую доску
		for (int i = 0; i < size; i++) {
			pieces[i]->draw_piece(_window);//рисую каждую фигуру
		}
	}

	void delete_backlight(Pieces_on_board *_obj) {//удаляю все подсвеченные клетки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				_obj->board.get_all_squares(i, j).off_backlight();
			}
		}
	}

	//Pieces_on_board operator = (vector <Game_moves> _obj) {
	//	this->size = _obj.size;
	//	for (int i = 0; i < _obj.size; i++) {
	//		this->pieces[i] = &_obj.back().pieces[i];//возможная ошибка из-за передачи по ссылке
	//	}
	//	this->board = _obj.back().board;
	//}

	/*Pieces_on_board(vector <Game_moves> _obj) {
		this->size = _obj.size;
		for (int i = 0; i < _obj.size; i++) {
			this->pieces[i] = &_obj.back().pieces[i];
		}
		this->board = _obj.back().board;
	}*/

	/*Pieces_on_board (const Pieces_on_board &_obj){
		this->size = _obj.size;
		for (int i = 0; i < _obj.size; i++) {
			this->pieces[i] = _obj.pieces[i];
		}
		this->board = _obj.board;
	}*/
};