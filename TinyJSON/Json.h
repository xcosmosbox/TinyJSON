#ifndef _JSON_H_
#define _JSON_H_

#include<string>
#include<vector>
#include<iostream>
#include<optional>

using namespace std;
/*
 *	Two functions:
 *	1.syntax parse
 *	2.CRUD to node
 *	
 *	Using the data structure of double linked list
 *	djsoadjioa
 */

enum class NodeValueType
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
	friend class JSON;
private:
	Node* _next = nullptr;
	Node* _prev = nullptr;
	Node* _child = nullptr;

	NodeValueType _type = NodeValueType::VALUE_TYPE_NULL;

	string _value_string;
	int _value_int;
	double _value_double;
	bool _value_bool;

	string _node_name;

public:
	Node();
	~Node();
private:
	void clear();

public:
	size_t size();
	optional<string> name();
	optional<int> as_int();
	optional<double> as_double();
	optional<bool> as_bool();
	optional<string> as_string();

	bool is_array();
	bool is_object();
	bool is_null();

	vector<Node*> set_child();
	
};




class JSON
{
private:
	string _end_position;
	string _create_nodes_used;
	vector<Node*> _create_nodes;
	Node* _root;


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
	Node* Parse(string& value);

	/*getting the error position*/
	string error_position();

private:
	//Increasing a new node
	Node* New_Node();

	/*
	* return_parse_end: last return position
	* require_null_terminate: if there is a error in parsing, do you want to exit.
	*/
	Node* Parse_Opts(string& value, string& return_parse_end, bool require_null_terminate);

	/*
	* Returns the position where processing is complete
	*/
	string Parse_Value(Node* item, string value);
	string Parse_String(Node* item, string value);
	string Parse_Number(Node* item, string value);
	string Parse_Array(Node* item, string value);
	string Parse_Object(Node* item, string value);

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
	Node* Create_String(string&& str);

	/*
	* Function: Create a node and set the node type to number
	*
	* Parameter: double
	*
	* Return value: JsonValueType::VALUE_TYPE_DOUBLE
	*/
	Node* Create_Double(double num);
	Node* Create_Int(int num);

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

	/*
	* Function: Recursively release the nodes of the JSON tree from the root node to free memory
	*
	* Parameter: JSON node
	*
	* Return value: void
	*/
	void Recycle_Node(Node* item);


public:
	/*
	* Function: Start recursive traversal from the item node and convert the node tree into a string
	*
	* Parameter: JSON node
	*
	* Return value: String (Tree string parsed from item node)
	*/
	string Print(Node* item);

private:
	/*Convert structure to string*/
	string Print_Json(Node* obj);
	string Print_Json(Node* obj, int depth);
	string Print_Array(Node* obj, int depth);
	string Print_Object(Node* obj, int depth);

	//Create structure
	void Suffix_Object(Node* prev, Node* item);

};






#endif // !_JSON_H_

