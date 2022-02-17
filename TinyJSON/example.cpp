#include"Json.h"
#include <format>

using namespace std;

int main()
{
	JSON json;
	auto root = json.Create_Object();
	auto arry1 = json.Create_Array();
	auto int1 = json.Create_Int(1);
	auto double2 = json.Create_Double(2);
	auto string3 = json.Create_String("3333");
	json.Add_Item_To_Array(arry1, int1).Add_Item_To_Array(arry1, double2).Add_Item_To_Array(arry1, string3);
	json.Add_Item_To_Obj(root, "array", arry1);
	json.Add_Item_To_Obj(root, "EventType", json.Create_Int(100));
	cout << json.Print(root) << endl;
	json.Recycle_Node(root);
	int1 = json.Create_Int(1);
	double2 = json.Create_Double(2);
	string3 = json.Create_String("4444");

	system("pause");
	return 0;
}