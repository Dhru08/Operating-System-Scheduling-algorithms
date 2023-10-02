#include <bits/stdc++.h>
using namespace std;

const int N = (int)5e2 + 10;
const int INF = (int)2e18;

int n, m; // n: number of processes, m: length of Gantt chart
int at[N], bt[N], ct[N], tat[N], wt[N], rt[N], gantt[N];

// Function to print various metrics
void print()
{
	// Print turnaround time, waiting time, response time, and details for each process
	for (int i = 0; i < n; i++)
	{
		cout << "Turnaround Time for Process " << i + 1 << ": " << tat[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "Waiting Time for Process " << i + 1 << ": " << wt[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "Response Time for Process " << i + 1 << ": " << rt[i] << endl;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "Arrival Time: " << at[i] << " Burst Time: " << bt[i] << " Turnaround Time: " << tat[i] << " Waiting Time: " << wt[i] << " Response Time: " << rt[i] << '\n';
	}
}

// Function to calculate the average of an array
double average(int arr[], int n)
{
	double avg = 0.0;
	for (int i = 0; i < n; i++)
	{
		avg += (double)arr[i];
	}
	avg /= n;
	return avg;
}

// Function to calculate overall throughput
double Overall_throughtput(int total_time, int total_process)
{
	double avg = 0.0;
	avg = (double)total_time / (double)total_process;
	return avg;
}

// FCFS Scheduling Algorithm
void FCFS()
{
	cout << "Scheduling According to FCFS :- \n\n";

	// Create a vector of processes with arrival time, burst time, and process ID
	vector<array<int, 3>> p(n);
	for (int i = 0; i < n; i++)
	{
		p[i] = {at[i], bt[i], i + 1};
	}

	// Sort processes based on arrival time
	sort(p.begin(), p.end());

	// Initialize time and process index
	for (int i = 0, t = 0; i < n;)
	{
		if (p[i][0] <= t)
		{
			for (int j = 0; j < p[i][1]; j++)
			{
				gantt[t] = p[i][2];
				t++;
			}
			i++;
		}
		else
		{
			t++;
		}
	}

	// Calculate start and end times for each process
	vector<int> st(n, INF), ed(n, -1);
	for (int i = 0; i < N; i++)
	{
		if (gantt[i] != 0)
		{
			m = i + 1;
			st[gantt[i] - 1] = min(st[gantt[i] - 1], i + 1);
			ed[gantt[i] - 1] = max(ed[gantt[i] - 1], i + 1);
		}
	}

	// Calculate turnaround time, waiting time, and response time
	for (int i = 0; i < n; i++)
	{
		ct[i] = ed[i];
		rt[i] = st[i] - at[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	// Display scheduling results
	cout << "Gantt chart                : ";
	for (int i = 0; i < m; i++)
	{
		cout << gantt[i] << " \n"[i == m - 1];
	}
	cout << "Average turnabround time   : " << average(tat, n) << '\n';
	cout << "Average waiting time       : " << average(wt, n) << '\n';
	cout << "Average response time      : " << average(rt, n) << '\n';
	cout << "Overall throughtput        : " << Overall_throughtput(m, n) << '\n';
}

// SJF Scheduling Algorithm
void SJF()
{
	cout << "Scheduling According to SJF :- \n\n";

	// Create a vector of processes with arrival time, burst time, and process ID
	vector<array<int, 3>> p(n);
	for (int i = 0; i < n; i++)
	{
		p[i] = {at[i], bt[i], i + 1};
	}

	// Sort processes based on burst time
	sort(p.begin(), p.end(), [](const array<int, 3> &a, const array<int, 3> &b)
		 { return a[1] < b[1]; });

	// Priority queue to handle the shortest job
	priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;

	for (int t = 0, i = 0; i < n || !pq.empty();)
	{
		while (i < n && p[i][0] <= t)
		{
			pq.push({p[i][1], p[i][0], p[i][2]});
			i++;
		}

		if (pq.empty())
		{
			t++;
			continue;
		}

		auto [burst, start, idx] = pq.top();
		pq.pop();

		// Add the process to the Gantt chart
		for (int j = 0; j < burst; j++)
		{
			gantt[t++] = idx;
		}
	}

	// Calculate start and end times for each process
	vector<int> st(n, INF), ed(n, -1);
	for (int i = 0; i < N; i++)
	{
		if (gantt[i] != 0)
		{
			m = i + 1;
			st[gantt[i] - 1] = min(st[gantt[i] - 1], i + 1);
			ed[gantt[i] - 1] = max(ed[gantt[i] - 1], i + 1);
		}
	}

	// Calculate turnaround time, waiting time, and response time
	for (int i = 0; i < n; i++)
	{
		ct[i] = ed[i];
		rt[i] = st[i] - at[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	// Display scheduling results
	cout << "Gantt chart                : ";
	for (int i = 0; i < m; i++)
	{
		cout << gantt[i] << " \n"[i == m - 1];
	}
	cout << "Average turnabround time   : " << average(tat, n) << '\n';
	cout << "Average waiting time       : " << average(wt, n) << '\n';
	cout << "Average response time      : " << average(rt, n) << '\n';
	cout << "Overall throughtput        : " << Overall_throughtput(m, n) << '\n';
}

// SRTF Scheduling Algorithm
void SRTF()
{
	cout << "Scheduling According to SRTF :- \n\n";

	// Create a vector of processes with arrival time, burst time, and process ID
	vector<array<int, 3>> p(n);
	for (int i = 0; i < n; i++)
	{
		p[i] = {at[i], bt[i], i + 1};
	}

	// Sort processes based on arrival time
	sort(p.begin(), p.end());

	// Priority queue to handle the shortest remaining time
	priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;

	for (int t = 0, i = 0; i < n || !pq.empty(); t++)
	{
		while (i < n && p[i][0] <= t)
		{
			pq.push({p[i][1], p[i][0], p[i][2]});
			i++;
		}

		if (pq.empty())
			continue;

		auto [burst, start, idx] = pq.top();
		pq.pop();

		// Add the process to the Gantt chart
		gantt[t] = idx;

		if (burst > 1)
		{
			pq.push({burst - 1, start, idx});
		}
	}

	// Calculate start and end times for each process
	vector<int> st(n, INF), ed(n, -1);
	for (int i = 0; i < N; i++)
	{
		if (gantt[i] != 0)
		{
			m = i + 1;
			st[gantt[i] - 1] = min(st[gantt[i] - 1], i + 1);
			ed[gantt[i] - 1] = max(ed[gantt[i] - 1], i + 1);
		}
	}

	// Calculate turnaround time, waiting time, and response time
	for (int i = 0; i < n; i++)
	{
		ct[i] = ed[i];
		rt[i] = st[i] - at[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	// Display scheduling results
	cout << "Gantt chart                : ";
	for (int i = 0; i < m; i++)
	{
		cout << gantt[i] << " \n"[i == m - 1];
	}
	cout << "Average turnabround time   : " << average(tat, n) << '\n';
	cout << "Average waiting time       : " << average(wt, n) << '\n';
	cout << "Average response time      : " << average(rt, n) << '\n';
	cout << "Overall throughtput        : " << Overall_throughtput(m, n) << '\n';
}

// RR Scheduling Algorithm
void RR()
{
	cout << "Scheduling According to RR :- \n\n";

	int time_quanta;
	cout << "Enter the value of time quanta: ";
	cin >> time_quanta;
	cout << '\n';

	// Create a vector of processes with arrival time, burst time, and process ID
	vector<array<int, 3>> p(n);
	for (int i = 0; i < n; i++)
	{
		p[i] = {at[i], bt[i], i + 1};
	}

	// Sort processes based on arrival time
	sort(p.begin(), p.end());

	// Queue to handle the Round Robin scheduling
	queue<array<int, 2>> q;

	for (int t = 0, i = 0; i < n || !q.empty();)
	{
		while (i < n && p[i][0] <= t)
		{
			q.push({p[i][1], p[i][2]});
			i++;
		}

		if (q.empty())
		{
			t++;
			continue;
		}

		auto [burst, idx] = q.front();
		q.pop();

		// Add the process to the Gantt chart
		for (int j = 0; j < min(burst, time_quanta); j++)
		{
			gantt[t++] = idx;
		}

		while (i < n && p[i][0] <= t)
		{
			q.push({p[i][1], p[i][2]});
			i++;
		}

		burst -= time_quanta;
		if (burst > 0)
		{
			q.push({burst, idx});
		}
	}

	// Calculate start and end times for each process
	vector<int> st(n, INF), ed(n, -1);
	for (int i = 0; i < N; i++)
	{
		if (gantt[i] != 0)
		{
			m = i + 1;
			st[gantt[i] - 1] = min(st[gantt[i] - 1], i + 1);
			ed[gantt[i] - 1] = max(ed[gantt[i] - 1], i + 1);
		}
	}

	// Calculate turnaround time, waiting time, and response time
	for (int i = 0; i < n; i++)
	{
		ct[i] = ed[i];
		rt[i] = st[i] - at[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	// Display scheduling results
	cout << "Gantt chart                : ";
	for (int i = 0; i < m; i++)
	{
		cout << gantt[i] << " \n"[i == m - 1];
	}
	cout << "Average turnabround time   : " << average(tat, n) << '\n';
	cout << "Average waiting time       : " << average(wt, n) << '\n';
	cout << "Average response time      : " << average(rt, n) << '\n';
	cout << "Overall throughtput        : " << Overall_throughtput(m, n) << '\n';
}

// Function to display the choice menu
void choice()
{
	cout << "\nSelect a Scheduling method: \n";
	cout << "1 - FCFS\n";
	cout << "2 - SJF\n";
	cout << "3 - SRTF\n";
	cout << "4 - RR\n";
	cout << "5 - Exit\n\n";
}

// Function to reset the Gantt chart and process counters
void reset()
{
	for (int i = 0; i < m; i++)
	{
		gantt[i] = 0;
	}
	m = 0;
}

// Function to read input
void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> at[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> bt[i];
	}
}

int main()
{
	read();

	bool flag = true;
	while (flag)
	{
		int ch;
		choice();
		cin >> ch;

		switch (ch)
		{
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
		reset();
	}
	return 0;
}
