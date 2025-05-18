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
    sf::CircleShape mCircle;
    sf::RectangleShape mRectangle;

public:
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

    float shapeX() const
    {
        return mShapeX;
    }

    float shapeY() const
    {
        return mShapeY;
    }

    float shapeXSpeed() const
    {
        return mShapeXSpeed;
    }

    float shapeYSpeed() const
    {
        return mShapeYSpeed;
    }

    float shapeWidth() const
    {
        return mShapeWidth;
    }

    float shapeHeight() const
    {
        return mShapeHeight;
    }

    float shapeRadius() const
    {
        return mShapeRadius;
    }

    bool isCircle() const
    {
        return mIsCircle;
    }

    void shapeX(float newX)
    {
        mShapeX = newX;
    }

    void shapeY(float newY)
    {
        mShapeY = newY;
    }

    void shapeXSpeed(float newXSpeed)
    {
        mShapeXSpeed = newXSpeed;
    }

    void shapeYSpeed(float newYSpeed)
    {
        mShapeYSpeed = newYSpeed;
    }

    void shapeWidth(float newShapeWidth) 
    {
        mShapeWidth = newShapeWidth;
    }

    void shapeHeight(float newShapeHeight)
    {
        mShapeHeight = newShapeHeight;
    }

    void shapeRadius(float newShapeRadius) 
    {
        mShapeRadius = newShapeRadius;
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