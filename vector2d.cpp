#include "vector2d.h"

#include <cmath>

Vector2D::Vector2D() : x(0.0), y(0.0) {}

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& otro) const {
    return Vector2D(x + otro.x, y + otro.y);
}

Vector2D Vector2D::operator-(const Vector2D& otro) const {
    return Vector2D(x - otro.x, y - otro.y);
}

Vector2D Vector2D::operator*(double escalar) const {
    return Vector2D(x * escalar, y * escalar);
}

Vector2D Vector2D::operator/(double escalar) const {
    return Vector2D(x / escalar, y / escalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& otro) {
    x += otro.x;
    y += otro.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& otro) {
    x -= otro.x;
    y -= otro.y;
    return *this;
}

Vector2D& Vector2D::operator*=(double escalar) {
    x *= escalar;
    y *= escalar;
    return *this;
}

Vector2D& Vector2D::operator/=(double escalar) {
    x /= escalar;
    y /= escalar;
    return *this;
}

double Vector2D::magnitud() const {
    return std::sqrt(magnitudCuadrada());
}

double Vector2D::magnitudCuadrada() const {
    return x * x + y * y;
}

Vector2D Vector2D::normalizado() const {
    const double mag = magnitud();
    if (mag == 0.0) {
        return Vector2D();
    }
    return *this / mag;
}

double Vector2D::punto(const Vector2D& otro) const {
    return x * otro.x + y * otro.y;
}

Vector2D operator*(double escalar, const Vector2D& vector) {
    return vector * escalar;
}
