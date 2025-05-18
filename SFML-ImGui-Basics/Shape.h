#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Shape
{
    std::string mShapeName;
    float mShapeX, mShapeY;
    float mShapeXSpeed, mShapeYSpeed;
    int mShapeR, mShapeG, mShapeB;
    float mShapeWidth, mShapeHeight, mShapeRadius;
    bool mIsCircle = false;

public:
    sf::CircleShape mCircle;
    sf::RectangleShape mRectangle;

    Shape(std::string name, float x, float y, float xSpeed, float ySpeed, int r, int g, int b, float width, float height) :
        mShapeName(name), mShapeX(x), mShapeY(y), mShapeXSpeed(xSpeed), mShapeYSpeed(ySpeed), mShapeR(r), mShapeG(g), mShapeB(b), mShapeWidth(width), mShapeHeight(height) 
    {
        mRectangle.setSize({ mShapeWidth, mShapeHeight });
        mRectangle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        mRectangle.setPosition({ mShapeX, mShapeY });
    }

    Shape(std::string name, float x, float y, float xSpeed, float ySpeed, int r, int g, int b, float radius) :
        mShapeName(name), mShapeX(x), mShapeY(y), mShapeXSpeed(xSpeed), mShapeYSpeed(ySpeed), mShapeR(r), mShapeG(g), mShapeB(b), mShapeRadius(radius) 
    {
        mCircle.setRadius(mShapeRadius);
        mCircle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        mCircle.setPosition({ mShapeX, mShapeY });
        mIsCircle = true;
    }

    void draw(sf::RenderWindow& window)
    {
        if (mIsCircle)
            window.draw(mCircle);
        else
            window.draw(mRectangle);
    }

    void update()
    {
        mShapeX += mShapeXSpeed;
        mShapeY += mShapeYSpeed;

        if (mIsCircle)
            mCircle.setPosition({ mShapeX, mShapeY });
        else
            mRectangle.setPosition({ mShapeX, mShapeY });
    }
};