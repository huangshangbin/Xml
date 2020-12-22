#pragma once

#include <xml/tinyxml2/tinyxml2.h>
using namespace tinyxml2;


#include <iostream>
#include <string>
#include <deque>
#include <functional>

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
	void setName(string name)
	{
		m_element->SetName(name.c_str());
	}

	void setContent(string content)
	{
		m_element->SetText(content.c_str());
	}

	void setKeyValue(string key, string value)
	{
		m_element->SetAttribute(key.c_str(), value.c_str());
	}

	string getName()
	{
		return m_element->Name();
	}

	string getContent()
	{
		if (m_element->FirstChild() == nullptr)
		{
			return "";
		}

		return m_element->FirstChild()->Value();
	}

	string getKeyValue(string key)
	{
		char* temp = const_cast<char*> (m_element->Attribute(key.c_str()));

		return temp;
	}


public:
	deque<XmlNode> getChildNodeList(string childNodeName)
	{
		deque<XmlNode> childNodeList;
		if (m_element == NULL)
		{
			return childNodeList;
		}

		XMLElement* xmlChildElement = m_element->FirstChildElement();
		while (xmlChildElement)
		{
			string compareNodeName = xmlChildElement->Name();
			if (childNodeName == compareNodeName)
			{
				XmlNode tempNode(xmlChildElement);
				childNodeList.push_back(tempNode);
			}

			xmlChildElement = xmlChildElement->NextSiblingElement();
		}

		return childNodeList;
	}

	deque<XmlNode> getChildNodeList(std::function<bool(XmlNode& node)> filter)
	{
		deque<XmlNode> childNodeList;
		if (m_element == NULL)
		{
			return childNodeList;
		}

		XMLElement* xmlChildElement = m_element->FirstChildElement();
		while (xmlChildElement)
		{
			XmlNode tempNode(xmlChildElement);
			if (filter(tempNode))
			{
				childNodeList.push_back(tempNode);
			}

			xmlChildElement = xmlChildElement->NextSiblingElement();
		}

		return childNodeList;
	}

	XmlNode getChildNode(std::function<bool(XmlNode& node)> filter)
	{
		XmlNode childNode(nullptr);

		deque<XmlNode> childNodeList = getChildNodeList(filter);
		if (childNodeList.size() < 1)
		{
			return childNode;
		}
		else
		{
			return childNodeList[0];
		}
	}

public:
	void insertChildNode(XmlNode xmlNode)
	{
		m_element->InsertEndChild(xmlNode.getElement());
	}

	void deleteChildNode(XmlNode xmlNode)
	{
		m_element->DeleteChild(xmlNode.getElement());
	}
};