#pragma once

#include "PrimitiveRenderer.h"
#include "Point2D.h"

class LineSegment {
public:
    LineSegment(const Point2D& start, const Point2D& end);

    Point2D getStart() const;

    Point2D getEnd() const;

    void setStart(const Point2D& newStart);

    void setEnd(const Point2D& newEnd);

    void draw(PrimitiveRenderer& renderer, bool useIncrementalAlgorithm = false) const;

private:
    Point2D start;
    Point2D end;

    void drawDefault(PrimitiveRenderer& renderer) const;

    void drawIncremental(PrimitiveRenderer& renderer) const;
};
