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
  Mat getMat() const { return this->toRowVector(); }; // TAOTODO: really?
  unique_ptr<BaseModel> clone() const;
  Mat toRowVector() const;
  Mat toColVector() const;

  // TAOTOREVIEW:
  virtual inline void save(const string path) const {};
  virtual inline void load(const string path) {};

  //------- Transformation -----------
  void realignTo(MeshShape& newShape);
};

#endif