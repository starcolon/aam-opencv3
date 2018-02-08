#include "ModelPCA.h"

Mat ModelPCA::toParam(BaseModel* m) const
{
  Mat vec = m->toRowVector();
  return this->pca.project(vec);
}

BaseModel* ShapeModelPCA::mean() const
{
  return new Shape(this->pca.mean);
}

BaseModel* ShapeModelPCA::toModel(const Mat& param) const 
{
  return new Shape(this->pca.backProject(param));
}

BaseModel* AppearanceModelPCA::mean() const
{
  auto bound  = meanShape.getBound();
  Mat spatial = Mat(bound.size(), CV_8UC3, Scalar(0,0,0));

  this->pca.mean.clone().reshape(3, bound.height).copyTo(spatial);
  // TAOTODO: Backproject mean appearance
  return new Appearance(meanShape, spatial);
}

BaseModel* AppearanceModelPCA::toModel(const Mat& param) const
{
  auto bound  = meanShape.getBound();
  Mat spatial = Mat(bound.size(), CV_8UC3, Scalar(0,0,0));

  Mat projected = this->pca.backProject(param);
  this->pca.mean.clone().reshape(3, bound.height).copyTo(spatial);
  // TAOTODO: Backproject param
  return new Appearance(meanShape, spatial);
}
