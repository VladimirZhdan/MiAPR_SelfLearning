#pragma once

#include "ImageVectorsRegion.h"
#include "ImageVector.h"
#include <vector>
#include <time.h>

class SelfLearningLogic
{
public:
	SelfLearningLogic(std::vector<ImageVector*> image_vector_list);
	~SelfLearningLogic();
	void DrawRegions(HDC hdc);
	void Init();
private:
	//fields

	std::vector<ImageVector*> image_vector_list;
	std::vector<ImageVectorsRegion*> region_list;

	//methods
	
	ImageVector* GetRandomImageVectorFromList(std::vector<ImageVector*> image_vector_list);
	ImageVector* GetFarthestImageVectorToImageVectorFromList(std::vector<ImageVector*> image_vector_list, ImageVector* desc);


};

