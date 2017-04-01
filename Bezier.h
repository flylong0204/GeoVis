#ifndef __BEZIER_H__
#define __BEZIER_H__

class Bezier
{
public:
	void getBezier(const std::vector<GVCoord>& controlPoints, std::vector<GVCoord>* bezierPoints);
};
#endif