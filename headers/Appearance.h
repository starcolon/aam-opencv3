#ifndef APPEARANCE_MODEL
#define APPEARANCE_MODEL

#include "master.h"
#include "BaseModel.h"
#include "Shape.h"
#include "MeshShape.h"
#include "Texture.h"

/**
 * Statistical model of bounded texture
 */
class Appearance : public BaseModel
{
private:
protected:
  
  Mat graphic;
  MeshShape mesh;
  vector<Texture> textureList;

  void reinitTextures();
public:
  Appearance(const MeshShape& shape, const Mat& img);
  Appearance(const Appearance& another);
  virtual inline ~Appearance(){};

  const double procrustesDistance(const BaseModel* that) const;

  //------ I/O --------------
  Mat render(IO::GenericIO* io, Mat background, bool withVertices=true, bool withEdges=true, double scaleFactor=1.0, Point2d recentre=Point2d(0,0)) const;
  Mat getMat() const { return this->toRowVector(); };
  unique_ptr<BaseModel> clone() const;
  Mat toRowVector() const;
  Mat toRowVectorReduced(int maxSize) const;
  Mat toColVector() const;
  MeshShape getShape() const { return this->mesh; };
  vector<Texture> getTextures() const { return this->textureList; };
  void setGraphic(const Mat& newGraphic) { newGraphic.copyTo(this->graphic); };
  const Mat& getGraphic() const { return this->graphic; };
  const Size getSize() const { return this->mesh.getBound().size(); };
  const Size getSpannedSize() const { return this->mesh.getSpannedSize(); };

  // TAOTOREVIEW:
  virtual inline void save(const string path) const {};
  virtual inline void load(const string path) {};

  //------- Transformation -----------
  void realignTo(MeshShape& newShape);
  void resizeTo(double newScale);
  void recentre(Point2d t);
};

#endif