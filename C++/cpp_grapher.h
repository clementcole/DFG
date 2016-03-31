#ifndef CPP_GRAPHER_H
#define CPP_GRAPHER_H

#include <string>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "cpp_grapher.h"
#include <boost/algorithm/string.hpp>
//#include <boost/lambda/lambda.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/phoenix.hpp>
//#include <boost/spirit/include/qi_string.hpp>
//#include <boost/spirit/include/qi_stream.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/filesystem/fstream.hpp>
//#include <boost/container/flat_set.hpp>

using namespace std;
using namespace boost::algorithm;
//using boost::lexical_cast;
//using boost::bad_lexical_cast;
//namespace fs = boost::filesystem;

//http://stanford.edu/~stepp/cppdoc/BasicGraph-class.html#Method:addEdge


typedef struct{
    string key;
    int val;
}symstr;

template <typename T>
struct matrix{
    int col, row;
    std::vector<std::vector<T> > data;
    matrix(int columns, int rows):
        col(columns), 
        row(rows), 
        data(col, row)
        {}

    //Usage mattrix m(4, 4)
    //m.data
};

typedef struct{
   const string nodes[7];
}node_matrix;



vector<string> &split(const string &s, char delim, vector<string> &elems ){
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)){
        elems.push_back(item);
    }
    return elems;

}

vector<string> split2(const string &s, char delim){
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


int brute_regex(string text, string pattern){
    int m, n;
    m = text.size();
    n = pattern.size();
    
    for ( unsigned i = 0; i < m; i++){
        int j = 0;
        while((j < m) && (text[i+j] == pattern[j]) ){
            j++;
        }
        if (j == n){
            
            return 1;
        }
    
    }
    return 0;
}


//Second function called from main
void second_main(){
    //Declarations of variables
        ifstream tracefile("Shashank25_output");
        ofstream test_file("testfile.txt");
        ofstream intermediate("intermediate_file");
        ofstream micros("micros");
        string trace_file;
        string bufferstream;
        vector<string> unsanitized;
        char delim = ':';
        string line;
        vector<string> absolute_address;
        vector<string> relative_address;
        vector<string> macro;
        vector<string> micro;
        vector<string> dest;
        vector<string> source1;
        vector<string> source2;
        vector<string> micro_inst;
        vector<string> modified_micros;
        int line_number = 0; 
        while (getline(tracefile, line)){
            if(brute_regex(line, "0x")){
                vector<string> temp;
                string word;
                stringstream ss(line);
                ostringstream stringify;
                stringify << line_number;
                string line_s = stringify.str();
                unsanitized.push_back(line_s); 
                while(getline(ss, word, ':')){ 
                    //word.erase(remove_if(word.begin(), word.end(), ::isspace ), word.end());
                    //unsanitized.push_back(line_s); 
                    unsanitized.push_back(word);
                }
                line_number++;
                unsanitized.push_back(" \n");
            }
        }

        for (int i = 0; i < unsanitized.size(); i++){
            //for (unsigned j = 0; j < 3; j++){
                //unsanitized.at(i).erase(remove_if(unsanitized.at(i).begin(), unsanitized.at(i).end(), ::isspace ), unsanitized.at(i).end());
               if (unsanitized.at(i) == " \n"){ //This is where I need to sanitize the microinstructions.
                    micro_inst.push_back(unsanitized.at(i-1));
               }
               intermediate <<"   "<< unsanitized.at(i);
        }
        
        int m = 0;
        for (int i = 0; i < micro_inst.size(); i++){
            stringstream ss(micro_inst.at(i));
            string word;
            int x = 0;
            while(getline(ss, word, ' ')){
                word.erase(remove_if(word.begin(), word.end(), ::isspace ), word.end() );
                word.erase(remove(word.begin(), word.end(), ','), word.end());
                trim(word);
                modified_micros.push_back(word);
                ++x;
            }
            if(x < 3){
                modified_micros.push_back("0");
                //modified_micros.push_back(" \n");
            }
            
            modified_micros.push_back("\n");
        }
        
        for (vector<string>::iterator it = modified_micros.begin(); it< modified_micros.end(); it++){
            if(it->find(" ") ==  0){
                modified_micros.erase(it);
            }
           
        }

         for (int i = 0; i < modified_micros.size(); i++)
            micros << "  "<<"{"<<modified_micros.at(i)<<"}";

        micros.close();
        intermediate.close();
        test_file.close();
        tracefile.close();
    
}
void third_main(){
    ifstream tracefile("intermediate_file");
    ofstream testingList("listTest");
    //ifstream micros("micros");
    vector<string> absoluteList;
    vector<string> relativeList;
    vector<string> macroList;
    vector<string> microList;
    vector<string> destList;
    vector<string> source1List;
    vector<string> source2List;
    vector<string> tagList;
    string line;
    string node_tag, a, r, M, m;
    //while(getline(tracefile, line)){
        while(tracefile >> node_tag >> a >> r >> M >> m){
            tagList.push_back(node_tag);
            absoluteList.push_back(a);
            relativeList.push_back(r);
            macroList.push_back(M);
            microList.push_back(m);


        }
    //}
    //Testing
    for (unsigned i =0; i< absoluteList.size(); i++){
         testingList << tagList.at(i)<<"  "<<absoluteList.at(i)<<"  "<<relativeList.at(i)<<"  "<<macroList.at(i)<< "  "<<microList.at(i)<<"\n";
    }


tracefile.close();
testingList.close();

}


class Vertex;
class Edge{
public:
  Edge(Vertex *org, Vertex *dest, int dist){// double address_org, double address_dest){
    origin = org;
    destination = dest;
    distance = dist;
    //org_address  = address_org;
    //dest_address = address_dest;
    //dist = distance;
  }
  Vertex* getOrigin() {return origin;}
  Vertex* getDestination() {return destination;}
  int getDistance(){return distance;} //Destination absolute address - origin absolute address.
private:
  Vertex* origin;
  Vertex* destination;
  int  distance;
};//end of class reg_edge

class Vertex{
public:
  Vertex(string id){
    node_name = id;
  }
  void addEdge(Vertex *v, int dist){
    Edge newEdge(this, v, dist); //Giving me problems because of function prototype of edges not completely defined.
    edges.push_back(newEdge);
  }
  void printEdges(){
    cout << node_name << ":" << endl;
    for (int i = 0; i < edges.size(); i++){
      Edge e = edges[i];
      cout << e.getDestination()->getName() << " - " << e.getDistance() << endl;
    }
    cout << endl;
  }
  string getName() {return node_name;}
  vector<Edge> getEdges() {return edges;}

private:
  string node_name;
  vector<Edge> edges;
};//End of class op_node

class Graph{
public:
  Graph() {}
  void insert(Vertex *v){
    vertices.push_back(v);
  }
  void printGraph(){
    for (int i =0; i< vertices.size(); i++)
      vertices[i]->printEdges();
  }
private:
  vector<Vertex*> vertices;
}; //End of Graph{} class

void build_graph(){

}

void create_labels(){

}
void block_matrix(){

}
//git remote add origin https://github.com/clementcole/DFG.git
//git push -u origin master

#endif