#ifndef __DRAGGER_POSITION_CHANGED_H__
#define __DRAGGER_POSITION_CHANGED_H__

#include "Coord.h"
#include "osg/ShapeDrawable"
#include "osg/AutoTransform"
#include <osgEarth/MapNode>


class DraggerPositionChanged
	: public osg::Group
{
public:
	DraggerPositionChanged();
	~DraggerPositionChanged();
	void CreatControlPonitsShow(std::vector<GVCoord> vtxBuffer,osgEarth::MapNode* mapNode,osg::Group* editGroup);
	void updateDraggerPosition(int idx,const GVCoord coord,osgEarth::MapNode* mapNode,osg::Group* editGroup);
};

#endif