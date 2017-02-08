#include "stdafx.h"
#include "DrawingLogic.h"

DrawingLogic::DrawingLogic()
{

}


DrawingLogic::~DrawingLogic()
{
}

void DrawingLogic::Drawing(HDC hdc, RECT clientRect, SelfLearningLogic* controlled_learning_logic)
{
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	HDC bufferHDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);

	try
	{
		HGDIOBJ oldBitmap = SelectObject(bufferHDC, bitmap);
		FillRect(bufferHDC, &clientRect, (HBRUSH)WHITE_BRUSH);

		controlled_learning_logic->DrawRegions(bufferHDC);

		BitBlt(hdc, 0, 0, windowWidth, windowHeight, bufferHDC, 0, 0, SRCCOPY);
		SelectObject(bufferHDC, oldBitmap);
	}
	catch (...)
	{
		DeleteDC(bufferHDC);
		DeleteObject(bitmap);
	}
	DeleteDC(bufferHDC);
	DeleteObject(bitmap);
}

//Генерирует случайны список, состоящий из ImageVector*, содержащий неповторяющиеся элементы
//Предусловия: count, max_x, max_y - целые положительные числа
vector<ImageVector*> DrawingLogic::GenerateRandomImageVectorList(int count, int max_x, int max_y)
{
	if (count < 0 || max_x < 0 || max_y < 0)
	{
		throw invalid_argument("Неверные агрументы функции GenerateRandomImageVectorList");
	}

	srand(time(NULL));

	vector<ImageVector*> result;

	ImageVector* added_image_vector = nullptr;
	for (int i = 0; i < count; ++i)
	{
		do
		{
			if (added_image_vector != nullptr)
			{
				delete(added_image_vector);
				added_image_vector = nullptr;
			}
			added_image_vector = ImageVector::GetRandomImageVector(max_x, max_y);
		} while (CheckRepeated(result, added_image_vector));
		result.push_back(added_image_vector);
		added_image_vector = nullptr;
	}

	return result;
}

bool DrawingLogic::CheckRepeated(vector<ImageVector*> image_vector_list, ImageVector * value)
{
	bool result = false;

	for (int i = 0; (i < image_vector_list.size()) && !result; ++i)
	{
		if (image_vector_list[i]->CompareTo(value))
		{
			result = true;
		}
	}

	return result;
}
