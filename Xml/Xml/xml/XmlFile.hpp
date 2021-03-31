#pragma once

#include <xml/tinyxml2/tinyxml2.h>
using namespace tinyxml2;



#include "XmlNode.hpp"

#include <xml/utils/XmlStringUtils.hpp>

class XmlFile
{
private:
	string m_filePath;
	string m_nodePath;

	tinyxml2::XMLDocument m_document;

public:
	XmlFile() {}
	~XmlFile() { m_document.Clear(); }

public:
	void loadFile(string filePath)
	{
		m_filePath = filePath;

		m_document.Clear();
		m_document.LoadFile(filePath.c_str());
	}

	void setNodePath(string nodePath)
	{
		m_nodePath = nodePath;
	}

public:
	XmlNode createNode(string nodeName)
	{
		return XmlNode(m_document.NewElement(nodeName.c_str()));
	}

	XmlNode rootNode()
	{
		return XmlNode(m_document.RootElement());
	}

public:
	deque<XmlNode> getNodeList()
	{
		deque<XmlNode> xmlNodeList;

		tinyxml2::XMLElement* rootElement = m_document.RootElement();
		if (rootElement == NULL)
		{
			return xmlNodeList;
		}

		deque<string> nodePathList = XmlStringUtils::splitString(m_nodePath, "\\");

		XMLElement* tempElement = nullptr;
		XMLElement* preElement = rootElement;
		XMLElement* needElement;
		if (nodePathList.size() > 2)
		{
			for (int i = 1; i < (nodePathList.size() - 1); i++)
			{
				deque<XmlNode> nodeList = XmlNode(preElement).getChildNodeList(nodePathList[i]);
				if (nodeList.size() == 0)
				{
					return xmlNodeList;
				}

				tempElement = nodeList[0].getElement();
				if (tempElement == NULL)
				{
					return xmlNodeList;
				}

				preElement = tempElement;

			}

			needElement = tempElement;
		}
		else
		{
			needElement = rootElement;
		}

		XmlNode needNode(needElement);
		return needNode.getChildNodeList(nodePathList[nodePathList.size() - 1]);
	}

	deque<XmlNode> getNodeList(std::function<bool(XmlNode& node)> filter)
	{
		deque<XmlNode> xmlNodeList;

		tinyxml2::XMLElement* rootElement = m_document.RootElement();
		if (rootElement == NULL)
		{
			return xmlNodeList;
		}

		deque<string> nodePathList = XmlStringUtils::splitString(m_nodePath, "\\");

		XMLElement* tempElement = nullptr;
		XMLElement* preElement = rootElement;
		XMLElement* needElement;
		if (nodePathList.size() > 2)
		{
			for (int i = 1; i < (nodePathList.size() - 1); i++)
			{
				deque<XmlNode> nodeList = XmlNode(preElement).getChildNodeList(nodePathList[i]);
				if (nodeList.size() == 0)
				{
					return xmlNodeList;
				}

				tempElement = nodeList[0].getElement();
				if (tempElement == NULL)
				{
					return xmlNodeList;
				}

				preElement = tempElement;

			}

			needElement = tempElement;
		}
		else
		{
			needElement = rootElement;
		}

		XmlNode needNode(needElement);
		return needNode.getChildNodeList([&](XmlNode& node) {
			if (filter(node) && (node.getName() == nodePathList[nodePathList.size() - 1]))
			{
				return true;
			}else
			{
				return false;
			}
		});
	}

	XmlNode getNode(std::function<bool(XmlNode& node)> filter)
	{
		XmlNode node(nullptr);

		deque<XmlNode> nodeList = getNodeList(filter);
		if (nodeList.size() < 1)
		{
			return node;
		}
		else
		{
			return nodeList[0];
		}
	}

public:
	void createFile(string filePath, string rootName)
	{
		const char* content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

		tinyxml2::XMLDocument document;
		document.Parse(content);

		XMLElement* root = document.NewElement(rootName.c_str());

		document.InsertEndChild(root);

		document.SaveFile(filePath.c_str());

		document.Clear();
	}

	void saveFile()
	{
		m_document.SaveFile(m_filePath.c_str());
	}

	void saveNewFile(string filePath)
	{
		m_document.SaveFile(m_filePath.c_str());
	}
};