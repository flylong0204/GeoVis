#pragma once
#include "LineGeometry.h"
#include "Coord.h"

class ConfigControlPoints
{
public:
	void configControlPoints(std::vector<GVCoord> &_controlPoints); //修正全部控制点

	void configControlPoints(GVCoord &vtx, std::vector<GVCoord> &_controlPoints); //根据已有的_controlPoints中的点，修正点vtx

	void configControlPoints(int idx, std::vector<GVCoord> &_controlPoints);
};