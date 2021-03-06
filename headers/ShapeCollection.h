/**
 * Series of Shape for training process
 */

#ifndef SHAPE_COLLECTION
#define SHAPE_COLLECTION

#include "IO.h"
#include "master.h"
#include "Shape.h"
#include "BaseModel.h"
#include "ModelCollection.h"

class ShapeCollection : public ModelCollection
{
public:
  inline ShapeCollection() : ModelCollection() {};
  ShapeCollection(const ShapeCollection& original) : ModelCollection(original.items) {};
  ShapeCollection(const vector<BaseModel*>& models) : ModelCollection(models) {};
  ShapeCollection(const vector<Shape*>& shapes);
  
  // ---------- Transformations ---------------
  unique_ptr<ModelCollection> clone() const;
  void normaliseScalingTranslation();
  void normaliseRotation();
  void translateBy(const Point2d &p);

  // ---------- I/O ------------------
  void renderShapeVariation(IO::GenericIO* io, Size sz, double scaleFactor=1.0, Point2d recentred=Point2d(0,0)) const;
  Mat toMat() const;
};




#endif