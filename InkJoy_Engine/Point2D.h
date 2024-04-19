// Point2D.h

#pragma once

#include "PrimitiveRenderer.h"

class Point2D {
public:
    Point2D(float x, float y);

    float getX() const;
    float getY() const;
    void setCoordinates(float newX, float newY);
    void draw(PrimitiveRenderer& renderer) const;

private:
    float x;
    float y;
};

