#include <iostream>

using namespace std;

#include <xml/tinyxml2/tinyxml2.h>
#include <xml/XmlNode.hpp>

using namespace tinyxml2;

void test()
{
	XMLDocument doc;
	doc.LoadFile("testXml.xml");

	XMLElement* element = doc.NewElement("User");
	XmlNode xmlNode(element);
	xmlNode.setKeyValue("name", "huang");
	xmlNode.setContent("test");

	XMLElement* rootElement = doc.RootElement();
	XmlNode rootNode(rootElement);

	rootNode.insertNode(xmlNode);


	doc.SaveFile("testXml.xml");
}

int main()
{
	test();

	int a;
	cin >> a;
	return 0;
}