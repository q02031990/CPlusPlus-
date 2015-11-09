
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>


#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include "KeyboardHandler.h"

#include <iostream>
#include <string>



class carCallback: public osg::NodeCallback{

};

// Create a transformation node
osg::PositionAttitudeTransform* PAT;
float Goc_Quay = 90;

osg::Geode* Tao_Mat_Ban(){
	osg::Geode* G_Mat_ban = new osg::Geode();
	float a = 0.0f;
	float b = 0.0f;
	osg::ShapeDrawable* _G_Mat_ban = new osg::ShapeDrawable(new osg::Box(osg::Vec3(a,b,0.0f), 200.0f, 200.0f ,3.0f));
	_G_Mat_ban->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Mat_ban->addDrawable(_G_Mat_ban);

	return G_Mat_ban;
}

osg::Geode* Tao_Duong_Ke1(int i,int j){
	osg::Geode* G_Duong_Ke = new osg::Geode();
	float a = 0.0f + i*20.0;
	float b = 0.0f;
	osg::ShapeDrawable* _G_Duong_Ke = new osg::ShapeDrawable(new osg::Box(osg::Vec3(a,b,2.0f), 0.5f, 200.0f ,0.5f));
	_G_Duong_Ke->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Duong_Ke->addDrawable(_G_Duong_Ke);

	return G_Duong_Ke;
}

osg::Geode* Tao_Duong_Ke2(int i,int j){
	osg::Geode* G_Duong_Ke = new osg::Geode();
	float a = 0.0f;
	float b = 0.0f + j*20.0;
	osg::ShapeDrawable* _G_Duong_Ke = new osg::ShapeDrawable(new osg::Box(osg::Vec3(a,b,2.0f),  200.0f , 0.5f, 0.5f));
	_G_Duong_Ke->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Duong_Ke->addDrawable(_G_Duong_Ke);

	return G_Duong_Ke;
}




//////////////////////////////////////////////////////////////////////////////
// MAIN SCENE GRAPH BUILDING FUNCTION
//////////////////////////////////////////////////////////////////////////////
void build_scene(osg::Group *root)
{
	// Create a group node for the complete car
	// Tao 1 Group : gom cac doi tuong thanh 1 cục để dễ chỉnh sửa.
	// Khi thay đổi thuộc tính của Group thì các đối tượng nằm trong Group sẽ thay đổi theo
	osg::Group *GR_car = new osg::Group();
	root->addChild(GR_car);

	// Creat Cylinder
	// Tạo đối tượng hình trụ
	osg::Geode* G_Cylinder = new osg::Geode();
	osg::ShapeDrawable* _G_Cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f,0.0f,0.0f), 5.0f, 45.0f));
	_G_Cylinder->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Cylinder->addDrawable(_G_Cylinder);

	// Ve doi tuong vao khong gian
	GR_car->addChild(G_Cylinder);


	// Creat Box im oben
	// Tạo đối tượng hình hộp
	osg::Geode* G_box = new osg::Geode();
	osg::ShapeDrawable* _G_box = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,30.0f),15.0f));
	_G_box->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Cylinder->addDrawable(_G_box);

	// Ve doi tuong vao khong gian
	GR_car->addChild(G_box);


	// Tạo đối tượng hình hộp(đế quạt)
	osg::Geode* G_Chan_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Chan_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, -25.0f), 40.0f, 40.0f ,3.0f));
	_G_Chan_Quat->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Chan_Quat->addDrawable(_G_Chan_Quat);
	GR_car->addChild(G_Chan_Quat);


	/*
	* Create Rotor
	* 
	*/
	
	// Tạo đối tượng hình tron
	osg::Geode* G_Sphere = new osg::Geode();
	osg::ShapeDrawable* _G_Sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),6.0f));
	_G_Sphere->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Sphere->addDrawable(_G_Sphere);


	// Tạo hinh cho canh quat(có 2 cánh)
	osg::Geode* G_Canh_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Canh_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(4.0f,0.0f,0.0f),0.7f ,60.0f,7.0f));
	_G_Canh_Quat->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Canh_Quat->addDrawable(_G_Canh_Quat);
	

	//Cánh quạt tạo Group đối tượng PAT(PositionAttitudeTransform)
	//Tạo Group thứ 2(PAT) : Cánh quạt + Hình tròn(làm rotor)
	PAT = new osg::PositionAttitudeTransform();
	PAT->setPosition(osg::Vec3(7.0f,0.0f,30.0f)); // đặt vị trí cho cho PAT
	root->addChild(PAT);
	
	PAT->addChild(G_Sphere);
	PAT->addChild(G_Canh_Quat);
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(90.0),osg::Vec3(10, 0, 0)));// Quay 1 góc 90 độ và quay quanh tọa độ 3D trong ko gian la osg::Vec3(10, 0, 0))
	
	
	/* Tạo cái bàn
	*
	*
	*
	*/
	osg::PositionAttitudeTransform* Table = new osg::PositionAttitudeTransform();
	Table->setPosition(osg::Vec3(-70.0f,0.0f,-28.0f));
	root->addChild(Table);

	//Tạo mặt bàn

	osg::Geode* G_Mat_ban = Tao_Mat_Ban();
	
	for(int i=-5;i<5;i++){
		for(int j=-5;j<5;j++){
			osg::Geode* G_Duong_ke1 = Tao_Duong_Ke1(i,j);
			osg::Geode* G_Duong_ke2 = Tao_Duong_Ke2(i,j);
			Table->addChild(G_Duong_ke1);	
			Table->addChild(G_Duong_ke2);	
		}
	}
	Table->addChild(G_Mat_ban);
	
	
	
	
}



void QuaySangTrai(){
	Goc_Quay = Goc_Quay + 5.0; // điểu chỉnh góc quay
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(10, 0, 0)));
}

void QuaySangPhai(){
	Goc_Quay = Goc_Quay - 5.0;
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(10, 0, 0)));
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

	// sự kiện nhấn lên keyboard-> gọi hàm quay sang trái hay sang phải
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
