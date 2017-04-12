#ifndef __LINE_GEOMETRY_H__

#define __LINE_GEOMETRY_H__

#include<vector>
#include "Coord.h"
#include "osg/Vec3d"
class LineGeometry
	
{
public:
	LineGeometry();
	~LineGeometry();
	virtual int getControlPointCount();
	virtual void getControlPoints(std::vector<GVCoord>& vtxBuffer);
	virtual GVCoord getControlPoint(int idx);
	virtual void setControlPointsEx(std::vector<GVCoord> &vtxBuffer);
    virtual void setControlPoints(std::vector<GVCoord>& vtxBuffer) = 0;
	virtual void setControlPoint(int idx, const GVCoord& vtx) = 0;
	virtual bool toVertice(std::vector<GVCoord>& vtxBuffer, std::vector<int>* vtxBuffer2 /* = NULL */) const = 0;

private:
	std::vector<GVCoord> allPoints;
};

#endif  // __LINE_GEOMETRY_H__