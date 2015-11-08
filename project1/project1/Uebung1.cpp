// Uebung1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

//#include "stdafx.h"

#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/Billboard>
#include <osg/LineWidth>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>

#include <osgDB/Registry>
#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
//#include <osgViewer/config/SingleWindow>

#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>

#include "KeyHandler.h"

class Uebung1
{
private: float rotation = 0;
public:
	osg::PositionAttitudeTransform* rotorMovement;


	osg::Node* createModel()
	{
		//Das Modell in der Übung besteht aus:
		// - Rotor
		//   - Kugel (Rotornabe)
		//   - 2 Quader (2x Rotorblätter)
		// - Turm
		//   - Zylinder (Turmdingsda)
		//   - 2 Quader für Gehäuse + Fundament

		//Gruppe (ist root Node)
		osg::Group* root = new osg::Group();

		//Die zwei Subnodes Rotor und Turm
		osg::Group* rotor = new osg::Group();
		osg::Group* tower = new osg::Group();

		root->addChild(rotor);
		root->addChild(tower);

		//Subnodes von Rotor...

		//Rotornabe
		osg::Geode* sphere = new osg::Geode();
		osg::ShapeDrawable* sphereShape = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(-0.25, 0, 0), 0.5));
		sphereShape->setColor(osg::Vec4(0.38, 0.75, 1.0, 1.0));
		sphere->addDrawable(sphereShape);

		//Rotorblätter
		osg::Geode* rotorBlade1 = new osg::Geode();
		osg::ShapeDrawable* rotorBladeShape1 = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 1.25, 0), 0.25, 2.0, 0.5));
		rotorBladeShape1->setColor(osg::Vec4(0.60, 0.0, 0.0, 1.0));
		rotorBlade1->addDrawable(rotorBladeShape1);
		osg::Geode* rotorBlade2 = new osg::Geode();
		osg::ShapeDrawable* rotorBladeShape2 = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, -1.25, 0), 0.25, 2.0, 0.5));
		rotorBladeShape2->setColor(osg::Vec4(0.60, 0.0, 0.0, 1.0));
		rotorBlade2->addDrawable(rotorBladeShape2);


		//Transform Node
		rotorMovement = new osg::PositionAttitudeTransform();
		rotorMovement->setPosition(osg::Vec3d(0.0, 0.0, 0.0));
		rotor->addChild(rotorMovement);

		rotorMovement->addChild(sphere);
		rotorMovement->addChild(rotorBlade1);
		rotorMovement->addChild(rotorBlade2);

		//Subnodes von Turm
		//Turmdingsda
		osg::Geode* towerThing = new osg::Geode();
		osg::ShapeDrawable* towerThingShape = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(-0.75, 0, -1.5), 0.25, 3.0));
		towerThingShape->setColor(osg::Vec4(0.71, 0.39, 0.17, 1.0));
		towerThing->addDrawable(towerThingShape);

		tower->addChild(towerThing);

		//Gehäuse
		osg::Geode* housing = new osg::Geode();
		osg::ShapeDrawable* housingShape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(-0.75, 0, 0), 1, 1, 1));
		housingShape->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
		housing->addDrawable(housingShape);

		tower->addChild(housing);

		//Fundament
		osg::Geode* base = new osg::Geode();
		osg::ShapeDrawable* baseShape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(-0.75, 0, -3), 1, 1, 0.25));
		baseShape->setColor(osg::Vec4(0.0, 0.11, 0.60, 1.0));
		base->addDrawable(baseShape);

		tower->addChild(base);

		return root;
	}

	void fuckThisUp()
	{
		exit(0);
	}

	void Rotate()
	{
		rotorMovement->setAttitude(osg::Quat(osg::DegreesToRadians(rotation), osg::Vec3(1, 0, 0)));
		rotation -= 5;
	}

	void hookEvent(KeyHandler* pSource) {
		__hook(&KeyHandler::Rotate, pSource, &Uebung1::Rotate);
	}

	void unhookEvent(KeyHandler* pSource) {
		__unhook(&KeyHandler::Rotate, pSource, &Uebung1::Rotate);
	}
};

int main(int, char**)
{
	Uebung1 uebung;

	KeyHandler* keh = new KeyHandler();
	uebung.hookEvent(keh);

	// construct the viewer
	osgViewer::Viewer viewer;
	//viewer.apply(new osgViewer::SingleWindow(0, 0, 800, 600));

	viewer.addEventHandler(keh);

	// set the scene to render
	viewer.setSceneData(uebung.createModel());

	// run the viewers frame loop
	return viewer.run();

	//// create the windows and run the threads.
	//viewer.realize();

	//// set the scene to render
	//viewer.setSceneData(createModel());

	//// main loop
	//while(!viewer.done())
	//{
	//	// fire off the cull and draw traversals of the scene.
	//	viewer.frame();

	//	osg::Vec3d vec = rotorMovement->getPosition();
	//	vec.x() += 0.001;
	//	rotorMovement->setPosition(vec);
	//}

	uebung.unhookEvent(keh);
	return 0;
}