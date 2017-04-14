#ifndef __USE_EVENT_HANDLER__
#define __USE_EVENT_HANDLER__
#include "InitOSG.h"
#include "GVLineCreator.h"
#include "InitOSG.h"
#include "LineGeometry.h"
#include "GV01.h"
#include "GV02.h"
#include "LineStyle.h"  


class UseEventHandler : public osgGA::GUIEventHandler 
{
public:
	UseEventHandler();
	UseEventHandler(osgEarth::MapNode* mapNode, osg::Group* annoGroup, osgViewer::Viewer* viewer,osg::Group* editGroup);
	~UseEventHandler();

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
    int pickLine(float x, float y); 
	int pickPoint(float x, float y);

public:
	unsigned int childNumOfAnnoGroup;
private:
	osgEarth::MapNode* myMapNode;
	osg::Group* myAnnoGroup;
	osg::Group* myEditGroup;
	osgViewer::Viewer* myViewer;
	bool isStartAnno; 
	bool isNew;
	bool lockDoubleClick;
	bool isSelect;
	bool isSelectPoint;
	std::vector<LineGeometry*> lineAddress; //存放线表函数指针
	int indexOfLine;
	int indexOfPoint;
};


#endif