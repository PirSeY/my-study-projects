#ifndef VERTEX_H
#define VERTEX_H

/**
*����� ������� �����
*/

template <class NameT, class DataT>
class Vertex {
	NameT name;     //��� �������
	DataT data;     //������ �������
	bool nameSet, dataSet;
public:
	int index;//������ �������
	int color;
	int distance;


	//������������
	Vertex() : nameSet(false), dataSet(false)
	{
		color = 0;//�����
		distance = INT_MAX;
	}
	Vertex(NameT name, DataT data) : name(name), data(data), nameSet(true), dataSet(true)
	{
		color = 0;//�����
		distance = INT_MAX;
	}

	//���������, ��������� ����� � ������
	void setName(NameT name) { this->name = name; nameSet = true; }
	void setData(DataT data) { this->data = data; dataSet = true; }
	NameT getName() { return name; }
	DataT getData() { return data; }
	bool isNameSet() { return nameSet; }
	bool isDataSet() { return dataSet; }
};

#endif // VERTEX_H
