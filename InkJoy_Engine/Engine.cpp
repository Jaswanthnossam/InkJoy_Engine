// Engine.cpp

#include "Engine.h"

// PrimitiveRenderer methods are unchanged

// Point2D methods are unchanged

// LineSegment methods are unchanged

Engine::Object::Object(float x, float y) : x(x), y(y) {}

void Engine::Object::move(float dx, float dy) {
    x += dx;
    y += dy;
}

float Engine::Object::getX() const {
    return x;
}

float Engine::Object::getY() const {
    return y;
}

Engine::Engine(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title),
    frameRate(60),
    clearColor(sf::Color::Black),
    isRunning(false),
    object(100.0f, 500.0f) {
    initialize();
    texture0.loadFromFile("C:\\Users\\USER\\Pictures\\politechnika.png");
    Birdy.loadFromFile("resources\\Birdy.png");
    
    BirdyObj.Scale(3.0f, 3.0f);
    BirdyObj.TranslateTo(width / 2, height / 2);

    Vec2<int> indiciesBirdy[] = {
            {0,0},
            {1,0},
            {2,0},
            {3,0},
            {4,0},
            {0,1},
            {1,1},
            {2,1},
            {3,1},
            {4,1},
            {0,2},
            {1,2},
            {2,2},
            {3,2}
    };

    BirdyIndicies = std::make_unique<std::vector<Vec2<int>>>(indiciesBirdy, indiciesBirdy + 14);
}

Engine::~Engine() {
    cleanup();
}

void Engine::setFullscreen(bool fullscreen) {
    window.create(sf::VideoMode::getFullscreenModes()[0], "Game Engine", (fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
}

void Engine::setResolution(int width, int height) {
    window.setSize(sf::Vector2u(width, height));
}

void Engine::setFrameRate(int fps) {
    frameRate = fps;
    frameTime = sf::seconds(1.0f / frameRate);
}

void Engine::setBackgroundColor(const sf::Color& color) {
    clearColor = color;
}

void Engine::setPredefinedBackgroundColor(int colorIndex) {
    if (colorIndex >= 0 && colorIndex < predefinedColors.size()) {
        clearColor = predefinedColors[colorIndex];
    }
}

void Engine::displayTexture(const std::string& filePath, float x, float y) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath))
    {
        sf::Sprite sprite(texture);
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
    else {
        std::cerr << "Error loading texture from file: " << filePath << std::endl;
    }
}

void Engine::run() {
    isRunning = true;
    sf::Clock clock;
    sf::Time elapsedTime;

    
    while (isRunning) {
        elapsedTime += clock.restart();

        processEvents();

        while (elapsedTime >= frameTime) {
            update();
            elapsedTime -= frameTime;
        }

        render();
    }
}

void Engine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isRunning = false; // Quit the game when Esc is pressed
            }
        }
    }
}

void Engine::update() {
    // Handle keyboard input to move the object
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        object.move(-5.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        object.move(5.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        object.move(0.0f, -5.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        object.move(0.0f, 5.0f);
    }
    window.setFramerateLimit(60);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        BirdyObj.Translate(0, -SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        BirdyObj.Translate(0, SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        BirdyObj.Translate(-SPEED, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        BirdyObj.Translate(SPEED, 0);
    }
}

void Engine::render() {
    window.clear(clearColor);
    
    // Draw game objects here
    //displayTexture("C:\\Users\\USER\\Pictures\\politechnika.png", object.getX(), object.getY());
    
    object0.Draw(&window, texture0);

    BirdyObj.Draw(&window, Birdy, *BirdyIndicies.get(), (int)(Birdy.getSize().x / 5.0f),
        (int)(Birdy.getSize().y / 3.0f), 14, 5, true);

    //primitiveRenderer.drawCircle(400.0f, 300.0f, 50, sf::Color::Red, 2.0f);
         // primitiveRenderer.drawRectangle(200.0f, 200.0f, 100.0f, 50.0f, sf::Color::Blue, 10.0f);
         // primitiveRenderer.drawLine(50.0f, 50.0f, 200.0f, 150.0f, 2.0f, sf::Color::Green);

         // Draw the point using the Point2D class
    point.draw(primitiveRenderer);

    // Draw the line segment using the LineSegment class
    lineSegment.draw(primitiveRenderer, true); // Use incremental drawing algorithm

    // Example: Draw an open polyline
    std::vector<sf::Vector2f> openPolylinePoints = { sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 150.0f), sf::Vector2f(300.0f, 100.0f) };
    primitiveRenderer.drawPolyline(openPolylinePoints, sf::Color::Yellow, 2.0f);

    // Example: Draw a closed polyline
    std::vector<sf::Vector2f> closedPolylinePoints = { sf::Vector2f(400.0f, 100.0f), sf::Vector2f(500.0f, 150.0f), sf::Vector2f(600.0f, 100.0f) };
    primitiveRenderer.drawPolyline(closedPolylinePoints, sf::Color::Cyan, 2.0f, true);

    // Example: Draw a circle with 8-fold symmetry
    primitiveRenderer.drawCircleSymmetric(300.0f, 300.0f, 50, sf::Color::Magenta, 2.0f, 8);

    // Example: Draw a circle with 4-fold symmetry
    primitiveRenderer.drawCircleSymmetric(500.0f, 300.0f, 50, sf::Color::Yellow, 2.0f, 4);

    // Example: Draw a circle using the default algorithm
    primitiveRenderer.drawCircle(700.0f, 300.0f, 50, sf::Color::Cyan, 2.0f);

    // Inside Engine::render() method or any other appropriate place:
    primitiveRenderer.drawEllipse(600.0f, 300.0f, 80.0f, 40.0f, sf::Color::Red, 2.0f, 8);



    window.display();
}

void Engine::initialize() {
    // Initialization code goes here
}

void Engine::cleanup() {
    // Cleanup code goes here
}

bool Engine::getIsRunning() const {
    return isRunning;
}
