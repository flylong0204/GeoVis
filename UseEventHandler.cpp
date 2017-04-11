#include "UseEventHandler.h"
#include "InitOSG.h"

GVLineCreator* _gvLineCreator = new GVLineCreator();
UseEventHandler::UseEventHandler(){

}

UseEventHandler::UseEventHandler(osgEarth::MapNode* _mapNode, osg::Group* _annoGroup, osgViewer::Viewer* _viewer)
{
	this->myMapNode = _mapNode;
	this->myAnnoGroup = _annoGroup;
	this->myViewer = _viewer;
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
			isStartAnno = false;
		}
		else if(isNew && ea.getButton() == 1) //第一次画标直接添加
		{
			_gvLineCreator->handle(ea,view,myMapNode);
			isNew = false;

			myAnnoGroup->addChild(_gvLineCreator->_controlPointShow.get());//新图标
			//myViewer->getSceneData()->asGroup()->setChild(1,myAnnoGroup);
			
			
			childNumOfAnnoGroup++;

		}
		else if(!isNew && ea.getButton() == 1)
		{
			_gvLineCreator->handle(ea,view,myMapNode);
			myAnnoGroup->setChild(childNumOfAnnoGroup-1,_gvLineCreator->_controlPointShow.get());
			myViewer->getSceneData()->asGroup()->setChild(1,myAnnoGroup);

		}
		return true;

	}
	if ( ea.getKey() == 'c' || ea.getKey() == 'C' )
	{
		isStartAnno = true;
		isNew = true;

	}

	return false;

}

