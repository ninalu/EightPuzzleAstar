//This is header file exercise1 section 2.4

#ifndef POINT_HEADER_FILE
#define POINT_HEADER_FILE

#include <string>
#include <iostream>

template<typename T>
class Point
{
private:
    T x;   //x coordinate
    T y;   //y coordinate
public:
    Point();                            //default constructor
    Point(const Point & pt);            //copy constructor
    Point(T newX, T newY);    //parametrized constructor
    explicit Point(T xy);          //constructor that accepts one T as argument
    //Destructor
    ~Point();

    //Normal inline for Getter functions for the x-and y-coordinates
    //code in header file
    T X() const;
    T Y() const;

    //Default inline for Setter functions for the x- and y- coordinates
    void X(T newX)
    {
        x=newX;
    }
    void Y(T newY)
    {
        y=newY;
    }
    std::string ToString() const;

    T Distance() const; // Calculate the distance to the origin (0, 0).
    T Distance(const Point & p) const; // Calculate the distance between two points.

    //Operators
    Point operator - () const; // Negate the coordinates.
    Point operator * (T factor) const; // Scale the coordinates.
    Point operator + (const Point& p) const; // Add coordinates.
    bool operator == (const Point& p) const; // Equally compare operator.
    Point& operator = (const Point& source); // Assignment operator.
    Point& operator *= (T factor); // Scale the coordinates & assign.
    //added friend global operator for exercise 2.4.4
    template<typename U>
    friend std::ostream& operator << (std::ostream& os, const Point<U>& pt);
};

//Normal inline for Getter functions for the x-and y-coordinates
//code in header file
template<typename T>
inline T Point<T>::X() const
{
    return x;
}
template<typename T>
inline T Point<T>::Y() const
{
    return y;
}
#include "Point.cpp"
#endif
