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




#ifndef GM_PARAMETRICS_CURVES_Myfirstcurve_H
#define GM_PARAMETRICS_CURVES_Myfirstcurve_H


#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/parametrics/src/gmpcurve.h"


namespace GMlib {


  template <typename T>
  class Myfirstcurve : public PCurve<T,3> {
    GM_SCENEOBJECT(Myfirstcurve)
  public:
    Myfirstcurve( T radius = T(20) );
    Myfirstcurve( const Myfirstcurve<T>& copy );
    virtual ~Myfirstcurve();

    // Public local functions
    T               getRadius() const;
    void            setRadius( T radius = T(20) );

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


    // Protected data for the curve
    T               _r;

  }; // END class Myfirstcurve

} // END namepace GMlib

// Include Myfirstcurve class function implementations
#include "myfirstcurve.c"


#endif // GM_PARAMETRICS_CURVES_Myfirstcurve_H
