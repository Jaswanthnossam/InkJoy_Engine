#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Constants.h"

class PrimitiveRenderer {
public:
    PrimitiveRenderer(sf::RenderWindow& window);

    void drawCircle(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness);

    void drawRectangle(float x, float y, float width, float height, const sf::Color& outlineColor, float outlineThickness);

    void drawLine(float x1, float y1, float x2, float y2, float thickness, const sf::Color& color);

    void drawCircleSymmetric(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness, int symmetry = 8);

    void drawPolyline(const std::vector<sf::Vector2f>& points, const sf::Color& color, float thickness, bool closed = false);

    void drawEllipse(float x, float y, float radiusX, float radiusY, const sf::Color& outlineColor, float outlineThickness, int symmetry = 8);

private:
    sf::RenderWindow& window;
};
