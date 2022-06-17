#ifndef LISKOW_SUBSTITUTION_HPP_89slpl
#define LISKOW_SUBSTITUTION_HPP_89slpl

namespace SolidDesign
{
    class Rectangle
    {
    public:
        Rectangle(int width, int height) : width(width), height(height) {}

        ///< setters and getters --
        void setWidth(int value) { width = value; }
        void setHeight(int value) { height = value; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        int area() const { return width * height; }
    protected:
        int width, height;
    };


    class Square : public Rectangle
    {
    public:
        Square(int width) : Rectangle(width, width) {}

        void setWidth(int value) { this->width = this->height = value; }
        void setHeight(int value) { this->height = this->width = value; }
    };
}

#endif /* end of include guard : LISKOW_SUBSTITUTION_HPP_89slpl */