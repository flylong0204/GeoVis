#include "GVCreator.h"
#include "osgViewer/View"
#include "osgEarth/MapNode"
#include "Coord.h"
#include "target.h"
#include <assert.h>

GVCreator::GVCreator()
	: _deleteTargetOnComplate(true)
{

}

bool GVCreator::getGeoPosition(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&aa,GVCoord &coord,osgEarth::MapNode* mapNode) const
{
	osgViewer::View* pView = dynamic_cast<osgViewer::View*>(&aa);
	if(pView == NULL)
		return false;
	
	return getGeoPosition(pView, ea.getX(), ea.getY(), coord,mapNode);
}

bool GVCreator::getGeoPosition(osgViewer::View *view, double mouseX, double mouseY, GVCoord &coord,osgEarth::MapNode* mapNode) const
{
	if(view == NULL)
		return false;

	const osgEarth::MapNode *node = mapNode;
	if(node == NULL)
	    return false;

	//获取当前点
	osgUtil::LineSegmentIntersector::Intersections intersection;
	view->computeIntersections(mouseX,mouseY,intersection);
	osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersection.begin();
	if(iter != intersection.end())
	{
		osg::Vec3d geoPt;
		const osgEarth::SpatialReference *srs = node->getMapSRS();
		srs->transformFromWorld(iter->getWorldIntersectPoint(),geoPt);
		coord.lon = geoPt.x();
		coord.lat = geoPt.y();
		coord.alt = geoPt.z();
		return true;
	}

	return false;
}

GVCreator::~GVCreator()
{

}
