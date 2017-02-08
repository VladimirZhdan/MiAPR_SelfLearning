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
	void PerformNextStepPackingRegions();	
	bool IsFormRegionsCompleted();
private:
	//fields

	std::vector<ImageVector*> image_vector_list;
	std::vector<ImageVectorsRegion*> region_list;
	bool is_form_regions_completed;

	//methods
	
	void AddRegion(ImageVector* region_core);
	ImageVector* GetRandomImageVectorFromList(std::vector<ImageVector*> image_vector_list);
	ImageVector* GetFarthestImageVectorToImageVectorFromList(std::vector<ImageVector*> image_vector_list, ImageVector* desc, double *farthest_distance = nullptr);
	void DefineRegions();
	double GetHalfArithmeticMeanDistanceBetweenRegionCores();

};

