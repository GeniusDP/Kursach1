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


using namespace std;
using namespace sf;

const int blockSize = 150;



class PlayWindow {
    RenderWindow form;
public:
    PlayWindow() {
        form.create(VideoMode(750, 600), "15 game debug", Style::Titlebar);
    }

    void initSprites(Texture& tx, vector<Sprite>& sp) {
        for (int i = 1; i <= 16; i++) {
            sp[i].setTexture(tx);
            sp[i].setTextureRect(IntRect((i - 1) % 4 * blockSize, (i - 1) / 4 * blockSize, blockSize, blockSize));
            sp[i].setColor(Color(207, 174, 139, 255));
        }
    }

    void letIsPlay(Game game) {
        Texture tx;
        tx.loadFromFile("15.jpg");

        vector<Sprite> block(17);
        initSprites(tx, block);

        Texture txbuttonHelp; txbuttonHelp.loadFromFile("help.png");
        Texture txbuttonExitAndSave; txbuttonExitAndSave.loadFromFile("exitandsave.png");
        Sprite spbuttonHelp, spbuttonExitAndSave;
        spbuttonHelp.setTexture(txbuttonHelp); spbuttonHelp.setPosition(600, 0);
        spbuttonExitAndSave.setTexture(txbuttonExitAndSave); spbuttonExitAndSave.setPosition(600, 300);

        bool madeStepAfterHelp = false;//дописать
        while (form.isOpen() && !game.getField().isAssembled()) {//*****
            Event event;

            while (form.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    cout << "Form has been closed!\n";
                    form.close();
                }
                if (event.type == Event::MouseButtonPressed) {
                    Mouse mouse;
                    Vector2i mousePos = mouse.getPosition(form);
                    //cout << "Mouse: " << mousePos.x << " " << mousePos.y << endl;
                    for (int i = 1; i <= 4; i++)
                        for (int j = 1; j <= 4; j++)
                            if ((i - 1) * blockSize < mousePos.y && (j - 1) * blockSize < mousePos.x && (i - 1) * blockSize + blockSize > mousePos.y && (j - 1) * blockSize + blockSize > mousePos.x) {
                                if (game.getField().changeMap(i, j)) {
                                    madeStepAfterHelp = true;
                                }
                                break;
                            }
                    if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>0 && mousePos.y < 300) {
                        //Help Button
                        MsgBox helpWindow;
                        helpWindow.show("Next step is: " + to_string(game.solve(madeStepAfterHelp)));
                        //cout << "Next step is: " << game.solve(madeStepAfterHelp) << "\n";
                        madeStepAfterHelp = false;
                        //throw MSGBOX with next step
                    }
                    else if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>300 && mousePos.y < 600) {
                        //ExitButton
                        form.close();
                    }

                }//MouseButtonPressedevent
            }


            form.clear(Color(207, 174, 139, 255));
            for (int i = 1; i <= 4; i++) {
                for (int j = 1; j <= 4; j++) {
                    block[game.getField().at(i, j)].setPosition((j - 1) * blockSize, (i - 1) * blockSize);//*****
                    form.draw(block[game.getField().at(i, j)]);//*****
                }
            }
            form.draw(spbuttonHelp);
            form.draw(spbuttonExitAndSave);

            form.display();
        }
        form.close();
        MsgBox finalMessage;
        if (game.getField().isAssembled()) {
            finalMessage.show("You have won!");
        }
        else {
            finalMessage.show("You loose!");
        }
    }
};