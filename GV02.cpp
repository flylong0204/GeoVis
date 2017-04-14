#include "GV02.h"

GV02::GV02()
{
}

GV02::~GV02()
{
}

int GV02::getControlPointCount()
{
	std::vector<GVCoord> controlPoints;
	getControlPoints(controlPoints);
	return controlPoints.size();
}

void GV02::getControlPoints(std::vector<GVCoord>& vtxBuffer)
{
	if(_controlPoints.size() <= 0)
		return ;
	vtxBuffer = _controlPoints;
}

GVCoord GV02::getControlPoint(int idx)
{
	if(idx >= 0 && idx < _controlPoints.size())
		return _controlPoints[idx];

	return GVCoord();
}

void GV02::setControlPointsEx(std::vector<GVCoord> &vtxBuffer)
{
	setControlPoints(vtxBuffer);
}

void GV02::setControlPoints(std::vector<GVCoord>& vtxBuffer)
{
	_controlPoints = vtxBuffer;
}

void GV02::setControlPoint(int idx, const GVCoord& vtx)
{
	int cpSize = _controlPoints.size();
	if(idx < 0 || idx >= cpSize)
		return ;
	_controlPoints[idx] = vtx;

}

bool GV02::toVertice(std::vector<GVCoord>& vtxBuffer, std::vector<int>* vtxBuffer2 ) const
{
	

	int cpSize = _controlPoints.size();
	vtxBuffer = _controlPoints;
	vtxBuffer2->push_back(_controlPoints.size());
	return true;
}