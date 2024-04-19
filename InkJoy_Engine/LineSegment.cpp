// LineSegment.cpp
#include "LineSegment.h"

LineSegment::LineSegment(const Point2D& start, const Point2D& end) : start(start), end(end) {}

Point2D LineSegment::getStart() const {
    return start;
}

Point2D LineSegment::getEnd() const {
    return end;
}

void LineSegment::setStart(const Point2D& newStart) {
    start = newStart;
}

void LineSegment::setEnd(const Point2D& newEnd) {
    end = newEnd;
}

void LineSegment::draw(PrimitiveRenderer& renderer, bool useIncrementalAlgorithm) const {
    if (useIncrementalAlgorithm) {
        drawIncremental(renderer);
    }
    else {
        drawDefault(renderer);
    }
}

void LineSegment::drawDefault(PrimitiveRenderer& renderer) const {
    // Draw the line using the start and end points
    renderer.drawLine(start.getX(), start.getY(), end.getX(), end.getY(), 1.0f, sf::Color::Red);
}

void LineSegment::drawIncremental(PrimitiveRenderer& renderer) const {
    // Implement incremental drawing if needed
    drawDefault(renderer); // For now, just use the default drawing
}
