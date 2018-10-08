#pragma once
//被管理的对象

class Object
{
public:
	Object(float _x, float _y, float _z, float _xSize, float _ySize, float _zSize);
	~Object();
public:
	//对象的属性，例如坐标和长宽高，以左上角为锚点
	float x;
	float y;
	float z;
	float xSize;
	float ySize;
	float zSize;
};