#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <queue>

/* Linux - Ubuntu 12.04 */

using namespace std;

#define left 0
#define right 1
#define down 2
#define up 3
#define maxi 50

struct statespace{
    int state[3][3];
    int mhd;        // ManHatten Distance of Given State
    int cost;       // Cost to reach this state
    bool expanded;
    struct statespace *s[4];
}*start,*root,*goal;

queue <struct statespace *> que,expanded;
int tempforbestone[3][3];
int total_nodes=0,remaining=0;

int location(int array[3][3],int value);

// Returns Manhatten distance of 8 puzzle problem
int manhatten_distance(int array[3][3])
{
    // Defined weight associated with every coordiante
    int defined[9][2]={{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};

    // For Debugging
    /*
    cout<<"Debugging Of MH Distance Starts for Following Matrix -------------------- "<<endl;
    for(int i=0;i<3;i++)
    {
    for(int j=0;j<3;j++)
    {
    cout<<array[i][j]<<" ";
    }
    cout<<endl;
    }
    cout<<"Point 0 : "<<abs(defined[array[0][0]-1][0]-defined[0][0])+abs(defined[array[0][0]-1][1]-defined[0][1])<<endl;
    cout<<"Point 1 : "<<abs(defined[array[0][1]-1][0]-defined[1][0])+abs(defined[array[0][1]-1][1]-defined[1][1])<<endl;
    cout<<"Point 2 : "<<abs(defined[array[0][2]-1][0]-defined[2][0])+abs(defined[array[0][2]-1][1]-defined[2][1])<<endl;
    cout<<"Point 3 : "<<abs(defined[array[1][0]-1][0]-defined[3][0])+abs(defined[array[1][0]-1][1]-defined[3][1])<<endl;
    cout<<"Point 4 : "<<abs(defined[array[1][1]-1][0]-defined[4][0])+abs(defined[array[1][1]-1][1]-defined[4][1])<<endl;
    cout<<"Point 5 : "<<abs(defined[array[1][2]-1][0]-defined[5][0])+abs(defined[array[1][2]-1][1]-defined[5][1])<<endl;
    cout<<"Point 6 : "<<abs(defined[array[2][0]-1][0]-defined[6][0])+abs(defined[array[2][0]-1][1]-defined[6][1])<<endl;
    cout<<"Point 7 : "<<abs(defined[array[2][1]-1][0]-defined[7][0])+abs(defined[array[2][1]-1][1]-defined[7][1])<<endl;
    cout<<"Point 8 : "<<abs(defined[array[2][2]-1][0]-defined[8][0])+abs(defined[array[2][2]-1][1]-defined[8][1])<<endl;

    cout<<"------------------------------- MH Distance Calculated ----------------"<<endl;
    */

    return (abs(defined[array[0][0]-1][0]-defined[0][0])+abs(defined[array[0][0]-1][1]-defined[0][1])+
    abs(defined[array[0][1]-1][0]-defined[1][0])+abs(defined[array[0][1]-1][1]-defined[1][1])+
    abs(defined[array[0][2]-1][0]-defined[2][0])+abs(defined[array[0][2]-1][1]-defined[2][1])+
    abs(defined[array[1][0]-1][0]-defined[3][0])+abs(defined[array[1][0]-1][1]-defined[3][1])+
    abs(defined[array[1][1]-1][0]-defined[4][0])+abs(defined[array[1][1]-1][1]-defined[4][1])+
    abs(defined[array[1][2]-1][0]-defined[5][0])+abs(defined[array[1][2]-1][1]-defined[5][1])+
    abs(defined[array[2][0]-1][0]-defined[6][0])+abs(defined[array[2][0]-1][1]-defined[6][1])+
    abs(defined[array[2][1]-1][0]-defined[7][0])+abs(defined[array[2][1]-1][1]-defined[7][1])+
    abs(defined[array[2][2]-1][0]-defined[8][0])+abs(defined[array[2][2]-1][1]-defined[8][1])-
    abs(defined[location(array,9)][0]-defined[8][0])-abs(defined[location(array,9)][1]-defined[8][1]));
}

int location(int array[3][3],int value)
{
int i,j,pos;
pos=0;
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
    if(array[i][j]==value)
        return pos;
    pos++;
}
}
}

int* possibility(int array[3][3],int possible[4])
{
    int *ptr;
    ptr=possible;
    possible[0]=0;
    possible[1]=0;
    possible[2]=0;
    possible[3]=0;

    int pos = location(array,9);
    //Debugging
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    //cout<<"Pos Is : "<<pos<<endl;


    switch(pos)
    {
    case 0:
    {
        possible[0]=0;
        possible[1]=1;
        possible[2]=1;
        possible[3]=0;
        break;
    }
    case 1:
    {
        possible[0]=1;
        possible[1]=1;
        possible[2]=1;
        possible[3]=0;
        break;
    }
    case 2:
    {
        possible[0]=1;
        possible[1]=0;
        possible[2]=1;
        possible[3]=0;
        break;
    }
    case 3:
    {
        possible[0]=0;
        possible[1]=1;
        possible[2]=1;
        possible[3]=1;
        break;
    }
    case 4:
    {
        possible[0]=1;
        possible[1]=1;
        possible[2]=1;
        possible[3]=1;
        break;
    }
    case 5:
    {
        possible[0]=1;
        possible[1]=0;
        possible[2]=1;
        possible[3]=1;
        break;
    }
    case 6:
    {
        possible[0]=0;
        possible[1]=1;
        possible[2]=0;
        possible[3]=1;
        break;
    }
    case 7:
    {
        possible[0]=1;
        possible[1]=1;
        possible[2]=0;
        possible[3]=1;
        break;
    }
    case 8:
    {
        possible[0]=1;
        possible[1]=0;
        possible[2]=0;
        possible[3]=1;
        break;
    }
    }

    // Debugging
    /*
    cout<<"Possibilities : ";
    if(possible[0]==1) cout<<" Left ";
    if(possible[1]==1) cout<<" Right ";
    if(possible[2]==1) cout<<" Down ";
    if(possible[3]==1) cout<<" Up ";
    cout<<endl;
    */
    return ptr;
}

//Check if two states are equal
bool areequal(statespace *ss1,statespace *ss2)
{
    for(int i=0;i<3;i++)
    {
    for(int j=0;j<3;j++)
    {
    if(ss1->state[i][j]!=ss2->state[i][j])
    {
        return false;
    }
    }
    }
    return true;
}

bool exist(struct statespace *ss1)
{
    bool flag=false;
    queue <struct statespace * > qtemp;
    while(expanded.empty()==false)
    {
        qtemp.push(expanded.front());
        if(areequal(expanded.front(),ss1))
            flag=true;
        expanded.pop();
    }
    while(qtemp.empty()==false)
    {
        expanded.push(qtemp.front());
        qtemp.pop();
    }
    while(que.empty()==false)
    {
        qtemp.push(que.front());
        if(areequal(que.front(),ss1))
            flag=true;
        que.pop();
    }
    while(qtemp.empty()==false)
    {
        que.push(qtemp.front());
        qtemp.pop();
    }
    return flag;
}

void statistics()
{
    queue <struct statespace * > qtemp;
    remaining=0;
    total_nodes=0;
    while(expanded.empty()==false)
    {
        qtemp.push(expanded.front());
        expanded.pop();
        total_nodes++;
    }
    while(qtemp.empty()==false)
    {
        expanded.push(qtemp.front());
        qtemp.pop();
    }
    while(que.empty()==false)
    {
        qtemp.push(que.front());
        que.pop();
        remaining++;
    }
    while(qtemp.empty()==false)
    {
        que.push(qtemp.front());
        qtemp.pop();
    }
    cout<<"\n\\\\\\\\\\\\\\\\\\\\\ Stats \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
    cout<<"Total Expanded Node : "<<total_nodes<<endl;
    cout<<"Total Repeated Node : "<<remaining<<endl;
    cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ "<<endl;
}

void printstate()
{
    queue <struct statespace * > qtemp;
    struct statespace *temp;
    cout<<"<<<<<<<<<<<<<<<<<<<<< Printing Nodes >>>>>>>>>>>>>>>>>>>>"<<endl;
    while(que.empty()!=true)
    {
        temp=que.front();
        qtemp.push(temp);
        que.pop();
        cout<<" [ ";
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<temp->state[i][j]<<" ";
        }
        }
        cout<<" ] "<<endl;
    }
    while(qtemp.empty()!=true)
    {
        que.push(qtemp.front());
        qtemp.pop();
    }
    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
}

void copy(int a[3][3],int b[3][3],int orient,int position)
{
    for(int i=0;i<3;i++)
    {
    for(int j=0;j<3;j++)
    {
    tempforbestone[i][j]=0;
    tempforbestone[i][j]=b[i][j];
    }
    }
    switch (orient)
    {
    case 0:
    {
        if(position==1)
        {
            tempforbestone[0][0]=b[0][1];
            tempforbestone[0][1]=b[0][0];
        }
        if(position==2)
        {
            tempforbestone[0][2]=b[0][1];
            tempforbestone[0][1]=b[0][2];
        }
        if(position==4)
        {
            tempforbestone[1][0]=b[1][1];
            tempforbestone[1][1]=b[1][0];
        }
        if(position==5)
        {
            tempforbestone[1][1]=b[1][2];
            tempforbestone[1][2]=b[1][1];
        }
        if(position==7)
        {
            tempforbestone[2][0]=b[2][1];
            tempforbestone[2][1]=b[2][0];
        }
        if(position==8)
        {
            tempforbestone[2][1]=b[2][2];
            tempforbestone[2][2]=b[2][1];
        }
        break;
    }
    case 1:         //Right
    {
        if(position==0)
        {
            tempforbestone[0][0]=b[0][1];
            tempforbestone[0][1]=b[0][0];
        }
        if(position==1)
        {
            tempforbestone[0][2]=b[0][1];
            tempforbestone[0][1]=b[0][2];
        }
        if(position==3)
        {
            tempforbestone[1][0]=b[1][1];
            tempforbestone[1][1]=b[1][0];
        }
        if(position==4)
        {
            tempforbestone[1][1]=b[1][2];
            tempforbestone[1][2]=b[1][1];
        }
        if(position==6)
        {
            tempforbestone[2][0]=b[2][1];
            tempforbestone[2][1]=b[2][0];
        }
        if(position==7)
        {
            tempforbestone[2][1]=b[2][2];
            tempforbestone[2][2]=b[2][1];
        }
        break;
    }
    case 2:             //Down
    {
        if(position==0)
        {
            tempforbestone[0][0]=b[1][0];
            tempforbestone[1][0]=b[0][0];
        }
        if(position==1)
        {
            tempforbestone[0][1]=b[1][1];
            tempforbestone[1][1]=b[0][1];
        }
        if(position==2)
        {
            tempforbestone[0][2]=b[1][2];
            tempforbestone[1][2]=b[0][2];
        }
        if(position==3)
        {
            tempforbestone[1][0]=b[2][0];
            tempforbestone[2][0]=b[1][0];
        }
        if(position==4)
        {
            tempforbestone[1][1]=b[2][1];
            tempforbestone[2][1]=b[1][1];
        }
        if(position==5)
        {
            tempforbestone[1][2]=b[2][2];
            tempforbestone[2][2]=b[1][2];
        }
        break;
    }
    case 3:             //Up
    {
        if(position==3)
        {
            tempforbestone[1][0]=b[0][0];
            tempforbestone[0][0]=b[1][0];
        }
        if(position==4)
        {
            tempforbestone[1][1]=b[0][1];
            tempforbestone[0][1]=b[1][1];
        }
        if(position==5)
        {
            tempforbestone[0][2]=b[1][2];
            tempforbestone[1][2]=b[0][2];
        }
        if(position==6)
        {
            tempforbestone[1][0]=b[2][0];
            tempforbestone[2][0]=b[1][0];
        }
        if(position==7)
        {
            tempforbestone[1][1]=b[2][1];
            tempforbestone[2][1]=b[1][1];
        }
        if(position==8)
        {
            tempforbestone[1][2]=b[2][2];
            tempforbestone[2][2]=b[1][2];
        }
        break;
    }
    }
}

struct statespace * find_node(struct statespace *ss1,struct statespace *ss2)
{
        struct statespace *temporary[5];
        temporary[0]=NULL;
        temporary[1]=NULL;
        temporary[2]=NULL;
        temporary[3]=NULL;
        temporary[4]=NULL;
        if(areequal(ss1,ss2)==true)
        {
            //cout<<"^^^^^^^^^^^^^^^^^^^^^^^^  Found ^^^^^^^^^^^^^^^^^^^^"<<endl;
            temporary[4]==ss2;
            return ss2;
        }
        else
        {
        if(ss2->s[0]!=NULL)
            temporary[0]=find_node(ss1,ss2->s[0]);
        if(temporary[0]==NULL && ss2->s[1]!=NULL)
            temporary[1]=find_node(ss1,ss2->s[1]);
        if(temporary[0]==NULL && temporary[1]==NULL && ss2->s[2]!=NULL)
            temporary[2]=find_node(ss1,ss2->s[2]);
        if(temporary[0]==NULL && temporary[1]==NULL && temporary[2]==NULL && ss2->s[3]!=NULL)
            temporary[3]=find_node(ss1,ss2->s[3]);
        }
        for(int i=0;i<5;i++)
        {
            if(temporary[i]!=NULL)
                return temporary[i];
        }
        return NULL;
}


void expand(struct statespace *ss1)
{
    if(areequal(ss1,goal))
        return ;

    expanded.push(ss1);

    int possible[4];
    int *ptr;
    int distance[]={maxi ,maxi ,maxi,maxi};
    int pos=location(ss1->state,9);
    struct statespace *tmp,*temporary[4];
    int minimum,index;

    temporary[0]=NULL;
    temporary[1]=NULL;
    temporary[2]=NULL;
    temporary[3]=NULL;
    ptr = possibility(ss1->state,possible);

    for(int i=0;i<4;i++)
    {
    possible[i]=*ptr;
    ptr++;
    }

    cout<<"-------------Expanding-----------------"<<endl;
    for(int i=0;i<3;i++)
    {
    for(int j=0;j<3;j++)
    {
        cout<<ss1->state[i][j]<<" ";
    }
    cout<<endl;
    }


    //Checking for Left Swap
    if(possible[0]==1)
    {
        copy(tempforbestone,ss1->state,left,pos);
        tmp=(struct statespace *)malloc(sizeof(struct statespace));
        tmp->expanded=0;
        tmp->mhd=manhatten_distance(tempforbestone);
        tmp->s[0]=NULL;
        tmp->s[1]=NULL;
        tmp->s[2]=NULL;
        tmp->s[3]=NULL;
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        tmp->state[i][j]=tempforbestone[i][j];
        }
        }
        cout<<"Checking For Left Existence : [";
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<(tmp->state[i][j])<<" ";
        }
        }
        cout<<" ]"<<endl;
        if(exist(tmp)!=true)
            que.push(tmp);
    }
    if(possible[1]==1)      //Checking for Right Swap
    {
        copy(tempforbestone,ss1->state,right,pos);
        tmp=(struct statespace *)malloc(sizeof(struct statespace));
        tmp->expanded=0;
        tmp->mhd=manhatten_distance(tempforbestone);
        tmp->s[0]=NULL;
        tmp->s[1]=NULL;
        tmp->s[2]=NULL;
        tmp->s[3]=NULL;
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        tmp->state[i][j]=tempforbestone[i][j];
        }
        }
        cout<<"Checking For Right Existence : [";
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<(tmp->state[i][j])<<" ";
        }
        }
        cout<<" ]"<<endl;
        if(exist(tmp)!=true)
            que.push(tmp);
    }
    if(possible[2]==1)      //Checking for Down Swap
    {
        copy(tempforbestone,ss1->state,down,pos);
        tmp=(struct statespace *)malloc(sizeof(struct statespace));
        tmp->expanded=0;
        tmp->mhd=manhatten_distance(tempforbestone);
        tmp->s[0]=NULL;
        tmp->s[1]=NULL;
        tmp->s[2]=NULL;
        tmp->s[3]=NULL;
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        tmp->state[i][j]=tempforbestone[i][j];
        }
        }
        cout<<"Checking For Down Existence : [";
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<(tmp->state[i][j])<<" ";
        }
        }
        cout<<" ]"<<endl;
        if(exist(tmp)!=true)
            que.push(tmp);
    }
    if(possible[3]==1)      //Checking for Up Swap
    {
        copy(tempforbestone,ss1->state,up,pos);
        tmp=(struct statespace *)malloc(sizeof(struct statespace));
        tmp->expanded=0;
        tmp->mhd=manhatten_distance(tempforbestone);
        tmp->s[0]=NULL;
        tmp->s[1]=NULL;
        tmp->s[2]=NULL;
        tmp->s[3]=NULL;
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        tmp->state[i][j]=tempforbestone[i][j];
        }
        }
        cout<<"Checking For Up Existence : [";
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<(tmp->state[i][j])<<" ";
        }
        }
        cout<<" ]"<<endl;
        if(exist(tmp)!=true)
            que.push(tmp);
    }

    cout<<"-------------Expansion Completed-------"<<endl;

    return;
}

void solve()
{
    if(que.front()!=NULL)
    {
        struct statespace *temp;
        temp=que.front();
        que.pop();
        expand(temp);
        if(areequal(temp,goal)==false)
        {
        //printstate();
        system("sleep 0");
        statistics();
        solve();
        }
        else
        {
        cout<<"Found : ---------------------"<<endl;
        for(int i=0;i<3;i++)
        {
        for(int j=0;j<3;j++)
        {
        cout<<(temp->state[i][j])<<" ";
        }
        cout<<endl;
        }
        cout<<endl;
        }
    }
}


int main()
{
    // Fill Initial State Here
    // Note : 9 - Space(Empty cell)
    int matrix[3][3]={1,2,3,4,5,6,7,9,8};

    // possible[0] = LEFT, possible[1] = RIGHT, possible[2] = DOWN, possible[3] = UP
    int possible[4];
    int *ptr;

    cout<<"MH Distance : "<<manhatten_distance(matrix)<<endl;
    ptr=possibility(matrix,possible);

    for(int i=0;i<4;i++)
    {
    possible[i]=*ptr;
    ptr++;
    }

    //Defining Goal State
    goal=(struct statespace *)malloc(sizeof(struct statespace));
    goal->cost=-1;
    goal->mhd=0;
    goal->state[0][0]=1;
    goal->state[0][1]=2;
    goal->state[0][2]=3;
    goal->state[1][0]=4;
    goal->state[1][1]=5;
    goal->state[1][2]=6;
    goal->state[2][0]=7;
    goal->state[2][1]=8;
    goal->state[2][2]=9;
    goal->expanded=0;
    goal->s[0]=NULL;
    goal->s[1]=NULL;
    goal->s[2]=NULL;
    goal->s[3]=NULL;

    //Defining Start State
    start=(struct statespace *)malloc(sizeof(struct statespace));
    start->cost=0;
    start->mhd=manhatten_distance(matrix);
    for(int i=0;i<3;i++)
    {
    for(int j=0;j<3;j++)
    {
    start->state[i][j]=matrix[i][j];
    }
    }
    start->s[0]=NULL;
    start->s[1]=NULL;
    start->s[2]=NULL;
    start->s[3]=NULL;

    root=start;
    que.push(root);
    solve();
    total_nodes=0;
    //printstate();

}
