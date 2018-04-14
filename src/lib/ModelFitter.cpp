#include "ModelFitter.h"

tuple<shared_ptr<BaseFittedModel>, double> ModelFitter::generateNextBestModel(shared_ptr<BaseFittedModel> model, const Mat& sample) const
{
  vector<SearchWith> actions = {SCALING, TRANSLATION, RESHAPING, REAPPEARANCING};
  vector<shared_ptr<BaseFittedModel>> candidates;

  #ifdef DEBUG
  cout << CYAN << "Fitter : Generating next best model" << RESET << endl;
  #endif

  // Generate action params
  auto pcaShape      = aamPCA->getShapePCA();
  auto pcaAppearance = aamPCA->getAppearancePCA();
  double scales[]    = {1.01, 0.99};
  Point2d trans[]    = {Point2d(-1,0), Point2d(0,-1), Point2d(1,0), Point2d(0,1)};
  auto smat          = pcaShape.permutationOfParams();
  auto amat          = pcaAppearance.permutationOfParams();

  for (auto a : actions)
  {
    // TAOTOREVIEW: better to use priority queue here?
    
    switch (a)
    {
      case SCALING:
        for (auto s : scales) 
        {
          auto ptrModel = model->clone();
          ptrModel->setScale(s * model->scale);
          candidates.push_back(ptrModel);
        }
        break;

      case TRANSLATION:
        for (auto t : trans)
        {
          auto ptrModel = model->clone();
          ptrModel->setOrigin(model->origin + t);
          candidates.push_back(ptrModel);
        }
        break;

      case RESHAPING:
        for (auto param : smat)
        {
          auto ptrModel = model->clone();
          ptrModel->setShapeParam(model->shapeParam + param);
          candidates.push_back(ptrModel);
        }
        break;

      case REAPPEARANCING:
        for (auto param : amat)
        {
          auto ptrModel = model->clone();
          ptrModel->setAppearanceParam(model->appearanceParam + param);
          candidates.push_back(ptrModel);
        }
        break;
    }
  }

  #ifdef DEBUG
  cout << "Candidates size : " << candidates.size() << endl;
  #endif

  // Identify the best model
  double bestError = numeric_limits<double>::max();
  shared_ptr<BaseFittedModel> bestCandidate = candidates.front()->clone();
  for (auto c : candidates)
  {
    double e = c->measureError(sample);
    if (e <= bestError)
    {
      bestError = e;
      bestCandidate = c->clone();
    }
  }

  return make_tuple(bestCandidate, bestError);
}

shared_ptr<BaseFittedModel> ModelFitter::fit(const BaseFittedModel* initModel, const Mat& sample, const FittingCriteria& crit) const 
{
  double errorDiff = numeric_limits<double>::max();
  int iter = 0;

  // Start with the given initial model
  auto prevModel = initModel->clone();
  prevModel->setOrigin(crit.initPos);
  prevModel->setScale(crit.initScale);

  #ifdef DEBUG
  cout << GREEN << "[Model fitting started]" << RESET << endl;
  cout << "[Init model]" << endl;
  cout << *prevModel << endl;
  #endif


  // Adjust model parameters until converges
  while (iter < crit.numMaxIter && errorDiff > crit.eps)
  {
    #ifdef DEBUG
    cout << CYAN << "Fitting model #" << iter << RESET << endl;
    #endif

    double prevError = prevModel->measureError(sample);
    if (prevError == 0)
    {
      #ifdef DEBUG
      cout << RED << "-- stopping, fitting error already is zero." << RESET << endl;
      #endif
      break;
    }

    #ifdef DEBUG
    cout << YELLOW << "... Error so far ~ " << prevError << RESET << endl;
    #endif

    // Explore next best parameters
    // TAOTOREVIEW: Add prev explored paths as taboo
    auto newModelWithError = generateNextBestModel(prevModel, sample);

    cout << "best model identified~" << endl; // TAODEBUG:

    shared_ptr<BaseFittedModel> newModel = get<0>(newModelWithError);
    double error = get<1>(newModelWithError);
    
    double errorDiff;
    if (error == 0)
    {
      #ifdef DEBUG
      cout << CYAN << "... Fitting error approaches ZERO" << RESET << endl;
      #endif
      break;
    }
    else if (error == prevError)
    {
      errorDiff = 0;
    }
    else (error - prevError)/min(error, prevError);

    #ifdef DEBUG
    auto errorStr = fmt::format("{0:2d} %", errorDiff/100);
    cout << "... Error diff : " << errorStr << endl;
    #endif

    iter++;
    prevModel = newModel;
  };

  #ifdef DEBUG
  cout << RED << "[Model fitting finished]" << RESET << endl;
  #endif

  return prevModel;
}