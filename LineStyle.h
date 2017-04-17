#ifndef __LINE_STYLE_H__
#define __LINE_STYLE_H__
#include "osgEarth/MapNode"
#include <osgEarthAnnotation/FeatureNode>
#include "InitOSG.h"
#include "Coord.h"
#include "LineGeometry.h"
using namespace osgEarth::Features;
class LineStyle
{
public:
	osg::Group* drawLine(osgEarth::MapNode* mapNode,LineGeometry* line,bool &lock);
};

#endif