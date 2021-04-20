/*
* Author: Ilan Valencius
* Email: valencig@bc.edu
* Note: add -lm when compiling to link with math.h library.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

// Stores x and y values of point.
typedef struct PointData {
    double x;
    double y;
    char str[64];
} PointData;

// Returns x value of a point.
double Point_x(Point * this) {
    return this->data->x;
}

// Returns y value of a point.
double Point_y(Point * this) {
    return this->data->y;
}

// Initialized a point and its data.
void PointData_init(Point * this, double x, double y) {
    this->data->x = x;
    this->data->y = y;
    sprintf(this->data->str,"(%f,%f)",this->data->x,this->data->y);
}
// Returns the magnitude of a point.
double Point_magnitude(Point * this) {
    return sqrt((this->data->x * this->data->x) + (this->data->y * this->data->y));
}

// Calculates the distance between 2 points (p2 - p1).
double Point_distance(Point * p1, Point * p2) {
    return sqrt((p2->data->x - p1->data->x) * (p2->data->x - p1->data->x)  + (p2->data->y - p1->data->y) * (p2->data->y - p1->data->y));
}

// Returns string representation of a point.
char * Point_string(Point * this) {
    return this->data->str;
}

// Deletes a point
void Point_free(Point * this) {
    free(this->data);
    free(this);
}

// Maps function addresses to a point.
void Point_functions_init(Point * this) {
    this->magnitude = &Point_magnitude;
    this->distance = &Point_distance;
    this->to_string = &Point_string;
    this->delete = &Point_free;
    this->x = &Point_x;
    this->y = &Point_y;
}

// Initialized new point with x and y values.
Point * Point_new(double x, double y) {
    Point * p = (struct Point *) malloc(sizeof(struct Point));
    p -> data = malloc(sizeof(struct PointData));
    PointData_init(p,x,y);
    Point_functions_init(p);
    return p;
}
