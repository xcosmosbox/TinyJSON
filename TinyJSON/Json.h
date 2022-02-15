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
 *	
 *	analysis the data of JSON into the tree of JSON
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
	/*
	* Function: Parse the JSON dataand fill it into the JSON tree
	* 
	* Parameter: Pointing the unparsed of JSON data
	* 
	* Return value: A node of JSON tree
	*/
	Node* parse(string &value);



};






#endif // !_JSON_H_

