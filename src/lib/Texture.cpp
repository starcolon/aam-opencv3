#include "Texture.h"

Triangle Triangle::operator >>(const Point2d &displacement) const
{
  Mat dist = Mat(3, 2, CV_64FC1);
  for (int i=0; i<3; i++)
  {
    dist.at<double>(i,0) = displacement.x;
    dist.at<double>(i,1) = displacement.y;
  }
  return Triangle(this->vertices + dist);
}

Triangle Triangle::operator <<(const Point2d &displacement) const
{
  Mat dist = Mat(3, 2, CV_64FC1);
  for (int i=0; i<3; i++)
  {
    dist.at<double>(i,0) = displacement.x;
    dist.at<double>(i,1) = displacement.y;
  }
  return Triangle(this->vertices - dist);
}

void Triangle::boundary(double& minX, double& minY, double& maxX, double& maxY) const
{
  minX = numeric_limits<double>::max();
  minY = numeric_limits<double>::max();
  maxY = -numeric_limits<double>::max();
  maxX = -numeric_limits<double>::max();
  for (int i=0; i<3; i++)
  {
    double x = this->vertices.at<double>(i,0);
    double y = this->vertices.at<double>(i,1);
    minX = x < minX ? x : minX;
    minY = y < minY ? y : minY;
    maxX = x > maxX ? x : maxX;
    maxY = y > maxY ? y : maxY;
  }
}

double Triangle::minX() const
{
  double a,b,c,d;
  boundary(a,b,c,d);
  return a;
}

double Triangle::minY() const
{
  double a,b,c,d;
  boundary(a,b,c,d);
  return b;
}

double Triangle::maxX() const
{
  double a,b,c,d;
  boundary(a,b,c,d);
  return c;
}

double Triangle::maxY() const
{
  double a,b,c,d;
  boundary(a,b,c,d);
  return d;
}

Point2d* Triangle::toArray() const
{
  Point2d *arr = new Point2d[3];
  for (int i=0; i<3; i++)
  {
    arr[i] = Point2d(vertices.at<double>(i,0), vertices.at<double>(i,1));
  }
  return arr;
}

void Texture::save(const string path) const
{

}

void Texture::load(const string path)
{

}

Mat Texture::render(IO::GenericIO* io, Mat background, double scaleFactor, Point2d recentre) const
{
  // TAOTODO:
}

/**
 * Piece-wise affine transformation.
 * Warping the texture to a new triangular boundary.
 */
Texture Texture::realignTo(const Triangle &newBound) const
{
  double minX, minY, maxX, maxY;
  newBound.boundary(minX, minY, maxX, maxY);

  Mat R( 2, 3, CV_64FC1 );
  Mat W( 2, 3, CV_64FC1 );

  // TAOTODO:

  return Texture(newBound, this->img);
}