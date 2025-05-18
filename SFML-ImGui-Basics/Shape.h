#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Shape
{
    std::string mShapeName = "";
    float mShapeX, mShapeY = 0.0f;
    float mShapeXSpeed, mShapeYSpeed = 0.0f;
    int mShapeR, mShapeG, mShapeB = 0;
    float mShapeWidth, mShapeHeight, mShapeRadius = 0.0f;
    bool mIsCircle = false;
    sf::CircleShape mCircle;
    sf::RectangleShape mRectangle;
    bool mCanDraw = true;
    float mScale = 1.0f;
    

public:
    Shape(std::string name, float x, float y, float xSpeed, float ySpeed, int r, int g, int b, float width, float height) :
        mShapeName(name), mShapeX(x), mShapeY(y), mShapeXSpeed(xSpeed), mShapeYSpeed(ySpeed), mShapeR(r), mShapeG(g), mShapeB(b), mShapeWidth(width), mShapeHeight(height) 
    {
        mRectangle.setSize({ mShapeWidth, mShapeHeight });
        mRectangle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        mRectangle.setPosition({ mShapeX, mShapeY });
        mShapeRadius = 0.0f;
    }

    Shape(std::string name, float x, float y, float xSpeed, float ySpeed, int r, int g, int b, float radius) :
        mShapeName(name), mShapeX(x), mShapeY(y), mShapeXSpeed(xSpeed), mShapeYSpeed(ySpeed), mShapeR(r), mShapeG(g), mShapeB(b), mShapeRadius(radius) 
    {
        mCircle.setRadius(mShapeRadius);
        mCircle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        mCircle.setPosition({ mShapeX, mShapeY });
        mIsCircle = true;
        mShapeWidth = 0;
        mShapeHeight = 0;
    }

    std::string shapeName() 
    {
        return mShapeName;
    }

    float scale() const
    {
        return mScale;
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

    bool canDraw()
    {
        return mCanDraw;
    }

    int shapeR() const
    {
        return mShapeR;
    }

    int shapeG() const
    {
        return mShapeG;
    }

    int shapeB() const
    {
        return mShapeB;
    }

    void shapeX(float newX)
    {
        mShapeX = newX;
    }

    void shapeY(float newY)
    {
        mShapeY = newY;
    }

    void setShapeXSpeed(float newXSpeed)
    {
        mShapeXSpeed = newXSpeed;
    }

    void setShapeYSpeed(float newYSpeed)
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

    void setCanDraw(bool draw)
    {
        mCanDraw = draw;
    }

    void setShapeR(int newR)
    {
        mShapeR = newR;
    }

    void setShapeG(int newG)
    {
        mShapeG = newG;
    }

    void setShapeB(int newB)
    {
        mShapeB = newB;
    }

    void setShapeName(char* newName)
    {
        mShapeName = newName;
    }

    void setScale(float scale)
    {
        mScale = scale;

        if (mIsCircle)
        {
            mCircle.setScale({ scale, scale });
        }
        else
        {
            mRectangle.setScale({ scale, scale });
        }
    }


    void draw(sf::RenderWindow& window)
    {
        if (mIsCircle)
        {
            window.draw(mCircle);
        }
        else
        {
            window.draw(mRectangle);
        }
    }

    void update()
    {
        mShapeX += mShapeXSpeed;
        mShapeY += mShapeYSpeed;

        if (mIsCircle)
        {
            mCircle.setPosition({ mShapeX, mShapeY });
        }   
        else
        {
            mRectangle.setPosition({ mShapeX, mShapeY });
        }
    }

    void setShapeColor()
    {
        if (mIsCircle)
        {
            mCircle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        }
        else
        {
            mRectangle.setFillColor(sf::Color(mShapeR, mShapeG, mShapeB));
        }
    }
};