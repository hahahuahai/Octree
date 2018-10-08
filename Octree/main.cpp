#include <iostream>
#include "object.h"
#include "octree_node.h"
#include "octree_node.cpp" //模板分开写要包含h和cpp
using namespace std;
int main()
{
	OctreeNode<Object> *octree = new OctreeNode<Object>(0, 0, 0, 200, 200, 200, ROOT, 1, 3);
	octree->BuildTree(1);

	octree->InsertObject(new Object(10, 10, 10, 30, 30, 30));
	octree->InsertObject(new Object(11, 11, 11, 32, 32, 32));
	octree->InsertObject(new Object(110, 60, 60, 30, 30, 30));
	octree->InsertObject(new Object(110, 110, 110, 30, 30, 30));

	octree->RemoveObjectsAt(0, 0, 0, 110, 70, 70);
	list<Object *> resObjects = octree->GetObjectsAt(0, 0, 0, 130, 130, 130);
	cout << resObjects.size() << endl;
	for (auto &t : resObjects)
		cout << t->x << ' ' << t->y << ' ' << t->z << ' ' << t->xSize << ' ' << t->ySize << ' ' << t->zSize << endl;

	delete octree;
	system("pause");
	return 0;
}
