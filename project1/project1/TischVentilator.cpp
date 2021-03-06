
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>


#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include "KeyboardHandler.h"

#include <iostream>
#include <string>





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
protected :
	double position;
	double speed; 

public:
	carCallback(double startPosition, double startSpeed){
		position = startPosition;
		speed = startSpeed;
	}

	double getSpeed(){return speed;}

	void setSpeed(double newSpeed){
		speed = newSpeed;
	}
	virtual void operator()(osg::Node* node,osg::NodeVisitor* nv){
		osg::ref_ptr<osg::PositionAttitudeTransform> transCar = 
			dynamic_cast<osg::PositionAttitudeTransform*>(node);

		position = transCar->getPosition().y();
		transCar->setPosition(osg::Vec3(position+speed,0.0,0.0));
			traverse(node,nv);
			
	}
};

carCallback* carCB = new carCallback(0.0,0.01);
osg::PositionAttitudeTransform* GR_car;
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
	osg::Group *GR_TischVentilator = new osg::Group();
	root->addChild(GR_TischVentilator);

	// Creat Cylinder
	// Tạo đối tượng hình trụ
	osg::Geode* G_Cylinder = new osg::Geode();
	osg::ShapeDrawable* _G_Cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f,0.0f,0.0f), 5.0f, 45.0f));
	_G_Cylinder->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
	G_Cylinder->addDrawable(_G_Cylinder);

	// Ve doi tuong vao khong gian
	GR_TischVentilator->addChild(G_Cylinder);


	// Creat Box im oben
	// Tạo đối tượng hình hộp
	osg::Geode* G_box = new osg::Geode();
	osg::ShapeDrawable* _G_box = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,30.0f),15.0f));
	_G_box->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Cylinder->addDrawable(_G_box);

	// Ve doi tuong vao khong gian
	GR_TischVentilator->addChild(G_box);


	// Tạo đối tượng hình hộp(đế quạt)
	osg::Geode* G_Chan_Quat= new osg::Geode();
	osg::ShapeDrawable* _G_Chan_Quat = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, -25.0f), 40.0f, 40.0f ,3.0f));
	_G_Chan_Quat->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
	G_Chan_Quat->addDrawable(_G_Chan_Quat);
	GR_TischVentilator->addChild(G_Chan_Quat);


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
	
	
	//Load oto

	// Add transformation node of the car to the scene
	Table->addChild(T_car);
	T_car->setUpdateCallback(carCB);
	
	// Create a group node for the complete car
	GR_car = new osg::PositionAttitudeTransform();
	GR_car->setPosition( osg::Vec3(0.0f,0.0f,-3.0f) );
	Table->addChild(GR_car);

	// Create a geometrie node (Geode) for the cars chassis and add a shape of a box
	osg::Geode* G_chassis = new osg::Geode();
	G_chassis->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,26.0f),30.0f,50.0f,30.0f)));

	// Add the chassis to the cars group node
	GR_car->addChild(G_chassis);

	// Create a group node for the wheels of the car
	//osg::Group *GR_wheels = new osg::Group();
	osg::PositionAttitudeTransform* GR_wheels = new osg::PositionAttitudeTransform();
	GR_wheels->setPosition( osg::Vec3(-10.0f,-10.0f,-5.0f) );
	

	// Add the group node of the wheels to the group node of the complete car
	GR_car->addChild(GR_wheels);

	// Create a geometrie node (Geode) for the cars wheels and add a shape of a sphere
	osg::Geode* G_wheel = new osg::Geode();
	G_wheel->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),10.0f)));

	// 1.Create transformation nodes for each wheel
	osg::PositionAttitudeTransform* T_wheel1 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel2 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel3 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel4 = new osg::PositionAttitudeTransform();

	
	// 2.Change the position of each wheel
	T_wheel1->setPosition( osg::Vec3(0.0f,-10.0f,20.0f) );
	T_wheel2->setPosition( osg::Vec3(0.0f,30.0f,20.0f) );
	T_wheel3->setPosition( osg::Vec3(20.0f,30.0f,20.0f) );
	T_wheel4->setPosition( osg::Vec3(20.0f,-10.0f,20.0f) );

	
	// 3.Add the geometrie node to the transformation
	GR_wheels->addChild(T_wheel1);
	GR_wheels->addChild(T_wheel2);
	GR_wheels->addChild(T_wheel3);
	GR_wheels->addChild(T_wheel4);
	
	// 4.Add the transformation node of the wheels to the cars wheel group
	T_wheel1->addChild(G_wheel);
	T_wheel2->addChild(G_wheel);
	T_wheel3->addChild(G_wheel);
	T_wheel4->addChild(G_wheel);
	

	//Backgroud cho vat the
	osg::Texture2D* carTexture = load_texture("wood.bmp");
	osg::StateSet* carState = new osg::StateSet();
	carState->setTextureAttributeAndModes(0,carTexture,osg::StateAttribute::ON);
	GR_wheels->setStateSet(carState);
	
}

void QuaySangTrai(){
	Goc_Quay = Goc_Quay + 5.0; // điểu chỉnh góc quay
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(10, 0, 0)));
}

void QuaySangPhai(){
	Goc_Quay = Goc_Quay - 5.0;
	PAT->setAttitude(osg::Quat(osg::DegreesToRadians(Goc_Quay),osg::Vec3(10, 0, 0)));
}

float vitri_x;
float vitri_y;
//x
void DiChuyenSangTrai(){
	GR_car->setPosition( osg::Vec3(vitri_x += 5,vitri_y,-3.0f) );
}
//d
void DiChuyenSangPhai(){
	GR_car->setPosition( osg::Vec3(vitri_x -= 5,vitri_y,-3.0f) );
}


//w
void DiChuyenLenTruoc(){
	GR_car->setPosition( osg::Vec3(vitri_x,vitri_y -= 5,-3.0f) );
}
//s
void DiChuyenPhiaSau(){
	GR_car->setPosition( osg::Vec3(vitri_x,vitri_y += 5,-3.0f) );
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
	viewer.setSceneData(root);
    viewer.realize();
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());

	// sự kiện nhấn lên keyboard-> gọi hàm quay sang trái hay sang phải
	keyboardEventHandler* myKeyboardEventhandler = new keyboardEventHandler();
	viewer.addEventHandler(myKeyboardEventhandler);
	myKeyboardEventhandler->addFunction('[',QuaySangTrai);
	myKeyboardEventhandler->addFunction(']',QuaySangPhai);

	//di chuyen xe oto
	myKeyboardEventhandler->addFunction('a',DiChuyenSangTrai);
	myKeyboardEventhandler->addFunction('d',DiChuyenSangPhai);
	myKeyboardEventhandler->addFunction('w',DiChuyenLenTruoc);
	myKeyboardEventhandler->addFunction('s',DiChuyenPhiaSau);

    double alpha = 0.8;

    while( !viewer.done() )
    {
        // fire off the cull and draw traversals of the scene.
        viewer.frame();
    }

    return 0;
}
