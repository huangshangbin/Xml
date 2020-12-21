#pragma once

#include <xml/tinyxml2/tinyxml2.h>
using namespace tinyxml2;

#include <iostream>
#include <string>

using namespace std;

class XmlNode
{
private:
	XMLElement* m_element;

public:
	XmlNode(XMLElement* element)
	{
		m_element = element;
	}

public:
	XMLElement* getElement()
	{
		return m_element;
	}

public:
	void setContent(string content)
	{
		m_element->SetText(content.c_str());
	}

	void setKeyValue(string key, string value)
	{
		m_element->SetAttribute(key.c_str(), value.c_str());
	}

	void insertNode(XmlNode xmlNode)
	{
		m_element->InsertEndChild(xmlNode.getElement());
	}
};