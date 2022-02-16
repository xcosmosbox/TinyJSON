#include"Json.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::clear()
{
}





//------------------------

JSON::JSON()
{
}

JSON::~JSON()
{
}

Node* JSON::Parse(string& value)
{
	string ret_end;
	Node* _root = Parse_Opts(value, ret_end,false);
	return _root;
}

string JSON::Print(Node* item)
{
	return string();
}

void JSON::Recycle_Node(Node* child)
{
}

Node* JSON::New_Node()
{
	int position = _create_nodes_used.find('0');

	/*
	* static const size_type npos = -1;
	* 
	* This is a special value equal to the maximum value representable by the type size_type. 
	* The exact meaning depends on context, but it is generally used either as end of string 
	* indicator by the functions that expect a string index or as the error indicator by the functions that return a string index
	* 
	* NOTE: Although the definition uses -1, size_type is an unsigned integer type, 
	* and the value of npos is the largest positive value it can hold, 
	* due to signed-to-unsigned implicit conversion. This is a portable way to specify the largest value of any unsigned type
	*/
	if (position != std::string::npos)
	{
		Node* node = _create_nodes[position];
		_create_nodes_used[position] = '1';
		node->clear();
		return node;
	}

	Node node;
	Node* node_ptr = &node;
	_create_nodes_used.push_back('1');
	_create_nodes.push_back(node_ptr);
	return node_ptr;
}

Node* JSON::Parse_Opts(string& value, string& return_parse_end, bool require_null_terminate)
{
	Node* item = New_Node();
	_end_position = {};

	string end = Parse_Value(item, Skip(value));

	return nullptr;
}

string JSON::Parse_Value(Node* item, string value)
{
	if (value.empty())
	{
		return string();
	}
	if (value.substr(0,5) == "false")//
	{
		item->_type = NodeValueType::VALUE_TYPE_BOOL;
		item->_value_bool = false;
		return value.substr(5);//
	}
	if (value.substr(0,4) == "true")
	{
		item->_type = NodeValueType::VALUE_TYPE_BOOL;
		item->_value_bool = true;
		return value.substr(4);
	}
	if (value.substr(0,4) == "null")
	{
		item->_type = NodeValueType::VALUE_TYPE_NULL;
		return value.substr(4);
	}
	if (value.size() < 1)
	{
		return string();
	}

	char front = value[0];
	if (front == '\"')
	{
		return Parse_String(item, value);
	}
	if (front == '-' || (front >= '0' && front <= '9') || front == '+')
	{
		return Parse_Number(item, value);
	}
	if (front == '[')
	{
		return Parse_Array(item, value);
	}
	if (front == '{')
	{
		return Parse_Object(item, value);
	}

	_end_position = value;
	return string();
}

string JSON::Parse_String(Node* item, string value)
{
	if (value[0] != '\"')
	{
		_end_position = value[0];
		return string();
	}

	int size = value.size();
	int length = 0;
	
	if (string position = value.find('\"',1))
	{
		length = position - 1;
	}

	if (length < 1)
	{
		return string();
	}

	string new_string = value.substr(1, length);
	string str(new_string.begin(), new_string.end());
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if(*it == '\"')
		{
			it = str.erase(it);
		}
	}

	item->_type = NodeValueType::VALUE_TYPE_STRING;
	item->_value_string = move(str);
	return value.substr(length + 2);

	return string();
}

string JSON::Parse_Number(Node* item, string value)
{
	return string();
}

string JSON::Parse_Array(Node* item, string value)
{
	return string();
}

string JSON::Parse_Object(Node* item, string value)
{
	return string();
}

string JSON::Skip(string value)
{
	int start_pos = 0;
	while (value.size() > start_pos && value[start_pos] <= 32)
	{
		start_pos++;
	}
	return value.substr(start_pos);
}

Node* JSON::Create_Object()
{
	return nullptr;
}

Node* JSON::Create_String(string& str)
{
	return nullptr;
}

Node* JSON::Create_Number(double num)
{
	return nullptr;
}

Node* JSON::Create_Array()
{
	return nullptr;
}

Node* JSON::Create_Bool(bool boolean)
{
	return nullptr;
}

Node* JSON::Create_Null()
{
	return nullptr;
}

JSON& JSON::Add_Item_To_Obj(Node* obj, string item_name, Node* item)
{
	// TODO: 在此处插入 return 语句
}

JSON& JSON::Add_Item_To_Array(Node* array, Node* item)
{
	// TODO: 在此处插入 return 语句
}
