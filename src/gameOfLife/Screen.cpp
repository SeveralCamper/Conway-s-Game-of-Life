#include "Screen.h"
#include "ShowGrid.h"
#include "ShowPixel.h"

class Helper {
public:
    static bool RandomGrid;
    static bool customModeFlag;
};

void CloseWindow(sf::RenderWindow& window)
{
    window.close();
}

void RandomGrid(sf::RenderWindow& window)
{
    Helper::customModeFlag = false;
    Helper::RandomGrid = true;
}

void CustomModeGrid(sf::RenderWindow& window)
{
}

bool Helper::RandomGrid = false;
bool Helper::customModeFlag = false;

void Screen(int width, int height, std::string name)
{
    LifeAlgorithm LAExmpl;
    LAExmpl.initLife();

    sf::RenderWindow window(sf::VideoMode(width, height), name);
    window.setVerticalSyncEnabled(true);

    /* Зоны */
    UserZone menuZone(
            5, 5, window.getSize().y - 10, window.getSize().x / 4, &window);
    menuZone.SetFillColor(sf::Color(0, 0, 0));

    UserZone gameZone(
            (window.getSize().x / 4) + 10,
            5,
            window.getSize().y - 100,
            ((window.getSize().x / 4) * 3) - 15,
            &window);
    gameZone.SetFillColor(sf::Color(0, 0, 0));

    UserZone statusZone(
            (window.getSize().x / 4) + 10,
            710,
            80,
            ((window.getSize().x / 4) * 3) - 15,
            &window);

    statusZone.SetFillColor(sf::Color(0, 0, 0));
    /* --- */

    /* кнопки */
    UserButton btnRandomMode("RANDOM MODE", 600, 20, 100, 100, &window);
    btnRandomMode.SetFillColor(sf::Color(0, 0, 0));
    btnRandomMode.ClickButton = RandomGrid;

    UserButton btnCustomMode("CUSTOM MODE", 600, 20, 100, 100, &window);
    btnCustomMode.SetFillColor(sf::Color(0, 0, 0));
    btnCustomMode.ClickButton = CustomModeGrid;

    UserButton btnClose("CLOSE", 600, 20, 100, 100, &window);
    btnClose.SetFillColor(sf::Color(0, 0, 0));
    btnClose.ClickButton = CloseWindow;
    /* --- */

    menuZone.PushButton(btnCustomMode);
    menuZone.PushButton(btnRandomMode);
    menuZone.PushButton(btnClose);

    // программа работает сколь угодно долго,пока открыто наше окно
    while (window.isOpen()) {
        // проверяем все события окна,которые были запущены после последней
        // итерации цикла
        sf::Event event;
        while (window.pollEvent(event)) {
            // если произошло событие Закрытие,закрываем наше окно
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Установка цвета фона
        window.clear(sf::Color(255, 136, 0, 0));

        menuZone.DrawZone();
        gameZone.DrawZone();
        statusZone.DrawZone();

        ShowGrid(window);

        if (Helper::RandomGrid) {
            LAExmpl.Step();
            // sf::Clock clock;
            // float time = 0;
            // while (time < 1) {
            // time = clock.getElapsedTime().asSeconds();

            // ShowGrid(window);
            ShowPixel(window, LAExmpl.fieldArray);

            sf::sleep(sf::milliseconds(300));
            // }
        }

        // Отрисовка окна
        window.display();
    }
}