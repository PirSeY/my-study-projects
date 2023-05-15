#ifndef GRAPH_H
#define GRAPH_H

/**
 *Класс простого графа, параметрами являются
 *тип вершины и тип ребра графа
 */

#include "graph_forms.h"
#include <time.h>
#include <vector>
#include <set>
#include <map>
using namespace std;

template <class VertexT, class EdgeT>
class Graph {

    //friend class VertexIterator;
    //friend class EdgeIterator;
    vector<VertexT*> vertexVector;//Вектор вставленных
    GraphForm<EdgeT>* data;       //Данные графа
    bool directed;                //Направленный граф
    bool dense;                   //М-граф
    int edgeCounter;              //Число рёбер





    //обновление индексов вершин
    void refreshIndex(int startIndex)
    {
        if (startIndex < 0 || startIndex >= vertexVector.size())
            return;

        for (int i = startIndex;i < vertexVector.size();i++)
            vertexVector[i]->index = i;
    }


    //Получение индекса вершины по дескриптору
    int getIndex(VertexT* v) {
        int index = 0;
        for (int i = 0; i < vertexVector.size(); ++i) {
            if (vertexVector[index] == v)
                break;
            ++index;
        }
        if (index == vertexVector.size())
            throw 1;
        return index;
    }
public:




    //Конструкторы:
    //Пустой L граф
    Graph() {
        data = new GraphListForm(false);
        directed = false;
        dense = false;
        edgeCounter = 0;
    }
    //Заданы кол-во вершин, направленность, форма
    Graph(int vertexCount, bool directed, bool dense) {
        if (dense)
            data = new GraphMatrixForm<EdgeT>(directed);
        else
            data = new GraphListForm<EdgeT>(directed);


        for (int i = 0; i < vertexCount; ++i) {
            VertexT* v = new VertexT();
            vertexVector.push_back(v);
            data->insertVertex(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;

        refreshIndex(0);
    }
    //+ задано кол-во случайных рёбер
    Graph(int vertexCount, int edgeCount, bool directed, bool dense) {
        if (dense)
            data = new GraphMatrixForm<EdgeT>(directed);
        else
            data = new GraphListForm<EdgeT>(directed);


        for (int i = 0; i < vertexCount; ++i) {
            VertexT* v = new VertexT();
            vertexVector.push_back(v);
            data->insertVertex(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;

        //Вставляем рёбра
        if (edgeCount <= 0) return;
        //Корректируем число рёбер, чтобы не превышало максимумы
        if (directed) {
            if (edgeCount > vertexCount * (vertexCount - 1))
                edgeCount = vertexCount * (vertexCount - 1);

        }
        else {
            if (edgeCount > (vertexCount * (vertexCount - 1)) / 2)
                edgeCount = (vertexCount * (vertexCount - 1)) / 2;
        }
        //Вставляем
        int v1, v2;

        refreshIndex(0);

        srand(time(0));
        while (edgeCounter < edgeCount) {
            v1 = rand() % vertexCount;
            v2 = rand() % vertexCount;
            if (v1 == v2)
                continue;
            if (data->hasEdge(v1, v2))
                continue;

            EdgeT* t = new EdgeT(vertexVector[v1], vertexVector[v2]);
            data->insertEdge(v1, v2, t);
            if (directed == false)
                data->insertEdge(v2, v1, t);
            ++edgeCounter;
        }
    }
    Graph(const Graph<VertexT, EdgeT>& G) {
        delete data;
        if (G.isDense())
            data = new GraphMatrixForm<EdgeT>(*(G.data));
        else
            data = new GraphListForm<EdgeT>(*(G.data));
        directed = G.directed;
        dense = G.dense;
    }
    ~Graph() {
        delete data;
    }


    //Информация о графе
    //Число вершин, рёбер, насыщенность
    int getVertexCount() { return vertexVector.size(); }
    int getEdgeCount() { return edgeCounter; }
    double getRatio() {
        int max = vertexVector.size() * (vertexVector.size() - 1);
        if (!directed)
            max /= 2;
        return (double)edgeCounter / (double)max;
    }
    //Тип графа
    bool isDirected() { return directed; }
    bool isDense() { return dense; }
    //Преобразования
    void toDenseGraph() {
        //Создаём структуру хранения М-графа
        GraphForm<EdgeT>* newData = new GraphMatrixForm<EdgeT>(directed);

        //Создаём вершины
        for (int i = 0; i < vertexVector.size(); ++i)
            newData->insertVertex(i);

        //Переносим рёбра
        for (int i = 0; i < vertexVector.size(); ++i)
            for (int j = 0; j < vertexVector.size(); ++j)
                if (data->hasEdge(i, j))
                    newData->insertEdge(i, j, data->getEdge(i, j));
        delete data;
        data = newData;
        dense = true;
    }
    void toSparseGraph() {
        //Создаём структуру хранения L-графа
        GraphForm<EdgeT>* newData = new GraphListForm<EdgeT>(directed);

        //Создаём вершины
        for (int i = 0; i < vertexVector.size(); ++i)
            newData->insertVertex(i);

        //Переносим рёбра
        for (int i = 0; i < vertexVector.size(); ++i)
            for (int j = 0; j < vertexVector.size(); ++j)
                if (data->hasEdge(i, j))
                    newData->insertEdge(i, j, data->getEdge(i, j));
        delete data;
        data = newData;
        dense = false;
    }


    //Данные
    //Вершины
    VertexT* insertVertex() {
        VertexT* v = new VertexT;
        if (data->insertVertex(vertexVector.size()) == false)
            throw 1;
        vertexVector.push_back(v);
        refreshIndex(vertexVector.size() - 1);
        return v;
    }
    VertexT* insertVertex(int index) {
        VertexT* v = new VertexT;
        if (data->insertVertex(index) == false)
            throw 1;
        vertexVector.insert(vertexVector.begin() + index, v);
        refreshIndex(index);
        return v;
    }
    bool deleteVertex(VertexT* v) {
        int index = getIndex(v);
        edgeCounter -= data->deleteEdgesFromVertex(index, directed);
        if (data->deleteVertex(index)) {
            vertexVector.erase(vertexVector.begin() + index);
            refreshIndex(index);
            return true;
        }
        return false;
    }
    bool deleteVertex(int index) {
        if (index < 0 || index >= vertexVector.size())
            return false;
        edgeCounter -= data->deleteEdgesFromVertex(index, directed);
        if (data->deleteVertex(index)) {
            vertexVector.erase(vertexVector.begin() + index);
            refreshIndex(index);
            return true;
        }
        return false;
    }
    VertexT* getVertex(int index) {
        if (index < 0 || index >= vertexVector.size())
            throw 1;
        return vertexVector[index];
    }

    //Рёбра
    EdgeT* insertEdge(VertexT* v1, VertexT* v2)
    {
        EdgeT* e = new EdgeT(v1, v2);
        bool success = data->insertEdge(getIndex(v1), getIndex(v2), e);
        if (directed == false)
            data->insertEdge(getIndex(v2), getIndex(v1), e);
        if (success == true)
        {
            ++edgeCounter;
            return e;
        }
        else
        {
            delete e;
            throw 1;
        }

    }

    EdgeT* insertEdge(int index1, int index2)
    {

        if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
            throw 1;

        EdgeT* e = new EdgeT(vertexVector[index1], vertexVector[index2]);
        bool success = data->insertEdge(index1, index2, e);
        if (directed == false)
            data->insertEdge(index2, index1, e);
        if (success == true)
        {
            ++edgeCounter;
            return e;
        }
        else
        {
            delete e;
            throw 1;
        }

    }


    bool deleteEdge(VertexT* v1, VertexT* v2) {
        if (data->deleteEdge(getIndex(v1), getIndex(v2))) {
            --edgeCounter;
            if (directed == false)
                data->deleteEdge(getIndex(v2), getIndex(v1));
            return true;
        }
        else
            return false;
    }

    bool deleteEdge(int index1, int index2) {
        if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
            return false;
        if (data->deleteEdge(index1, index2)) {
            --edgeCounter;
            if (directed == false)
                data->deleteEdge(index2, index1);
            return true;
        }
        else
            return false;
    }


    bool hasEdge(VertexT* v1, VertexT* v2) {
        int ind1, ind2;
        try { ind1 = getIndex(v1); }
        catch (int& a) { return false; }
        try { ind2 = getIndex(v2); }
        catch (int& a) { return false; }
        return data->hasEdge(getIndex(v1), getIndex(v2));
    }
    bool hasEdge(int v1, int v2) {
        if (v1 < 0 || v1 >= vertexVector.size()) return false;
        if (v2 < 0 || v2 >= vertexVector.size()) return false;
        return data->hasEdge(v1, v2);
    }
    EdgeT* getEdge(VertexT* v1, VertexT* v2) {
        return data->getEdge(getIndex(v1), getIndex(v2));
    }
    EdgeT* getEdge(int v1, int v2) {
        return data->getEdge(v1, v2);
    }



    //Вложенные классы
    //Итератор вершин
    class VertexIterator {
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        bool end;

        int current;
    public:
        VertexIterator(Graph<VertexT, EdgeT>& g) {
            graph = &g;
            begin();
        }
        //Установка в начало
        bool begin() {
            if (graph->vertexVector.size() == 0) {
                end = true;
                return false;
            }
            current = 0;
            end = false;
            return true;
        }
        //Сдвиг на следующий элемент
        bool operator++() {
            if (end)
                return false;
            ++current;
            if (graph->vertexVector.size() == current)
            {
                end = true;
                return false;
            }

            return true;
        }
        //Проверка на выход
        bool onEnd() {
            return end;
        }
        //Получение вершины
        VertexT* operator*() {
            if (current >= graph->vertexVector.size())
                throw 1;
            return graph->vertexVector[current];
        }
    };

    //Итератор рёбер
    class EdgeIterator {
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<EdgeT>::EdgeIterator* mIt;
        typename GraphListForm<EdgeT>::EdgeIterator* lIt;
        bool end;
        bool useM;

        int curV1, curV2;
    public:
        EdgeIterator(Graph<VertexT, EdgeT>& g) {
            graph = &g;
            if (graph->isDense()) {
                mIt = new typename GraphMatrixForm<EdgeT>::EdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data));
                useM = true;
            }
            else {
                lIt = new typename GraphListForm<EdgeT>::EdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data));
                useM = false;
            }
            begin();
        }
        //Установка в начало
        bool begin() {
            if (useM)
                return mIt->begin();
            else
                return lIt->begin();
        }
        //Сдвиг на следующий элемент
        bool operator++() {
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }
        //Проверка на выход
        bool onEnd() {
            //return end;
            if (useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }
        //Получение ребра
        EdgeT* operator*() {
            if (useM)
                return mIt->getEdge();
            else
                return lIt->getEdge();
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<EdgeT>::OutputEdgeIterator* mIt;
        typename GraphListForm<EdgeT>::OutputEdgeIterator* lIt;
        bool end;
        bool useM;

        int curV1;
    public:
        OutputEdgeIterator(Graph<VertexT, EdgeT>& g, VertexT& v) {
            graph = &g;
            curV1 = graph->getIndex(&v);
            if (graph->isDense()) {
                mIt = new typename GraphMatrixForm<EdgeT>::OutputEdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data), curV1);
                useM = true;
            }
            else {
                lIt = new typename GraphListForm<EdgeT>::OutputEdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data), curV1);
                useM = false;
            }
            begin();
        }
        //Установка в начало
        bool begin() {
            if (useM)
                return mIt->begin();
            else
                return lIt->begin();
        }
        //Сдвиг на следующий элемент
        bool operator++() {
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }
        //Проверка на выход
        bool onEnd() {
            //return end;
            if (useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }
        //Получение ребра
        EdgeT* operator*() {
            if (useM)
                return mIt->getEdge();
            else
                return lIt->getEdge();
        }
    };
};

#endif // GRAPH_H
