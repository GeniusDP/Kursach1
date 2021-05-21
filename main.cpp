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
#include "AskWindow.h"

using namespace std;
using namespace sf;



int main()
{
    AskWindow aAskWindow;
    WayOfInput wayofinput = aAskWindow.whereToGetCombination();
    Game game;//Main game class
    bool combinationFromFileCanBeAssembled = true;
    if(wayofinput == fromFile)combinationFromFileCanBeAssembled = game.inputFile();
        else game.generateCombination();
    
    if (combinationFromFileCanBeAssembled) {
        PlayWindow aPlayWindow;
        aPlayWindow.letIsPlay(game);
    }
    else {
        MsgBox errorMessage;
        errorMessage.show("Can`t be solved!");
    }
    return 0;
}

