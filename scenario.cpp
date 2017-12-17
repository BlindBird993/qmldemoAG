#include "scenario.h"
#include "myfirstcurve.h"
#include "myspline.h"
#include "testtorus.h"
#include "mybcurve.h"
#include "mybsurface.h"
#include "myblendcurve.h"
#include "myclosedcurve.h"
//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

  // Insert a light
  GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
  GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::white(), GMlib::GMcolor::white(),
                                                     GMlib::GMcolor::white(), init_light_pos );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, false );

  // Insert Sun
  scene()->insertSun();

  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Projection cam
  auto proj_rcpair = createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Front cam
  auto front_rcpair = createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );







   //Surface visualizers
  auto plane_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;
  auto cylinder_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;
  auto torus_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;

  auto myCurve = new GMlib::Myfirstcurve<float>();
  myCurve->translate(GMlib::Vector<float,3>(35,15,0));
  myCurve->toggleDefaultVisualizer();
  myCurve->replot(200,0);
  scene()->insert(myCurve);

  int m = 20;
  GMlib::DVector<GMlib::Vector<float,3>>p(m);
  for (int i=0;i<m;i++){
      p[i] = myCurve->getPosition(myCurve->getParStart() + (i*myCurve->getParEnd())/(m-1));
  }
    //vector of control points
  GMlib::DVector<GMlib::Vector<float,3>>c(8);
  c[0] = GMlib::Vector<float,3>(0,0,0);
  c[1] = GMlib::Vector<float,3>(1,1,0);
  c[2] = GMlib::Vector<float,3>(2,2,0);
  c[3] = GMlib::Vector<float,3>(3,3,0);
  c[4] = GMlib::Vector<float,3>(4,3,0);
  c[5] = GMlib::Vector<float,3>(5,1,0);
  c[6] = GMlib::Vector<float,3>(6,0.5,0);
  c[7] = GMlib::Vector<float,3>(7,0,0);

  myPCurve = new GMlib::MSpline<float>(p,2,8);
  myPCurve->translate(GMlib::Vector<float,3>(35,10,0));
  myPCurve->toggleDefaultVisualizer();
  myPCurve->replot(200,0);
  scene()->insert(myPCurve);

  //B-spline with vector of control points
  myPCurve2Const = new GMlib::MSpline<float>(c,2);
  myPCurve2Const->translate(GMlib::Vector<float,3>(35,-10,0));
  myPCurve2Const->toggleDefaultVisualizer();
  myPCurve2Const->replot(200,0);
  scene()->insert(myPCurve2Const);

//curves for blending
  GMlib::Myfirstcurve<float>* myCurve1 = new GMlib::Myfirstcurve<float>();
  GMlib::Myfirstcurve<float>* myCurve2 = new GMlib::Myfirstcurve<float>();
  myCurve2->translate(GMlib::Vector<float,3>(40,3,0));
  myCurve1->translate(GMlib::Vector<float,3>(40,0,0));
  myCurve1->toggleDefaultVisualizer();
  myCurve1->replot(200,0);
  scene()->insert(myCurve1);

  myCurve2->toggleDefaultVisualizer();
  myCurve2->replot(200,0);
  scene()->insert(myCurve2);

//my blended curve
  auto myMultiCurve = new GMlib::MyBlendCurve<float>(myCurve1, myCurve2,0.3);
  myMultiCurve->toggleDefaultVisualizer();
  myMultiCurve->setColor(GMlib::GMcolor::blue());
  myMultiCurve->replot(200,0);
  scene()->insert(myMultiCurve);

  //plane
  auto myMSurface = new GMlib::PPlane<float>(GMlib::Point<float,3>(-10.0f, 10.0f, 20.0f),
                             GMlib::Vector<float,3>(0.0f, -20.0f, 0.0f),
                             GMlib::Vector<float,3>(0.0f, 0.0f, -20.0f));
  mybsurfePlane = new GMlib::MyBSurface<float>(myMSurface,4,4);
  mybsurfePlane->translate(GMlib::Vector<float,3>(-3,0,0));
  mybsurfePlane->toggleDefaultVisualizer();
  mybsurfePlane->insertVisualizer(plane_visualizer);
  mybsurfePlane->replot(50,50,1,1);
  scene()->insert(mybsurfePlane);

  //torus
  auto myClosedTorus = new GMlib::PTorus<float>(1.5f,0.5f,0.5f);
  mybsurfeTorus = new GMlib::MyBSurface<float>(myClosedTorus,4,4);
  mybsurfeTorus->translate(GMlib::Vector<float,3>(0,10,0));
  mybsurfeTorus->toggleDefaultVisualizer();
  mybsurfeTorus->insertVisualizer(torus_visualizer);
  mybsurfeTorus->replot(50,50,1,1);
  scene()->insert(mybsurfeTorus);

  //cylinder
  auto cylinder=new GMlib::PCylinder<float>(2,2,15);
  mybsurfeCylinder = new GMlib::MyBSurface<float>(cylinder,4,4);
  mybsurfeCylinder->translate(GMlib::Vector<float,3>(12,0,0));
  mybsurfeCylinder->toggleDefaultVisualizer();
  mybsurfeCylinder->insertVisualizer(cylinder_visualizer);
  mybsurfeCylinder->replot(50,50,1,1);
  scene()->insert(mybsurfeCylinder);


  //closed GERBS blended curve circle
  auto myClosedCurve = new GMlib::MyClosedCurve<float>();
  myClosedCurve->setRadius(60);
  mybcurveClosed = new GMlib::MyBCurve<float>(myClosedCurve,8);
  mybcurveClosed->toggleDefaultVisualizer();
  mybcurveClosed->translate(GMlib::Vector<float,3>(20,0,0));
  mybcurveClosed->replot(200,0);
  scene()->insert(mybcurveClosed);

  //open GERBS blended curve
  GMlib::Myfirstcurve<float>* myCurve3 = new GMlib::Myfirstcurve<float>();
  mybcurveOpen = new GMlib::MyBCurve<float>(myCurve3,8);
  mybcurveOpen->toggleDefaultVisualizer();
  mybcurveOpen->translate(GMlib::Vector<float,3>(25,0,0));
  mybcurveOpen->replot(200,0);
  scene()->insert(mybcurveOpen);



}

void Scenario::cleanupScenario() {

}

void Scenario::callGl()
{
    if (myPCurve){
        myPCurve->replot();
    }

    if (myPCurve2Const){
        myPCurve2Const->replot();
    }

    if (mybcurveOpen){
        mybcurveOpen->replot(100,0);
    }

    if (mybcurveClosed){
        mybcurveClosed->replot(100,0);
    }


    if (mybsurfePlane){
        mybsurfePlane->replot(50,50,1,1);
    }

    if (mybsurfeCylinder){
        mybsurfeCylinder->replot(50,50,1,1);
    }

    if (mybsurfeTorus){
        mybsurfeTorus->replot(50,50,1,1);
    }
}

