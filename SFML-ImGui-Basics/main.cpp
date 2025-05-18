#include <iostream>
#include <fstream>
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Shape.h"


int main() 
{
    // Read config file
    std::ifstream myFileStream("config.txt");
    std::string temp;
    // Window variables
    unsigned int wWidth = 0;
    unsigned int wHeight = 0;
    // Font variables
    std::string fontFilename;
    int fontSize;
    int fontR;
    int fontG;
    int fontB;
    // Shapes variables
    std::string shapeName;
    float shapeX;
    float shapeY;
    float shapeXSpeed;
    float shapeYSpeed;
    int shapeR;
    int shapeG;
    int shapeB;
    float shapeWidth;
    float shapeHeight;
    float shapeRadius;

    // Shapes vector
    std::vector<Shape> shapes;

    // If the file doesn't open we tell the user and exit out
    if (!myFileStream)
    {
        std::cout << "Error: Unable to open file for reading.\n";
        return -1;
    }

    // Read every word of every line
    while (myFileStream >> temp)
    {
        // If word equals Window next to words are width and height
        if (temp == "Window")
        {
            myFileStream >> wWidth >> wHeight;
        }

        // If word equals Font next lines are for font variables
        if (temp == "Font")
        {
            myFileStream >> fontFilename >> fontSize >> fontR >> fontG >> fontB;
        }

        // Shapes create a custom shape class to be stored in shapes vector
        if (temp == "Circle")
        {
            myFileStream >> shapeName >> shapeX >> shapeY >> shapeXSpeed >> shapeYSpeed >> shapeR >> shapeG >> shapeB >> shapeRadius;
            Shape shape(shapeName, shapeX, shapeY, shapeXSpeed, shapeYSpeed, shapeR, shapeG, shapeB, shapeRadius);
            shapes.push_back(shape);
        }

        if (temp == "Rectangle")
        {
            myFileStream >> shapeName >> shapeX >> shapeY >> shapeXSpeed >> shapeYSpeed >> shapeR >> shapeG >> shapeB >> shapeWidth >> shapeHeight;
            Shape shape(shapeName, shapeX, shapeY, shapeXSpeed, shapeYSpeed, shapeR, shapeG, shapeB, shapeWidth, shapeHeight);
            shapes.push_back(shape);
        }
    }

    // Create a window with the given width and height
    sf::RenderWindow window(sf::VideoMode({ wWidth, wHeight }), "Shapes");

    // Cap Frame Rate 
    window.setFramerateLimit(60);

    // Initialize ImGui 
    ImGui::SFML::Init(window);

    // Scale ImGui ui and text size by 2
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    // Circle rgb values
    float c[3] = { 0.0f, 1.0f, 1.0f };

    // Shape properties based on the config.txt
    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 0.5f;
    bool drawCircle = true;
    bool drawText = true;

    // Create a circle with the given properties
    sf::CircleShape shape(circleRadius, circleSegments);
    shape.setFillColor(sf::Color::Green);

    // Load font from fonts folder
    // If it doesn't load send an error message
    sf::Font font;
    if (!font.openFromFile(fontFilename))
    {
        std::cerr << "Failed to load font!\n";
        return -1;
    }

    // Create text object with the font
    // Set its size, color, and position on the screen
    sf::Text text(font);  
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color(fontR, fontG, fontB));
    text.setPosition({100.f, 100.f});

    // Make display string to set text
    char displayString[255] = "Sample Text";

    // Clock for internal timing
    sf::Clock deltaClock;

    // While window is active
    while (window.isOpen()) {
        // Event handler
        while (const auto event = window.pollEvent()) {
            // pass event for ImGui to parse
            ImGui::SFML::ProcessEvent(window, *event);
            // this event happens when window is closes
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Update ImGui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        // clear window every frame to get rid of drawn shapes
        window.clear();

        for (Shape& shape : shapes)
        {
            shape.update();
            shape.draw(window);
        }

        // ImGui Ui
        ImGui::Begin("Window Title");
        ImGui::Text("Window Text!");
        ImGui::Checkbox("Draw Circle", &drawCircle);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Text", &drawText);
        ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 64);
        ImGui::ColorEdit3("Circle Color", c);
        ImGui::InputText("Text", displayString, 255);

        // Press button to set text string
        if (ImGui::Button("Set Text"))
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset Circle"))
        {
            shape.setPosition({ 0.0f, 0.0f });
        }
        // End of Ui box
        ImGui::End();

        // set circle properties again in case ui changed them
        shape.setPointCount(circleSegments);
        shape.setRadius(circleRadius);

        // Imgui uses 0-1 for colors but sfml uses 0-255 so we have to conver
        shape.setFillColor(sf::Color(c[0] * 255, c[1] * 255, c[2] * 255));

        // Move circle based on circleSpeedX and Y
        shape.move({ circleSpeedX, circleSpeedY });

        // Draw ui last so it's on top
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // Make sure imgui gets destroyed when sfml quits out
    ImGui::SFML::Shutdown();

    return 0;
}