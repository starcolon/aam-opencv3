/**
 * Generic Shape Model
 */

#ifndef SHAPE_MODEL
#define SHAPE_MODEL

#include "master.h"
#include "IO.h"
#include "aux.h"

class Shape
{
protected:
  Rect constraint;
  vector<Point2d> vertices; // Triangulated mesh vertices
  Mat app; // Appearance image
  Subdiv2D subdiv;

public:
  Shape(){};
  Shape(const Rect& size);
  Shape(const Rect& size, const vector<Point2d>& vs);
  Shape(const Shape& original);
  virtual ~Shape(){};
  size_t length() const { return this->vertices.size(); };
  Rect size() const { return constraint; }

  void setAppearance(const Mat& src);
  void resize(const Size& newSize);
  void normalise();
  void applyParameters(const vector<double>& params);
  vector<Point2d> convexHull() const;

  // Render the shape onto a background image
  // into an IO object.
  void render(IO::GenericIO io, Mat background, double scaleFactor = 1.0) const;
};



#endif