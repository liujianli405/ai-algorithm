#include "dijkstra.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;

Vertex* createVertex(int vtx1,int vtx2, int value)
{
	Vertex *vert = new Vertex();
	vert->vtx1 = vtx1;
	vert->vtx2 = vtx2;
	vert->value = value;
	return vert;
}

vector<string> split(const string str,const char * pattern)
{
	vector<string> vec;
	if (pattern == NULL || strlen(pattern) == 0) return vec;
	string temp = str;
	int pos;
	int len = temp.length();
	while((pos = temp.find_first_of(pattern)) != string::npos) 
	{
		vec.push_back(temp.substr(0, pos));
		temp = temp.substr(pos + 1, len);
		len = temp.length();
	}
	if (len != 0)
		vec.push_back(temp.substr(0, len));
	return vec;	
}

#if 0
map<string, string> tdsplit(const string str, const char* pattern)
{
	static string keys[] = {"vet1", "vet2", "edge"};
	map<string,string> map;
	string temp = str;
	int pos; 
	int cnt = 0;
	int len = temp.length();
	if (pattern == NULL || strlen(pattern) == 0) return map;
	while((pos = temp.find_first_of(pattern)) != string::npos)
	{
		if (cnt < 3) map.insert(keys[cnt], temp.substr(0, pos));
		temp = temp.substr(pos + 1, len);
		len = temp.length();
		cnt++;
	}
	
	if (len != 0)
		map.insert(keys[2], temp.substr(0, len));
	return map;

}
#endif

bool createMap(const char* file, Vertex *head)
{
	int start, end, len;
	if (file == NULL || strlen(file) == 0) return false;
	cout<< file << endl;
	ifstream in;
	in.open(file, ios::in);
	start = in.tellg();
	in.seekg(0, ios::end);
	end = in.tellg();
	in.seekg(0, ios::beg);
	len = end - start;
	cout << "len: " << len << endl;
	
	Vertex *p = head;
	string temp;
	string value[3];
	while (getline(in, temp)) {
		vector<string> vec = split(temp, ",");
		start = 0;
		for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
		{
			value[start] = *iter;
			start++;
			cout << *iter << endl;
		}
		Vertex *node = new Vertex();
		node->vtx1 = atoi(value[0].c_str());
		node->vtx2 = atoi(value[1].c_str());
		node->value = atoi(value[2].c_str());
		p -> next = node;
		node -> next = NULL;
		p = node;
	} 
	return true;
/*	buff = new char[len];
	in.read(buff, len);
	in.close();
	string s(buff);
	string &temp = s;
	cout << temp << endl;
*/	
}


static int dijkstra(int n, int **)
{
	

}

int main(int argc, char ** argv)
{
	Vertex head = {
	.vtx1 = 0,
	.vtx2 = 0,
	.value = 0,
	.next = NULL
	};
	createMap("/home/jimmy/learn/AI/dijkstra/param", &head);
	Vertex *list = (&head)->next;
	while(list != NULL) {
		cout << "vtx1: " << list->vtx1  << ",  vtx2: " << list->vtx2 << ", value: " << list->value << endl;
		list = list->next;
	}	
	return 0;
}
