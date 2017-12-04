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
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/scene/src/visualizers/gmselectorgridvisualizer.h"
#include "C:/STE6245/gmlib-50e676222977fbf777a43302e74828ed87558300/gmlib.git/modules/parametrics/src/curves/gmpsubcurve.h"


namespace GMlib {


//*****************************************
// Constructors and destructor           **
//*****************************************
template<typename T>
GMlib::MyBlendCurve<T>::MyBlendCurve( PCurve<T,3> *c1,  PCurve<T,3> *c2, T x)
{
     _x = x;
     _C1 = c1;
     _C2 = c2;

}


  template <typename T>
  MyBlendCurve<T>::~MyBlendCurve() {}


  //**************************************
  //        Public local functons       **
  //**************************************


  //***************************************************
  // Overrided (public) virtual functons from PCurve **
  //***************************************************

  template <typename T>
  bool MyBlendCurve<T>::isClosed() const {
    return false;
  }


  //******************************************************
  // Overrided (protected) virtual functons from PCurve **
  //******************************************************

  template <typename T>
  void MyBlendCurve<T>::eval( T t, int d, bool /*l*/ ) const {

    this->_p.setDim( d + 1 );
    if (t < _C1->getParEnd() - _x*_C1->getParDelta()){
        this->_p = _C1->evaluateParent(t,0);
    }
    else if (t < _C1->getParEnd()){
        const T b1 = 1-_B((t-_C1->getParEnd()+_x*_C1->getParDelta())/(_x*_C1->getParDelta()));
        const T b2 = _B((t-_C1->getParEnd()+_x*_C1->getParDelta())/(_x*_C1->getParDelta()));
        this->_p = b1*_C1->evaluateParent(t,0) + b2*_C2->evaluateParent(t-(1-_x)*_C1->getParDelta(),0);//_C[i-2]*b1 + _C[i-1]*b2 + _C[i]*b3;
    }
    else
        this->_p = _C2->evaluateParent(t-(1-_x)*_C1->getParDelta(),0);



  }


  template <typename T>
  T MyBlendCurve<T>::getStartP() const {
    return _C1->getParStart();
  }


  template <typename T>
  T MyBlendCurve<T>::getEndP()const {
      return _C1->getParEnd()+(1-_x)*_C2->getParDelta();
  }


  template<typename T>
  T MyBlendCurve<T>::_B(T t) const
  {
    return 3*(t*t) - 2*(t*t*t);
  }




} // END namespace GMlib