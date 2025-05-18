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
    int fontSize = 0;
    int fontR = 0;
    int fontG = 0;
    int fontB = 0;
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

            float winW = window.getSize().x;
            float winH = window.getSize().y;
            float r = shape.shapeRadius();
            float x = shape.shapeX();
            float y = shape.shapeY();
            float w = shape.shapeWidth();
            float h = shape.shapeHeight();
            float xSpeed = shape.shapeXSpeed();
            float ySpeed = shape.shapeYSpeed();

            if (shape.isCircle())
            {
                // Bounce on X axis
                if (x - r < 0 || x + 2*r > winW)
                {
                    float newXSpeed = xSpeed * -1;
                    shape.shapeXSpeed(newXSpeed);
                }

                // Bounce on Y axis
                if (y < 0 || y + 2*r> winH)
                {
                    float newYSpeed = ySpeed * -1;
                    shape.shapeYSpeed(newYSpeed);
                }
            }
            else
            {
                // Bounce on X axis
                if (x < 0 || x + w  > winW)
                {
                    float newXSpeed = xSpeed * -1;
                    shape.shapeXSpeed(newXSpeed);
                }

                // Bounce on Y axis
                if (y < 0 || y + h  > winH)
                {
                    float newYSpeed = ySpeed * -1;
                    shape.shapeYSpeed(newYSpeed);
                }
            }
        }

        // ImGui Ui
        ImGui::Begin("Window Title");
        ImGui::Text("Window Text!");
        //ImGui::Checkbox("Draw Circle", &drawCircle);
        ImGui::SameLine();
       // ImGui::Checkbox("Draw Text", &drawText);
        //ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
       // ImGui::SliderInt("Sides", &circleSegments, 3, 64);
        //ImGui::ColorEdit3("Circle Color", c);
        ImGui::InputText("Text", displayString, 255);

        // Press button to set text string
        //if (ImGui::Button("Set Text"))
        //{
        //    text.setString(displayString);
        //}
        //ImGui::SameLine();
        //if (ImGui::Button("Reset Circle"))
        //{
        //    shape.setPosition({ 0.0f, 0.0f });
        //}
        // End of Ui box
        ImGui::End();

        // Draw ui last so it's on top
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // Make sure imgui gets destroyed when sfml quits out
    ImGui::SFML::Shutdown();

    return 0;
}