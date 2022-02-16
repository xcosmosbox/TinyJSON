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
	return nullptr;
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
