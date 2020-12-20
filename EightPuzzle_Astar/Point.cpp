//This source implements methods of class Point
#include "Point.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

//Constructor
template<typename T>
Point<T>::Point()  :x(0),y(0)
{   //Default constructor
    //std::cout <<"Default constructor was called\n";
}
template<typename T>
Point<T>::Point(const Point & pt)  :x(pt.x),y(pt.y)        //copy constructor
{
    //std::cout <<"copy constructor was called...\n";
}
template <typename T>
Point<T>::Point(T newX, T newY)  :x(newX),y(newY)     //parametrized constructor
{

}
template <typename T>
Point<T>::Point(T xy) :x(xy),y(xy)        //constructor that accepts one T as argument
{

}
template <typename T>
Point<T>::~Point()
{   //Destructor
    //std::cout <<"Bye my point...\n";
}

// Method ToString() convert a Point to a string representation
template <typename T>
std::string Point<T>::ToString() const
{
    std::stringstream ss;
    ss << "Point(" << x << ", " << y << ")" ;
    return ss.str();
}
template <typename T>
T Point<T>::Distance() const// Calculate the distance to the origin (0, 0).
{
    return std::sqrt (x*x+y*y);
}
template <typename T>
T Point<T>::Distance(const Point<T> & p) const// Calculate the distance between two points.
{
    //p.x=x;        //this results in complier error since point p is const
    T dx=x-p.x;
    T dy=y-p.y;
    return std::sqrt(dx*dx+dy*dy);
}
//Operators
template <typename T>
Point<T> Point<T>::operator - () const    // Negate the coordinates.
{
    return Point<T> (-x,-y);
}
template <typename T>
Point<T> Point<T>::operator * (T factor) const   // Scale the coordinates.
{
    return  Point<T> (factor*x,factor*y);
}
template <typename T>
Point<T> Point<T>::operator + (const Point<T>& p) const  // Add coordinates.
 {
    return Point<T>(x+p.x,y+p.y);
 }
 template <typename T>
bool Point<T>::operator == (const Point<T>& p) const  // Equally compare operator.
{
    return x==p.x && y==p.y;
}
template <typename T>
Point<T>& Point<T>::operator = (const Point<T>& source)  // Assignment operator.
{
// Avoid doing assign to myself
	if (this == &source)
		return *this;

	x = source.x;
	y = source.y;

	return *this;
}
template <typename T>
Point<T>& Point<T>::operator *= (T factor)   // Scale the coordinates & assign.
{
    x*=factor;
    y*=factor;
	return *this;
}
//added global operator for exercise 2.4.2
template <typename T>
std::ostream& operator << (std::ostream& os, const Point<T>& pt)
{ // Print the point

	os << "Point("<<pt.x<<","<<pt.y<<")";
	return os;
}
