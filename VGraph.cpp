#include "VGraph.h"

namespace VgHelpers {
	std::string umapii2str(const std::unordered_map<int, int>& mp)
	{
		std::string ret("\n");
		for (auto [key, value] : mp)
		{
			ret += std::to_string(key) + " : " + std::to_string(value) + " ,\n";
		}
		return ret;
	}
}

VGraph::VGraph(const std::string& fname)
	:dfilename(fname)
{
	file.open(dfilename, std::ios_base::out);
	file << "digraph g {  ";
	dataVec.push_back("Intital");
}

// this is same as the inline one but with no 3rd parameter.
// remember to edit the other one while making changes.
void VGraph::add(const std::string& title, const std::string& data)
{
	if (nArgsProvided == 0)
	{
		tempLabel = title + " : " + data;
	}
	else
	{
		tempLabel += "\n" + title + " : " + data;
	}
	nArgsProvided++;

	if (nArgs == nArgsProvided)	//if provided all arguments then add node to dot file and then push back id to vec
	{
		nNodes++;
		id = std::to_string(nNodes);	//new pseudo ID for new node;
		std::string idnLabel = id + " [label =\"" + tempLabel + "\"]";
		file << idnLabel << ';';	// new node declaration (associating label with id)
		file << dataVec.back() << " -> " << id << ";\n";
		dataVec.push_back(id);
		nArgsProvided = 0;	//reset for new node
	}
}

void VGraph::end()
{
	dataVec.pop_back();
}

void VGraph::end(const std::string& returnVal)
{
	file << dataVec.back() << " -> " << dataVec[dataVec.size()-2] << " [ label = \""<<returnVal<<"\", style=\"dotted\" ];\n";
	dataVec.pop_back();
}

void VGraph::finish()
{
	file << "}";
}

void VGraph::fLaunch()
{
	file << "}";
	file.flush();
	file.close();
	std::string cmd = "cmd.exe /c dot.exe -Tsvg " + dfilename + " -o output.svg";
	system(cmd.c_str());
	if (outfmt == "")
		outfmt = "svg";
	cmd = "cmd.exe /c output." + outfmt;
	system(cmd.c_str());
}

void VGraph::breakAtID(int _id)
{
	if (std::to_string(_id) == id)
		__debugbreak();
}
