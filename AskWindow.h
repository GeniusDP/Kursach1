#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>
#include "Game.h"
#include "MsgBox.h"
#include "PlayWindow.h"

using namespace std;
using namespace sf;


enum WayOfInput {
    fromFile = 0,
    generateCombination = 1
};

class AskWindow {
    RenderWindow form;
public:
    AskWindow() {
        form.create(VideoMode(300, 240), "How to get start combination?", Style::Titlebar);
    }
    WayOfInput whereToGetCombination() {
        Texture txbuttonInputFromFile;
        Texture txbuttonGenerate;
        txbuttonInputFromFile.loadFromFile("inputFromFile.png");
        txbuttonGenerate.loadFromFile("generate.png");
        Sprite spbuttonInputFromFile;
        Sprite spbuttonGenerate;
        spbuttonInputFromFile.setTexture(txbuttonInputFromFile); spbuttonInputFromFile.setPosition(Vector2f(10, 30));
        spbuttonGenerate.setTexture(txbuttonGenerate); spbuttonGenerate.setPosition(Vector2f(10, 135));


        while (form.isOpen()) {
            Event event;

            while (form.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    cout << "Ask form has been closed!\n";
                    form.close();
                }
                if (event.type == Event::MouseButtonPressed) {
                    Mouse mouse;
                    Vector2i mousePos = mouse.getPosition(form);
                    if (mousePos.x > 5 && mousePos.x < 285 && mousePos.y>30 && mousePos.y < 130) {
                        //inputFromFile Button
                        form.close();
                        return fromFile;
                    }
                    else if (mousePos.x > 5 && mousePos.x < 285 && mousePos.y>135 && mousePos.y < 235) {
                        //generate button
                        form.close();
                        return generateCombination;
                    }

                }
            }
            form.clear(Color(207, 174, 139, 255));
            form.draw(spbuttonInputFromFile);
            form.draw(spbuttonGenerate);
            form.display();
        }//main while
    }
};