#ifndef VERTEX_MAP
#define VERTEX_MAP

#include <map>
using namespace std;

template<class NameT, class DataT>
class MapVertex
{
	map<NameT, DataT> mapVertex;

public:
	//если второе имя не занято то делаем замену
	bool replaceName(NameT name1, NameT name2)
	{
		if (mapVertex.find(name2) == mapVertex.end())
		{
			DataT data = mapVertex[name1];
			mapVertex.erase(name1);
			mapVertex[name2] = data;
			return true;
		}
		return false;
	}

	bool addPair(NameT name, DataT data)
	{
		if (mapVertex.find(name) == mapVertex.end())
		{
			mapVertex[name] = data;
			return true;
		}
		return false;
	}

	DataT getData(NameT name)
	{
		if (mapVertex.find(name) != mapVertex.end())
			return mapVertex[name];
		else
			throw 1;
	}

	bool delPair(NameT name)
	{
		if (mapVertex.erase(name) == 1)
			return true;
		else
			return false;
	}
};

#endif // VERTEX_MAP_H
