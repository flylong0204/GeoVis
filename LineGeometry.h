#ifndef __LINE_GEOMETRY_H__

#define __LINE_GEOMETRY_H__

#include<vector>
#include "Coord.h"
#include "osg/Vec3d"
class lineGeometry
{
public:
	lineGeometry();
	virtual void setControlPoints(std::vector<GVCoord>& vtxBuffer);
	virtual bool toVertice(std::vector<GVCoord>& vtxBuffer, std::vector<int>* vtxBuffer2 /* = NULL */);

private:
	std::vector<GVCoord> _controlPoints;
	double scale;
};

#endif  // __LINE_GEOMETRY_H__