#ifndef _JSON_H_
#define _JSON_H_

#include<string>
#include<vector>

using namespace std;
/*
 *	Two functions:
 *	1.syntax parse
 *	2.CRUD to node
 *	
 *	Using the data structure of double linked list
 */

enum class JsonValueType
{
	VALUE_TYPE_NULL,
	VALUE_TYPE_BOOL,
	VALUE_TYPE_INT,
	VALUE_TYPE_DOUBLE,
	VALUE_TYPE_STRING,
	VALUE_TYPE_ARRAY,
	VALUE_TYPE_OBJECT
};

class Node
{
private:
	Node* _next = nullptr;
	Node* _prev = nullptr;
	Node* _child = nullptr;

	JsonValueType _type = JsonValueType::VALUE_TYPE_NULL;

	string value_string;
	int value_int;
	double value_double;
	bool value_bool;

	string node_name;

public:
	Node();
	~Node();

public:
	
};




class JSON
{
private:


public:
	JSON();
	~JSON();

	/*
	* Function: Parse the JSON dataand fill it into the JSON tree
	*
	* Parameter: Pointing the unparsed of JSON data
	*
	* Return value: A node of JSON tree
	*/
	Node* Parse(const string& value);

	/*
	* Function: Start recursive traversal from the item node and convert the node tree into a string
	*
	* Parameter: JSON node
	*
	* Return value: String (Tree string parsed from item node)
	*/
	Node* Print(Node* item);

	/*
	* Function: Recursively release the nodes of the JSON tree from the root node to free memory
	*
	* Parameter: JSON node
	*
	* Return value: void
	*/
	void Recycle_Node(Node* child);

public:
	/*
	* Function: Create a node and set the node type to object
	*
	* Parameter: null
	*
	* Return value: JsonValueType::VALUE_TYPE_OBJECT
	*/
	Node* Create_Object();




};

JSON::JSON()
{
}

JSON::~JSON()
{
}




#endif // !_JSON_H_

