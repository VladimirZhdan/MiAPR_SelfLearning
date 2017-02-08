#include "stdafx.h"
#include "SelfLearningLogic.h"


SelfLearningLogic::SelfLearningLogic(std::vector<ImageVector*> image_vector_list)
{
	this->image_vector_list = image_vector_list;	
	this->is_form_regions_completed = false;
	Init();
}


SelfLearningLogic::~SelfLearningLogic()
{
}

void SelfLearningLogic::DrawRegions(HDC hdc)
{
	for (ImageVectorsRegion* region : region_list)
	{
		region->Draw(hdc);
	}
}

void SelfLearningLogic::Init()
{
	ImageVector* core = GetRandomImageVectorFromList(image_vector_list);
	AddRegion(core);

	core = GetFarthestImageVectorToImageVectorFromList(image_vector_list, region_list[0]->GetCore());
	AddRegion(core);

	DefineRegions();
}

void SelfLearningLogic::PerformNextStepPackingRegions()
{	
	ImageVector* farthest_regions_image_vector = nullptr;
	double farthest_regions_distance = 0;

	ImageVector* current_farthest_image_vector;
	double current_distance = 0;
	for (ImageVectorsRegion* region : region_list)
	{
		current_farthest_image_vector = GetFarthestImageVectorToImageVectorFromList(region->GetImageVectorList(), region->GetCore(), &current_distance);
		if (current_distance > farthest_regions_distance)
		{
			farthest_regions_image_vector = current_farthest_image_vector;
			farthest_regions_distance = current_distance;
		}				
	}

	double half_arithmetic_mean_distance = GetHalfArithmeticMeanDistanceBetweenRegionCores();

	if ((farthest_regions_image_vector != nullptr) && (farthest_regions_distance > half_arithmetic_mean_distance))
	{
		AddRegion(farthest_regions_image_vector);
		DefineRegions();
	}
	else
	{
		is_form_regions_completed = true;
	}
}

bool SelfLearningLogic::IsFormRegionsCompleted()
{
	return is_form_regions_completed;
}

void SelfLearningLogic::AddRegion(ImageVector * region_core)
{
	ImageVectorsRegion* region = new ImageVectorsRegion(ImageVector::GetRandomColor());
	region->SetCore(region_core);
	region_list.push_back(region);
}

//Выбирает случайный элемент из вектора
//Предусловия размер вектора должен быть больше 0
ImageVector * SelfLearningLogic::GetRandomImageVectorFromList(std::vector<ImageVector*> image_vector_list)
{
	if (!(image_vector_list.size() > 0))
	{
		throw std::invalid_argument("Неверные агрументы функции GetRandomImageVectorFromList");
	}

	srand(time(NULL));	

	int random_index = rand() % image_vector_list.size();

	return image_vector_list[random_index];
}

//Выбирает самый далекий элемент от переданного в векторе
//Предусловия размер вектора должен быть больше 0
ImageVector * SelfLearningLogic::GetFarthestImageVectorToImageVectorFromList(std::vector<ImageVector*> image_vector_list, ImageVector * desc, double *distance)
{
	if (!(image_vector_list.size() > 0))
	{
		throw std::invalid_argument("Неверные агрументы функции GetFarthestImageVectorToImageVectorFromList");
	}

	double farthest_distance = 0;
	int farthest_image_vector_index = 0;
	double current_distance;
	for (int i = 0; i < image_vector_list.size(); ++i)
	{
		current_distance = desc->DistanceTo(image_vector_list[i]);
		if (current_distance > farthest_distance)
		{
			farthest_distance = current_distance;
			farthest_image_vector_index = i;
		}
	}

	if (distance != nullptr)
	{
		*distance = farthest_distance;
	}

	return image_vector_list[farthest_image_vector_index];
}

void SelfLearningLogic::DefineRegions()
{
	for (ImageVectorsRegion* region : region_list)
	{
		region->ClearRegion();
	}

	double min_distance;
	double current_distance;
	ImageVectorsRegion* choosen_region;
	for (ImageVector* image_vector : image_vector_list)
	{
		if (region_list.size() > 0)
		{
			choosen_region = region_list[0];
			min_distance = image_vector->DistanceTo(region_list[0]->GetCore());

			for (int i = 1; i < region_list.size(); ++i)
			{
				current_distance = image_vector->DistanceTo(region_list[i]->GetCore());
				if (current_distance < min_distance)
				{
					min_distance = current_distance;
					choosen_region = region_list[i];
				}
			}

			choosen_region->AddImageVectorToRegion(image_vector);
		}
	}
}

double SelfLearningLogic::GetHalfArithmeticMeanDistanceBetweenRegionCores()
{
	double arithmetion_mean_distance = 0;
	int distances_count = 0;

	for (int i = 0; i < region_list.size(); ++i)
	{
		ImageVector* current_core = region_list[i]->GetCore();
		for (int j = i + 1; j < region_list.size(); ++j)
		{
			arithmetion_mean_distance += current_core->DistanceTo(region_list[j]->GetCore());
			++distances_count;
		}
	}

	arithmetion_mean_distance /= distances_count;
	
	double result = arithmetion_mean_distance / 2;

	return result;
}
