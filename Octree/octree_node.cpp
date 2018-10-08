#include "octree_node.h"

template <class T>
OctreeNode<T>::OctreeNode(float _x, float _y, float _z, float _xSize, float _ySize, float _zSize, OctreeType _octreeNodeType, int _level, int _maxLevel) :
	x(_x),
	y(_y),
	z(_z),
	xSize(_xSize),
	ySize(_ySize),
	zSize(_zSize),
	octreeNodeType(_octreeNodeType),
	level(_level),
	maxLevel(_maxLevel)
{
	//初始子节点都赋空值
	bottom_left_front_node = nullptr;
	bottom_right_front_node = nullptr;
	bottom_left_back_node = nullptr;
	bottom_right_back_node = nullptr;
	top_left_front_node = nullptr;
	top_right_front_node = nullptr;
	top_left_back_node = nullptr;
	top_right_back_node = nullptr;
}

template <class T>
OctreeNode<T>::~OctreeNode()
{

}

template <class T>
bool OctreeNode<T>::IsContain(float px, float py, float pz, float x_size, float y_size, float z_size, T *object) const
{
	if (object->x >= px
		&&object->x + object->xSize <= px + x_size
		&&object->y >= py
		&&object->y + object->ySize <= py + y_size
		&&object->z >= pz
		&&object->z + object->zSize <= pz + z_size)
		return true;
	return false;
}

template <class T>
bool OctreeNode<T>::IsContain(float px, float py, float pz, float x_size, float y_size, float z_size, OctreeNode<T> *octreeNode) const
{
	if (octreeNode->x >= px
		&&octreeNode->x + octreeNode->xSize <= px + x_size
		&&octreeNode->y >= py
		&&octreeNode->y + octreeNode->ySize <= py + y_size
		&&octreeNode->z >= pz
		&&octreeNode->z + octreeNode->zSize <= pz + z_size)
		return true;
	return false;
}

template <class T>
bool OctreeNode<T>::IsInterSect(float px, float py, float pz, float x_size, float y_size, float z_size, OctreeNode<T> *octreeNode) const
{
	if (octreeNode->x>px + x_size
		|| octreeNode->x + xSize<px
		|| octreeNode->y>py + y_size
		|| octreeNode->y + ySize<py
		|| octreeNode->z + zSize<pz
		|| octreeNode->z>pz + z_size)
		return false;
	return true;
}

template <class T>
void OctreeNode<T>::BuildTree(int level)
{
	//递归地进行八叉树空间划分，直到最大深度
	if (level == maxLevel)
		return;
	//创建子节点
	bottom_left_front_node = new OctreeNode(x, y, z, xSize / 2, ySize / 2, zSize / 2, BOTTOM_LEFT_FRONT, level + 1, maxLevel);
	bottom_right_front_node = new OctreeNode(x + xSize / 2, y, z, xSize / 2, ySize / 2, zSize / 2, BOTTOM_RIGHT_FRONT, level + 1, maxLevel);
	bottom_left_back_node = new OctreeNode(x, y + ySize / 2, z, xSize / 2, ySize / 2, zSize / 2, BOTTOM_LEFT_BACK, level + 1, maxLevel);
	bottom_right_back_node = new OctreeNode(x + xSize / 2, y + ySize / 2, z, xSize / 2, ySize / 2, zSize / 2, BOTTOM_RIGHT_BACK, level + 1, maxLevel);
	top_left_front_node = new OctreeNode(x, y, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, TOP_LEFT_FRONT, level + 1, maxLevel);
	top_right_front_node = new OctreeNode(x + xSize / 2, y, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, TOP_RIGHT_FRONT, level + 1, maxLevel);
	top_left_back_node = new OctreeNode(x, y + ySize / 2, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, TOP_LEFT_BACK, level + 1, maxLevel);
	top_right_back_node = new OctreeNode(x + xSize / 2, y + ySize / 2, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, TOP_RIGHT_BACK, level + 1, maxLevel);
	//递归构造
	bottom_left_front_node->BuildTree(level + 1);
	bottom_right_front_node->BuildTree(level + 1);
	bottom_left_back_node->BuildTree(level + 1);
	bottom_right_back_node->BuildTree(level + 1);
	top_left_front_node->BuildTree(level + 1);
	top_right_front_node->BuildTree(level + 1);
	top_left_back_node->BuildTree(level + 1);
	top_right_back_node->BuildTree(level + 1);
}

template <class T>
void OctreeNode<T>::InsertObject(T *object)
{
	if (level == maxLevel)
	{
		objectList.push_back(object);
		return;
	}
	//递归地插入，直到叶子节点
	//1
	if (bottom_left_front_node&&IsContain(x, y, z, xSize / 2, ySize / 2, zSize / 2, object))
	{
		bottom_left_front_node->InsertObject(object);
		return;
	}
	//2
	if (bottom_right_front_node&&IsContain(x + xSize / 2, y, z, xSize / 2, ySize / 2, zSize / 2, object))
	{
		bottom_right_front_node->InsertObject(object);
		return;
	}
	//3
	if (bottom_left_back_node&&IsContain(x, y + ySize / 2, z, xSize / 2, ySize / 2, zSize / 2, object))
	{
		bottom_left_back_node->InsertObject(object);
		return;
	}
	//4
	if (bottom_right_back_node&&IsContain(x + xSize / 2, y + ySize / 2, z, xSize / 2, ySize / 2, zSize / 2, object))
	{
		bottom_right_back_node->InsertObject(object);
		return;
	}
	//5
	if (top_left_front_node&&IsContain(x, y, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, object))
	{
		top_left_front_node->InsertObject(object);
		return;
	}
	//6
	if (top_right_front_node&&IsContain(x + xSize / 2, y, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, object))
	{
		top_right_front_node->InsertObject(object);
		return;
	}
	//7
	if (top_left_back_node&&IsContain(x, y + ySize / 2, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, object))
	{
		top_left_back_node->InsertObject(object);
		return;
	}
	//8
	if (top_right_back_node&&IsContain(x + xSize / 2, y + ySize / 2, z + zSize / 2, xSize / 2, ySize / 2, zSize / 2, object))
	{
		top_right_back_node->InsertObject(object);
		return;
	}
}

template <class T>
std::list<T *> OctreeNode<T>::GetObjectsAt(float px, float py, float pz, float x_size, float y_size, float z_size)
{
	if (level == maxLevel)
		return objectList;
	std::list<T *> resObjects;
	//递归地判断选定区域是否与某个节点相交（包含或被包含都算）
	//1
	if (bottom_left_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_left_front_node))
	{
		std::list<T *> childObjects1 = bottom_left_front_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects1.begin(), childObjects1.end());
	}
	//2
	if (bottom_right_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_right_front_node))
	{
		std::list<T *> childObjects2 = bottom_right_front_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects2.begin(), childObjects2.end());
	}
	//3
	if (bottom_left_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_left_back_node))
	{
		std::list<T *> childObjects3 = bottom_left_back_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects3.begin(), childObjects3.end());
	}
	//4
	if (bottom_right_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_right_back_node))
	{
		std::list<T *> childObjects4 = bottom_right_back_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects4.begin(), childObjects4.end());
	}
	//5
	if (top_left_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_left_front_node))
	{
		std::list<T *> childObjects5 = top_left_front_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects5.begin(), childObjects5.end());
	}
	//6
	if (top_right_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_right_front_node))
	{
		std::list<T *> childObjects6 = top_right_front_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects6.begin(), childObjects6.end());
	}
	//7
	if (top_left_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_left_back_node))
	{
		std::list<T *> childObjects7 = top_left_back_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects7.begin(), childObjects7.end());
	}
	//8
	if (top_right_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_right_back_node))
	{
		std::list<T *> childObjects8 = top_right_back_node->GetObjectsAt(px, py, pz, x_size, y_size, z_size);
		resObjects.insert(resObjects.end(), childObjects8.begin(), childObjects8.end());
	}

	return resObjects;
}

template <class T>
void OctreeNode<T>::RemoveObjectsAt(float px, float py, float pz, float x_size, float y_size, float z_size)
{
	if (level == maxLevel)
	{
		if (IsContain(px, py, pz, x_size, y_size, z_size, this))
			objectList.clear(); //到了叶子节点且完全被包含就把该节点存储的对象清空
		return;
	}
	//递归地判断选定区域是否与某个节点相交（包含或被包含都算）,没有相交就不用再递归了
	//1
	if (bottom_left_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_left_front_node))
		bottom_left_front_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//2
	if (bottom_right_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_right_front_node))
		bottom_right_front_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//3
	if (bottom_left_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_left_back_node))
		bottom_left_back_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//4
	if (bottom_right_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, bottom_right_back_node))
		bottom_right_back_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//5
	if (top_left_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_left_front_node))
		top_left_front_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//6
	if (top_right_front_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_right_front_node))
		top_right_front_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//7
	if (top_left_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_left_back_node))
		top_left_back_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
	//8
	if (top_right_back_node&&IsInterSect(px, py, pz, x_size, y_size, z_size, top_right_back_node))
		top_right_back_node->RemoveObjectsAt(px, py, pz, x_size, y_size, z_size);
}
