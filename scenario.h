#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>
namespace GMlib {


template<typename T, int n>
class PCurve;

}

class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;

private:

  GMlib::PCurve<float,3>* myPCurve{nullptr};
  GMlib::PCurve<float,3>* myPCurve2Const{nullptr};

  GMlib::PCurve<float,3>* mybcurveOpen{nullptr};
  GMlib::PCurve<float,3>* mybcurveClosed{nullptr};

  GMlib::PSurf<float,3>* mybsurfePlane{nullptr};
  GMlib::PSurf<float,3>* mybsurfeCylinder{nullptr};
  GMlib::PSurf<float,3>* mybsurfeTorus{nullptr};

public slots:

  void      callGl();
};

#endif // SCENARIO_H
