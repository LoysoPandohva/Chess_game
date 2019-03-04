#include <SFML/Graphics.hpp>
#include "Game_moves.h"
#include "Interactive.h"
#include "Dangmen_eggs.h"
#include "Main.h"
#include <list>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(){
	setlocale(LC_ALL, "rus");
	int egg = 1;
	Texture texture;
	Sprite sprite;
	RenderWindow window(VideoMode(500, 500), "Chessboard");

	Interactive hand;
	Pieces_on_board start(window);
	Mause_control mause_control;
	Main m;
	Dangmen_eggs dangmen_eggs;
	list <Game_moves> game_moves;
	game_moves.push_back(start);

	int switcher = 0;
	int end = 0;
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			m.instruction(window, event, switcher);
			hand.AI(window, start, game_moves, event, mause_control, end);
			hand.choise_of_shapes(window, start, event, mause_control, game_moves, end);//выбираю фигуру для хода
			hand.change_position(window, &start, event, game_moves, hand.x_alignment_in_the_squere(window, event, mause_control), hand.y_alignment_in_the_squere(window, event, mause_control), hand.get_ch(), 1, mause_control, end);//переставляю фигуру на выбранную клетку
			hand.move_back(start, event, game_moves);
			if (egg == 1) {
				egg = dangmen_eggs.you_find_it(window, event, start, game_moves);
			}
		}
		window.clear(Color(200, 200, 200));
		if (switcher == 0) {}
		else {
			start.draw_pieces(window);//рисую доску и фигуры на ней
			hand.draw_cursor(window); //рисую курсор (а так же двигаю его)
			if (egg == 0) {
				texture.loadFromFile("Images//Death.png");;
				sprite.setTexture(texture);
				sprite.setTextureRect(IntRect(0, 0, 45 , 45));
				sprite.setPosition(dangmen_eggs.get_sprite().getPosition().x, dangmen_eggs.get_sprite().getPosition().y);
				if (game_moves.back().delete_last_move(start, game_moves)) {
					hand.set_player(hand.get_player());
				}
				egg = 2;		
			}
			if (egg == 2) {
				window.draw(sprite);
			}
			if (end) {
				m.is_chekmate(window, event, end);
			}
		}
		window.display();
		
	}
	return 0;
}