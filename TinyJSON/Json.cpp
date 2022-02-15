#include"Json.h"

Node::Node()
{
}

Node::~Node()
{
}





//------------------------

JSON::JSON()
{
}

JSON::~JSON()
{
}

Node* JSON::Parse(const string& value)
{
	return nullptr;
}

string JSON::Print(Node* item)
{
	return string();
}

void JSON::Recycle_Node(Node* child)
{
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
