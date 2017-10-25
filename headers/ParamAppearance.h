#ifndef PARAM_APP
#define PARAM_APP

#include "master.h"
#include "AppearanceModel.h"

class ParameterisedAppearance;

// TAOTOREVIEW: Shall we make this generic to both [[Shape]] and [[AppearanceModel]] ?
class AppearanceEncoder
{
protected:
  Mat mean; // Mean column vector
  Mat eigen;
  Mat eigen_1; // Invert of eigen matrix (NxN)
public:
  AppearanceEncoder(Mat mean, Mat eigen) : mean(mean), eigen(eigen), eigen_1(eigen.inv()) {};
  virtual ~AppearanceEncoder(){};
  Appearance decode(const ParameterisedAppearance& p) const;
  Mat encode(const Appearance& a) const;
};

/**
 * Parameterised Appearance, encoded by PCA parameters
 */
class ParameterisedAppearance
{
private:
protected:
  Mat params; // Column vector (Nx1)
public:
  ParameterisedAppearance(const Appearance& app, const AppearanceEncoder& enc);
  ParameterisedAppearance(const Mat& params) : params(params) {};
  inline virtual ~ParameterisedAppearance(){};

  Mat getParams() const { return this->params; };

  // ---------- Conversion -----------
  Appearance toAppearance(const AppearanceEncoder& enc) const;

};

#endif