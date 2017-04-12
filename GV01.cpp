#include "GV01.h"
#include "Bezier.h"

GV01::GV01()
{
}

GV01::~GV01()
{
}

int GV01::getControlPointCount()
{
	std::vector<GVCoord> controlPoints;
	getControlPoints(controlPoints);
	return controlPoints.size();
}

void GV01::getControlPoints(std::vector<GVCoord>& vtxBuffer)
{
	if(_controlPoints.size() <= 0)
		return ;
	vtxBuffer = _controlPoints;
}

GVCoord GV01::getControlPoint(int idx)
{
	if(idx >= 0 && idx < _controlPoints.size())
		return _controlPoints[idx];

	return GVCoord();
}

void GV01::setControlPointsEx(std::vector<GVCoord> &vtxBuffer)
{
	setControlPoints(vtxBuffer);
}

void GV01::setControlPoints(std::vector<GVCoord>& vtxBuffer)
{
	_controlPoints = vtxBuffer;
}

void GV01::setControlPoint(int idx, const GVCoord& vtx)
{
	int cpSize = _controlPoints.size();
	if(idx < 0 || idx >= cpSize)
		return ;
	_controlPoints[idx] = vtx;

}

bool GV01::toVertice(std::vector<GVCoord>& vtxBuffer, std::vector<int>* vtxBuffer2 ) const
{
	int cpSize = _controlPoints.size();
	Bezier bezier;
	std::vector<GVCoord> bezierPoints;
	bezier.getBezier(_controlPoints,&bezierPoints);
	vtxBuffer = bezierPoints;
	vtxBuffer2->push_back(bezierPoints.size());
	return true;
}