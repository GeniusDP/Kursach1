#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

class MsgBox {
	RenderWindow form;
public:
	MsgBox() {
		
		form.create(VideoMode(400, 200), "Message", Style::Close);
	}
	
	void show(string text) {
		while (form.isOpen()) {
			Event event;
			while (form.pollEvent(event)) {
				if (event.type == Event::Closed) {
					form.close();
				}
			}
			Text textOnScreen;
			sf::Font font;
			font.loadFromFile("myFont.ttf");
			textOnScreen.setFont(font);
			textOnScreen.setString(text);
			textOnScreen.setCharacterSize(40);
			form.clear(Color::Blue);
			form.draw(textOnScreen);
			form.display();
		}
	}
};