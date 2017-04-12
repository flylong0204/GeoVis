#include "InitOSG.h"
#include "UseEventHandler.h"

#define EARTH_FILE "E:\\OSG3.2.1\\osgEarth\\tests\\gdal_tiff.earth"
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;
using namespace osgEarth::Drivers;

int main(int argc, char** argv)


{

	osg::Group* root = new osg::Group();
	osg::ArgumentParser arguments(&argc, argv);
	osgViewer::Viewer* viewer = new osgViewer::Viewer(arguments);

	viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());

	osgEarth::Map* map = new Map();
	TMSOptions imagery;
	imagery.url() = "E:/base_image/tms.xml";
	map->addImageLayer( new ImageLayer("Imagery", imagery) );
	// add a TMS elevation layer:
	TMSOptions elevation;
	elevation.url() = "E:/dem/tms.xml";
	map->addElevationLayer( new ElevationLayer("Elevation", elevation) );
	osgEarth::MapNode* mapNode = new MapNode(map);

	root->addChild(mapNode);

	osg::Group* annoGroup = new osg::Group();
	root->addChild(annoGroup);

	osg::Group* editGroup = new osg::Group();
	root->addChild(editGroup);
	

	viewer->setSceneData(root);

	viewer->addEventHandler( new osgViewer::WindowSizeHandler );
	viewer->addEventHandler( new osgViewer::StatsHandler);
	viewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));
	viewer->addEventHandler(new UseEventHandler(mapNode,annoGroup,viewer,editGroup)) ; 

	

	return viewer->run();

}