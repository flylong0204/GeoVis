#include "LineStyle.h"


//osg::Group* LineStyle::drawLine(osgEarth::MapNode* mapNode,LineGeometry* line,bool& _lock)
//{
//	osg::Group* annoGroup = new osg::Group();
//		osgEarth::Features::Style lineStyle;
//		osgEarth::Symbology::LineSymbol *ls = lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>();
//		ls->stroke()->color() = osgEarth::Symbology::Color(1.0,0,0,1.0);
//		ls->stroke()->width() = 3.0f;
//		/*ls->stroke()->widthUnits() = osgEarth::Symbology::Units::PIXELS;
//		ls->tessellation() = 200.0f;*/
//	
//		osgEarth::Symbology::AltitudeSymbol *as = lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>();
//		as->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
//		as->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_GPU;
//	
//	
//		const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
//	std::vector<GVCoord> vtxBuffer;
//	std::vector<int> vtxBuffer2;
//	if(line->toVertice(vtxBuffer,&vtxBuffer2))
//	{
//		osg::ref_ptr<osgEarth::Features::MultiGeometry> geoms = new osgEarth::Features::MultiGeometry;
//		unsigned int count = 0;
//		for(int i =0; i < vtxBuffer2.size(); i++)
//		{
//			osg::ref_ptr<osgEarth::Symbology::LineString> geom = new osgEarth::Symbology::LineString;
//			for(int j =0; j < vtxBuffer2[i]; j++)
//			{
//				geom->push_back(osg::Vec3d(vtxBuffer[count].lon,vtxBuffer[count].lat,vtxBuffer[count].alt));
//				count++;
//			}
//			geoms->add(geom);
//
//			osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(geoms,mapNode->getMapSRS(),lineStyle);
//			osg::ref_ptr<osgEarth::Annotation::FeatureNode> gnode = new osgEarth::Annotation::FeatureNode(mapNode,feature);
//			gnode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);
//			annoGroup->addChild( gnode );
//		}
//	}
//	_lock = true;
//	return annoGroup;
//}


osg::Group* LineStyle::drawLine(osgEarth::MapNode* mapNode,LineGeometry* line,bool& _lock)
{
	osg::Group* annoGroup = new osg::Group();
	osgEarth::Features::Style lineStyle;
	osgEarth::Symbology::LineSymbol *ls = lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>();
	ls->stroke()->color() = osgEarth::Symbology::Color(1.0,0,0,1.0);
	ls->stroke()->width() = 3.0f;
	/*ls->stroke()->widthUnits() = osgEarth::Symbology::Units::PIXELS;
	ls->tessellation() = 200.0f;*/

	osgEarth::Symbology::AltitudeSymbol *as = lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>();
	as->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	as->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_GPU;


	const SpatialReference* geoSRS = mapNode->getMapSRS()->getGeographicSRS();
	std::vector<GVCoord> vertexs;
	std::vector<int> *vertexInt = new std::vector<int>;
	if(line->toVertice(vertexs,vertexInt))
	{
		osg::ref_ptr<osgEarth::Features::MultiGeometry> geoms = new osgEarth::Features::MultiGeometry;
		int count = 0;
		for(int i =0; i < vertexInt->size(); i++)
		{
			osg::ref_ptr<osgEarth::Symbology::LineString> geom = new osgEarth::Symbology::LineString;

			for(int j = count; j < count + vertexInt->at(i); j++)
			{
				geom->push_back(osg::Vec3d(vertexs[j].lon,vertexs[j].lat,vertexs[j].alt));
			}
			count += vertexInt->at(i);
			geoms->add(geom);

			osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(geoms,mapNode->getMapSRS(),lineStyle);
			osg::ref_ptr<osgEarth::Annotation::FeatureNode> gnode = new osgEarth::Annotation::FeatureNode(mapNode,feature);
			gnode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);
			annoGroup->addChild( gnode );
		}
	}
	_lock = true;
	return annoGroup;
}