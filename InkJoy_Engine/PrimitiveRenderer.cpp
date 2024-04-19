#include "PrimitiveRenderer.h"
#include "Constants.h"

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& window) : window(window) {}

void PrimitiveRenderer::drawCircle(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness) {
    sf::CircleShape circle(radius);
    circle.setPosition(x - radius, y - radius);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(outlineThickness);
    window.draw(circle);
}

void PrimitiveRenderer::drawRectangle(float x, float y, float width, float height, const sf::Color& outlineColor, float outlineThickness) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOutlineThickness(outlineThickness);
    window.draw(rectangle);
}

void PrimitiveRenderer::drawLine(float x1, float y1, float x2, float y2, float thickness, const sf::Color& color) {
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x1, y1), color),
            sf::Vertex(sf::Vector2f(x2, y2), color)
    };
    window.draw(line, 2, sf::Lines);
}

void PrimitiveRenderer::drawCircleSymmetric(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness, int symmetry) {
    // Ensure that the symmetry value is either 4 or 8
    if (symmetry != 4 && symmetry != 8) {
        std::cerr << "Invalid symmetry value. Supported values are 4 or 8." << std::endl;
        return;
    }

    // Calculate the initial points of the circle using the symmetry
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < symmetry; ++i) {
        float theta = 2 * M_PI * i / symmetry;
        float px = x + radius * std::cos(theta);
        float py = y + radius * std::sin(theta);
        points.push_back(sf::Vector2f(px, py));
    }

    // Draw the polyline connecting the symmetric points
    drawPolyline(points, outlineColor, outlineThickness, true);
}

void PrimitiveRenderer::drawEllipse(float x, float y, float radiusX, float radiusY, const sf::Color& outlineColor, float outlineThickness, int symmetry) {
    // Ensure that the symmetry value is either 4 or 8
    if (symmetry != 4 && symmetry != 8) {
        std::cerr << "Invalid symmetry value. Supported values are 4 or 8." << std::endl;
        return;
    }

    // Calculate the initial points of the ellipse using the symmetry
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < symmetry; ++i) {
        float theta = 2 * M_PI * i / symmetry;
        float px = x + radiusX * std::cos(theta);
        float py = y + radiusY * std::sin(theta);
        points.push_back(sf::Vector2f(px, py));
    }

    // Draw the polyline connecting the symmetric points
    drawPolyline(points, outlineColor, outlineThickness, true);
}



void PrimitiveRenderer::drawPolyline(const std::vector<sf::Vector2f>& points, const sf::Color& color, float thickness, bool closed) {
    if (points.size() < 2) {
        // Cannot draw a polyline with less than two points
        return;
    }

    sf::VertexArray lines(sf::LinesStrip, points.size());

    for (size_t i = 0; i < points.size(); ++i) {
        lines[i].position = points[i];
        lines[i].color = color;
    }

    if (closed) {
        // If the polyline is closed, add the first point at the end to complete the loop
        lines.append(lines[0]);
    }


    // Draw the polyline
    window.draw(lines);
}