#include "logic.h"

void LifeAlgorithm::CreateUniverse()
{
    for (int i = 0; i < Widht; i++) {
        for (int j = 0; j < Height; j++) {
            fieldArray[i][j] = false;
        }
    }
}

void LifeAlgorithm::RandFillUniverse()
{
    srand(time(NULL));

    for (int i = 1; i < Widht - 1; i++) {
        for (int j = 1; j < Height - 1; j++) {
            fieldArray[i][j] = rand() % 2;
        }
    }
}

void LifeAlgorithm::Step()
{
    for (int i = 1; i < Widht - 1; i++) {
        for (int j = 1; j < Height - 1;
             j++) { // первый проход: вычисляем будущее состоянее

            int numNeigbours = 0;
            bool isAlive = fieldArray[i][j];

            for (int ii = i - 1; ii < i + 2; ii++) {
                for (int jj = j - 1; jj < j + 2; jj++) {
                    {
                        if (fieldArray[ii][jj])
                            numNeigbours++;
                    }
                }
            }

            if (fieldArray[i][j]) {
                numNeigbours--;
            }

            bool keepAlive
                    = isAlive && (numNeigbours == 2 || numNeigbours == 3);
            bool makeNewLive = !isAlive && numNeigbours == 3;
            tempArray[i][j] = keepAlive | makeNewLive;
        }
    }
    for (int i = 1; i < Widht - 1; i++)
        for (int j = 1; j < Height - 1; j++)
            // второй проход: копируем вычисленное состояние в текущее
            fieldArray[i][j] = tempArray[i][j];
}

void LifeAlgorithm::initLife()
{
    LifeAlgorithm::CreateUniverse();
    LifeAlgorithm::RandFillUniverse();
}

void LifeAlgorithm::RunLife()
{
    LifeAlgorithm::Step();
}