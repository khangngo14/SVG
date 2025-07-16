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




int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Rectangle(20, 20, 800, 400, "rgb(55,55,55)", "rgb(200,100,150)", 2, 0.2, 1.0));

    cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\">\n";
    for (auto s : shapes) {
        cout << s->toSVG();
        delete s;
    }
    cout << "</svg>" << endl;

    return 0;
}
