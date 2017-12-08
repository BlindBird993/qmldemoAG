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




#ifndef GM_PARAMETRICS_CURVES_MyBSurface_H
#define GM_PARAMETRICS_CURVES_MyBSurface_H


#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/parametrics/src/gmpcurve.h"
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/scene/src/selector/gmselector.h"

namespace GMlib {


  template <typename T>
  class MyBSurface : public GMlib::PSurf<T,3> {
    GM_SCENEOBJECT(MyBSurface)
  public:
    MyBSurface(  PSurf<T,3> *s, int n1, int n2);
    MyBSurface( const MyBSurface<T>& copy );
    virtual ~MyBSurface();

    // Public local functions



    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosedU() const override;
    bool                isClosedV() const override;

  protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) const override;

    T                   getStartPV() const override;
    T                   getEndPV()   const override;

    T                   getStartPU() const override;
    T                   getEndPU()   const override;

    //void                localSimulate(double dt) override;


    // Protected data for the curve

    DMatrix<PSurf<T,3>*> _S; //local curves
    DVector<T>           _u; //knot vector
    DVector<T>           _v; //knot vector
    int                  _d; //degree
    T                    _su;
    T                    _eu;
    T                    _sv;
    T                    _ev;
    bool                 _isclosed;

  private:

    T                   _W(int i, int d, T t,const DVector<T>& knot) const;
    T                   _B(T t) const;
    T                   _BDeriv(T t) const;
    int                 _findIndex(T t,const DVector<T>& knot) const;
    void                _makeKnotVectors(DVector<T>& t,int n,T start,T end);
    void                _createLocalSurfaces(PSurf<T, 3>* s,int n1,int n2);


  }; // END class MyBSurface

} // END namepace GMlib

// Include MyBSurface class function implementations
#include "mybsurface.c"


#endif // GM_PARAMETRICS_CURVES_MyBSurface_H
