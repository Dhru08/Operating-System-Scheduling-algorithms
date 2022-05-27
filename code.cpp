#include "bits/stdc++.h"
using namespace std;

const int N = (int)5e2 + 10;
const int INF = (int)2e18;

int n,m;
int at[N],bt[N],ct[N],tat[N],wt[N],rt[N],gantt[N];

void print(){
    // for(int i = 0;i < n;i++) cout << tat[i] << " \n"[i == n - 1];
    // for(int i = 0;i < n;i++) cout << wt[i] << " \n"[i == n - 1];
    // for(int i = 0;i < n;i++) cout << tat[i] << " \n"[i == n - 1];
    // for(int i = 0;i < n;i++) cout << rt[i] << " \n"[i == n - 1];
    for(int i = 0;i < n;i++) cout << at[i] << ' ' << bt[i] << ' ' << tat[i] << ' ' << wt[i] << ' ' << rt[i] << '\n';
}

double average(int arr[],int n){
    double avg = 0.0;
    for(int i =  0;i < n;i++){
        avg += (double)arr[i];
    }
    avg /= n;
    return avg;
}

double Overall_throughtput(int total_time,int total_process){
    double avg = 0.0;
    avg = (double)total_time/(double)total_process;
    return avg;
}

// int p[n][3];
// p[i][0] = at[i], p[i][1] = bt[i], p[i][2] = pid[i]

void FCFS(){
    cout << "Scheduling According to FCFS :- \n\n";
    
    vector<array<int,3>> p(n);
    for(int i = 0;i < n;i++) p[i] = {at[i],bt[i],i + 1};
    
    // bubble
    // for(int i = 0;i < n;i++){

    // }

    sort(p.begin(), p.end());
    for(int i = 0,t = 0;i < n;){
        if(p[i][0] <= t){
            for(int j = 0;j < p[i][1];j++){
                gantt[t] = p[i][2];
                t++;
            }
            i++;
        }
        else{
            t++;
        }
    }
            
    vector<int> st(n,INF),ed(n,-1);
    for(int i = 0;i < N;i++){
        if(gantt[i] != 0){
            m = i + 1;
            st[gantt[i] - 1] = min(st[gantt[i] - 1],i + 1);
            ed[gantt[i] - 1] = max(ed[gantt[i] - 1],i + 1);
        }
    }
    
    for(int i = 0;i < n;i++){
        ct[i] = ed[i];
        rt[i] = st[i] - at[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    
    cout << "Gantt chart                : "; for(int i = 0;i < m;i++) cout << gantt[i] << " \n"[i == m - 1];
    cout << "Average turnabround time   : " << average(tat,n) << '\n';
    cout << "Average waiting time       : " << average(wt,n) << '\n';
    cout << "Average response time      : " << average(rt,n) << '\n';
    cout << "Overall throughtput        : " << Overall_throughtput(m,n) << '\n';
}

void SJF(){
    cout << "Scheduling According to SJF :- \n\n";
    
    vector<array<int,3>> p(n);
    for(int i = 0;i < n;i++) p[i] = {at[i],bt[i],i + 1};
    sort(p.begin(), p.end());
    
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;
    for(int t = 0,i = 0;i < n || !pq.empty();){
        while(i < n && p[i][0] <= t){
            pq.push({p[i][1],p[i][0],p[i][2]});
            i++;
        }
        
        if(pq.empty()){
            t++;
            continue;
        }
        
        auto [burst,start,idx] = pq.top(); pq.pop();
        for(int j = 0;j < burst;j++){
            gantt[t++] = idx;
        }
    }
    
    vector<int> st(n,INF),ed(n,-1);
    for(int i = 0;i < N;i++){
        if(gantt[i] != 0){
            m = i + 1;
            st[gantt[i] - 1] = min(st[gantt[i] - 1],i + 1);
            ed[gantt[i] - 1] = max(ed[gantt[i] - 1],i + 1);
        }
    }
    
    for(int i = 0;i < n;i++){
        ct[i] = ed[i];
        rt[i] = st[i] - at[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    
    cout << "Gantt chart                : "; for(int i = 0;i < m;i++) cout << gantt[i] << " \n"[i == m - 1];
    cout << "Average turnabround time   : " << average(tat,n) << '\n';
    cout << "Average waiting time       : " << average(wt,n) << '\n';
    cout << "Average response time      : " << average(rt,n) << '\n';
    cout << "Overall throughtput        : " << Overall_throughtput(m,n) << '\n';
}

void SRTF(){
    cout << "Scheduling According to SRTF :- \n\n";
    
    vector<array<int,3>> p(n);
    for(int i = 0;i < n;i++) p[i] = {at[i],bt[i],i + 1};
    
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;
    sort(p.begin(), p.end());
    
    for(int t = 0,i = 0;i < n || !pq.empty();t++){
        while(i < n && p[i][0] <= t){
            pq.push({p[i][1],p[i][0],p[i][2]});
            i++;
        }
        
        if(pq.empty()) continue;
        
        auto [burst,start,idx] = pq.top(); pq.pop();
        gantt[t] = idx;
        
        if(burst > 1){
            pq.push({burst - 1,start,idx});
        }
    }
    
    vector<int> st(n,INF),ed(n,-1);
    for(int i = 0;i < N;i++){
        if(gantt[i] != 0){
            m = i + 1;
            st[gantt[i] - 1] = min(st[gantt[i] - 1],i + 1);
            ed[gantt[i] - 1] = max(ed[gantt[i] - 1],i + 1);
        }
    }
    
    for(int i = 0;i < n;i++){
        ct[i] = ed[i];
        rt[i] = st[i] - at[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    
    cout << "Gantt chart                : "; for(int i = 0;i < m;i++) cout << gantt[i] << " \n"[i == m - 1];
    cout << "Average turnabround time   : " << average(tat,n) << '\n';
    cout << "Average waiting time       : " << average(wt,n) << '\n';
    cout << "Average response time      : " << average(rt,n) << '\n';
    cout << "Overall throughtput        : " << Overall_throughtput(m,n) << '\n';
}

void RR(){
    cout << "Scheduling According to RR :- \n\n";
    
    int time_quanta;
    cout << "Enter the value of time quanta : ";
    cin >> time_quanta;
    cout << '\n';
    
    vector<array<int,3>> p(n);
    for(int i = 0;i < n;i++) p[i] = {at[i],bt[i],i + 1};
    
    queue<array<int,2>> q;
    sort(p.begin(), p.end());
    
    for(int t = 0,i = 0;i < n || !q.empty();){
        while(i < n && p[i][0] <= t){
            q.push({p[i][1],p[i][2]});
            i++;
        }
        
        if(q.empty()){
            t++;
            continue;
        }
        
        auto [burst,idx] = q.front(); q.pop();
        for(int j = 0;j < min(burst,time_quanta);j++){
            gantt[t++] = idx;
        }
        
        while(i < n && p[i][0] <= t){
            q.push({p[i][1],p[i][2]});
            i++;
        }
        
        burst -= time_quanta;
        if(burst > 0){
            q.push({burst,idx});
        }
    }
    
    vector<int> st(n,INF),ed(n,-1);
    for(int i = 0;i < N;i++){
        if(gantt[i] != 0){
            m = i + 1;
            st[gantt[i] - 1] = min(st[gantt[i] - 1],i + 1);
            ed[gantt[i] - 1] = max(ed[gantt[i] - 1],i + 1);
        }
    }
    
    for(int i = 0;i < n;i++){
        ct[i] = ed[i];
        rt[i] = st[i] - at[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    
    cout << "Gantt chart                : "; for(int i = 0;i < m;i++) cout << gantt[i] << " \n"[i == m - 1];
    cout << "Average turnabround time   : " << average(tat,n) << '\n';
    cout << "Average waiting time       : " << average(wt,n) << '\n';
    cout << "Average response time      : " << average(rt,n) << '\n';
    cout << "Overall throughtput        : " << Overall_throughtput(m,n) << '\n'; 
}

void choice(){
    cout << "\nSelect any Scheduling method : \n";
    cout << "1 - FCFS\n";
    cout << "2 - SJF\n";
    cout << "3 - SRTF\n";
    cout << "4 - RR\n";
    cout << "5 - Exit\n\n";
}

void reset(){
    for(int i = 0;i < m;i++){
        gantt[i] = 0;
    }
    m = 0;
}

void read(){
    // string line,str;
    // ifstream myfile ("input.txt");
    // if(myfile.is_open())
    // {
    //     getline(myfile,line);
    //     n = stoi(line);
    //     getline(myfile,line);
    //     for(int i = 0,j = 0,k = 0;j < line.size();j++){
    //         if(line[j] == ' ' || (j == line.size() - 1)){
    //             string temp = line.substr(i,j - i + 1);
    //             while(temp.size() > 0 && !('0' <= temp.back() && temp.back() <= '9')) temp.pop_back();
    //             if(temp.size() > 0) at[k++] = stoi(temp);
    //             i = j + 1;
    //         }
    //     }
    //     getline(myfile,line);
    //     for(int i = 0,j = 0,k = 0;j < line.size();j++){
    //         if(line[j] == ' ' || (j == line.size() - 1)){
    //             string temp = line.substr(i,j - i + 1);
    //             while(temp.size() > 0 && !('0' <= temp.back() && temp.back() <= '9')) temp.pop_back();
    //             if(temp.size() > 0) bt[k++] = stoi(temp);
    //             i = j + 1;
    //         }
    //     }
    //     myfile.close();
    // }
    cin >> n;
    for(int i = 0;i < n;i++) cin >> at[i];
    for(int i = 0;i < n;i++) cin >> bt[i];
}

int main()
{
    read();
        
    bool flag = true;
    while(flag){
        int ch;
        choice();
        cin >> ch;
        
        switch(ch){
            case 1:
                FCFS();
                break;
            case 2:
                SJF();
                break;
            case 3:
                SRTF();
                break;
            case 4:
                RR();
                break;
            case 5:
                flag = false;
                break;
        }
        // print();
        reset();
    }
    return 0;
}