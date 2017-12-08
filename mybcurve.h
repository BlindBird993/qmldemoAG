/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/




#ifndef GM_PARAMETRICS_CURVES_MyBCurve_H
#define GM_PARAMETRICS_CURVES_MyBCurve_H


#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/parametrics/src/gmpcurve.h"
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/scene/src/selector/gmselector.h"

namespace GMlib {


  template <typename T>
  class MyBCurve : public PCurve<T,3> {
    GM_SCENEOBJECT(MyBCurve)
  public:
    MyBCurve(  PCurve<T,3> *c, int n);
    //MyBCurve( const DVector<Vector<T,3>> &c, int d, int n);
    MyBCurve( const MyBCurve<T>& copy );
    virtual ~MyBCurve();

    // Public local functions



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosed() const override;

  protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval(T t, int d, bool l) const override;
    T                   getStartP() const override;
    T                   getEndP()   const override;
    void                localSimulate(double dt) override;


    // Protected data for the curve

    DVector<PCurve<T,3>*>_C; //local curves
    DVector<T>           _t; //knot vector
    int                  _d; //degree
    T                    _s;
    T                    _e;
    bool                 _isclosed;

  private:

    T                   _W(int i, int d, T t) const;
    T                   _B(T t) const;
    int                 _findIndex(T t) const;
    void                _makeKnotVector(int n);
    void                _createLocalCurves(PCurve<T,3> *c,int n);


  }; // END class MyBCurve

} // END namepace GMlib

// Include MyBCurve class function implementations
#include "mybcurve.c"


#endif // GM_PARAMETRICS_CURVES_MyBCurve_H
