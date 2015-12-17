#include "Tower.h"

Tower::Tower()
{}
Tower::Tower(float x, float z, float height, float cubeSize)
{
	startPosition.x = x;
	startPosition.y = cubeSize / 2;
	startPosition.z = z;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			Cube* cube = new Cube(cubeSize, cubeSize, cubeSize);
			float offsetX = 0;
			float offsetZ = 0;
			if (w == 1 || w == 3)
				offsetX = cubeSize;
			if (w > 1)
				offsetZ = cubeSize;

			float x = startPosition.x + offsetX;
			float y = startPosition.y + h * cubeSize;
			float z = startPosition.z + offsetZ;
			cube->SetPos(x, y, z);
			cubes.PushBack(cube);

		}
	}
	/*
	column.size.x = cubeSize;
	column.size.y = cubeSize;
	column.size.z = cubeSize;
	column.SetPos(x, (height/2), z);
	*/

}
void Tower::Update()
{
	for (int i = 0; i < cubes.Count(); i++)
	{
		cubes[i]->Render();
	}
	/*
	float x, y, z;

	pb->GetPos(&x, &y, &z);
	float difX = startPosition.x - x;
	float difY = startPosition.y - y;
	float difZ = startPosition.z - z;
	if (difX < -0.2f || 0.2f < difX || difY < -0.2f || 0.2f < difY || difZ < -0.2f || 0.2f < difZ)
	{
	if (pb->isResting())
	{
	fallen = true;
	column.color = { 0.5f, 0, 0 };
	}
	}
	column.Render();
	*/

}