/*
//八叉树节点类，用头节点代表八叉树
//采用opengl右手坐标系，靠近原点的那个角为锚点，方便计算
//本八叉树的策略是：1，一次划分所有节点，是满树；2，当立方体空间完全包含某物体才剔除,当立方体空间与某物体相交或者完全包含时才查询；3，对象放在完全包含它的区域叶子节点内，非根节点不存储对象，默认为物体不可能跨多个叶子节点，都在一个叶子节点的空间范围内部，未考虑交叉的情况
*/
#pragma once
#include <list>

//八叉树节点类型
enum OctreeType
{
	ROOT,                   //根
	BOTTOM_LEFT_FRONT,		// 1 
	BOTTOM_RIGHT_FRONT,		// 2 
	BOTTOM_LEFT_BACK,		// 3 
	BOTTOM_RIGHT_BACK,      // 4 
	TOP_LEFT_FRONT,         // 5 
	TOP_RIGHT_FRONT,        // 6 
	TOP_LEFT_BACK,          // 7 
	TOP_RIGHT_BACK          // 8   
};

template <class T>
class OctreeNode
{
public:
	OctreeNode(float _x, float _y, float _z, float _xSize, float _ySize, float _zSize, OctreeType _octreeNodeType, int _level, int _maxLevel);
	~OctreeNode();
public:
	void BuildTree(int level); //建立八叉树，划分到所有子节点
	void InsertObject(T *object); //插入对象
	std::list<T *> GetObjectsAt(float px, float py, float pz, float x_size, float y_size, float z_size); //查询对象,获得一片区域里的对象链表,考虑包含或相交,由于
	void RemoveObjectsAt(float px, float py, float pz, float x_size, float y_size, float z_size); //删除对象，删除一片区域里的对象，此处只考虑完全包含的
private:
	bool IsContain(float px, float py, float pz, float x_size, float y_size, float z_size, T *object) const; //判断某个区域是否包含某对象
	bool IsContain(float px, float py, float pz, float x_size, float y_size, float z_size, OctreeNode<T> *octreeNode) const; //重载，判断某个区域是否包含某个节点
	bool IsInterSect(float px, float py, float pz, float x_size, float y_size, float z_size, OctreeNode<T> *octreeNode) const; //判断某个区域是否与节点相交，如果相交，则查询时要递归到其子节点
public:
	std::list<T *> objectList; //节点存储的对象列表
private:
	//节点属性
	OctreeType octreeNodeType;
	float x;
	float y;
	float z;
	float xSize;
	float ySize;
	float zSize;
	int level;
	int maxLevel;
	//子节点,根据opengl坐标系，依次坐标增大
	OctreeNode *bottom_left_front_node;
	OctreeNode *bottom_right_front_node;
	OctreeNode *bottom_left_back_node;
	OctreeNode *bottom_right_back_node;
	OctreeNode *top_left_front_node;
	OctreeNode *top_right_front_node;
	OctreeNode *top_left_back_node;
	OctreeNode *top_right_back_node;
};
