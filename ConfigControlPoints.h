#pragma once
#include "LineGeometry.h"
#include "Coord.h"

class ConfigControlPoints
{
public:
	void configControlPoints(std::vector<GVCoord> &_controlPoints); //����ȫ�����Ƶ�

	void configControlPoints(GVCoord &vtx, std::vector<GVCoord> &_controlPoints); //�������е�_controlPoints�еĵ㣬������vtx

	void configControlPoints(int idx, std::vector<GVCoord> &_controlPoints);
};