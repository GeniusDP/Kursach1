#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>


using namespace std;
using namespace sf;

const int blockSize = 150;

void initmap(vector<vector<int>>& map);

void initSprites(Texture& tx, vector<Sprite>& sp) {
    for (int i = 1; i <= 16; i++) {
        sp[i].setTexture(tx);
        sp[i].setTextureRect( IntRect( (i-1)%4*blockSize, (i-1)/4*blockSize, blockSize, blockSize ) );
        sp[i].setColor(Color(207, 174, 139, 255));
    }
}

void changeMap(vector<vector<int>>& map, int i, int j) {
    if (map[i + 1][j] == 16) {
        swap(map[i][j], map[i + 1][j]);
    }

    if (map[i - 1][j] == 16) {
        swap(map[i][j], map[i - 1][j]);
    }

    if (map[i][j + 1] == 16) {
        swap(map[i][j], map[i][j + 1]);
    }

    if (map[i][j - 1] == 16) {
        swap(map[i][j], map[i][j - 1]);
    }
}

bool isAssembled(const vector<vector<int>>& map) {
    vector<vector<int>> etalon(6, vector<int>(6, -1));
    initmap(etalon);
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (etalon[i][j] != map[i][j])return false;
        }
    }
    cout << "You have won!\n";
    return true;
}

void inputMap(vector<vector<int>>& arr) {
    ifstream in("input.txt");
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            in >> arr[i][j];
}

int main()
{
    RenderWindow form(VideoMode(750, 600), "15 game debug", Style::Close);

    Texture tx;
    tx.loadFromFile("15.jpg");
    vector<vector<int>> map(6, vector<int>(6, -1));
    vector<Sprite> block(17);
    initSprites(tx, block);
    inputMap(map);

    Texture txbuttonHelp; txbuttonHelp.loadFromFile("help.png");
    Texture txbuttonExitAndSave; txbuttonExitAndSave.loadFromFile("exitandsave.png");
    Sprite spbuttonHelp, spbuttonExitAndSave;
    spbuttonHelp.setTexture(txbuttonHelp); spbuttonHelp.setPosition( 600, 0 );
    spbuttonExitAndSave.setTexture(txbuttonExitAndSave); spbuttonExitAndSave.setPosition(600, 300);
    

    while (form.isOpen() && !isAssembled(map)) {
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
                        if ( (i-1)*blockSize < mousePos.y && (j - 1) * blockSize < mousePos.x && (i - 1) * blockSize + blockSize > mousePos.y && (j - 1) * blockSize + blockSize > mousePos.x ) {
                            changeMap(map, i, j);
                            break;
                        }
                if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>0 && mousePos.y < 300) {
                    //Help Button

                    //throw MSGBOX with next step

                }
                else if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>300 && mousePos.y < 600) {
                    //ExitButton
                    
                    //print info about game into file

                    //throw MSGBOX with 
                    form.close();
                }

            }//MouseButtonPressedevent
        }


        form.clear(Color(207, 174, 139, 255));
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                block[map[i][j]].setPosition( (j-1)*blockSize, (i-1)*blockSize );
                form.draw(block[map[i][j]]);
            }
        }
        form.draw(spbuttonHelp);
        form.draw(spbuttonExitAndSave);

        form.display();
    }

    return 0;
}


void initmap(vector<vector<int>>& map) {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            map[i][j] = (i - 1) * 4 + j;
        }
    }
}
