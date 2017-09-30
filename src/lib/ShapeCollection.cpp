#include "ShapeCollection.h"

ShapeCollection ShapeCollection::normaliseScalingTranslation() const
{
  // Rescale each shape so the centroid size = 1
  // and translate to the centroid
  vector<Shape> scaled;
  for (auto shape : this->items)
  {
    auto centroid = shape.centroid();
    auto cdist    = shape.sumSquareDistanceToPoint(centroid);
    scaled.push_back((shape << centroid) * (1.0/cdist));
  }
  return ShapeCollection(scaled);
}

ShapeCollection ShapeCollection::translateBy(const Point2d &p) const
{
  vector<Shape> tr;
  for (auto shape : this->items)
  {
    tr.push_back(shape >> p);
  }
  return ShapeCollection(tr);
}

ShapeCollection ShapeCollection::normaliseRotation() const
{
  vector<Shape> norml;
  // Use the first shape as base rotation = 0
  Mat x0 = this->items[0].mat;
  for (auto shapeIter=this->items.begin()+1; shapeIter!=this->items.end(); shapeIter++)
  {
    // Compute SVD on xj•x0
    Mat xj = shapeIter->mat;
    Mat xx = xj.t() * x0;
    auto svd = SVD(xx, SVD::FULL_UV);
    auto u = svd.u;
    auto v = svd.vt.t();
    auto R = v * u.t();

    // rotate shape by theta and store in norm<>
    norml.push_back(Shape(R * xj));
  }

  return ShapeCollection(norml);
}

vector<Shape> ShapeCollection::getItems() const
{
  return this->items;
}

void ShapeCollection::renderShapeVariation(IO::GenericIO* io, Size sz, double scaleFactor, Point2d recentred) const
{
  // TAOTODO: Find boundary of the shapes
  Mat canvas = Mat::zeros(sz, CV_8UC3);
  for (auto shape : this->items)
  {
    canvas = shape.render(io, canvas, scaleFactor, recentred);
    waitKey(100);
  }
}