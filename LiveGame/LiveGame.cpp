#include <iostream>
#include <windows.h>
#include <stdlib.h>

void startLive();
void cycle(int(&)[9][18]);
void dragPole(int(&)[9][18]);

int main()
{
    std::setlocale(LC_ALL, "Russian");
    startLive();
}

void startLive()
{
    int numberInitialLife;
    int polye[9][18] = { 0 };

    std::cout << "Введите количество начальных живых единиц: ";
    std::cin >> numberInitialLife;

    for (int i = 0; i < numberInitialLife; i++)
    {
        int goris, vertical;

        std::cout << "Введите положение " << i << " жизни по горизонтали (0-8): ";
        std::cin >> goris;
        if (goris < 0 || goris >= 9) {
            std::cout << "Некорректный ввод для горизонтали!" << std::endl;
            return;
        }

        std::cout << "Введите положение " << i << " жизни по вертикали (0-17): ";
        std::cin >> vertical;
        if (vertical < 0 || vertical >= 18) {
            std::cout << "Некорректный ввод для вертикали!" << std::endl;
            return;
        }

        polye[goris][vertical] = 1;
    }

    cycle(polye);
}

void cycle(int(&polye)[9][18])
{
    int i, j;
    int newPolye[9][18] = { 0 };

    newPolye[0][0]  = polye[0][0]  + polye[0][1]  + polye[1][0]  + polye[1][1];
    newPolye[0][17] = polye[0][17] + polye[0][16] + polye[1][16] + polye[1][17];
    newPolye[8][0]  = polye[8][0]  + polye[7][0]  + polye[7][1]  + polye[8][1];
    newPolye[8][17] = polye[8][17] + polye[7][17] + polye[7][16] + polye[8][16];

    for (i = 1; i < 8; i++) {
        for (j = 1; j < 17; j++) {
            newPolye[i][j]= polye[i-1][j-1] + polye[i-1][j] + polye[i-1][j+1] + polye[i][j-1] + polye[i][j+1] + polye[i+1][j-1] + polye[i+1][j] + polye[i+1][j+1];
        }
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 18; j++) {
            if (newPolye[i][j] == 2 || newPolye[i][j] == 3) {
                polye[i][j] = 1;
            }
            else {
                polye[i][j] = 0;
            }
        }
    }

    dragPole(polye);
}

void dragPole(int(&polye)[9][18])
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 18; j++) {
            if (polye[i][j] == 0)
                std::cout << "0 ";
            else
                std::cout << "1 ";
        }
        std::cout << std::endl;
    }

    Sleep(500);
    system("cls");

    cycle(polye);
}