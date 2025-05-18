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

    // Clock for internal timing
    sf::Clock deltaClock;

    // Shape names for imgui combo list
    // I have to convert the strings to c style string to use them for combo box
    // I also need to have them stored here so they do not disappear
    std::vector<std::string> shapesNamesStrings;
    std::vector<const char*> shapeNames;
    static int item_current = 0;
    for (int i = 0; i < shapes.size(); i++)
    {
        shapesNamesStrings.push_back(shapes[i].shapeName());
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        shapeNames.push_back(shapesNamesStrings[i].c_str());
    }

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

            if (shape.canDraw())
            {
                shape.draw(window);
            }
            
            float winW = window.getSize().x;
            float winH = window.getSize().y;
            float r = shape.shapeRadius();
            float x = shape.shapeX();
            float y = shape.shapeY();
            float w = shape.shapeWidth();
            float h = shape.shapeHeight();
            float xSpeed = shape.shapeXSpeed();
            float ySpeed = shape.shapeYSpeed();
            float scale = shape.scale();

            if (shape.isCircle())
            {
                // Bounce on X axis
                if (x < 0 || x  + 2*r * scale > winW)
                {
                    float newXSpeed = xSpeed * -1;
                    shape.setShapeXSpeed(newXSpeed);
                }

                // Bounce on Y axis
                if (y < 0 || y + 2*r * scale> winH)
                {
                    float newYSpeed = ySpeed * -1;
                    shape.setShapeYSpeed(newYSpeed);
                }
            }
            else
            {
                // Bounce on X axis
                if (x < 0 || x + w * scale > winW)
                {
                    float newXSpeed = xSpeed * -1;
                    shape.setShapeXSpeed(newXSpeed);
                }

                // Bounce on Y axis
                if (y < 0 || y + h * scale  > winH)
                {
                    float newYSpeed = ySpeed * -1;
                    shape.setShapeYSpeed(newYSpeed);
                }
            }
        }

        // ImGui Ui
        ImGui::Begin("Shape Properties");

        Shape& currentShape = shapes[item_current];
        ImGui::Combo("Shape", &item_current, shapeNames.data(), shapeNames.size());

        bool draw = currentShape.canDraw();
        if (ImGui::Checkbox("Draw Shape", &draw)) 
        {
            currentShape.setCanDraw(draw);
        }

        float scale = currentShape.scale();
        if (ImGui::SliderFloat("Scale", &scale, 0.0f, 5.0f))
        {
            currentShape.setScale(scale);
        }

        // Manually set slider width to keep velocity boxes inside window
        float sliderWidth = 200.0f; 
        // Force width on imgui widget
        ImGui::PushItemWidth(sliderWidth);
        // get shape xspeed
        float xSpeed = currentShape.shapeXSpeed();
        // Create the slider that controls x speed
        if (ImGui::SliderFloat("##VelocityX", &xSpeed, -10.0f, 10.0f))
        {
            currentShape.setShapeXSpeed(xSpeed);
        }

        // keep everything on the same line
        ImGui::SameLine();

        float ySpeed = currentShape.shapeYSpeed();
        if (ImGui::SliderFloat("##VelocityY", &ySpeed, -10.0f, 10.0f))
        {
            currentShape.setShapeYSpeed(ySpeed);
        }

        // Stop setting width
        ImGui::PopItemWidth();
        ImGui::SameLine();
        // Make label for both velocity boxes
        ImGui::Text("Velocity");

        // Casting the integers and floats because it makes the numbers more precise
        float imguiColor[3] = { static_cast<float>(currentShape.shapeR()) / 255,static_cast<float>(currentShape.shapeG()) / 255, static_cast<float>(currentShape.shapeB()) / 255 };
        if (ImGui::ColorEdit3("Shape Color", imguiColor))
            {
            currentShape.setShapeR(static_cast<int>(imguiColor[0] * 255));
            currentShape.setShapeG(static_cast<int>(imguiColor[1] * 255));
            currentShape.setShapeB(static_cast<int>(imguiColor[2] * 255));
            currentShape.setShapeColor();
        }

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

        //ImGui::ShowDemoWindow();

        // Draw ui last so it's on top
        ImGui::SFML::Render(window);
        // display window
        window.display();
    }

    // Make sure imgui gets destroyed when sfml quits out
    ImGui::SFML::Shutdown();

    return 0;
}