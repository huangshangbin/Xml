#include <iostream>

using namespace std;

#include <xml/tinyxml2/tinyxml2.h>
#include <xml/XmlNode.hpp>
#include <xml/XmlFile.hpp>

using namespace tinyxml2;

void test()
{
	XmlFile testXmlFile;
	testXmlFile.loadFile("testXml.xml");

	testXmlFile.setNodePath("Root\\User");

	XmlNode node = testXmlFile.getNode([](XmlNode& node) {
		if (node.getKeyValue("age") == "25")
		{
			return true;
		}
		else
		{
			return false;
		}
	});

	testXmlFile.rootNode().deleteChildNode(node);

	testXmlFile.saveFile();
}

int main()
{
	test();

	int a;
	cin >> a;
	return 0;
}