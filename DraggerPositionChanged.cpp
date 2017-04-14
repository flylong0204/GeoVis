#include "DraggerPositionChanged.h"
#include "osg/Node"
#include <osg/StateSet>


DraggerPositionChanged::DraggerPositionChanged()
{
	osg::StateSet* stateSet = getOrCreateStateSet();
	stateSet->setMode(0x0B71,0);
	stateSet->setRenderBinDetails(99,"RenderBin");
	stateSet->setMode(0x0B50,osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
}

DraggerPositionChanged::~DraggerPositionChanged()
{
	
}

void DraggerPositionChanged::CreatControlPonitsShow(std::vector<GVCoord> vtxBuffer,osgEarth::MapNode* mapNode,osg::Group* editGroup)
{
	osg::Sphere* shape = new osg::Sphere(osg::Vec3(0,0,0),4.0f);
	osg::ShapeDrawable *_centerSphere = new osg::ShapeDrawable(shape);
	_centerSphere->setDataVariance(osg::Object::DYNAMIC);
	_centerSphere->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));

	osg::Geode* geode = new osg::Geode();
	geode->addDrawable(_centerSphere);

	osg::AutoTransform *at = new osg::AutoTransform;
	at->setAutoScaleToScreen(true);
	at->addChild(geode);

	
	int cpSize = vtxBuffer.size();
	for(int i = 0; i < cpSize; i++)
	{
		const osgEarth::SpatialReference *srs = mapNode->getMapSRS();
		osg::Vec3d worldPt;
		srs->transformFromWorld(osg::Vec3d(vtxBuffer[i].lon, vtxBuffer[i].lat, vtxBuffer[i].alt),worldPt);

		osgEarth::GeoPoint abs(srs,vtxBuffer[i].lon,vtxBuffer[i].lat,vtxBuffer[i].alt + 1,osgEarth::ALTMODE_ABSOLUTE);
		osg::Matrixd local2world;
		abs.createLocalToWorld(local2world);

		osg::MatrixTransform *mt = new osg::MatrixTransform;
		mt->setMatrix(local2world);
		mt->addChild(at);
		editGroup->addChild(mt);
	}
	_centerSphere->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	
}

void DraggerPositionChanged::updateDraggerPosition(int idx,const GVCoord coord,osgEarth::MapNode* mapNode,osg::Group* editGroup)
{
	osg::Sphere* shape = new osg::Sphere(osg::Vec3(0,0,0),4.0f);
	osg::ShapeDrawable *_centerSphere = new osg::ShapeDrawable(shape);
	_centerSphere->setDataVariance(osg::Object::DYNAMIC);
	_centerSphere->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));

	osg::Geode* geode = new osg::Geode();
	geode->addDrawable(_centerSphere);

	osg::AutoTransform *at = new osg::AutoTransform;
	at->setAutoScaleToScreen(true);
	at->addChild(geode);

	const osgEarth::SpatialReference *srs = mapNode->getMapSRS();
	osg::Vec3d worldPt;
	srs->transformFromWorld(osg::Vec3d(coord.lon, coord.lat, coord.alt),worldPt);

	osgEarth::GeoPoint abs(srs,coord.lon,coord.lat,coord.alt + 1,osgEarth::ALTMODE_ABSOLUTE);
	osg::Matrixd local2world;
	abs.createLocalToWorld(local2world);

	osg::MatrixTransform *mt = new osg::MatrixTransform;
	mt->setMatrix(local2world);
	mt->addChild(at);
	editGroup->setChild(idx,mt);
	_centerSphere->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
}