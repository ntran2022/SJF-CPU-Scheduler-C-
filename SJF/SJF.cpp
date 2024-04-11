/*
Nhat-Huy Tran
10-21-2023
COP4106
CPU Scheduling Programming Assignment - FCFS Algorithm
*/

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Process                                                             //Each object under Process will have their own data stored.  I.e. CPU Burst, Arrival time, etc.
{
    public:
        void setID(Process P[], int count);                               //Sets ID for each Process in the class array
        void getBursts(Process P[], int count);                           //User input for each Process's CPU and IO Burst arrays.
        void SJF(Process P[], int count);                                 //Main function of SJF.
        void sortProcess(Process P[], int count);                         //Sorts Class array elements in order of updated CPU Bursts.
        void setArrival(Process P[], int ID);                             //Sets and Updates the arrival time.
        void check(Process P[], int ID);                                  //Checks the CPU and I/O Burst inputs to see if a process is complete.
        void firstSort(Process P[], int count);                           //Sorts the process in ascending order by CPU Burst time at the start.
        void sortID(Process P[], int count);                              //Sorts Class array elements in order of Process ID for results output.
        void endProcess(Process P[], int count);                          //Ends the loop and displays the results after all processes in the array are completed.
        void idleCheck(Process P[], int count);                           //Checks if there are no available processes in the ready queue.
        void waitCheck(Process P[], int count);                           //Checks if the process is in the waiting queue during I/O Burst or if the execution time has arrived after the burst.
        void calculateTurnaround(Process P[], int count);                 //Calculates turnaround time for each process and average.
        void calculateWaiting(Process P[], int count);                    //Calculates Waiting time for each process and average.
        void calculateResponse(Process P[], int count);                   //Gets response time for each process and average.
        void getNextBurst(Process P[], int count);                        //Gets the next lowest burst for SJF.
        void ZeroSort(Process P[], int count);                            //Sorts out any completed process out of the loop.
    private:
        int CPUBurst[10];
        int IOBurst[10];
        int arrival=0;
        int num;
        int firstArrive=0;
        int totalBurst=0;
        int complete=0;
        int waitQueue=0;
        int waiting;
        int turnaround;
        int response;
        int responseCheck=0;
        int CPUincre=0;
};

int completeCount=0;                                     //Keeps track of how many process are completed.
int minBurst;                                                  //Stores the next burst.
int exeTime=0, idleTime=0;                                      //Execution time and Idle time for algorithm.
double AVGresponse, AVGturnaround, AVGwaiting;                  //Averages of Turnaround, Waiting, and Response time.

int main()
{
    cout << "Welcome to the Shortest-Job-First (SJF) Simulation!\n\n";
    Process P[8];
    P[8].setID(P, 8);
    P[8].getBursts(P,8);
    P[8].firstSort(P, 8);
    P[8].SJF(P,8);

// Data used:
//    P1 5 3 5 4 6 4 3 4 0 0
//       27 31 43 18 22 26 24 0 0 0
//    P2 4 5 7 12 9 4 9 7 8 0
//       48 44 42 37 76 41 31 43 0 0
//    P3 8 12 18 14 4 15 14 5 6 0
//       33 41 65 21 61 18 26 31 0 0
//    P4 3 4 5 3 4 5 6 5 3 0
//       35 41 45 51 61 54 82 77 0 0
//    P5 16 17 5 16 7 13 11 6 3 4
//       24 21 36 26 31 28 21 13 11 0
//    P6 11 4 5 6 7 9 12 15 8 0
//       22 8 10 12 14 18 24 30 0 0
//    P7 14 17 11 15 4 7 16 10 0 0
//       46 41 42 21 32 19 33 0 0 0
//    P8 4 5 6 14 16 6 0 0 0 0
//       14 33 51 73 87 0 0 0 0 0

}

//Sets ID for Processes in the class array
void Process::setID(Process P[], int count)
{
    for(int i=0; i<count; i++)
    {
        P[i].num = i+1;
    }
}

//User input for each Process's CPU and IO Burst arrays.
void Process::getBursts(Process P[], int count)
{
    for (int i=0; i<count; i++)
    {
        cout << "Enter the CPU Bursts for Process #" << P[i].num << ": ";
        for (int j=0; j<10; j++)
        {
            cin >> P[i].CPUBurst[j];

        }
        cout << "Enter the IO Bursts for Process #" << P[i].num << ": ";
        for (int j=0; j<10; j++)
        {
            cin >> P[i].IOBurst[j];
        }
    }
    cout << "\nGREAT!\n";
}

//Main function of SJF.
void Process::SJF(Process P[], int count)
{
    for (int i=0; i<count; i++)
    {
        if (P[i].complete == 1)
        {
            continue;
        }
        else
        {
            idleCheck(P,8);
            waitCheck(P,8);
            getNextBurst(P,8);
            if(P[i].waitQueue==0)
            {
                if((P[i].arrival <= exeTime)||(P[i].CPUBurst[P[i].CPUincre] <= minBurst))
                {
                    if(P[i].CPUBurst[P[i].CPUincre] <= minBurst)
                    {
                        sortProcess(P, i);
                        cout << "Process #" << P[i].num << " is set to arrive at " << P[i].arrival << endl;
                        cout << "Current CPU Burst for Process #" << P[i].num << ": " << P[i].CPUBurst[P[i].CPUincre] << endl;
                        cout << "Current IO Burst for Process #" << P[i].num << ": " << P[i].IOBurst[P[i].CPUincre] << endl;
                        check(P,i);
                        cout << "\n";
                        endProcess(P,8);
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }
    sortProcess(P, 8);

    P[8].SJF(P,8);

}

//Ends the loop and displays the results after all processes in the array are completed.
void Process::endProcess(Process P[], int count)
{
    if (completeCount == 8)                                     //If all processes are completed, Prints out results for turnaround, waiting, response, and CPU Utilization
    {
        cout << "RESULTS:\n";
        cout << "______________________________________________________\n";
        cout << "\nTotal Execution time: " << exeTime << " units.\n";                       //Prints Total execution time to complete the algorithm.
        cout << "Total Idle time: " << idleTime << " units.\n";                         //Prints Total idle time between processes.

        double AVGcpu = exeTime-idleTime;                                           //Calculates CPU Utilization in the program.
        AVGcpu = AVGcpu/double(exeTime);
        AVGcpu = AVGcpu*100;

        sortID(P, 8);                                                                   //Sorts Processes in ascending order based on Process ID.

        cout << "CPU Utilization: " << fixed << setprecision(2) << AVGcpu << "%\n";

        cout << "\nTurnaround time results:\n" << "__________________________________\n";
        calculateTurnaround(P,8);                                                                       //Prints turnaround time for each process and average turnaround time.
        cout << "\nAverage turnaround time: " << fixed << setprecision(2) << AVGturnaround << "\n";

        cout << "\nWaiting time results:\n" << "__________________________________\n";
        calculateWaiting(P,8);                                                                      //Prints waiting time for each process and average waiting time.
        cout << "\nAverage waiting time: " << fixed << setprecision(2) << AVGwaiting << "\n";

        cout << "\nResponse time results:\n" << "__________________________________\n";
        calculateResponse(P,8);                                                                         //Prints response time for each process and average response time.
        cout << "\nAverage response time: " << fixed << setprecision(2) << AVGresponse << "\n";

        exit(1);                                                                                    //Ends program.
    }
}

//Sets and Updates the arrival time.
void Process::setArrival(Process P[], int ID)
{
    P[ID].arrival = P[ID].IOBurst[P[ID].CPUincre] + P[ID].CPUBurst[P[ID].CPUincre] + exeTime;
    exeTime = exeTime + P[ID].CPUBurst[P[ID].CPUincre];
    P[ID].CPUincre++;
}

//Checks the CPU and I/O Burst inputs to see if a process is complete.
void Process::check(Process P[], int ID)
{
    P[ID].totalBurst = P[ID].totalBurst + P[ID].CPUBurst[P[ID].CPUincre] + P[ID].IOBurst[P[ID].CPUincre];          //Updates the combined number of used CPU and IO bursts for each process.  Important for waiting time calculation.

    if(P[ID].responseCheck==0)
    {
        P[ID].response = exeTime;
        P[ID].responseCheck=1;
    }

    if (P[ID].IOBurst[P[ID].CPUincre]==0)                                                          //0 units for IO bursts completes the process as it recognizes the last CPU burst.
    {
        P[ID].complete = 1;
        exeTime = exeTime + P[ID].CPUBurst[P[ID].CPUincre];
        P[ID].turnaround = exeTime - P[ID].firstArrive;                                     //Calculates turnaround time based on execution time - arrival time.
        cout << "Process #" << P[ID].num  << " is completed at " << exeTime << " units\n";    //Prints the completion time for each process.
        completeCount++;
        cout << "Number of Processes complete: " << completeCount << endl;
    }
    else
    {
        setArrival(P, ID);                                                          //If the process has not ended, update arrival time.
    }
    cout << "\nCurrent execution time: " << exeTime << endl;                    //Displays the current execution time for the algorithm.
}

//Sorts the process in ascending order by CPU Burst time at the start.
void Process::firstSort(Process P[], int count)
{
    for(int i=0; i<count; i++)                                      //Bubble sort for the class array.
    {
        for(int j=0; j<count-i-1; j++)
        {
            if(P[j].CPUBurst[P[j].CPUincre] > P[j+1].CPUBurst[P[j+1].CPUincre])                       //Sorts processes in ascending order based on CPU Burst.
            {
                std::swap(P[j], P[j+1]);
            }
            else if (P[j].CPUBurst[P[j].CPUincre] == P[j+1].CPUBurst[P[j+1].CPUincre])                //In a situation where two processes have the same CPU Burst and arrival time, the class array is sorted based on process ID.
            {
                if (P[j].num > P[j+1].num)
                {
                    std::swap(P[j], P[j+1]);
                }
                else if (P[j].arrival > P[j+1].arrival)
                {
                    std::swap(P[j], P[j+1]);
                }
            }
        }
    }
}

//Sorts Class array elements in order of updated CPU Bursts.
void Process::sortProcess(Process P[], int count)
{
    for(int i=0; i<count; i++)                                      //Bubble sort for the class array.
    {
        for(int j=0; j<count-i-1; j++)
        {
                if(P[j].CPUBurst[P[j].CPUincre] > P[j+1].CPUBurst[P[j+1].CPUincre])                       //Sorts processes in ascending order based on arrival time.
                {
                    std::swap(P[j], P[j+1]);
                }
                else if (P[j].CPUBurst[P[j].CPUincre] == P[j+1].CPUBurst[P[j+1].CPUincre])                //In a situation where two processes have the same arrival time, the class array is sorted based on process ID.
                {
                    if (P[j].arrival == P[j+1].arrival)
                    {
                        if(P[j].num > P[j+1].num)
                        {
                            std::swap(P[j], P[j+1]);
                        }
                    }
                    else if (P[j].arrival > P[j+1].arrival)
                    {
                        std::swap(P[j], P[j+1]);
                    }
                }
        }
    }
}

//Sorts Class array elements in order of Process ID for results output.
void Process::sortID(Process P[], int count)
{
    for(int i=0; i<count; i++)                              //Bubble sort for sorting class array.
    {
        for(int j=0; j<count-i-1; j++)
        {
            if(P[j].num > P[j+1].num)
            {
                std::swap(P[j], P[j+1]);
            }
        }
    }
}

//Assigns the next minimum CPU Burst time of the updated class array.
void Process::getNextBurst(Process P[], int count)
{
    for(int i=0; i<count; i++)
    {
        if(P[i].complete != 1)                                  //If a process is not complete, proceed.
        {
            minBurst = P[i].CPUBurst[P[i].CPUincre];
        }
        else                                                    //If completed then skip element.
        {
            continue;
        }
    }

    for(int i=0; i<count; i++)
    {
        if(P[i].arrival <= exeTime)
        {
            if(P[i].CPUBurst[P[i].CPUincre] < minBurst)
            {
                if(P[i].complete != 1)
                {
                    minBurst = P[i].CPUBurst[P[i].CPUincre];
                }
                else
                {
                    continue;               //if process is completed, skip the element.
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
}

//Check if the process is in the wait queue or waiting for execution time.
void Process::waitCheck(Process P[], int count)
{
    for(int i=0; i<count; i++)                              //Scans the list to check which processes are in ready queue or not.
    {
        if(exeTime < P[i].arrival)
        {
            P[i].waitQueue=1;                              //Goes into Waiting queue.
        }
        else
        {
            P[i].waitQueue=0;                              //Returns to Ready queue.
        }
    }
}

//Checks if there are no processes in the ready queue.
void Process::idleCheck(Process P[], int count)
{
    int waitCount=0, cCount=0;
    for(int i=0; i<count; i++)
    {
        if(P[i].complete != 1)
        {
            if(P[i].waitQueue==1)
            {
                waitCount++;                        //Counts which processes are in waiting queue.
            }
            else
            {
                continue;
            }
        }
        else
        {
            cCount++;                           //Counts which processes are completed.
        }
    }

    if(waitCount == (8-cCount))                       //Remaining processes that are not in ready queue, and the algorithm goes into idle.
    {
        exeTime++;
        idleTime++;
        cout << "The Algorithm is Idle at execution time: " << exeTime << " units.\n";
    }
}

//Prints response time for each process and calculates average response time.
void Process::calculateResponse(Process P[], int count)
{
    double TotalResponse=0;
    cout << "\n";
    for(int i=0; i<count; i++)
    {
        cout << "Response time for Process #" << P[i].num << ": " << P[i].response << "\n";
        TotalResponse = TotalResponse + P[i].response;
    }
    AVGresponse = TotalResponse/8;
}

//Prints turnaround time for each process and calculates average turnaround time.
void Process::calculateTurnaround(Process P[], int count)
{
    double TotalTurnaround=0;
    cout << "\n";
    for(int i=0; i<count; i++)
    {
        cout << "Turnaround time for Process #" << P[i].num << ": " << P[i].turnaround << "\n";
        TotalTurnaround = TotalTurnaround + P[i].turnaround;
    }
    AVGturnaround = TotalTurnaround/8;
}

//Prints waiting time for each process and calculates average waiting time.
void Process::calculateWaiting(Process P[], int count)
{
    double TotalWaiting=0;
    cout << "\n";
    for(int i=0; i<count; i++)
    {
        P[i].waiting = P[i].turnaround-P[i].totalBurst;
        cout << "Waiting time for Process #" << P[i].num << ": " << P[i].waiting << "\n";
        TotalWaiting = TotalWaiting + P[i].waiting;
    }
    AVGwaiting = TotalWaiting/8;
}
