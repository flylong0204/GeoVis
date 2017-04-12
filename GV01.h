#ifndef __GV_01_H__
#define __GV_01_H__
#include "Coord.h"
#include <vector>
#include "LineGeometry.h"

class GV01 
	:public LineGeometry
{

public:
	GV01();
	~GV01();
	virtual int getControlPointCount();
	virtual void getControlPoints(std::vector<GVCoord>& vtxBuffer);
	virtual GVCoord getControlPoint(int idx);
	virtual void setControlPointsEx(std::vector<GVCoord>& vtxBuffer);
	virtual void setControlPoints(std::vector<GVCoord>& vtxBuffer);
	virtual void setControlPoint(int idx, const GVCoord& vtx);
	virtual bool toVertice(std::vector<GVCoord>& vtxBuffer, std::vector<int>* vtxBuffer2 ) const;
private:
	std::vector<GVCoord> _controlPoints;
};


#endif