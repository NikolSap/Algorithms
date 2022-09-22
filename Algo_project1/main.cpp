#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Edge.h"
#include "Kruskal.h"
#include "Algorithms.h"
bool InputValidation1(string& inputStr, Graph& graph);
bool InputValidation2(vector<int>& input, Graph& graph);
void getInput(vector<int>& input,string& str, int len);
void errorMessage(fstream& OutputFile, const char* msg = "invalid input");

int main(int argc, char** argv)
{
	fstream InputFile;
	fstream OutputFile;
	int n, m, i = 0;
	string str;
	Graph graph;
	vector<int> input;
	Edge edgeToRemove;
	vector<Edge> edgeList;
	int edgeListIndex = 0;
	try {
		if (argc < 2)
		{
			cerr << "Error: missing file name argument!" << endl;
			exit(1);
		}
		InputFile.open(argv[1], ios_base::in);
		OutputFile.open(argv[2], ios_base::out);
		if (!InputFile)
		{
			cerr << "Error: file could not be opened" << endl;
			exit(1);
		}

		while (getline(InputFile, str))
		{
			if (i == 0)
			{
				n = stoi(str);
				graph.MakeEmptyGraph(n);
			}
			if (i == 1)
			{
				m = stoi(str);
				edgeList.reserve(m);
				graph.setNumberOfEdges(m);
			}
			else if (i > 1 && i != m + 2)
			{
				if (!InputValidation1(str, graph))
				{
					errorMessage(OutputFile);
				}
				getInput(input, str, str.length());
				if(input.size()==1 && input[0]==-1)
				{
					errorMessage(OutputFile);
				}
				
				if(!InputValidation2(input,graph))
				{
					errorMessage(OutputFile);
				}
				graph.AddEdge(input[0], input[1], input[2]);
				edgeList.push_back(Edge(input[0], input[1], input[2]));
				edgeListIndex++;
			}
			if (i > 1 && i == m + 2)
			{
				getInput(input, str, str.length());
				edgeToRemove.setSrc(input[0]);
				edgeToRemove.setDest(input[1]);
			}
			i++;
		}

		InputFile.close();
		if (edgeListIndex != m || !CheckIfGraphConnected(graph))
		{
			errorMessage(OutputFile);
		}
		else
		{

			vector<Edge> F;
			int* parentTree = nullptr;
			int kruskalRes = kruskal(graph, edgeList,F);
			int primRes = Prim(graph, parentTree);
			std::cout << "Kruskal " << kruskalRes << endl;
			OutputFile<< "Kruskal " << kruskalRes << endl;
			std::cout << "Prim " << primRes << endl;
			OutputFile << "Prim " << primRes << endl;
			kruskalRes= FindNewMSTAfterRemoveEdge(graph, F, edgeToRemove, edgeList);
			std::cout << "Kruskal2 " << kruskalRes << endl;
			OutputFile << "Kruskal2 " << kruskalRes << endl;
			OutputFile.close();
			return 0;
		}
	
	}
	catch (const char* msg)
	{
		if (strcmp(msg, "No MST") == 0)
			errorMessage(OutputFile, "No MST");
		else
			errorMessage(OutputFile);
	}
	
}

void getInput(vector<int>& input, string& str, int len)
{
	int number = 0;
	int i = 0;
	//vector<int> input;
	input.clear();
	while (i < len)
	{
		if(!std::isdigit(str[i]))
		{
			input.clear();
			input.push_back(-1);
		}
		while (str[i] != ' ' && str[i] != '\0')
		{
			number += str[i] - '0';
			number *= 10;
			i++;
		}
		number /= 10;
		input.push_back(number);
		i++;
		number = 0;
	}

}

bool InputValidation1(string& inputStr, Graph& graph)
{
	if (inputStr.length() < 3)
		return false;
	if (!(inputStr.find(".") == string::npos)) // not integer number
		return false;
	return true;
}

bool InputValidation2(vector<int>& input,Graph& graph)
{
	if (input.size() != 3 || input[0] > graph.getNumVertices() || input[1] > graph.getNumVertices())
		return false;
}

void errorMessage(fstream& OutputFile,const char* msg)
{
	cerr << msg << endl;
	OutputFile << msg << endl;
	exit(1);
}