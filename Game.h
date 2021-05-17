#pragma once
#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "VertoxTree.h"
//#include "Functions.h"
#include <queue>
#include <set>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Field.h"

using namespace std;

/*constants*/



/*defines*/
#define mp make_pair


/*typedefs*/
typedef int heuristic_t;
typedef uint64_t hash_t;

/*+++++++++++++++++++++++++++++*/

class Game {
    Field m_field;
    vector<int> helpCalls;
public:
    void inputFile();
    int solve(bool);
    Field& getField() {
        return m_field;
    }
    void generateCombination() {
        srand(time(NULL));
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                m_field.at(i, j) = 4 * (i - 1) + j;
            }
        }
        int ii=4, jj=4;
        
        pair<int, int> shift[5] = { mp(0, 0), mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0) };
        int curr=0, last = 0;
        for (int step = 1; step <= 20; step++) {
            do {
                last = curr;
                curr = rand() % 4 + 1;
            } while (m_field.at(ii + shift[curr].first,jj + shift[curr].second) == -1 || last==curr);

            swap(m_field.at(ii, jj), m_field.at(ii + shift[curr].first, jj + shift[curr].second));

            ii += shift[curr].first;
            jj += shift[curr].second;
        }

        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                cout << setw(3) << m_field.at(i, j);
            }
            cout << endl;
        }

    }
};


void Game::inputFile() {
    ifstream in("input.txt");
    for (int i = 1; i <= 4; i++)
        for (int j = 1, x; j <= 4; j++) {
            in >> x;
            m_field.at(i, j) = (x == 0) ? 16 : x;
        }
}


int Game::solve(bool madeStepAfterHelp) {
    //srand(time(NULL));
    if (madeStepAfterHelp==false && helpCalls.size()>0) {
        return *helpCalls.rbegin();
    }
    else {
        int __MAXDEPTH__ = 17;//rand() % 5 + 5;
        pair<int, int> shift[4] = { mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0) };
        //limited bfs
        //создаём стартовую вершину
        VertoxTree* start = new VertoxTree;
        start->currDepth = 0;
        start->hash = m_field.getHash();
        start->m = m_field;
        start->prev = NULL;

        queue<VertoxTree*> q;
        vector<VertoxTree*> allVertoxes;
        set<hash_t> used;
        q.push(start);
        allVertoxes.push_back(start);
        while (!q.empty()) {
            VertoxTree* curr = q.front();
            if (!used.count(curr->hash) && curr->currDepth <= __MAXDEPTH__) {
                if (curr->m.isAssembled()) { /*cout << "ASSEMBLED!!!\n" << curr->currDepth << "\n";*/ break; }
                else {
                    used.insert(curr->hash);
                    VertoxTree* p;//для создания новых вершин
                    pair<int, int> blankPoint = curr->m.getBlankPosition();
                    for (int sh = 0; sh < 4; sh++) {
                        if (curr->m.at(shift[sh].first + blankPoint.first, shift[sh].second + blankPoint.second) != -1) {//есть куда сдвинуть пустой место
                            p = new VertoxTree;
                            p->m = curr->m;
                            swap(p->m.at(blankPoint.first, blankPoint.second), p->m.at(shift[sh].first + blankPoint.first, shift[sh].second + blankPoint.second));
                            p->hash = p->m.getHash();
                            if (!used.count(p->hash)) {
                                p->prev = curr;
                                p->currDepth = curr->currDepth + 1;
                                curr->next.push_back(p);
                                //добавление в очередь
                                q.push(p);
                                allVertoxes.push_back(p);
                            }
                            else delete p;//:)
                        }
                    }
                }
            }
            q.pop();
        }

        //пробрать листья
        //и выбрать среди них с минимальной эвристикой
        bool gotHeuristic = false;
        set<VertoxTree*> setOfClosedVertoxes;//используется для отсечения тех вершин, которые приводят к зацикливаемуму шагу

        VertoxTree* last = NULL;
        while (!gotHeuristic) {
            VertoxTree* currlast = NULL;
            int minHeuristic = 1'000;
            for (auto vertox : allVertoxes) {//поиск лиска с минимальной эвристикой, который ещё не отсечен
                if (!vertox->next.size() && !setOfClosedVertoxes.count(vertox)) {
                    if (minHeuristic > vertox->m.getHeuristic()) {
                        minHeuristic = vertox->m.getHeuristic();
                        currlast = vertox;
                    }

                }
            }
            //в currlast лежит указатель на такой листок
            VertoxTree* save = currlast;

            //переходим на предпоследнюю вершину(1 шаг от начала)
            while (currlast && currlast->prev && (currlast->prev)->prev) { //
                currlast = currlast->prev;
            }

            if (!helpCalls.size() || (whatBlockToClick(currlast->m, currlast->prev->m) != helpCalls[helpCalls.size() - 1])) {
                gotHeuristic = true;
                last = currlast;
            }
            else setOfClosedVertoxes.insert(save);
        }//now we have gotten help




        int answer = -1;
        if (last && last->prev) {
            answer = whatBlockToClick(last->m, last->prev->m);
            helpCalls.push_back(answer);
        }
        //удаление вершин
        for (auto v : allVertoxes)
            delete v;
        return answer;
    }
}