#ifndef __GV_CREATOR_H__
#define __GV_CREATOR_H__
#include "osgGA/GUIEventHandler"
#include "Coord.h"
#include "target.h"
#include "osgEarth/MapNode"
#include "osgViewer/View"
class GVCreator{
public:
	GVCreator();
	~GVCreator();
public:
	bool getGeoPosition(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&aa,GVCoord &coord,osgEarth::MapNode* mapNode)const;
	bool getGeoPosition(osgViewer::View *view, double mouseX, double mouseY, GVCoord &coord,osgEarth::MapNode* mapNode) const;

protected:
	bool _deleteTargetOnComplate;
};

#endif

