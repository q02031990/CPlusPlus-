
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>


#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include "KeyboardHandler.h"

#include <iostream>
#include <string>


// Create a transformation node for the car
osg::PositionAttitudeTransform* T_car = new osg::PositionAttitudeTransform();


class carCallback: public osg::NodeCallback{

};

public:
	osg::PositionAttitudeTransform* PAT;
	float Goc_Quay = 90;

carCallback* carCB = new carCallback();

//////////////////////////////////////////////////////////////////////////////
// MAIN SCENE GRAPH BUILDING FUNCTION
//////////////////////////////////////////////////////////////////////////////
void build_scene(osg::Group *root)
{

	
	osg::Group* rotor = new osg::Group();
	root->addChild(rotor);

	// Add transformation node of the car to the scene
	root->addChild(T_car);
	T_car->setUpdateCallback(carCB);

	// Create a group node for the complete car
	osg::Group *GR_car = new osg::Group();
	T_car->addChild(GR_car);

	// tao hinh trụ
	osg::Geode* G_Cylinder = new osg::Geode();
	osg::ShapeDrawable* _G_Cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f,0.0f,0.0f), 5.0f, 45.0f));
	_G_Cylinder->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Cylinder->addDrawable(_G_Cylinder);

	// Them hinh tru vao chuong trinh
	GR_car->addChild(G_Cylinder);


	// Tạo hình box TREN
	osg::Geode* G_box = new osg::Geode();
	osg::ShapeDrawable* _G_box = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,30.0f),15.0f));
	_G_box->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Cylinder->addDrawable(_G_box);

	// Them hinh box vao chuong trinh
	GR_car->addChild(G_box);


	// Tạo hinh cho chan quat
	osg::Geode* G_Chan_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Chan_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, -25.0f), 40.0f, 40.0f ,3.0f));
	_G_Chan_Quat->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Chan_Quat->addDrawable(_G_Chan_Quat);
	GR_car->addChild(G_Chan_Quat);


	/*
	* Tao Rotor
	*
	*/
	// Tạo hình tron
	osg::Geode* G_Sphere = new osg::Geode();
	osg::ShapeDrawable* _G_Sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),6.0f));
	_G_Sphere->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Sphere->addDrawable(_G_Sphere);


	// Tạo hinh cho canh quat
	osg::Geode* G_Canh_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Canh_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(4.0f,0.0f,0.0f),0.7f ,60.0f,7.0f));
	_G_Canh_Quat->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Canh_Quat->addDrawable(_G_Canh_Quat);
	

	//quay canh quat
	PAT = new osg::PositionAttitudeTransform();
	PAT->setPosition(osg::Vec3(7.0f,0.0f,30.0f));
	root->addChild(PAT);
	
	PAT->addChild(G_Sphere);
	PAT->addChild(G_Canh_Quat);
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(10, 0, 0)));
}


void QuaySangTrai(){
	Goc_Quay = Goc_Quay + 10;
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(0, 0, 0)));
}

void QuaySangPhai(){
	Goc_Quay = Goc_Quay - 10;
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(0, 0, 0)));
}
//////////////////////////////////////////////////////////////////////////////
// main()
/////////////////////////////////////////////////////////////////////////////
int main()
{
    // Create the root node of the scenegraph
    osg::Group *root = new osg::Group;

    // build the scenegraph begining from the root node
    build_scene(root);

    //Construct the viewer.
    osgViewer::Viewer viewer;
	viewer.setSceneData( root );
    viewer.realize();
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());

	keyboardEventHandler* myKeyboardEventhandler = new keyboardEventHandler();
	viewer.addEventHandler(myKeyboardEventhandler);
	myKeyboardEventhandler->addFunction('a',QuaySangTrai);
	myKeyboardEventhandler->addFunction('d',QuaySangPhai);
	


    double alpha = 0.8;

    while( !viewer.done() )
    {
        // fire off the cull and draw traversals of the scene.
        viewer.frame();
    }

    return 0;
}
