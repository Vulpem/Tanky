#include "Tower.h"

Tower::Tower()
{}
Tower::Tower(float x, float z, float height, float cubeSize)
{
	for (int h = 0; h < height; h++)
	{
		int w = 0;
		Cube* cube = new Cube(cubeSize, cubeSize, cubeSize);
		float offsetX = 0;
		float offsetZ = 0;
		if (w == 1 || w == 3)
			offsetX = cubeSize;
		if (w > 1)
			offsetZ = cubeSize;
		int y = cubeSize / 2;

		cube->SetPos(x, y + h*cubeSize, z);
		positions.PushBack({ x, y + h*cubeSize, z });
		cube->color = Color(0.8f, 0.3f, 0.0f);

		cubes.PushBack(cube);
	}

}
void Tower::Update()
{
	for (int i = 0; i < cubes.Count(); i++)
	{
		pbs[i]->GetTransform(&cubes[i]->transform);
		cubes[i]->Render();
	}
	if (!fallen)
	{
		if (isDestroyed())
		{
			ChangeColor(Color{ 0.0f, 0.6f, 0.0f });
			fallen = true;
		}
	}
}

bool Tower::isDestroyed()
{
	int blocksDown = 0;
	for (int i = 0; i < pbs.Count(); i++)
	{
		float x, y, z;
		pbs[i]->GetPos(&x, &y, &z);
		float difX = abs(x - positions[i].x);
		float difY = abs(y - positions[i].y);
		float difZ = abs(z - positions[i].z);

		float distance = difX + difY + difZ;
		if (distance > 1.0f)
			blocksDown++;
	}
	if (blocksDown > pbs.Count() / 3 + 0.5)
		return true;
	return false;
}

void Tower::ChangeColor(Color color)
{
	for (int i = 0; i < cubes.Count(); i++)
	{
		cubes[i]->color = color;
	}
}