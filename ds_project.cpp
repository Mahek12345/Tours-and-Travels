#include <bits/stdc++.h>
using namespace std;
#define C 100

vector<string> final_ans;
int minimum_key(int data[], bool Visited[],int no_cities)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < no_cities; i++)
    {
        if (Visited[i] == false && data[i] < min)
        {
            min = data[i], min_index = i;
        }
    }
    return min_index;
}

vector<vector<int>> MST(int parent[], int City[C][C],int no_cities)
{
    vector<vector<int>> v;
    for (int i = 1; i < no_cities; i++)
    {
        vector<int> p;
        p.push_back(parent[i]);
        p.push_back(i);
        v.push_back(p);
        p.clear();
    }
    return v;
}
vector<vector<int>> primMST(int City[C][C],int no_cities,string Name_cities[C])
{
    // initi parent and key array
    int parent[C];
    int data[C];

    // to keep track of vertices already visited
    bool Visited[C];

    // initialize data  to infinite and false for all visited vertices
    for (int i = 0; i < no_cities; i++)
    {
        data[i] = INT_MAX, Visited[i] = false;
    }

    // picking up the first vertex and assigning it to 0
    data[0] = 0;
    // make parent of 0th index to -1
    parent[0] = -1;

    for (int count = 0; count < no_cities - 1; count++)
    {
        // checking and updating values of u wrt minimum key
        int u = minimum_key(data, Visited,no_cities);
        Visited[u] = true;
        for (int v = 0; v < no_cities; v++)
        {
            if (City[u][v] && Visited[v] == false && City[u][v] < data[v])
            {
                parent[v] = u, data[v] = City[u][v];
            }
        }
    }

    vector<vector<int>> v;
    v = MST(parent, City,no_cities);
    printf("\nEnter the Rupees per kilometer:");
    printf("1-->BUS, 2-->Train :- ");
    int c;
    scanf("%d", &c);
    switch (c)
    {
    case 1:
        int rupee;
        printf("\nEnter the rupees per kilometer for Bus:-");
        scanf("%d", &rupee);
        printf("\n Route \t\t   Cost \n");
        for (int i = 1 ; i < no_cities; i++)

           { // printf(" %s <-> %s    %d   \n", Name_cities[parent[i]], Name_cities[i], City[i][parent[i]] * rupee2);
            cout << Name_cities[parent[i]] ;
            cout << " <-> " ;
            cout << Name_cities[i] ;
            cout << " " ;
            cout << City[i][parent[i]] * rupee ;
            cout << "\n " ;
           }
        break;

    case 2:

        int rupee2;
        printf("\nEnter the rupees per kilometer for Train:-");
        scanf("%d", &rupee2);
        printf("\n Route \t\t   Cost \n");
        for (int i = 1 ; i < no_cities; i++)

           { // printf(" %s <-> %s    %d   \n", Name_cities[parent[i]], Name_cities[i], City[i][parent[i]] * rupee2);
            cout << Name_cities[parent[i]] ;
            cout << " <-> " ;
            cout << Name_cities[i] ;
            cout << " " ;
            cout << City[i][parent[i]] * rupee2 ;
            cout << "\n " ;
           }
        break;
    }
    printf("\n Route \t\t  Distance \n");
    for (int i = 1; i < no_cities; i++)
    {

        cout << Name_cities[parent[i]] ;
            cout << " <-> " ;
            cout << Name_cities[i] ;
            cout << " " ;
            cout << City[i][parent[i]] ;
            cout << "\n" ;
    }

    return v;
}
// getting the preorder walk of the MST using DFS
void DFS(int **edges_list, int num_nodes, int starting_vertex, bool *visited_nodes,int no_cities,string Name_cities[C])
{
    // adding the node to final answer
    final_ans.push_back(Name_cities[starting_vertex]);

    // checking the visited status
    visited_nodes[starting_vertex] = true;

    // using a recursive call
    for (int i = 0; i < num_nodes; i++)
    {
        if (edges_list[starting_vertex][i] == 1)
        {
            if (visited_nodes[i])
            {
                continue;
            }
            DFS(edges_list, num_nodes, i, visited_nodes,no_cities,Name_cities);
        }
    }
}
int main()

{
    // cout << "Abcd";
     system("cls");
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "\t\t\t ************************        WELCOME TO TRAVELLING SALESMAN PROBLEM      **************************\n\n\n"
         << endl;

    int no_cities;
    cout << "Enter the Number of cities you want to visit:- " << endl;
    cin >> no_cities;
    int City[C][C];
    string Name_cities[C];
    string st;
    cout << "Enter the Name of cities you want to visit:- " << endl;
    for(int count = 0 ; count<no_cities ; count++)
    {
        cin >> st;
         Name_cities[count] = st;
    }
    for (int i = 0; i < no_cities; i++)
    {
        for (int j = i+1; j < no_cities; j++)
        {
            if(i==j)
            continue;
            else
            {
                cout << "\nEnter the distance between cities from ";
                cout << Name_cities[i];
                cout << " to ";
                cout << Name_cities[j];
                cout << ":- ";
            }
            cin >> City[i][j];
            City[j][i] = City[i][j];
        }
    }
    for (int i = 0; i < no_cities; i++)
    {
        for (int j = 0; j < no_cities; j++)
        {
            cout << City[i][j] << " ";
        }
        cout << endl;
    }
    vector<vector<int>> v;
    // getting the output as MST

    v = primMST(City,no_cities,Name_cities);

    // creating a dynamic matrix
    int **edges_list = new int *[no_cities];
    for (int i = 0; i < no_cities; i++)
    {
        edges_list[i] = new int[no_cities];
        for (int j = 0; j < no_cities; j++)
        {
            edges_list[i][j] = 0;
        }
    }
    // setting up MST as adjacency matrix
    for (int i = 0; i < v.size(); i++)
    {
        int first_node = v[i][0];
        int second_node = v[i][1];
        edges_list[first_node][second_node] = 1;
        edges_list[second_node][first_node] = 1;
    }
    // a checker function for the DFS
    bool *visited_nodes = new bool[C];
    for (int i = 0; i < no_cities; i++)
    {
        bool visited_node;
        visited_nodes[i] = false;
    }

    // performing DFS
    DFS(edges_list,no_cities, 0, visited_nodes,no_cities,Name_cities);

    // adding the source node to the path
    final_ans.push_back(final_ans[0]);

    printf("\n\nShortest route Starting from home to return back to home: ");

    // printing the path
    for (int i = 0; i < final_ans.size(); i++)
    {
        cout << final_ans[i] << "--> ";
    }
    cout<<"DONE";
    int sml = 1;
    char ch = sml;
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "                        *************************               ";
    cout << ch;
    cout << " Thank You!! ";
    cout << ch;

    cout << "                        ***************************             ";

    return 0;
}