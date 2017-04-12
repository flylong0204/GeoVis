#include "UseEventHandler.h"
#include "InitOSG.h"
#include "LineGeometry.h"
#include "GV01.h"
#include "LineStyle.h"

#include "osgEarth/IntersectionPicker"

LineGeometry *myLine;
LineStyle *myLineStyle = new LineStyle();

GVLineCreator* _gvLineCreator = new GVLineCreator();
UseEventHandler::UseEventHandler(){

}

UseEventHandler::UseEventHandler(osgEarth::MapNode* mapNode, osg::Group* annoGroup, osgViewer::Viewer* viewer,osg::Group* editGroup)
{
	this->myMapNode = mapNode;
	this->myAnnoGroup = annoGroup;
	this->myViewer = viewer;
	this->myEditGroup = editGroup;
	childNumOfAnnoGroup = 0;
	isStartAnno = false;

}



UseEventHandler::~UseEventHandler(){

}

bool UseEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());
	if(isStartAnno && ea.getButtonMask())
	{
		
		if(ea.getButtonMask() & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			_gvLineCreator->handle(ea,view,myMapNode);
			myEditGroup->removeChild(0,myEditGroup->getNumChildren());
			isStartAnno = false;
		}
		else if(isNew && ea.getButton() == 1) //第一次画标直接添加
		{
			_gvLineCreator->handle(ea,view,myMapNode);
			isNew = false;
			myEditGroup->addChild(_gvLineCreator->_controlPointShow.get());//新图标
			myLine->setControlPoints(_gvLineCreator->_curCoords);
			myAnnoGroup->addChild(myLineStyle->drawLine(myMapNode,myLine));
			
			
			childNumOfAnnoGroup++;

		}
		else if(!isNew && ea.getButton() == 1)
		{
			_gvLineCreator->handle(ea,view,myMapNode);
			myEditGroup->setChild(childNumOfAnnoGroup-1,_gvLineCreator->_controlPointShow.get());
			myLine->setControlPoints(_gvLineCreator->_curCoords);
			myAnnoGroup->setChild(childNumOfAnnoGroup-1,myLineStyle->drawLine(myMapNode,myLine));

		}
		return true;

	}
	/*************开始画标绘****************/
	if ( ea.getKey() == 'c' || ea.getKey() == 'C' )
	{
		isStartAnno = true;
		isNew = true;
		myLine =new GV01();

	}
	/*********鼠标双击状态处理*****************/
	if(ea.getButton() == 2)
	{
		osg::ref_ptr<osgGA::GUIEventAdapter> event = new osgGA::GUIEventAdapter(ea);
		std::cout<<pick(ea.getX(),ea.getY())<<std::endl;
		/*event->setX((ea.getXmin()+ea.getXmax())*0.5);
		event->setY((ea.getYmin()+ea.getYmax())*0.5);
		std::cout<<pick(event->getX(),event->getY())<<std::endl;*/
	}

	return false;

}

int UseEventHandler::pick(float x, float y)
{
	osgEarth::IntersectionPicker picker(myViewer,myAnnoGroup, ~0, 5, osgEarth::IntersectionPicker::LIMIT_ONE_PER_DRAWABLE);
	osgEarth::IntersectionPicker::Hits hits;


	if (picker.pick(x, y, hits))
	{
		osgEarth::IntersectionPicker::Hits::const_iterator h = hits.begin();
		if(h != hits.end())
		{
			const osgEarth::IntersectionPicker::Hit& hit = *h;
			osgEarth::Util::AnnotationNode* anno = picker.getNode<osgEarth::Util::AnnotationNode>(hit);
			osgEarth::Annotation::FeatureNode* p = dynamic_cast<osgEarth::Annotation::FeatureNode*>(anno);
			int i = myAnnoGroup->getChildIndex(p->getParent(0));
		    return i;
		}
	}
	return -1;
}

int UseEventHandler::pick1(float x, float y)
{
	osgUtil::LineSegmentIntersector::Intersections intersections; 
	if (myViewer->computeIntersections(x, y, intersections)) 
	{
		for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin(); hitr != intersections.end(); ++hitr) 
		{
			if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) 
			{
				

			}
		}
	}
}
