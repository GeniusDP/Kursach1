#pragma once
#include <vector>
using namespace std;

/*typedefs*/
typedef int heuristic_t;
typedef uint64_t hash_t;


class Field {
	vector<vector<int>> f;
public:
	Field() {
		f = vector<vector<int>>(6);
		for (int i = 0; i < 6; i++)
			f[i] = vector<int>(6, -1);
	}

	int& at(int i, int j) {
		return f[i][j];
	}

	hash_t getHash() {
		hash_t sum = 0;
		int cnt = 15;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				sum += f[i][j] * (1LLU << (((i - 1) * 4 + j - 1) * 4));
			}
		}
		return sum;
	}


	bool isAssembled() {
		vector<vector<int>> ideal(6, vector<int>(6, -1));
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++)
				ideal[i][j] = (i - 1) * 4 + j;
		}

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++)
				if (ideal[i][j] != f[i][j])return false;
		}
		return true;
	}


    heuristic_t getHeuristic() {
        int sum = 0;
         for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                sum += (i - 1) * 4 + j != f[i][j];
        /*math_distance*/
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                sum += abs(i - (f[i][j] / 4 + 1)) + abs(j - (f[i][j] % 4 + 1));
            }
        }
        /*not on their positions*/
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
                sum += (i - 1) * 4 + j != f[i][j];
        /*Last move*/
        sum += (f[4][4] == 15 || f[4][4] == 12) ? 0 : 2;
        /*Corner Tiles*/
        int conflictCount = 0;
        //upper left corner
        if (f[1][1] != 1) {
            if (f[1][2] == 2 || f[2][1] == 5)conflictCount++;
        }
        //upper right corner
        if (f[1][4] != 4) {
            if (f[1][3] == 3 || f[2][3] == 8)conflictCount++;
        }
        //lower lefft corner
        if (f[4][1] != 13) {
            if (f[3][1] == 9 || f[4][2] == 14)conflictCount++;
        }

        sum += 2 * conflictCount;
        return sum;
    }

    pair<int, int> getBlankPosition() {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                if (f[i][j] == 16)return make_pair(i, j);
            }
        }
    }


    friend int whatBlockToClick(Field beforeTheStepCondition, Field afterOneStepCondition) {
        pair<int, int> beforeStep;
        pair<int, int> afterStep;
        beforeStep = beforeTheStepCondition.getBlankPosition();
        afterStep = afterOneStepCondition.getBlankPosition();
        pair<int, int> shiftVector = make_pair(afterStep.first - beforeStep.first, afterStep.second - beforeStep.second);
        return beforeTheStepCondition.at(beforeStep.first + shiftVector.first,beforeStep.second + shiftVector.second);
    }

    void changeMap(int i, int j) {
        if (f[i + 1][j] == 16) {
            swap(f[i][j], f[i + 1][j]);
        }

        if (f[i - 1][j] == 16) {
            swap(f[i][j], f[i - 1][j]);
        }

        if (f[i][j + 1] == 16) {
            swap(f[i][j], f[i][j + 1]);
        }

        if (f[i][j - 1] == 16) {
            swap(f[i][j], f[i][j - 1]);
        }
    }

};