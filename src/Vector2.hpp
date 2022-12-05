#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    Vector2() : x(0.0), y(0.0) { }
    Vector2(float x, float y) : x(x), y(y) { }
    float getX() const { return x; };
    float getY() const { return y; };
    void setX(const float x) { this->x = x; }
    void setY(const float y) { this->y = y; }
private:
    float x;
    float y;
};

#endif
