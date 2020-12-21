#pragma once

#include <xml/tinyxml2/tinyxml2.h>
using namespace tinyxml2;

#include <iostream>
#include <string>

using namespace std;


class XmlFile
{
private:
	string m_filePath;
	string m_nodePath;

	XMLDocument m_document;

public:
	XmlFile() {}
	~XmlFile() { m_document.Clear(); }

public:
	void loadFile(string filePath)
	{

	}
};