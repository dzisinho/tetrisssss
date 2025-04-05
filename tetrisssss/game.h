/*#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

const int M = 20;  // Кількість рядків на полі
const int N = 10;  // Кількість стовпців на полі

struct Point { int x, y; };

extern int field[M][N];
extern Point a[4], b[4];
extern int figures[7][4];
extern unsigned score;

void spawnNewFigure();
bool check();
void updateGame(float &timer, float delay, sf::Clock &clock, int &dx, bool &rotate);
void drawGame(sf::RenderWindow &window, sf::Sprite &s, sf::Sprite &background, sf::Sprite &frame);

#endif
*/