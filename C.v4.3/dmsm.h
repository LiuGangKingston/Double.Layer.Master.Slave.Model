/*
C    This is the header file for the DMSM library. Some detailed
C    description for it is available in the comment area at the
C    beginning of the file dmsm.c .
C
C    www.hpcvl.org
C    Copyright (c) 2009-2011 by High Performance Computing Virtual Laboratory
*/


#include <mpi.h>


#define DMSM_MASTER_SLAVE_PROCESS_SHOWING 0
#define DMSM_ALWAYS_ZERO                  0
#define DMSM_COLLECT_RESULTS_PARALLEL     1
#define DMSM_JOB_GROUPING                 1
#define DMSM_ONLY_MPI_TRUE_MASTER_PLAN    1

int DMSM_Get_Master();


void DMSM_Initialize(int Total_Number_Of_Threads_Per_Process,
                     int Job_Distribution_Plan,
                     int Total_Num_Of_Jobs,
                     int Num_Of_Jobs_Per_Group);

void DMSM_Working(   void (*Do_The_Job) (int),
                     void (*Job_Group_Preparation) (int,int,int,int),
                     void (*Result_Collection) (int,int),
                     int  Result_Collection_Enabled);

void DMSM_Job_Distribution_Checkup();

void DMSM_Finalize();

void DMSM_All(       int  Total_Number_Of_Threads_Per_Process,
                     int  Job_Distribution_Plan,
                     int  Total_Num_Of_Jobs,
                     int  Num_Of_Jobs_Per_Group,
                     void (*Do_The_Job) (int),
                     void (*Job_Group_Preparation) (int,int,int,int),
                     void (*Result_Collection) (int,int),
                     int  Result_Collection_Enabled);

void DMSM_Unset_An_Initial_Lock();
void DMSM_Wait_For_Initial_Locks();
void DMSM_Set_Node_Result_Lock();
void DMSM_Unset_Node_Result_Lock();
void DMSM_Set_Final_Result_Lock();
void DMSM_Unset_Final_Result_Lock();

int DMSM_All_Jobs_Done();
int DMSM_Get_Job_Rank();
int DMSM_Get_Job_Procs();
MPI_Comm DMSM_Get_Job_Comm();
int DMSM_Get_Dist_Rank();
int DMSM_Get_Dist_Procs();
MPI_Comm DMSM_Get_Dist_Comm();
int DMSM_Get_Distribution_Plan();
int DMSM_Get_Tag();
int DMSM_Get_Group_Start( int job_number);
int DMSM_Get_Group_End(   int job_number);
int DMSM_Get_Group_Number(int job_number);
void DMSM_Set_Journal_Number(long jn);

void DMSM_Set_Comm(MPI_Comm An_MPI_Communicator);

void DMSM_Gen_Comm_MPI_All(int Toal_Processes_For_a_Job,
                      MPI_Comm   All_Communicator, int  *All_Rank, int  *All_Processes,
                      MPI_Comm  *Job_Communicator, int  *Job_Rank, int  *Job_Processes,
                      MPI_Comm *Dist_Communicator, int *Dist_Rank, int *Dist_Processes);
void DMSM_Set_Comm_10(int Toal_Processes_For_a_Job,
                      MPI_Comm   All_Communicator, int  *All_Rank, int  *All_Processes,
                      MPI_Comm  *Job_Communicator, int  *Job_Rank, int  *Job_Processes,
                      MPI_Comm *Dist_Communicator, int *Dist_Rank, int *Dist_Processes);
void DMSM_MPI_All(    int  Total_Num_Of_Jobs,
                      int  Num_Of_Jobs_Per_Group,
                      void (*Do_The_Job) (int),
                      void (*Job_Group_Preparation) (int,int,int,int),
                      void (*Result_Collection) (int,int),
                      int  Result_Collection_Enabled                   );



