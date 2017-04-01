#include "osgEarth/MapNode"
#include "osgEarthUtil/EarthManipulator"
#include "osgEarthUtil//AutoClipPlaneHandler"
#include "osgViewer/Viewer"
#include "osgGA/StateSetManipulator"
#include "osgDB/ReadFile"

#include <osgEarth/MapNode>
#include <osgEarth/Decluttering>
#include <osgEarth/ECEF>
#include <osgEarth/Registry>

#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/ExampleResources>

#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarthAnnotation/AnnotationRegistry>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/ImageOverlayEditor>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/HighlightDecoration>
#include <osgEarthAnnotation/ScaleDecoration>
#include <osgEarthUtil/ActivityMonitorTool>

#include <osgEarthSymbology/GeometryFactory>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/EventVisitor>
#include <osgDB/WriteFile>

#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/tms/TMSOptions>



#include "LineGeometry.h"
#include "GVCreator.h"
#include "Coord.h"
#include "target.h"

#define EARTH_FILE "E:\\OSG3.2.1\\osgEarth\\tests\\gdal_tiff.earth"

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;
using namespace osgEarth::Drivers;

osg::Group* root;
osgViewer::Viewer* viewer;
osgEarth::Map* map;
osgEarth::MapNode* mapNode;
osg::Group* annoGroup;
osg::Group* editGroup;

static std::vector<GVCoord> tempCoords;
GVCreator *gvcreator = new GVCreator ;
target *_target = new target;
lineGeometry _lineGeometry;
class UseEventHandler : public osgGA::GUIEventHandler 
{
private:
	osgEarth::MapNode* mapNode;
	unsigned int childNum;
	bool flagMouse; 
	bool isNew;
public:
	UseEventHandler(osgEarth::MapNode* mapNode)
	{
		this->mapNode = mapNode;
		childNum = 2;
		flagMouse = false;
		isNew = true;
	}

	osg::Group* drawLine(osgEarth::MapNode* mapNode)
	{
		annoGroup = new osg::Group;
		Style geomStyle;
		geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Red;
		geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 5.0f;
		geomStyle.getOrCreate<LineSymbol>()->stroke()->widthUnits() = osgEarth::Symbology::Units::PIXELS;
	    geomStyle.getOrCreate<LineSymbol>()->tessellation() = 200.0f;
		geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
		const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
		std::vector<GVCoord> vtxBuffer;
		std::vector<int> vtxBuffer2;
		if(_lineGeometry.toVertice(vtxBuffer,&vtxBuffer2))
		{
			osg::ref_ptr<osgEarth::Features::MultiGeometry> geoms = new osgEarth::Features::MultiGeometry;
			unsigned int count = 0;
			for(int i =0; i < vtxBuffer2.size(); i++)
			{
				osg::ref_ptr<osgEarth::Symbology::LineString> geom = new osgEarth::Symbology::LineString;
				for(int j =0; j < vtxBuffer2[i]; j++)
				{
					geom->push_back(osg::Vec3d(vtxBuffer[count].lon,vtxBuffer[count].lat,vtxBuffer[count].alt));
					count++;
				}
				geoms->add(geom);

				osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(geoms,mapNode->getMapSRS(),geomStyle);
				osg::ref_ptr<osgEarth::Annotation::FeatureNode> gnode = new osgEarth::Annotation::FeatureNode(mapNode,feature);
				gnode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
				annoGroup->addChild( gnode );
			}
		}
		return annoGroup;
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{
		switch(ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
			if(ea.getButton() == 1 && flagMouse)
			{
				GVCoord coord;
				if( gvcreator->getGeoPosition(ea,aa,coord,mapNode) )		
				{
					std::cout<<coord.lon<<std::endl;
					tempCoords.push_back(coord);
					_lineGeometry.setControlPoints(tempCoords);
					viewer->getSceneData()->asGroup()->addChild(drawLine(mapNode));
					if(isNew)
					{
						childNum++;
						isNew = false;
					}
					else if(!isNew)
					{
						viewer->getSceneData()->asGroup()->removeChild(childNum-1);
					}
				}

			}
			else if(ea.getButton() == 2)
			{
				flagMouse = true;
				isNew = true;
			}
			else if(ea.getButton() == 4)
			{

				tempCoords.clear();
				flagMouse = false;
				std::cout<<viewer->getSceneData()->asGroup()->getNumChildren()<<std::endl;
			}
			break;
		}
		return false;
	}
};



int main(int argc, char** argv)


{
	
	root = new osg::Group();
	osg::ArgumentParser arguments(&argc, argv);
	viewer = new osgViewer::Viewer(arguments);

	viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());

	map = new Map();
	TMSOptions imagery;
	imagery.url() = "E:/base_image/tms.xml";
	map->addImageLayer( new ImageLayer("Imagery", imagery) );
	// add a TMS elevation layer:
	TMSOptions elevation;
	elevation.url() = "E:/dem/tms.xml";
	map->addElevationLayer( new ElevationLayer("Elevation", elevation) );
	mapNode = new MapNode( map );
	
	root->addChild(mapNode);

	editGroup = new osg::Group();
	root->addChild(editGroup);

	/*annoGroup = new osg::Group();
	root->addChild(annoGroup);*/  
	
	//std::vector<GVCoord> coords;
	std::cout<<tempCoords.size()<<std::endl;
	/*coords.push_back(GVCoord(0,   60, 0));
	coords.push_back(GVCoord(30,  50, 0));*/
	//_lineGeometry.setControlPoints(coords);
	
	viewer->setSceneData(root);
	
	viewer->addEventHandler( new osgViewer::WindowSizeHandler );
	viewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));
	viewer->addEventHandler(new UseEventHandler(mapNode)) ; 
	
	return viewer->run();
	
}