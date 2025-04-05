/*#include "Game.h"
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

int field[M][N] = {0};
Point a[4], b[4];

int figures[7][4] = {
    1,3,5,7,  // I
    2,4,5,7,  // Z
    3,5,4,6,  // S
    3,5,4,7,  // T
    2,3,5,7,  // L
    3,5,7,6,  // J
    2,3,4,5   // O
};

unsigned score = 0;

bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M || field[a[i].y][a[i].x])
        {
            return false;
        }
    }
    return true;
}

void spawnNewFigure()
{
    int n = rand() % 7;
    for (int i = 0; i < 4; i++)
    {
        a[i].x = figures[n][i] % 2 + N / 2 - 1;
        a[i].y = figures[n][i] / 2;
    }
    if (!check())
    {
        std::cout << "Game Over\n";
        std::cout << "Your score: " << score << std::endl;
        exit(0);
    }
}

void updateGame(float &timer, float delay, sf::Clock &clock, int &dx, bool &rotate)
{
    timer += clock.restart().asSeconds();
    if (timer >= delay)
    {
        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
        if (!check())
        {
            for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = 1;
            score += 10;
            spawnNewFigure();
        }
        timer = 0;
    }

    // Переміщення фігур
    for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
    if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

    if (rotate)
    {
        Point p = a[1];
        for (int i = 0; i < 4; i++)
        {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
    }
}

void drawGame(sf::RenderWindow &window, sf::Sprite &s, sf::Sprite &background, sf::Sprite &frame)
{
    window.clear(sf::Color::White);
    window.draw(background);

    // Малюємо поле
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (field[i][j])
            {
                s.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31);
                window.draw(s);
            }

    // Малюємо поточну фігуру
    for (int i = 0; i < 4; i++)
    {
        s.setTextureRect(sf::IntRect(18 * 1, 0, 18, 18));  // Фігури будуть мати колір, визначений тут
        s.setPosition(a[i].x * 18, a[i].y * 18);
        s.move(28, 31);  // Трошки зміщуємо для коректного відображення
        window.draw(s);
    }

    window.draw(frame);
    window.display();
}
*/