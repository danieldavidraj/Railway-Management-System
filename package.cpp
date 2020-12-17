#include<iostream>
#include<string>
using namespace std;
class Train
{
    public:
    int station;
    string time;
    Train *next;
};
class Station
{
    public:
    int train;
    string time;
    Station *next;
};
class System
{
    public:
    Train *train;
    Station *station;
    int number;
};
bool Check(Train *data,Station *station,int i)
{
    Station *current;
    current=station;
    while(current!=NULL && current->time!=data->time)
    {
        current=current->next;
    }
    if(current==NULL)
    {
        return true;
    }
    else
    {
        if(i==current->train)
        {
            cout<<"Repeated Entry\n";
        }
        else
        {
            cout<<"Train "<<i<<" will collide with Train "<<current->train<<"!!!\n";
            return false;
        }
    }
}
Station* EnterDataStation(Train *data,Station *station,int i)
{
    Station *data1,*current;
    data1=new Station;
    data1->train=i;
    data1->time=data->time;
    data1->next=NULL;
    if(station==NULL)
    {
        station=data1;
    }
    else
    {
        current=station;
        while(current->next!=NULL)
        {
            current=current->next;
        }
        current->next=data1;
    }
    return station;
}
System* EnterDataTrain(Train *train,Station **station,int i)
{
    Train *data,*current;
    data=new Train;
 l2:cout<<"Enter the station:";
    cin>>data->station;
 l3:cin.sync();
    cout<<"Enter the time:";
    getline(cin,data->time);
    if(data->time[0]<'0' || data->time[0]>'2' ||
       data->time[1]<'0' || data->time[1]>'9' || (data->time[0]=='2' && data->time[1]>'4') ||
       data->time[2]!=':' ||
       data->time[3]<'0' || data->time[3]>'6' ||
       data->time[4]<'0' || data->time[4]>'9' || (data->time[3]=='6' && data->time[4]!='0') )
    {
        cout<<"Please Enter correct time format\n";
        goto l3;
    }
    data->next=NULL;
    if( Check(data,station[data->station],i) != true)
    {
        goto l2;
    }
    station[data->station]=EnterDataStation(data,station[data->station],i);
    if(train==NULL)
    {
        train=data;
    }
    else
    {
        current=train;
        while(current->next!=NULL)
        {
            current=current->next;
        }
        current->next=data;
    }
    System *system=new System;
    system->train=train;
    system->station=station[data->station];
    system->number=data->station;
    return system;
}
Station* RemoveDataStation(Train *data,Station *station,int i)
{
    Station *data1,*current,*prev;
    data1=new Station;
    data1->train=i;
    data1->time=data->time;
    current=station;
    prev=station;
    while(current!=NULL && (current->train!=data1->train || current->time!=data1->time) )
    {
        prev=current;
        current=current->next;
    }
    if(current->next==NULL && current==station)
    {
        station=NULL;
    }
    else if(current==station)
    {
        station=current->next;
    }
    else if(current->next==NULL)
    {
        prev->next=NULL;
    }
    else
    {
        prev->next=current->next;
    }
    return station;
}
System* RemoveDataTrain(Train *train,Station **station,int i)
{
    Train *data,*current,*prev;
    data=new Train;
 l3:cout<<"Enter the station:";
    cin>>data->station;
    cout<<"Enter the time:";
    cin>>data->time;
    current=train;
    prev=train;
    while( current!=NULL && (current->station!=data->station || current->time!=data->time) )
    {
        prev=current;
        current=current->next;
    }
    if(current==NULL)
    {
        cout<<"No such entry\n";
        goto l3;
    }
    else
    {
        station[data->station]=RemoveDataStation(data,station[data->station],i);
        if(current->next==NULL && current==train)
        {
            train=NULL;
        }
        else if(current==train)
        {
            train=current->next;
        }
        else if(current->next==NULL)
        {
            prev->next=NULL;
        }
        else
        {
            prev->next=current->next;
        }
    }
    System *system=new System;
    system->train=train;
    system->station=station[data->station];
    system->number=data->station;
    return system;
}
void DisplayTrain(Train *train)
{
    if(train==NULL)
    {
        cout<<"Nothing to display\n\n";
    }
    else
    {
        while(train!=NULL)
        {
            cout<<"Station "<<train->station<<"\t\t"<<"Time:"<<train->time<<endl;
            cout<<"   ||\n   \\/\n";
            train=train->next;
        }
    }
}
void DisplayStation(Station *station)
{
    if(station==NULL)
    {
        cout<<"Nothing to display\n\n";
    }
    else
    {
        while(station!=NULL)
        {
            cout<<"Train "<<station->train<<"\t\t"<<"Time:"<<station->time<<endl<<endl;
            station=station->next;
        }
    }
}
void Transit(Train **train)
{
    int from,to;
    int f=0;
    cout<<"From Station:";
    cin>>from;
    cout<<"To Station:";
    cin>>to;
    int i;
    Train *current,*current1;
    for(i=1;i<=10;i++)
    {
        current=train[i];
        while(current!=NULL)
        {
            if(current->station==from)
            {
                current1=current;
                while(current1!=NULL)
                {
                    if(current1->station==to)
                    {
                        f=1;
                        cout<<"\nTrain "<<i<<endl;
                        while(current!=current1)
                        {
                            cout<<"Station "<<current->station<<"\t\t"<<"Time:"<<current->time<<endl;
                            cout<<"   ||\n   \\/\n";
                            current=current->next;
                        }
                        cout<<"Station "<<current->station<<"\t\t"<<"Time:"<<current->time<<endl;
                    }
                    current1=current1->next;
                }
            }
            current=current->next;
        }
    }
    if(!f)
    {
        cout<<"No Trains available\n";
    }
    cout<<endl;
}
void Tracker(Train **train,string time)
{
    int i;
    Train *current,*pre;
    for(i=1;i<=10;i++)
    {
        current=train[i];
        pre=train[i];
        if(current!=NULL)
        {
            if(current->time>time)
            {
                cout<<"Train "<<i<<" hasn't started it's journey yet\n";
            }
            else
            {
                while(current!=NULL)
                {
                    if(current->time==time)
                    {
                        cout<<"Train "<<i<<" at Station "<<current->station<<endl;
                        break;
                    }
                    else if(current->time>time)
                    {
                        cout<<"Train "<<i<<" departed from Station "<<pre->station<<endl;
                        break;
                    }
                    pre=current;
                    current=current->next;
                }
                if(current==NULL)
                {
                    cout<<"Train "<<i<<" has completed it's journey\n";
                }
            }
        }
    }
    cout<<endl;
}
int main()
{
    int i,n;
    System *system;
    Train *train[11];
    Station *station[11];
    for(i=0;i<=10;i++)
    {
        train[i]=NULL;
        station[i]=NULL;
    }
    cout<<"\n\t\tR A I L W A Y  M A N A G E M E N T  S Y S T E M\n\n";
 l1:cout<<"1)Enter Train Route"<<endl;
    cout<<"2)Remove Train Route"<<endl;
    cout<<"3)View Train Route"<<endl;
    cout<<"4)View details of Station"<<endl;
    cout<<"5)Transit Stations Finder"<<endl;
    cout<<"6)Train Tracker"<<endl;
    cin>>n;
    if(n==1)
    {
        cout<<"Enter train number:";
        cin>>i;
        system=EnterDataTrain(train[i],station,i);
        train[i]=system->train;
        station[system->number]=system->station;
        goto l1;
    }
    else if(n==2)
    {
        cout<<"Enter train number:";
        cin>>i;
        system=RemoveDataTrain(train[i],station,i);
        train[i]=system->train;
        station[system->number]=system->station;
        goto l1;
    }
    else if(n==3)
    {
        cout<<"Enter train number:";
        cin>>i;
        DisplayTrain(train[i]);
        goto l1;
    }
    else if(n==4)
    {
        cout<<"Enter station number:";
        cin>>i;
        DisplayStation(station[i]);
        goto l1;
    }
    else if(n==5)
    {
        Transit(train);
        goto l1;
    }
    else if(n==6)
    {
        cin.sync();
        string time;
        cout<<"Enter the time:";
        getline(cin,time);
        Tracker(train,time);
        goto l1;
    }
}
