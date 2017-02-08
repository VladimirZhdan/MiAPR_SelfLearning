#include "stdafx.h"
#include "ImageVectorsRegion.h"


ImageVectorsRegion::ImageVectorsRegion(COLORREF region_color)
{
	this->color = region_color;
	this->old_core = nullptr;
	this->current_core = nullptr;
	this->is_core_completed = false;
	this->hPen = CreatePen(PS_SOLID, 1, color);
	this->hBrush = CreateSolidBrush(color);
}

void ImageVectorsRegion::SetCore(ImageVector * value)
{
	if (value == current_core || value == old_core)
	{
		is_core_completed = true;
	}
	else
	{
		is_core_completed = false;
	}
	old_core = current_core;
	current_core = value;
}

ImageVector * ImageVectorsRegion::GetCore()
{
	return current_core;
}

bool ImageVectorsRegion::IsCoreCompleted()
{
	return is_core_completed;
}

void ImageVectorsRegion::AddImageVectorToRegion(ImageVector * value)
{
	image_vector_list.push_back(value);
}

void ImageVectorsRegion::ClearRegion()
{
	image_vector_list.clear();
}


void ImageVectorsRegion::DefineRegionCore(long* sync_variable)
{
	this->sync_variable = sync_variable;

	QueueUserWorkItem(DefineRegionCoreThreadFunc, this, 0);
}

void ImageVectorsRegion::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	for (ImageVector* image_vector : image_vector_list)
	{
		image_vector->Draw(hdc);
	}


	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));

	current_core->Draw(hdc);

	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}

ImageVectorsRegion::~ImageVectorsRegion()
{
	image_vector_list.clear();
}

DWORD ImageVectorsRegion::DefineRegionCoreThreadFunc(LPVOID lpParameter)
{
	ImageVectorsRegion* thisObj = (ImageVectorsRegion*)lpParameter;
	std::vector<ImageVector*> image_vector_list = thisObj->image_vector_list;

	int index_min_squared_distance_sum = 0;
	double min_squared_distance_sum = DBL_MAX;

	for (int i = 0; i < image_vector_list.size(); ++i)
	{
		ImageVector* current_image_vector = image_vector_list[i];
		double current_squared_distance_sum = 0;
		for (int j = 0; j < image_vector_list.size(); ++j)
		{
			current_squared_distance_sum += current_image_vector->SquaredDistanceTo(image_vector_list[j]);
		}

		if (current_squared_distance_sum < min_squared_distance_sum)
		{
			index_min_squared_distance_sum = i;
			min_squared_distance_sum = current_squared_distance_sum;
		}
	}

	thisObj->SetCore(image_vector_list[index_min_squared_distance_sum]);

	InterlockedDecrement(thisObj->sync_variable);

	return 0;
}
