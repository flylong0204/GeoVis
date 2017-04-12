#include "LineGeometry.h"

LineGeometry::LineGeometry()
{

}

LineGeometry::~LineGeometry()
{

}

int LineGeometry::getControlPointCount()
{
	std::vector<GVCoord> controlPoints;
	getControlPoints(controlPoints);
	return controlPoints.size();
}

void LineGeometry::getControlPoints(std::vector<GVCoord>& vtxBuffer)
{
	if(allPoints.size() <= 0)
		return ;
	vtxBuffer = allPoints;
}

GVCoord LineGeometry::getControlPoint(int idx)
{
	if(idx >= 0 && idx < allPoints.size())
		return allPoints[idx];

	return GVCoord();
}

void LineGeometry::setControlPointsEx(std::vector<GVCoord> &vtxBuffer)
{
	setControlPoints(vtxBuffer);
}