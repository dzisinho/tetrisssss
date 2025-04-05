#include <algorithm>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

const int M = 21; // Кількість рядків
const int N = 21; // Кількість стовпців

int field[M][N] = {0};

struct Point { int x, y; } a[4], b[4];

int figures[7][4] = {
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5  // O
};

bool escapeButtonStatus = false;
bool pause = false;
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

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(950, 980), "Tetris");

    Texture t1, t2, t3;
    t1.loadFromFile("photo/tiles.png");
    t2.loadFromFile("photo/background.png");
    t3.loadFromFile("photo/frame.png");

    Sprite s(t1), background(t2), frame(t3);

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;
    spawnNewFigure();

    while (window.isOpen())
    {
        if (!pause && !escapeButtonStatus)
            timer += clock.restart().asSeconds();

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::LostFocus)
                pause = true;
            if (e.type == Event::GainedFocus)
                pause = false;
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                    escapeButtonStatus = !escapeButtonStatus;
                else if (e.key.code == Keyboard::Up)
                    rotate = true;
                else if (e.key.code == Keyboard::Left)
                    dx = -1;
                else if (e.key.code == Keyboard::Right)
                    dx = 1;
            }
        }

        if (pause || escapeButtonStatus)
        {
            sf::sleep(sf::milliseconds(250));
            continue;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05;

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

        if (timer >= delay)
        {
            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
            if (!check())
            {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
                colorNum = 1 + rand() % 7;
                spawnNewFigure();
            }
            timer = 0;
        }

        int k = M - 1;
        for (int i = M - 1; i >= 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < N) k--;
            else score += 10;
        }

        dx = 0;
        rotate = false;
        delay = 0.3;

        window.clear(Color::White);
        window.draw(background);

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (field[i][j])
                {
                    s.setTextureRect(IntRect(field[i][j] * 45, 0, 45, 45));  // Блоки 45x45
                    s.setPosition(j * 45, i * 45);  // Відстань між блоками
                    window.draw(s);
                }

        for (int i = 0; i < 4; i++)
        {
            s.setTextureRect(IntRect(colorNum * 45, 0, 45, 45));  // Блоки 45x45
            s.setPosition(a[i].x * 45, a[i].y * 45);  // Відстань між блоками
            window.draw(s);
        }

        window.draw(frame);
        window.display();
    }
    return 0;
}
