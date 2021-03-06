#include"Json.h"


//-----------NODE-------------//

Node::Node()
{
}

Node::~Node()
{

}

void Node::clear()
{
	_next = nullptr;
	_prev = nullptr;
	_child = nullptr;
	_type = NodeValueType::VALUE_TYPE_NULL;
	_value_string.clear();
	_node_name.clear();
}

size_t Node::size()
{
	size_t child_size = 0;
	auto child = this->_child;
	while (child)
	{
		child = child->_child;
		child_size++;
	}
	return child_size;
}

optional<string> Node::name()
{
	if (this->_node_name.size())
	{
		return this->_node_name;
	}
	
	return nullopt;
}

optional<int> Node::as_int()
{
	if (this->_type == NodeValueType::VALUE_TYPE_INT)
	{
		return this->_value_int;
	}
		
	return nullopt;
}

optional<double> Node::as_double()
{
	if (this->_type == NodeValueType::VALUE_TYPE_DOUBLE)
	{
		return this->_value_int;
	}
		
	return nullopt;
}

optional<bool> Node::as_bool()
{
	if (this->_type == NodeValueType::VALUE_TYPE_BOOL)
	{
		return this->_value_bool;
	}
		
	return nullopt;
}

optional<string> Node::as_string()
{
	if (this->_type == NodeValueType::VALUE_TYPE_STRING)
	{
		return this->_value_string;
	}
		
	return nullopt;
}

bool Node::is_array()
{
	return this->_type == NodeValueType::VALUE_TYPE_ARRAY;
}

bool Node::is_object()
{
	return this->_type == NodeValueType::VALUE_TYPE_OBJECT;
}

bool Node::is_null()
{
	return this->_type == NodeValueType::VALUE_TYPE_NULL;
}

vector<Node*> Node::set_child()
{
	vector<Node*> ret;
	auto child = this->_child;
	while (child)
	{
		ret.push_back(child);
		child = child->_next;
	}
	return ret;
}





//-----------JSON-------------//

JSON::JSON()
{
	this->_root = nullptr;
}

JSON::~JSON()
{
	for (auto node : this->_create_nodes)
	{
		delete node;
	}
	this->_create_nodes.clear();
	this->_create_nodes_used.clear();
}

Node* JSON::Parse(string& value)
{
	string ret_end;
	_root = Parse_Opts(value, ret_end,false);
	return _root;
}

string JSON::error_position()
{
	return _end_position;
}

void JSON::Recycle_Node(Node* item)
{
	auto it = find_if(_create_nodes.begin(), _create_nodes.end(), [item](auto node)
		{
			return item == node;
		});
	if (it != _create_nodes.end())
	{
		//created node
		Node* next;
		while (item)
		{
			next = item->_next;
			if (item->_child)
			{
				Recycle_Node(item->_child);
			}
			auto position = distance(_create_nodes.begin(), it);//
			item->clear();
			_create_nodes_used[position] = '0';
			item = next;

		}
	}
	else
	{
		delete item;
	}
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

	Node* node_ptr = new Node();
	//Node* node_ptr = &node;
	_create_nodes_used.push_back('1');
	_create_nodes.push_back(node_ptr);
	return node_ptr;
}

Node* JSON::Parse_Opts(string& value, string& return_parse_end, bool require_null_terminate)
{
	Node* item = New_Node();
	_end_position = {};

	auto end = Parse_Value(item, Skip(value));
	if (!end.empty())
	{
		Recycle_Node(item);
		return nullptr;
	}
	if (require_null_terminate)
	{
		end = Skip(end);
		if (end.size())
		{
			_end_position = end;
			return nullptr;
		}
	}
	return_parse_end = end;
	return item;
}

string JSON::Parse_Value(Node* item, string value)
{
	if (value.empty())
	{
		return {};
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
		return {};
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
	return {};
}

string JSON::Parse_String(Node* item, string value)
{
	if (value[0] != '\"')
	{
		_end_position = value[0];
		return {};
	}

	int size = value.size();
	int length = 0;
	auto position = value.find('\"', 1);
	if (position)
	{
		length = position - 1;
	}

	if (length < 1)
	{
		return {};
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
}

string JSON::Parse_Number(Node* item, string value)
{
	bool sign = 1;
	int start_position = 0;
	if (value[0] == '-')
	{
		sign = false;
		start_position = 1;
	}
	if (value[0] == '+')
	{
		sign = true;
		start_position = 1;
	}
	while (value[start_position] == 0)
	{
		start_position++;
	}
	
	string num_str;
	if (value[start_position] >= '0' && value[start_position] <= '9')
	{
		while ((value[start_position] >= '0' && value[start_position] <= '9') || value[start_position] == 'e' || value[start_position] == 'E' ||
			value[start_position] == '.' || (value[start_position - 1] == 'e' && (value[start_position] == '+' || value[start_position] == '-')) ||
			(value[start_position - 1] == 'E' && (value[start_position] == '+' || value[start_position] == '-')))
		{
			num_str += value[start_position];
			start_position++;
		}
	}
	if (num_str.size() < 1)
	{
		return {};
	}

	double num_double = stod(num_str);
	int num_int = stol(num_str);
	if (num_double - num_int > 0)
	{
		item->_type = NodeValueType::VALUE_TYPE_DOUBLE;
		item->_value_double = sign ? num_double : (-num_double);
	}
	else
	{
		item->_type = NodeValueType::VALUE_TYPE_INT;
		item->_value_int = sign ? num_int : (-num_int);
	}
	return value.substr(start_position);
	

}

string JSON::Parse_Array(Node* item, string value)
{
	Node* child = New_Node();
	if (value[0] != '[')
	{
		_end_position = value[0];
		return {};
	}

	item->_type = NodeValueType::VALUE_TYPE_ARRAY;
	value = Skip(value.substr(1));
	//[]
	if (value[0] == ']')
	{
		return value.substr(1);
	}

	item->_child = child;
	value = Parse_Value(child, Skip(value));
	if (value.empty())
	{
		return {};
	}

	while (value[0] == ',' && value.size() > 1)
	{
		Node* new_item = New_Node();
		child->_next = new_item;
		new_item->_prev = child;
		child = new_item;

		value = Skip(Parse_Value(child, Skip(value.substr(1))));
		if (value.empty())
		{
			return {};
		}
	}
	if (value[0] == ']')
	{
		return value.substr(1);
	}
	_end_position = value[0];
	return {};
}

string JSON::Parse_Object(Node* item, string value)
{
	Node* child = New_Node();
	if (value[0] != '{')
	{
		_end_position = value[0];
		return {};
	}

	item->_type = NodeValueType::VALUE_TYPE_OBJECT;
	value = Skip(value.substr(1));
	if (value.size() && value[0] == '}')
	{
		return value.substr(1);
	}

	item->_child = child;
	value = Parse_String(child, Skip(value));
	if (value.empty())
	{
		return {};
	}

	child->_node_name = child->_value_string;
	child->_value_string.clear();
	if (Skip(value)[0] != ':')
	{
		_end_position = value[0];
		return {};
	}

	value = Parse_Value(child, Skip(value.substr(1)));
	while (value[0] == ',' && value.size() > 1)
	{
		Node* new_item = New_Node();
		child->_next = new_item;
		new_item->_prev = child;
		child = new_item;

		value = Skip(Parse_String(child, Skip(value.substr(1))));
		if (value.empty())
		{
			return {};
		}

		child->_node_name = child->_value_string;
		child->_value_string.clear();
		if (Skip(value)[0] != ':')
		{
			_end_position = value[0];
			return {};
		}

		value = Parse_Value(child, Skip(value.substr(1)));
		if (value.empty())
		{
			return {};
		}
	}
	if (value.empty())
	{
		return {};
	}
	if (value[0] == '}')
	{
		return value.substr(1);
	}
	_end_position = value[0];
	return {};
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
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_OBJECT;
	return item;
}

Node* JSON::Create_String(string& str)
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_STRING;
	item->_value_string = str;
	return item;
}

Node* JSON::Create_String(string&& str)
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_STRING;
	item->_value_string = move(str);
	return item;
}

Node* JSON::Create_Double(double num)
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_DOUBLE;
	item->_value_double = num;
	return item;
}

Node* JSON::Create_Int(int num)
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_INT;
	item->_value_int = num;
	return item;
}

Node* JSON::Create_Array()
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_ARRAY;
	return item;
}

Node* JSON::Create_Bool(bool boolean)
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_BOOL;
	item->_value_bool = boolean;
	return item;
}

Node* JSON::Create_Null()
{
	Node* item = New_Node();
	item->_type = NodeValueType::VALUE_TYPE_NULL;
	return item;
}

JSON& JSON::Add_Item_To_Obj(Node* obj, string item_name, Node* item)
{
	if (obj == nullptr)
	{
		return *this;
	}
		
	if (item == nullptr)
	{
		return *this;
	}
		
	item->_node_name = item_name;
	obj->_type = NodeValueType::VALUE_TYPE_OBJECT;
	return Add_Item_To_Array(obj, item);
}

JSON& JSON::Add_Item_To_Array(Node* array, Node* item)
{
	if (array == nullptr)
	{
		return *this;
	}
		
	if (item == nullptr)
	{
		return *this;
	}
		
	auto child = array->_child;
	if (!child)
	{
		array->_child = item;
	}
	else
	{
		while (child->_next != nullptr)
		{
			child = child->_next;
		}
		Suffix_Object(child, item);
	}
	return *this;
}


string JSON::Print(Node* item)
{
	return Print_Json(item);
}

string JSON::Print_Json(Node* obj)
{
	return Print_Json(obj, 0);
}

string JSON::Print_Json(Node* obj, int depth)
{
	string out;
	if (obj == nullptr)
		return {};
	switch (obj->_type)
	{
	case NodeValueType::VALUE_TYPE_NULL:
		out = { "null" };
		return out;
		break;
	case NodeValueType::VALUE_TYPE_BOOL:
		out = obj->_value_bool ? "true" : "false";
		return out;
		break;
	case NodeValueType::VALUE_TYPE_INT:
		out = to_string(obj->_value_int);
		return out;
		break;
	case NodeValueType::VALUE_TYPE_DOUBLE:
		out = to_string(obj->_value_double);
		return out;
		break;
	case NodeValueType::VALUE_TYPE_STRING:
		out = "\"" + obj->_value_string + "\"";
		return out;
		break;
	case NodeValueType::VALUE_TYPE_ARRAY:
		out = Print_Array(obj, depth);
		return out;
		break;
	case NodeValueType::VALUE_TYPE_OBJECT:
		out = Print_Object(obj, depth);
		return out;
		break;
	}
	return out;
}

string JSON::Print_Array(Node* obj, int depth)
{
	string out;
	if (obj == nullptr)
		return {};
	auto child = obj->_child;
	while (child)
	{
		auto ret = Print_Json(child, depth + 1);
		if (ret.size())
		{
			out += (ret + (child->_next ? "," : ""));
		}
		child = child->_next;
	}
	return "[" + out + "]";
}

string JSON::Print_Object(Node* obj, int depth)
{
	string out;
	if (obj == nullptr)
		return {};
	auto child = obj->_child;
	while (child)
	{
		auto name = "\"" + child->_node_name + "\"";
		auto ret = Print_Json(child, depth + 1);
		if (ret.size())
		{
			out += (name + ':' + ret + (child->_next ? "," : ""));
		}
		child = child->_next;
	}
	return "{" + out + "}";
}

void JSON::Suffix_Object(Node* prev, Node* item)
{
	prev->_next = item;
	item->_prev = prev;
}
