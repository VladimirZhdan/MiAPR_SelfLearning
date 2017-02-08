#include "stdafx.h"
#include "SelfLearningLogic.h"


SelfLearningLogic::SelfLearningLogic(std::vector<ImageVector*> image_vector_list)
{
	this->image_vector_list = image_vector_list;
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
	ImageVectorsRegion* region = new ImageVectorsRegion(ImageVector::GetRandomColor());
	region->SetCore(core);
	region_list.push_back(region);

	core = GetFarthestImageVectorToImageVectorFromList(image_vector_list, region_list[0]->GetCore());
	region = new ImageVectorsRegion(ImageVector::GetRandomColor());
	region->SetCore(core);
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
ImageVector * SelfLearningLogic::GetFarthestImageVectorToImageVectorFromList(std::vector<ImageVector*> image_vector_list, ImageVector * desc)
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
		if (current_distance < farthest_distance)
		{
			farthest_distance = current_distance;
			farthest_image_vector_index = i;
		}
	}

	return image_vector_list[farthest_image_vector_index];
}
