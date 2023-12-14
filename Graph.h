#ifndef PROJECT2_SIMPLIFIEDPAGERANKS_GRAPH_H
#define PROJECT2_SIMPLIFIEDPAGERANKS_GRAPH_H
#include <map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class Graph{
private:
    std::map<std::string, std::vector<std::string>> adjList; //stores the webpages and the pages they point to
    std::map<std::string, float> rankContainer; //store webpages and thier ranks
    std::map<std::string, int> outdegrees;
    std::map<std::string, std::vector<std::string>> tempMap;

public:
    void InsertEdge(std::string from, std::string to);
    std::vector<int> GetAdjacent(int vertex);
    void PrintGraph();
    void PrintPageRank();
    void CalcPageRank(int iterations);
    void CalcOutdegree(map<std::string, int> outdegrees);
};

///citation: graphs slides
void Graph::InsertEdge(std::string from, std::string to) { //if to and from are not present add vertex otherwise add edge at end of list
    adjList[from].push_back(to);
    if(adjList.find(to) == adjList.end()){
        adjList[to] = {};
    }
}

void Graph::PrintGraph() {
    for(auto iter = adjList.begin(); iter !=adjList.end(); ++iter){
        std::cout << iter->first << " ->";
        for(int j = 0; j < iter->second.size(); j++)
            std::cout << " " << iter->second[j] <<  " |";
        std::cout<<"\n";
    }

    for(auto iter = outdegrees.begin(); iter!=outdegrees.end(); iter++){
        cout << "outDegrees" << " " <<  iter->first << " " << iter->second<< endl;
    }

}

void Graph::CalcPageRank(int iterations) {
    float initRank = 0;
    for(auto iter = adjList.begin(); iter != adjList.end(); iter++){ // initializing outdegree vector
        outdegrees[iter->first] = iter->second.size();
    }

    for(auto iter = outdegrees.begin(); iter != outdegrees.end(); iter++){ //initialize rank based on outdegrees
        initRank = 1.0/adjList.size();
        rankContainer.emplace(iter->first,initRank);
    }

    if(iterations > 1){
       auto tempMap = rankContainer;
       auto tempRankMap = rankContainer;
        for(int i = 0; i<iterations-1; i++){// each iteration
            float tempRank = 0;
            string tempname = "";
            for(auto it = rankContainer.begin(); it != rankContainer.end(); it++){
                tempRank = 0;
                float tempRank2 = 0;
                for(auto adjIter = adjList.begin(); adjIter != adjList.end(); adjIter++){
                    for(int i = 0; i < adjIter->second.size(); i++){
                        if(adjIter->second.at(i) == it->first){
                            tempRank2 += rankContainer[adjIter->first]/adjIter->second.size();//the rank of the website
                        }
                    }
                }
                tempRankMap[it->first] = tempRank2;
            }
            rankContainer = tempRankMap;
        }
    }
    return;
}

void Graph::PrintPageRank(){
    for(auto it = adjList.begin(); it != adjList.end(); ++it){
        std::cout << it->first << " " << std::setprecision(2) <<std::fixed<< rankContainer[it->first] << std::endl;
    }

}
#endif //PROJECT2_SIMPLIFIEDPAGERANKS_GRAPH_H