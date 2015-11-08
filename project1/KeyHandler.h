// KeyHandler.h
#pragma once

#include <osgGA/GUIEventHandler>

class KeyHandler : public osgGA::GUIEventHandler
{
public:
	KeyHandler()
	{}

public:
	__event void Rotate();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
	{
		osgGA::GUIEventAdapter::EventType eventType = ea.getEventType();
		
		switch (eventType)
		{
		case(osgGA::GUIEventAdapter::KEYDOWN) :
		{
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_R)
			{
				Rotate();
			}
			else
			{
				return false;
			}
		}
		case(osgGA::GUIEventAdapter::FRAME) :
		{
			return false;
		}
		case(osgGA::GUIEventAdapter::MOVE) :
		{
			//Bei Mausmove?
			return false;
		}
		case(osgGA::GUIEventAdapter::PUSH) :
		{
			//Bei Mausklick?
			return false;
		}
		case(osgGA::GUIEventAdapter::DRAG) :
		{
			//Bei Mausdrag
			return false;
		}
		case(osgGA::GUIEventAdapter::RELEASE) :
		{
			//Gedrückte Maus loslassen
			return false;
		}

		default:
			return false;
		}
	}

	/*virtual void accept(osgGA::GUIEventHandlerVisitor& v)
	{
		v.visit(*this);
	}*/
};