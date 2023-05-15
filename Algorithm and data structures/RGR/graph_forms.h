#ifndef GRAPH_FORMS_H
#define GRAPH_FORMS_H

/**
 *������ �������� ���� �����:
 *����������� ����� ���������
 *��������� ����� �� �������
 *��������� ����� �� ������
 */

#include <vector>
#include <list>
using namespace std;

template <class EdgeT>
class GraphForm {
public:
    //������� � �������� ������ � ����
    virtual bool insertVertex(int index) = 0;
    virtual bool deleteVertex(int index) = 0;
    virtual bool insertEdge(int v1, int v2, EdgeT* t) = 0;
    virtual bool deleteEdge(int v1, int v2) = 0;
    //������� �������� � ��������� �� ������� ����
    virtual int deleteEdgesFromVertex(int index, bool directed) = 0;


    //�������� � ���������
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual EdgeT* getEdge(int v1, int v2) = 0;

    //virtual void showGraph() = 0;
};


template <class EdgeT>
class GraphMatrixForm : public GraphForm<EdgeT> {
    //friend class EdgeIterator;
    bool directed;
    vector<vector<EdgeT*>> matrix; //������� ���������
public:

    GraphMatrixForm(bool directed) : directed(directed) {}

    //������� � �������� ������ � ����
    bool insertVertex(int index) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (index < 0 || index > size) return false;

        //������ ����� ������ ������
        vector<EdgeT*> newLine;
        newLine.assign(size, NULL);

        //��������� ����� ������:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;

        //��������� ����� �������:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (EdgeT*)NULL);

        return true;
    }
    bool deleteVertex(int index) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (index < 0 || index >= size) return false;

        //������� ������:
        matrix.erase(matrix.begin() + index);
        --size;

        //������� �������:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);

        return true;
    }
    bool insertEdge(int v1, int v2, EdgeT* t) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ��� ����� ��� ����
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;

        //��������� �����
        matrix[v1][v2] = t;

        return true;
    }
    bool deleteEdge(int v1, int v2) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ���
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;

        matrix[v1][v2] = NULL;
        return true;
    }
    //������� �������� � ��������� �� ������� ����
    int deleteEdgesFromVertex(int index, bool directed) {
        int size = matrix.size(); //����� ������
        int deleted = 0;

        //�������� ����� �������
        if (index < 0 || index >= size) return 0;

        //������� ��������� � �������� ����
        for (int i = 0; i < size; i++) {
            if (matrix[i][index] != NULL) {
                delete matrix[i][index];
                matrix[i][index] = NULL;
                ++deleted;
                //������� ������������ �����
                if (directed == false)
                    matrix[index][i] = NULL;
            }
            if (matrix[index][i] != NULL) {
                delete matrix[index][i];
                matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
    }


    //�������� � ���������
    bool hasEdge(int v1, int v2) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //�����
        if (v1 == v2) return false;

        if (matrix[v1][v2] != NULL) return true;
        return false;
    }
    EdgeT* getEdge(int v1, int v2) {
        int size = matrix.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) throw 1;
        //�����
        if (v1 == v2 || matrix[v1][v2] == NULL) throw 1;
        return matrix[v1][v2];
    }

    //�������� ����
    class EdgeIterator {
        int curI, curJ;
        bool end;
        GraphMatrixForm* f;
    public:
        EdgeIterator(GraphMatrixForm* f) {
            this->f = f;
            begin();
        }
        bool begin() {
            for (int i = 0; i < f->matrix.size(); ++i)
                for (int j = 0; j < f->matrix.size(); ++j)
                    if (f->matrix[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return 1;
                    }
            end = true;
            return 0;
        }
        bool onEnd() { return end; }
        bool next() {
            if (end)
                return 0;
            ++curJ;
            while (curI < f->matrix.size()) {
                while (curJ < f->matrix.size()) {
                    if (f->matrix[curI][curJ])
                        return 1;
                    ++curJ;
                }
                ++curI;
                curJ = (f->directed ? 0 : curI + 1);
            }
            end = true;
            return false;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return f->matrix[curI][curJ];
        }
    };

    //�������� ��������� ����
    class OutputEdgeIterator {
        int curI, curJ;
        bool end;
        GraphMatrixForm* f;
    public:
        OutputEdgeIterator(GraphMatrixForm* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }
        bool begin()
        {
            for (curJ = 0; curJ < f->matrix.size(); ++curJ)
                if (f->matrix[curI][curJ])
                {
                    end = false;
                    return 1;
                }

            end = true;
            return 0;
        }
        bool onEnd() { return end; }
        bool next() {
            if (end)
                return 0;
            ++curJ;
            while (curJ < f->matrix.size()) {
                if (f->matrix[curI][curJ])
                    return 1;
                ++curJ;
            }
            end = true;
            return 0;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return f->matrix[curI][curJ];
        }
    };
};


template <class EdgeT>
class GraphListForm : public GraphForm<EdgeT> {
    //������� ������
    class Node {
    public:
        EdgeT* edge; //���� �����
        int v2;      //������ �������, ������� ����� ���������
    };

    vector<list<Node>> edgeList; //������ ���������
    bool directed;
public:

    GraphListForm(bool directed) : directed(directed) {}
    //������� � �������� ������ � ����
    bool insertVertex(int index) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (index < 0 || index > size) return false;

        //������ ����� ������ ���������
        list<Node> newList;

        //���������
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;

        //��������� �����������
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)
                    ++((*j).v2);

        return true;
    }
    bool deleteVertex(int index) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (index < 0 || index >= size) return false;


        //������� ������ ���������
        edgeList.erase(edgeList.begin() + index);
        --size;

        //��������� �����������
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 > index)
                    --((*j).v2);
        return true;
    }
    bool insertEdge(int v1, int v2, EdgeT* t) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ��� ����� ��� ����
        if (v1 == v2 || hasEdge(v1, v2)) return false;

        //��������� �����
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);

        return true;
    }
    bool deleteEdge(int v1, int v2) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //����� ���
        if (v1 == v2 || hasEdge(v1, v2) == false) return false;

        //������� �����
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }
    //������� �������� � ��������� �� ������� ����
    int deleteEdgesFromVertex(int index, bool directed)
    {
        int size = edgeList.size(); //����� ������
        int deleted = 0;

        //�������� ����� �������
        if (index < 0 || index >= size) return 0;

        //������� ��������� � �������� ����
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
            {
                if ((*j).v2 == index)
                {
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    //������� ������������ �����
                    if (directed == false)
                        for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if ((*k).v2 == i)
                            {
                                edgeList[index].erase(k);
                                break;
                            }
                    break;
                }

            }


        if (directed == true)
        {
            for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
            {
                delete (*k).edge;
                deleted++;
            }
            edgeList[index].clear();
        }


        return deleted;
    }


    //�������� � ���������
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //�����
        if (v1 == v2) return false;

        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }
    EdgeT* getEdge(int v1, int v2) {
        int size = edgeList.size(); //����� ������

        //�������� ����� �������
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) throw 1;
        //�����
        if (v1 == v2) throw 1;

        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw 1;
    }


    //�������� ����
    class EdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        EdgeIterator(GraphListForm* f) {
            this->f = f;
            begin();
        }
        bool begin() {
            for (curI = 0; curI < f->edgeList.size(); ++curI)
                for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                    if ((*curJ).edge) {
                        end = false;
                        return 1;
                    }
            end = true;
            return 0;
        }
        bool onEnd() { return end; }
        bool next() {
            if (end)
                return 0;
            ++curJ;
            while (curI < f->edgeList.size()) {
                while (curJ != f->edgeList[curI].end()) {
                    if ((*curJ).edge &&
                        (f->directed || !f->directed && (*curJ).v2 > curI))
                        return 1;
                    ++curJ;
                }
                ++curI;
                if (curI < f->edgeList.size())
                    curJ = f->edgeList[curI].begin();
            }
            end = true;
            return false;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return (*curJ).edge;
        }
    };

    //�������� ��������� ����
    class OutputEdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        OutputEdgeIterator(GraphListForm* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }
        bool begin() {
            for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge) {
                    end = false;
                    return 1;
                }
            end = true;
            return 0;
        }
        bool onEnd() { return end; }
        bool next() {
            if (end)
                return 0;
            ++curJ;
            while (curJ != f->edgeList[curI].end()) {
                if ((*curJ).edge)
                    return 1;
                ++curJ;
            }
            end = true;
            return false;
        }
        EdgeT* getEdge() {
            if (end)
                throw 1;
            return (*curJ).edge;
        }
    };
};

#endif // GRAPH_FORMS_H
