# define ftype int
# define PI 3.14159265

struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const {
        return point2d(*this) /= t;
    }
};

point2d operator*(ftype a, point2d b) {
    return b * a;
}

//Dot product
ftype dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}

ftype norm(point2d a) {
    return dot(a, a);
}

//Length of "position" vector a
double abs(point2d a) {
    return sqrt(norm(a));
}

//Projection of a on b: |a|cos(theta) = a.b/|b|
double proj(point2d a, point2d b) {
    return dot(a, b) / abs(b);
}

double angle(point2d a, point2d b) {
	//For angle in terms of degree :
	// return acos(dot(a, b) / abs(a) / abs(b)) * 180.0/PI;
	//Angle theta in terms of radians
    return acos(dot(a, b) / abs(a) / abs(b));
}

ftype cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}

//Line Intersection: Returns the point of intersection of 2 lines
//a1 -> initial point; d1 -> direction
//r = a1 + t.d1 -> t is a parameter
point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
