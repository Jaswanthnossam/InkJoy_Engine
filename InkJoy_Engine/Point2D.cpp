// Point2D.cpp
#include "Point2D.h"
#include "PrimitiveRenderer.h"  // Add this line to include the header file

Point2D::Point2D(float x, float y) : x(x), y(y) {}

float Point2D::getX() const {
    return x;
}

float Point2D::getY() const {
    return y;
}

void Point2D::setCoordinates(float newX, float newY) {
    x = newX;
    y = newY;
}

void Point2D::draw(PrimitiveRenderer& renderer) const {
    renderer.drawCircle(x, y, 2, sf::Color::White, 1.0f);
}
