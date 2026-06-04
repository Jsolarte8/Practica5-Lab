#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D operator+(const Vector2D& otro) const;
    Vector2D operator-(const Vector2D& otro) const;
    Vector2D operator*(double escalar) const;
    Vector2D operator/(double escalar) const;

    Vector2D& operator+=(const Vector2D& otro);
    Vector2D& operator-=(const Vector2D& otro);
    Vector2D& operator*=(double escalar);
    Vector2D& operator/=(double escalar);

    double magnitud() const;
    double magnitudCuadrada() const;
    Vector2D normalizado() const;
    double punto(const Vector2D& otro) const;
};

Vector2D operator*(double escalar, const Vector2D& vector);

#endif
