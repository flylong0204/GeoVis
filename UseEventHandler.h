#ifndef __USE_EVENT_HANDLER__
#define __USE_EVENT_HANDLER__
#include "InitOSG.h"
#include "GVLineCreator.h"

class UseEventHandler : public osgGA::GUIEventHandler 
{
public:
	UseEventHandler();
	UseEventHandler(osgEarth::MapNode* mapNode, osg::Group* annoGroup, osgViewer::Viewer* viewer,osg::Group* editGroup);
	~UseEventHandler();

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
    int pick(float x, float y);

public:
	unsigned int childNumOfAnnoGroup;
private:
	osgEarth::MapNode* myMapNode;
	osg::Group* myAnnoGroup;
	osg::Group* myEditGroup;
	osgViewer::Viewer* myViewer;
	bool isStartAnno; 
	bool isNew;
};


#endif