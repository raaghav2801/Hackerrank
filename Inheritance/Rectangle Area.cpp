#include <iostream>

using namespace std;
class Rectangle {
    public:
    int width, height;
    Rectangle(){}
     void display() {
        cout << width << " " << height << "\n";
    }
};

class RectangleArea : public Rectangle {
    public:
    RectangleArea(){}
    void read_input() {
        cin >> width;
        cin >> height;
    }
     void display() {
        cout << width * height << "\n";
    }
};
int main()
{
    RectangleArea r_area;
    r_area.read_input();
    r_area.Rectangle::display();
    r_area.display();
    return 0;
}
