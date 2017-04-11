#ifndef __USE_EVENT_HANDLER__
#define __USE_EVENT_HANDLER__
#include "InitOSG.h"
#include "GVLineCreator.h"

class UseEventHandler : public osgGA::GUIEventHandler 
{
public:
	UseEventHandler();
	UseEventHandler(osgEarth::MapNode* mapNode, osg::Group* annoGroup, osgViewer::Viewer* viewer);
	~UseEventHandler();
	//osgEarth::MapNode* getMapNode();

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

public:
	unsigned int childNumOfAnnoGroup;
private:
	osgEarth::MapNode* myMapNode;
	osg::Group* myAnnoGroup;
	osgViewer::Viewer* myViewer;
	bool isStartAnno; 
	bool isNew;
};


#endif