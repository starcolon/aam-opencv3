#include "ShapeCollection.h"

const ShapeCollection& ShapeCollection::normaliseScalingTranslation() const
{
  // Rescale each shape so the centroid size = 1
  // and translate to the centroid
  vector<Shape> scaled;
  for (auto shape : this->items)
  {
    auto centroid = shape.centroid();
    auto cdist    = shape.sumSquareDistanceToPoint(centroid);
    scaled.push_back((shape * (1.0/cdist)) >> centroid);
  }
  return ShapeCollection(scaled);
}

const ShapeCollection& ShapeCollection::normaliseRotation() const
{
  vector<Shape> norml;
  // Use the first shape as base rotation = 0
  Mat x0 = this->items[0].mat;
  for (auto shapeIter=this->items.begin()+1; shapeIter!=this->items.end(); shapeIter++)
  {
    // Compute SVD on xj•x0
    Mat xj = shapeIter->mat;
    Mat xx = mul(xj.t(), x0);
    auto svd = SVD(xx, FULL_UV);
    u = svd.u;
    v = svt.vt.t();
    vut = mul(v, u.t()) ;

    auto theta = acos(vut.at(0,0));

    // TAOTODO: rotate shape by theta and store in norm<>
  }

  return ShapeCollection(norml);
}