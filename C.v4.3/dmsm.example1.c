/*
!    Copyright (c) 2009-2012 by High Performance Computing Virtual Laboratory
!
!    This is test example 1 of square root summation
!    for the DMSM library.
!
!    In this test, there are three input data
!    files. One is
!    TotalNumberOfOpenMPThreadsPerProcess
!    which containes only one integer as it names.
!
!    Another input data file is in.dat, which
!    containes two lines of integers as follows.
!
!    The first line is the JOB_DISTRIBUTION_PLAN
!    which can only take 11, 12, 13, 21, 22, 23,
!    31, 32, or 33.
!
!    The second line is the total number of jobs,
!    and number of jobs in each job group.
!
!    The last file is integers.dat, which is
!    the upper bound for square root summation.
!
!    The comment lines of the file dmsm.c is
!    a little more detailed description of the
!    DMSM model and its examples.
*/


#include "dmsm.h"
#include <mpi.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int  My_MPI_Rank, Total_MPI_Processes;
int  Job_Distribution_Plan;
int  Total_Num_Of_Jobs,Num_Of_Jobs_Per_Group;
int  Total_Number_Of_Threads_Per_Process;
long *Initial_Data_For_Jobs;
double *Results_in_Process;
double *Final_Total_Results_In_Master;


void Initial_MPI(int *rank, int *totps);
void Data_Initialize();
void Do_The_Job(int my_job);
void Output_Results();
void Data_Finalize();


int main(argc,argv)
int argc;
char *argv[];
{
  MPI_Init(&argc,&argv);
  Initial_MPI(&My_MPI_Rank, &Total_MPI_Processes);
  Data_Initialize();
  DMSM_All(Total_Number_Of_Threads_Per_Process,
           Job_Distribution_Plan,
           Total_Num_Of_Jobs,
           Num_Of_Jobs_Per_Group,
           Do_The_Job,
           NULL,
           NULL,
           1
           );
  Output_Results();
  Data_Finalize();
  MPI_Finalize();
  return(0);
}




void Initial_MPI(int *rank, int *totps)
{
  MPI_Comm_rank(MPI_COMM_WORLD,rank);
  MPI_Comm_size(MPI_COMM_WORLD,totps);
}




void Data_Initialize()
{ int i,j;
  FILE * fin;

  if(My_MPI_Rank==DMSM_Get_Master())
    {
        fin=fopen("TotalNumberOfOpenMPThreadsPerProcess","r");
        fscanf(fin,"%d \n",&Total_Number_Of_Threads_Per_Process);
        fclose(fin);

        fin=fopen("in.dat","r");
        fscanf(fin,"%d \n",&Job_Distribution_Plan);
        fscanf(fin,"%d %d\n",&Total_Num_Of_Jobs,&Num_Of_Jobs_Per_Group);
        fclose(fin);
    }

  MPI_Bcast(&Total_Num_Of_Jobs, 1, MPI_INT, DMSM_Get_Master(), MPI_COMM_WORLD);

  if((Initial_Data_For_Jobs=(long *) malloc(Total_Num_Of_Jobs*sizeof(long)))==NULL)
     {printf( "Error on memory allocation in Data_Initialize().\n") ;
      MPI_Finalize(); exit(0);}
  if(My_MPI_Rank==DMSM_Get_Master())
     {fin=fopen("integers.dat","r");
      for(i=0;i<Total_Num_Of_Jobs;i++)
         fscanf(fin," %d %ld \n", &j, &Initial_Data_For_Jobs[i]);
      fclose(fin);

      if((Final_Total_Results_In_Master=(double *)  malloc(Total_Num_Of_Jobs*sizeof(double)))==NULL)
         {printf( "Error on memory allocation in Data_Initialize().\n") ;
          MPI_Finalize(); exit(0);}
      }
  else
     {if((Final_Total_Results_In_Master=(double *)  malloc(1*sizeof(double)))==NULL)
        {printf( "Error on memory allocation in Data_Initialize().\n") ;
         MPI_Finalize(); exit(0);}}

  MPI_Bcast(Initial_Data_For_Jobs, Total_Num_Of_Jobs, MPI_LONG, DMSM_Get_Master(), MPI_COMM_WORLD);

  if((Results_in_Process=(double *) malloc(Total_Num_Of_Jobs*sizeof(double)))==NULL)
              {printf( "Error on memory allocation in Data_Initialize().\n") ;
               MPI_Finalize(); exit(0);}
  for(i=0;i<Total_Num_Of_Jobs;i++) Results_in_Process[i]=(double)0.0;

}




void Data_Finalize()
{
  free(Initial_Data_For_Jobs);
  free(Final_Total_Results_In_Master);
  free(Results_in_Process);
}




void Do_The_Job(int my_job)
{
   long integer,i;
   double r;
   integer=Initial_Data_For_Jobs[my_job];
   r=(double)0.0;
   for(i=(long)0; i<=integer; i++)
      {r+=sqrt((double)i);}
   Results_in_Process[my_job]=r;
}




void Output_Results()
{  FILE * fout;
   int i;
   if (My_MPI_Rank == DMSM_Get_Master())
       for(i=0;i<Total_Num_Of_Jobs;i++) Final_Total_Results_In_Master[i]=(double)0.0;
   MPI_Reduce(Results_in_Process,Final_Total_Results_In_Master,Total_Num_Of_Jobs,
              MPI_DOUBLE,MPI_SUM,DMSM_Get_Master(),MPI_COMM_WORLD);

   if (My_MPI_Rank == DMSM_Get_Master())
      {fout=fopen("sqrtrootsumall.dat","w");
       fprintf(fout, " %d \n", Total_Num_Of_Jobs);
       for(i=0;i<Total_Num_Of_Jobs;i++)
           fprintf(fout, " %d %24.12e \n", i, Final_Total_Results_In_Master[i]);
       fprintf(fout, " Done with example1. \n");
       fclose(fout);
       printf(" Done with example1. \n");
      }
}



