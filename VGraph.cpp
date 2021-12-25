#include "VGraph.h"



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
		std::string id = std::to_string(nNodes);	//new pseudo ID for new node;
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