#include <iostream>

class Position
{
private:
    int latitude; //широта(Y)
    int longitude; //долгота(X)
public:
    Position(){}
    Position(int x, int y)
    {
        longitude = x;
        latitude = y;
    }
    friend std::istream& operator>>(std::istream& is, Position& p)
    {
        is >> p.longitude >> p.latitude;
        if (p.longitude > 90) p.longitude = p.longitude % 90 - 90;
        if (p.longitude < -90) p.longitude = p.longitude % 90 + 90;
        if (p.latitude > 180) p.latitude = p.latitude % 180 - 180;
        if (p.latitude < -180) p.latitude = p.latitude % 180 + 180;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Position& p)
    {
        os << "долгота:" << p.longitude << " широта:" << p.latitude;
        return os;
    }
    Position operator+(const Position& p)
    {
        longitude += p.longitude;
        latitude += p.latitude;
        if (longitude > 90) longitude = longitude % 90 - 90;
        if (longitude < -90) longitude = longitude % 90 + 90;
        if (latitude > 180) latitude = latitude % 180 - 180;
        if (latitude < -180) latitude = latitude % 180 + 180;
        return Position(longitude, latitude);
    }
    Position operator-(const Position& p)
    {
        longitude -= p.longitude;
        latitude -= p.latitude;
        if (longitude > 90) longitude = longitude % 90 - 90;
        if (longitude < -90) longitude = longitude % 90 + 90;
        if (latitude > 180) latitude = latitude % 180 - 180;
        if (latitude < -180) latitude = latitude % 180 + 180;
        return Position(longitude, latitude);
    }
    Position operator*(const Position& p)
    {
        longitude *= p.longitude;
        latitude *= p.latitude;
        if (longitude > 90) longitude = longitude % 90 - 90;
        if (longitude < -90) longitude = longitude % 90 + 90;
        if (latitude > 180) latitude = latitude % 180 - 180;
        if (latitude < -180) latitude = latitude % 180 + 180;
        return Position(longitude, latitude);
    }
    Position operator/(const Position& p)
    {
        longitude /= p.longitude;
        latitude /= p.latitude;
        if (longitude > 90) longitude = longitude % 90 - 90;
        if (longitude < -90) longitude = longitude % 90 + 90;
        if (latitude > 180) latitude = latitude % 180 - 180;
        if (latitude < -180) latitude = latitude % 180 + 180;
        return Position(longitude, latitude);
    }
    bool operator>(const Position& p)
    {
        return (longitude > p.longitude) && (latitude > p.latitude);
    }
    bool operator>=(const Position& p)
    {
        return (longitude >= p.longitude) && (latitude >= p.latitude);
    }
    bool operator<(const Position& p)
    {
        return (longitude < p.longitude) && (latitude < p.latitude);
    }
    bool operator<=(const Position& p)
    {
        return (longitude <= p.longitude) && (latitude <= p.latitude);
    }
    bool operator==(const Position& p)
    {
        return (longitude == p.longitude) && (latitude == p.latitude);
    }
    bool operator!=(const Position& p)
    {
        return (longitude != p.longitude) && (latitude != p.latitude);
    }
    ~Position(){}
};

int main()
{
    Position a,b;
    std::cin >> a >> b;
    std::cout << "позиция а: " << a << std::endl; 
    std::cout << "позиция б: " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b =" << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;
    if (a >= b) std::cout << "a >= b" << std::endl;
    if (a <= b) std::cout << "a <= b" << std::endl;
    if (a == b) std::cout << "a == b" << std::endl;
    if (a != b) std::cout << "a != b" << std::endl;
    return 0;
}
