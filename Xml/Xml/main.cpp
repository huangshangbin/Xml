#include <iostream>

using namespace std;

#include <xml/tinyxml2/tinyxml2.h>
#include <xml/XmlNode.hpp>
#include <xml/XmlFile.hpp>

using namespace tinyxml2;

void test()
{
	XmlFile testXmlFile;
	testXmlFile.loadFile("config.xml");

	deque<XmlNode> mainUserNodeList = testXmlFile.rootNode().getChildNodeList("MainUser");

	if (mainUserNodeList.size() <= 0)
	{
		cout << "size <= 0" << endl;
	}
	else
	{
		cout << mainUserNodeList[0].getKeyValue("login") << endl;
	}
}

int main()
{
	test();

	int a;
	cin >> a;
	return 0;
}