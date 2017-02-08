#pragma once

#include "ImageVector.h"
#include <vector>

class ImageVectorsRegion
{
public:
	//methods

	ImageVectorsRegion(COLORREF region_color);
	ImageVector* GetCore();
	void SetCore(ImageVector* value);
	bool IsCoreCompleted();

	void AddImageVectorToRegion(ImageVector* value);
	std::vector<ImageVector*> GetImageVectorList();
	void ClearRegion();

	void DefineRegionCore(long* sync_variable);

	void Draw(HDC hdc);
	~ImageVectorsRegion();
private:
	//fields		

	COLORREF color;
	HPEN hPen;
	HBRUSH hBrush;

	ImageVector* old_core;
	ImageVector* current_core;
	std::vector<ImageVector*> image_vector_list;
	bool is_core_completed;

	long* sync_variable;

	//methods
	static DWORD WINAPI DefineRegionCoreThreadFunc(LPVOID lpParameter);
};
