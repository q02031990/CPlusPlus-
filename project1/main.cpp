#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>


#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include "KeyboardHandler.h"


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

//////////////////////////////////////////////////////////////////////////////
// MAIN SCENE GRAPH BUILDING FUNCTION
//////////////////////////////////////////////////////////////////////////////
void build_scene(osg::Group *root)
{
	//Creat Obj leoman from file legoman.obj
	osg::Group *legoMan = new osg::Group;
	osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("legoman.obj");

	if(!loadedModel){
		std::cout<<" No data loaded"<<std::endl;
	}else{
		osgUtil::Optimizer optimizer; 
		optimizer.optimize(loadedModel.get());

		root->addChild(legoMan);
		legoMan->addChild(loadedModel);
	}

	// Add transformation node of the car to the scene
	root->addChild(T_car);
	T_car->setUpdateCallback(carCB);

	// Create a group node for the complete car
	osg::Group *GR_car = new osg::Group();
	T_car->addChild(GR_car);

	// Create a geometrie node (Geode) for the cars chassis and add a shape of a box
	osg::Geode* G_chassis = new osg::Geode();
	G_chassis->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f,0.0f,0.0f),10.0f)));

	// Add the chassis to the cars group node
	GR_car->addChild(G_chassis);

	// Create a group node for the wheels of the car
	osg::Group *GR_wheels = new osg::Group();

	// Add the group node of the wheels to the group node of the complete car
	GR_car->addChild(GR_wheels);

	// Create a geometrie node (Geode) for the cars wheels and add a shape of a sphere
	osg::Geode* G_wheel = new osg::Geode();
	G_wheel->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),3.0f)));

	// 1.Create transformation nodes for each wheel
	osg::PositionAttitudeTransform* T_wheel1 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel2 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel3 = new osg::PositionAttitudeTransform();
	osg::PositionAttitudeTransform* T_wheel4 = new osg::PositionAttitudeTransform();

	
	// 2.Change the position of each wheel
	T_wheel1->setPosition( osg::Vec3(-5,5,-5) );
	T_wheel2->setPosition( osg::Vec3(5,5,5) );
	T_wheel3->setPosition( osg::Vec3(-5,5,5) );
	T_wheel4->setPosition( osg::Vec3(5,5,-5) );

	
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

void increase(){
	carCB->setSpeed(carCB->getSpeed() + 0.5);
}

void decrease(){
	carCB->setSpeed(carCB->getSpeed() - 0.5);
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
	myKeyboardEventhandler->addFunction('a',increase);
	myKeyboardEventhandler->addFunction('d',decrease);
	


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
