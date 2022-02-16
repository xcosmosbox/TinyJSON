#ifndef _JSON_H_
#define _JSON_H_

#include<string>
#include<vector>
#include<iostream>

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
	string Print(Node* item);

	/*
	* Function: Recursively release the nodes of the JSON tree from the root node to free memory
	*
	* Parameter: JSON node
	*
	* Return value: void
	*/
	void Recycle_Node(Node* child);

private:
	//Increasing a node
	Node* New_Node();

	/*
	* return_parse_end: last return position
	* require_null_terminate: if there is a error in parsing, do you want to exit.
	*/
	Node* Parse_Opts(string& value, string& return_parse_end, bool require_null_terminate);

	/*
	* Finding start position
	*/
	string Skip(string value);

public:
	/*
	* Function: Create a node and set the node type to object
	*
	* Parameter: null
	*
	* Return value: JsonValueType::VALUE_TYPE_OBJECT
	*/
	Node* Create_Object();

	/*
	* Function: Create a node and set the node type to string
	*
	* Parameter: string
	*
	* Return value: JsonValueType::VALUE_TYPE_STRING
	*/
	Node* Create_String(string& str);

	/*
	* Function: Create a node and set the node type to number
	*
	* Parameter: double
	*
	* Return value: JsonValueType::VALUE_TYPE_DOUBLE
	*/
	Node* Create_Number(double num);

	/*
	* Function: Create a node and set the node type to array
	*
	* Parameter: null
	*
	* Return value: JsonValueType::VALUE_TYPE_ARRAY
	*/
	Node* Create_Array();

	/*
	* Function: Create a node and set the node type to bool
	*
	* Parameter: bool
	*
	* Return value: JsonValueType::VALUE_TYPE_BOOL
	*/
	Node* Create_Bool(bool boolean);

	/*
	* Function: Create a node and set the node type to null
	*
	* Parameter: null
	*
	* Return value: JsonValueType::VALUE_TYPE_NULL
	*/
	Node* Create_Null();

public:
	/*
	* Function: Set the name of the item node to item_ name
	*			If the object node has no child nodes, set item as the child node of the object node
	*			Otherwise, add the item to the tail of the object -> child linked list 
	*			and become the sibling node of the object child node
	* 
	* Parameter: 
	*			obj: added node
	*			item: node to add
	*
	* Return value: JSON&
	*/
	JSON& Add_Item_To_Obj(Node* obj, string item_name, Node* item);

	/*
	* Function: If the array node has no child nodes, set item as the child node of the array node
	*			Otherwise, add the item to the tail of the array -> child linked list 
	*			and become the sibling node of the array child node
	* 
	* Parameter: 
	*			obj: added node
	*			item: node to add
	*
	* Return value: JSON&
	*/
	JSON& Add_Item_To_Array(Node* array, Node* item);






};






#endif // !_JSON_H_

