#pragma once

#include <vector>
#include "ImageVector.h"
#include "SelfLearningLogic.h"

using namespace std;

class DrawingLogic
{
public:
	DrawingLogic();
	~DrawingLogic();
	static void Drawing(HDC hdc, RECT clientRect, SelfLearningLogic* controlled_learning_logic);
	static vector<ImageVector*> GenerateRandomImageVectorList(int count, int max_x, int max_y);
private:
	static bool CheckRepeated(vector<ImageVector*> image_vector_list, ImageVector* value);
};

