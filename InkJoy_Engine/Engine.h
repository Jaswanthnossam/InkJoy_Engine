// Engine.h

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Object.hpp"
#include <memory>

#define SPEED 7

class PrimitiveRenderer {
public:
    PrimitiveRenderer(sf::RenderWindow& window);
    // In PrimitiveRenderer.h, add the following method declaration:

    void drawEllipse(float x, float y, float radiusX, float radiusY, const sf::Color& outlineColor, float outlineThickness, int symmetry = 8);
    void drawCircle(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness);
    void drawRectangle(float x, float y, float width, float height, const sf::Color& outlineColor, float outlineThickness);
    void drawLine(float x1, float y1, float x2, float y2, float thickness, const sf::Color& color);
    void drawCircleSymmetric(float x, float y, int radius, const sf::Color& outlineColor, float outlineThickness, int symmetry = 8);
    void drawPolyline(const std::vector<sf::Vector2f>& points, const sf::Color& color, float thickness, bool closed = false);

private:
    sf::RenderWindow& window;
};

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

class Engine {
public:
    Engine(int width, int height, const std::string& title);
    ~Engine();

    void setFullscreen(bool fullscreen);
    void setResolution(int width, int height);
    void setFrameRate(int fps);
    void setBackgroundColor(const sf::Color& color);
    void setPredefinedBackgroundColor(int colorIndex);
    void displayTexture(const std::string& filePath, float x, float y);
    void run();

private:
    sf::RenderWindow window;
    int frameRate;
    sf::Time frameTime;
    sf::Color clearColor;
    bool isRunning;

    sf::Texture texture0;   
    sf::Texture Birdy;

    ENGINE::Object object0;
    ENGINE::Object BirdyObj;

    std::unique_ptr<std::vector<Vec2<int>>> BirdyIndicies;

    std::vector<sf::Color> predefinedColors = {
        sf::Color::Black,
        sf::Color::White,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue
    };

    class Object {
    public:
        Object(float x, float y);
        void move(float dx, float dy);
        float getX() const;
        float getY() const;

    private:
        float x;
        float y;
    } object;

    PrimitiveRenderer primitiveRenderer{ window };

    Point2D point{ 200.0f, 300.0f };
    LineSegment lineSegment{ Point2D(300.0f, 100.0f), Point2D(500.0f, 400.0f) };

    void initialize();
    void cleanup();
    bool getIsRunning() const;
    void processEvents();
    void update();
    void render();
};