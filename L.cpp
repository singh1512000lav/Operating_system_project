
	#include <bits/stdc++.h>
	using namespace std;

	struct Process_Data
	{
	int Num;
	int ID;
	int ARI_time;
	int BUR_time;
	int Priority;
	int FINISH_time;
	int Remaining_time;
	int WAIT_time;
	int START_time;
	int Responce_time;

	};

	struct Process_Data cur;
	typedef struct Process_Data pr_da ;

	bool idsort(const pr_da& x , const pr_da& y)
	{
	return x.ID < y.ID;
	}
	/** base of arrival_time **/
	bool arrivalsort( const pr_da& x ,const pr_da& y)
	{
	if(x.ARI_time < y.ARI_time)
	return true;
	else if(x.ARI_time > y.ARI_time)
	return false;
	if(x.Priority < y.Priority)
	return true;
	else if(x.Priority > y.Priority)
	return false;
	if(x.ID < y.ID)
	return true;

	return false;
	}


	bool Numsort( const pr_da& x ,const pr_da& y)
	{
	return x.Num < y.Num;
	}

	/* base of Priority if that same then on the base of ID*/

	struct comPare
    {
	bool operator()(const pr_da& x ,const pr_da& y)
	{
	if( x.Priority > y.Priority )
	return true;
	else if( x.Priority < y.Priority )
	return false;
	if( x.ID > y.ID )
	return true;

	return false;

	}

	};

	/**To check the Input **/
	void my_check(vector<pr_da> mv)
	{
	for(unsigned int t= 0; t < mv.size() ;t++)
	{
	cout<<" ID :"<<mv[t].ID<<" _time : "<<mv[t].ARI_time<<" BUR_time : "<<mv[t].BUR_time<<" Priority : "<<mv[t].Priority<<endl;
	}

	}

	int main()
	{
	int i;
	vector< pr_da > input;
	vector<pr_da> input_copy;
	pr_da temp;
	int pq_process = 0;
	int rq_process = 0;
	int ARI_time;
	int BUR_time;
	int ID;
	int Priority;
	int n;
	int clock;
	int total_exectiontime = 0;
	cout<<"\n** Enter the number of processes :  ";
	cin>>n;
	int j=1;
	for( i= 0; i< n; i++ )
	{

    cout<<"\n\nEnter details of process ["<<j<<"] :";
    cout<<"\n\n-Arrival Time :- ";
	cin>>ARI_time;
	cout<<"-Burst Time :- ";
	cin>>BUR_time;
	cout<<"-Priority :- ";
	cin>>Priority;
	temp.Num = i+1;
	temp.ARI_time = ARI_time;
	temp.BUR_time = BUR_time;
	temp.Remaining_time = BUR_time;
	temp.ID = j;
	temp.Priority = Priority;
	input.push_back(temp);
	j=j+1;
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );

	total_exectiontime = total_exectiontime + input[0].ARI_time;
	for( i= 0 ;i< n; i++ )
	{
	if( total_exectiontime >= input[i].ARI_time )
	{
	total_exectiontime = total_exectiontime +input[i].BUR_time;
	}
	else
	{
	int diff = (input[i].ARI_time - total_exectiontime);
	total_exectiontime = total_exectiontime + diff + BUR_time;

	}
	}

	int Ghant[total_exectiontime]={0};
	for( i= 0; i< total_exectiontime; i++ )
	{
	Ghant[i]=-1;
	}


	priority_queue < pr_da ,vector<Process_Data> ,comPare> pq;
	queue< pr_da > rq;
	int cpu_state = 0;
	int quantum = 4 ;
	cur.ID = -2;
	cur.Priority = 999999;

	for ( clock = 0; clock< total_exectiontime; clock++ )
	{
	/**Insert the process with same Arrival time in Priority Queue**/
	for( int j = 0; j< n ; j++ )
	{
	if(clock == input[j].ARI_time)
	{
	pq.push(input[j]);
	}
	}


	if(cpu_state == 0)
	{
	if(!pq.empty())
	{
	cur = pq.top();
	cpu_state = 1;
	pq_process = 1;
	pq.pop();
	quantum = 4;
	}
	else if(!rq.empty())
	{
	cur = rq.front();
	cpu_state = 1;
	rq_process = 1;
	rq.pop();
	quantum = 4;
	}
	}
	else if(cpu_state == 1)
	{
	if(pq_process == 1 && (!pq.empty()))
	{
	if(pq.top().Priority < cur.Priority )
	{
	rq.push(cur);
	cur = pq.top();
	pq.pop();
	quantum = 4;
	}
	}
	else if(rq_process == 1 && (!pq.empty()))
	{
	rq.push(cur);
	cur = pq.top();
	pq.pop();
	rq_process = 0;
	pq_process = 1;
	quantum = 4 ;
	}


	}


	if(cur.ID != -2)
	{
	cur.Remaining_time--;
	quantum--;
	Ghant[clock] = cur.ID;
	if(cur.Remaining_time == 0)
	{
	cpu_state = 0 ;
	quantum = 4 ;
	cur.ID = -2;
	cur.Priority = 999999;
	rq_process = 0;
	pq_process = 0;
	}

	else if(quantum == 0 )
	{
	rq.push(cur);
	cur.ID = -2;
	cur.Priority = 999999;
	rq_process = 0;
	pq_process = 0;
	cpu_state=0;

	}

	}

	}


	sort( input.begin(), input.end(), idsort );

	for(int i=0;i<n;i++)
	{
	for(int k=total_exectiontime;k>=0;k--)
	{
	if(Ghant[k]==i+1)
	{
	input[i].FINISH_time=k+1;
	break;

	}
	}
	}
	for(int i=0;i<n;i++)
	{
	for(int k=0;k<total_exectiontime;k++)
	{

	if(Ghant[k]==i+1)
	{
	input[i].START_time=k;
	break;
	}
	}
	}

	sort( input.begin(), input.end(), Numsort );

	for(int i=0;i<n;i++)
	{
	input[i].Responce_time=input[i].START_time-input[i].ARI_time;
	input[i].WAIT_time=(input[i].FINISH_time-input[i].ARI_time)-input[i].BUR_time;

	}
    cout<<"\n\n\n\n** Now Processes According to Priority given in Problem **";
    cout<<"\n\n----------------------------------------------------------\n";
    cout<<"   process   Responce_time   Finish_time   Waiting_time  \n";
    cout<<"----------------------------------------------------------\n";
	for(int i=0;i<n;i++)
	{

	cout<<"     "<<input[i].ID<<"           "<<input[i].Responce_time<<"               "<<input[i].FINISH_time<<"            "<<input[i].WAIT_time<<endl;

	}
	cout<<"----------------------------------------------------------\n\n\n\n";
	return 0;
	}
