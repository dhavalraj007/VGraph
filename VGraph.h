#pragma once
#include<string>
#include<vector>
#include<fstream>
#define Vnreturn vg.end(); return
#define Vreturn(x) auto __Vval = x;vg.end();return __Vval

namespace VgHelpers
{
	template<typename T>
	std::string vec2str(const std::vector<T>& vec)
	{
		std::string ret;
		for (auto e : vec)
		{
			ret += std::to_string(e) + " ";
		}
		return ret;
	}

	template<typename T>
	std::string grid2str(const std::vector<std::vector<T>>& grid)
	{
		std::string ret;
		for (auto row : grid)
		{
			for (auto ele : row)
			{
				ret += to_string(ele) + " ";
			}
			ret += "\n";
		}
		return ret;
	}
}

class VGraph
{
	std::string dfilename;
	std::string outfmt;
	std::fstream file;
	std::vector<std::string> dataVec;//holds ids
	int nArgs = 0;
	int nArgsProvided = 0;
	std::string tempLabel = "";
	int nNodes = 0;
public:
	inline void setArgs(int _nArgs) { nArgs = _nArgs; }
	//Open the file,(initialize fstream)
	VGraph(const std::string& dfilename);
	//set output format
	inline void setFormat(const std::string& fmt) { outfmt = fmt; }
	//creates id for new data
	//set parent of this data as the last element from vector **then** add data's id to vector at back
	void add(const std::string& title, const std::string& data);
	template<typename T, class ftype>
	void add(const std::string& title, const T& data, ftype func);
	//strand ended thus remove last element from vector
	void end();
	//end the dot file with '}'
	void finish();
	//end the dot file with '}' and launch it
	void fLaunch();
};

//func should convert data to string
template<typename T, class ftype>
inline void VGraph::add(const std::string& title, const T& data, ftype func)
{
	if (nArgsProvided == 0)
	{
		tempLabel = title + " : " + func(data);
	}
	else
	{
		tempLabel += " ,\n" + title + " : " + func(data);
	}
	nArgsProvided++;

	if (nArgs == nArgsProvided)	//if provided all arguments then add node to dot file and then push back id to vec
	{
		nNodes++;
		std::string id = std::to_string(nNodes);	//new pseudo random ID for new node;
		std::string idnLabel = id + " [label =\"" + tempLabel + "\"]";
		file << idnLabel << ';';	// new node declaration (associating label with id)
		file << dataVec.back() << " -> " << id << ";\n";
		dataVec.push_back(id);
		nArgsProvided = 0;	//reset for new node
	}
}




