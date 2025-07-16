#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath> 

using namespace std;

class Shape {
protected:
    string strokeColor;
    string fillColor;
    float strokeWidth;
    float fillOpacity;
    float strokeOpacity;

public:
    Shape(string stroke = "black", string fill = "none", float strokeW = 1.0, float fillO = 1.0, float strokeO = 1.0)
        : strokeColor(stroke), fillColor(fill), strokeWidth(strokeW), fillOpacity(fillO), strokeOpacity(strokeO) {}

    virtual string toSVG() const = 0;
    virtual ~Shape() = default;
};

class Line : public Shape {
    float x1, y1, x2, y2;

public:
    Line(float x1, float y1, float x2, float y2,
         string stroke, float strokeW, float strokeO)
        : Shape(stroke, "none", strokeW, 0, strokeO), x1(x1), y1(y1), x2(x2), y2(y2) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
            << "\" stroke=\"" << strokeColor << "\" stroke-width=\"" << strokeWidth
            << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};

class Rectangle : public Shape {
    float x, y, width, height;

public:
    Rectangle(float x, float y, float width, float height,
              string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Shape(stroke, fill, strokeW, fillO, strokeO), x(x), y(y), width(width), height(height) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width
            << "\" height=\"" << height << "\" stroke=\"" << strokeColor
            << "\" fill=\"" << fillColor << "\" stroke-width=\"" << strokeWidth
            << "\" fill-opacity=\"" << fillOpacity << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};

class Circle : public Shape {
    float cx, cy, r;

public:
    Circle(float cx, float cy, float r,
           string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Shape(stroke, fill, strokeW, fillO, strokeO), cx(cx), cy(cy), r(r) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r
            << "\" stroke=\"" << strokeColor << "\" fill=\"" << fillColor
            << "\" stroke-width=\"" << strokeWidth << "\" fill-opacity=\"" << fillOpacity
            << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};

class Polygon : public Shape {
    vector<pair<float, float>> points;

public:
    Polygon(const vector<pair<float, float>>& pts,
            string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Shape(stroke, fill, strokeW, fillO, strokeO), points(pts) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<polygon points=\"";
        for (auto& p : points)
            oss << p.first << "," << p.second << " ";
        oss << "\" stroke=\"" << strokeColor << "\" fill=\"" << fillColor
            << "\" stroke-width=\"" << strokeWidth << "\" fill-opacity=\"" << fillOpacity
            << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};

class Text : public Shape {
    float x, y;
    string content;
    int fontSize;

public:
    Text(float x, float y, string content, int size, string color)
        : Shape(color, "none", 0, 0, 1.0), x(x), y(y), content(content), fontSize(size) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<text x=\"" << x << "\" y=\"" << y << "\" fill=\"" << strokeColor
            << "\" font-size=\"" << fontSize << "\">" << content << "</text>\n";
        return oss.str();
    }
};

class Square : public Rectangle {
public:
    Square(float x, float y, float side,
           string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Rectangle(x, y, side, side, stroke, fill, strokeW, fillO, strokeO) {}
};

class Triangle : public Polygon {
public:
    Triangle(pair<float, float> p1, pair<float, float> p2, pair<float, float> p3,
             string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Polygon({p1, p2, p3}, stroke, fill, strokeW, fillO, strokeO) {}
};

class Hexagon : public Polygon {
public:
    Hexagon(float cx, float cy, float radius,
            string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Polygon(generateHexagonPoints(cx, cy, radius), stroke, fill, strokeW, fillO, strokeO) {}

private:
    static vector<pair<float, float>> generateHexagonPoints(float cx, float cy, float r) {
        vector<pair<float, float>> pts;
        for (int i = 0; i < 6; ++i) {
            float angle = M_PI / 3 * i;  
            pts.emplace_back(cx + r * cos(angle), cy + r * sin(angle));
        }
        return pts;
    }
};



class Ellipse : public Shape {
    float cx, cy, rx, ry;

public:
    Ellipse(float cx, float cy, float rx, float ry,
            string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Shape(stroke, fill, strokeW, fillO, strokeO), cx(cx), cy(cy), rx(rx), ry(ry) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<ellipse cx=\"" << cx << "\" cy=\"" << cy << "\" rx=\"" << rx
            << "\" ry=\"" << ry << "\" stroke=\"" << strokeColor
            << "\" fill=\"" << fillColor << "\" stroke-width=\"" << strokeWidth
            << "\" fill-opacity=\"" << fillOpacity << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};

class Polyline : public Shape {
    vector<pair<float, float>> points;

public:
    Polyline(const vector<pair<float, float>>& pts,
             string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Shape(stroke, fill, strokeW, fillO, strokeO), points(pts) {}

    string toSVG() const override {
        ostringstream oss;
        oss << "<polyline points=\"";
        for (auto& p : points)
            oss << p.first << "," << p.second << " ";
        oss << "\" stroke=\"" << strokeColor << "\" fill=\"" << fillColor
            << "\" stroke-width=\"" << strokeWidth << "\" fill-opacity=\"" << fillOpacity
            << "\" stroke-opacity=\"" << strokeOpacity << "\" />\n";
        return oss.str();
    }
};


class Star : public Polygon {
public:
    Star(float cx, float cy, float outerR, float innerR,
         string stroke, string fill, float strokeW, float fillO, float strokeO)
        : Polygon(generateStarPoints(cx, cy, outerR, innerR), stroke, fill, strokeW, fillO, strokeO) {}

private:
    static vector<pair<float, float>> generateStarPoints(float cx, float cy, float R, float r) {
        vector<pair<float, float>> pts;
        for (int i = 0; i < 10; ++i) {
            float angle = i * M_PI / 5; 
            float radius = (i % 2 == 0) ? R : r;
            pts.emplace_back(cx + radius * cos(angle), cy + radius * sin(angle));
        }
        return pts;
    }
};

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Ellipse(400, 500, 300, 80, "none", "lightblue", 0, 0.5, 1.0));
    shapes.push_back(new Star(400, 200, 60, 30, "orange", "yellow", 4, 0.9, 1.0));
    vector<pair<float, float>> mountainPoints = {
        {100, 500}, {300, 300}, {500, 500}
    };
    shapes.push_back(new Polygon(mountainPoints, "darkgreen", "lightgreen", 2, 1.0, 1.0));
    vector<pair<float, float>> birdPoints = {
        {600, 200}, {620, 180}, {640, 200}
    };
    shapes.push_back(new Polyline(birdPoints, "black", "none", 2, 0, 1.0));




    
    cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\">\n";
    for (auto s : shapes) {
        cout << s->toSVG();
        delete s;
    }
    cout << "</svg>" << endl;

    return 0;
}
