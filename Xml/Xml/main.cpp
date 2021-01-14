#include <iostream>

using namespace std;

#include <xml/tinyxml2/tinyxml2.h>
#include <xml/XmlNode.hpp>
#include <xml/XmlFile.hpp>

using namespace tinyxml2;

void test()
{
	XmlFile testXmlFile;
	testXmlFile.loadFile("E:\\project\\c++\\github\\myProject\\Xml\\Xml\\x64\\Debug\\testXml.xml");

	deque<XmlNode> userNodeList = testXmlFile.rootNode().getChildNodeList("User");
	
	for (auto& userNode : userNodeList)
	{
		cout << "value = " << userNode.getKeyValue("name1") << endl;
	}
	
}

int main()
{
	test();

	int a;
	cin >> a;
	return 0;
}