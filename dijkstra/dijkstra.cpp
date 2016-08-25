#include "dijkstra.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;
const int cnt = 10;
const unsigned int maxint = 10000;

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
//            cout << *iter << endl;
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
}

void dijkstra(int n, int v, int content[cnt][cnt], int *prev, int *dist)
{
    bool s[cnt];
    for(int i = 0; i < cnt; i++)
    {
        dist[i] = content[v][i];
        s[i] = false;
        if (dist[i] == maxint)
            prev[i] = -1;
        else 
            prev[i] = v;
    
    }
    dist[v] = 0;
    s[v] = true;

    for (int row = 1; row < cnt; row++)
    {
        int temp = maxint;
        int u = v;
        for (int col = 0; col < cnt; col++) 
            if((!s[col]) && dist[col] < temp)
            {
                u = col;
                temp = dist[col];
            }

        s[u] = true;
        for (int col = 0; col < cnt; col++)
            if((!s[col]) && content[u][col] < maxint)
            {
               if(dist[u] + content[u][col] < dist[col])
               {
                
                   dist[col] = dist[u] + content[u][col];
                   prev[col] = u;
               }
            }
    
    }
}

void search_path(int *prev, int v, int u)
{
    int que[cnt];
    int tot = 0;
    que[tot] = u;
    tot++;
    int tmp = prev[u];
    while(tmp != v)
    {
        que[tot] = tmp;
        tot++;
        tmp = prev[tmp];
    }
    que[tot] = v;
    for(int i=tot; i>=0; --i)
        if(i != 0)
            cout << que[i] << " -> ";
        else
            cout << que[i] << endl;
}

int main(int argc, char ** argv)
{
    int a[10][10];
    int prev[10];
    int dist[10];
    for(int row = 0; row < cnt; row++) 
    {
        for(int col = 0; col < cnt; col++)
        {
            if (col == row) 
            {
                a[row][col] = 0;
            }
            else 
            {
                a[row][col] = maxint;
            }
        }
    }
    Vertex head = {
        .vtx1 = 0,
        .vtx2 = 0,
        .value = 0,
        .next = NULL
    };
    createMap("/home/jimmy/learn/AI/dijkstra/param", &head);
    Vertex *list = (&head)->next;
    while(list != NULL) {
 //       cout << "vtx1: " << list->vtx1  << ",  vtx2: " << list->vtx2 << ", value: " << list->value << endl;
        a[list->vtx1][list->vtx2] = list->value;
        list = list->next;
    }	

    for(int row = 0; row < cnt; row++) 
    {
        for(int col = 0; col < cnt; col++)
        {

            cout << a[row][col] << "\t";
        }
        cout << endl;
    }
    
    dijkstra(10, 0, a, prev, dist);
    search_path(prev, 0, 8); 
    for (int i = 0 ; i < cnt; i++)
    {
       cout << dist[i] << "\t"; 
    }
    return 0;
}















