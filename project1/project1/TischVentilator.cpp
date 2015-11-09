#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>


#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include "KeyboardHandler.h"

#include <iostream>


osg::Texture2D* load_texture(const char* textureName){
	osg::Texture2D* texture = new osg::Texture2D;

	texture->setDataVariance(osg::Object::DYNAMIC);
	osg::Image* image = osgDB::readImageFile(textureName);
	if(!image){
		std::cout<<"Not load image";
	}else{
		texture->setImage(image);
	}
	return texture;
}
// Create a transformation node for the car
osg::PositionAttitudeTransform* T_car = new osg::PositionAttitudeTransform();


class carCallback: public osg::NodeCallback{

public:
	osg::PositionAttitudeTransform* rotorMovement;
	static float rotation() { return 0; }
};

osg::PositionAttitudeTransform* PAT;

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

	/*
	// Create a geometrie node (Geode) for the cars chassis and add a shape of a box
	osg::Geode* G_chassis = new osg::Geode();
	G_chassis->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,0.0f),10.0f)));
	*/

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

	// Them hinh canh quat vao chuong trinh
	//GR_car->addChild(G_Canh_Quat);
	

	//quay canh quat
	PAT = new osg::PositionAttitudeTransform();
	PAT->setPosition(osg::Vec3(0.0f,7.0f,30.0f));
	root->addChild(PAT);
	
	PAT->addChild(G_Sphere);
	PAT->addChild(G_Canh_Quat);
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(130.0f),osg::Vec3(0, 0, 1)));


	// Tạo hinh cho chan quat
	osg::Geode* G_Chan_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Chan_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, -25.0f), 40.0f, 40.0f ,3.0f));
	_G_Chan_Quat->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Chan_Quat->addDrawable(_G_Chan_Quat);

	// Them hinh tron vao chuong trinh
	GR_car->addChild(G_Chan_Quat);

	// Create a group node for the wheels of the car
	osg::Group *GR_wheels = new osg::Group();

	// Add the group node of the wheels to the group node of the complete car
	GR_car->addChild(GR_wheels);

	// Create a geometrie node (Geode) for the cars wheels and add a shape of a sphere
	// Tạo một nut Geometrie  cho bánh xe và tạo hình cầu cho nó
	osg::Geode* G_wheel = new osg::Geode();
	G_wheel->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),3.0f)));

	/*
	// 1.Create transformation nodes for each wheel(Banh xe)
	// 1. Tạo 4 nut cho 4 bánh xe
	osg::PositionAttitudeTransform* T_wheel1 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel2 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel3 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel4 = new osg::PositionAttitudeTransform();

	
	// 2.Change the position of each wheel
	// 2.Thay doi vi tri cua xe
	T_wheel1->setPosition( osg::Vec3(-5,5,-5) );
	T_wheel2->setPosition( osg::Vec3(5,5,5) );
	T_wheel3->setPosition( osg::Vec3(-5,5,5) );
	T_wheel4->setPosition( osg::Vec3(5,5,-5) );

	
	// 3.Add the geometrie node to the transformation
	// 3.Nhóm 4 bánh xe thành 1 nhóm
	GR_wheels->addChild(T_wheel1);
	GR_wheels->addChild(T_wheel2);
	GR_wheels->addChild(T_wheel3);
	GR_wheels->addChild(T_wheel4);
	
	// 4.Add the transformation node of the wheels to the cars wheel group
	// 4.Thêm các nút chuyển đổi của bánh xe
	T_wheel1->addChild(G_wheel);
	T_wheel2->addChild(G_wheel);
	T_wheel3->addChild(G_wheel);
	T_wheel4->addChild(G_wheel);

	//Backgroud cho vat the
	osg::Texture2D* carTexture = load_texture("wood.bmp");
	osg::StateSet* carState = new osg::StateSet();
	carState->setTextureAttributeAndModes(0,carTexture,osg::StateAttribute::ON);
	GR_wheels->setStateSet(carState);
	*/
}


void Rotate()
	{
		/*
		rotorMovement->setAttitude(osg::Quat(osg::DegreesToRadians(rotation), osg::Vec3(1, 0, 0)));
		rotation -= 5;
		*/
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
//	myKeyboardEventhandler->addFunction('a',increase);
//	myKeyboardEventhandler->addFunction('d',decrease);
	


    double alpha = 0.8;

    while( !viewer.done() )
    {
        // fire off the cull and draw traversals of the scene.
        viewer.frame();
		

		// autoposition wird neu gesetzt
		//T_car->setPosition( osg::Vec3(alpha,0,0) );
        //T_car->setAttitude( osg::Quat(osg::DegreesToRadians(alpha*10.0), osg::Vec3(0,0,1)) );
	
		// autoposition wird inkrementiert
		//alpha+=0.02;
    }

    return 0;
}
