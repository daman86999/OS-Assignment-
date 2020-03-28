#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct job{
	int p_id;
	int arr_time;
	int brst_time;
	int cmpl_time;
	int btr;
}Fclty[100],Stdn[100],Fnl[100];

int n , fac_count=0 , std_count=0, fnl_count=0 , quant_time=0;

void setData(){
	int n;
	printf("\nENTER NO QUERIES TO PROCESS :\t");
	scanf("%d",&n);
	
	int i,t;
	int select;
	for (i=0; i<n ;i++ ){
		printf("\n>FACULTY QUEUE\n\n");
		printf(">STUDENT QUEUE\n\n");
		printf("\nENTER 1 FOR FACULTY AND 2 FOR STUDENT :\t");
		scanf("%d",&select);printf("\n");
		if (select==1){
			printf("\nENTER PROCESS ID FOR FACULTY QUERY :\t");scanf("%d",&Fclty[fac_count].p_id);
			printf("\nSince query processing time is between 10am to 2pm so enter arrival time between the range 1000 to 1200\n");
			x:
			printf("\nENTER ARRIVAL TIME:\t"); scanf("%d",&t);
			if(t<1000 || t>1200){
					printf("\nProcess is supposed to be queued in between 10:00 to 12:00.. \n");
					goto x;
				}
			if (t>=1060 && t<1100){
				printf("\nEnter time in  24 hours format ..\n");
				goto x;
			}
			if(t>=1160 && t<1200){
				printf("\nEnter time in  24 hours format ..\n");
				goto x;
			}
			if(t==1200){
				printf("\nSorry no more processes.. time is over\n");
				goto x;
			}
			else{Fclty[fac_count].arr_time= t-1000;}
				printf("\n\nENTER BURST TIME: "); scanf("%d", &Fclty[fac_count].brst_time);	 
				Fclty[fac_count].btr = Fclty[fac_count].brst_time; 
				fac_count++;
		}		
		if(select==2){
			printf("\nENTER PROCESS ID FOR STUDENT QUERY:\t");scanf("%d",&Stdn[std_count].p_id);
		    printf("\nSince query processing time is between 10am to 12pm so enter arrival time between the range 1000 to 1200\n");
			r:
			printf("\n\nENTER ARRIVAL TIME:\t"); scanf("%d",&t);
			if(t<1000 || t>1200){
				printf("\nProcess is supposed to be queued in between 10:00 to 12:00.. \n");
				goto r;
			}
			if (t>=1060 && t<1100){
				printf("\nEnter time in  24 hours format ..\n");
				goto r;
			}
			if(t>=1160 && t<1200){
				printf("\nEnter time in  24 hours format ..\n");
				goto r;
			}
			if(t==1200){
				printf("\nSorry no more processes.. time is over\n");
				goto r;
			}
			else{Stdn[std_count].arr_time= t-1000;}
				printf("\n\nENTER BURST TIME: "); scanf("%d", &Stdn[std_count].btr);	 
				Stdn[std_count].brst_time = Stdn[std_count].btr; 
				std_count++;
				
		}
	
	}
	printf("\n\nEnter quatum time to allot for the round robin sheduling .\t");
	scanf("%d",&quant_time);
	
}

void cmpr() {
	int nf=0 , ns=0;
	if(fac_count!=0 && std_count!=0){
		while(nf<std_count && nf<fac_count ){
			if(Fclty[nf].arr_time ==  Stdn[ns].arr_time)
			{
				Fnl[fnl_count] = Fclty[nf];
				fnl_count++;
				nf++;
				Fnl[fnl_count] = Stdn[ns];
				fnl_count++;
				ns++;
			}
			if(Fclty[nf].arr_time<Stdn[ns].arr_time){
				Fnl[fnl_count]=Fclty[nf];
				fnl_count++;
				nf++;
			}
			if(Fclty[nf].arr_time>Stdn[ns].arr_time){
				Fnl[fnl_count]=Stdn[ns];
				fnl_count++;
				ns++;
			}
			
		}
		if (fnl_count != (fac_count + std_count)){
			if(fac_count!=nf){
				while(nf!=fac_count){
					Fnl[fnl_count]=Fclty[nf];
					fnl_count++;
					nf++;
				}
			}
			if (std_count!=ns){
				while(ns!=std_count){
					Fnl[fnl_count]=Stdn[ns];
					fnl_count++;
					ns++;	
					
				}
			}
		}

	}
	if(fac_count==0){
		while(ns!=std_count){
			Fnl[fnl_count]=Stdn[ns];
			fnl_count++;
			ns++;
		}
	}
	if(std_count==0){
		while(nf!=fac_count){
			Fnl[fnl_count]=Fclty[nf];
			fnl_count++;
			nf++;
		}
	}
}
void roundRobin(){
	int t=Fnl[0].arr_time,mk=0, c=0 ,i, rc;
	while(t!=120 && c!=fnl_count){
		for(i=0; i<=mk;i++){
			if(Fnl[i].brst_time>quant_time){
				t+=quant_time;
				Fnl[i].brst_time-=quant_time;
			}
			if(Fnl[i].brst_time<=quant_time && Fnl[i].brst_time!=0){
				t+=Fnl[i].brst_time;
				Fnl[i].brst_time=0;
				Fnl[i].cmpl_time = t;
				c++;
			}
		}
		int st=mk+1;
		for(rc=st;rc<fnl_count;rc++){
			if(Fnl[rc].arr_time<=t){
				mk++;
			}
		}
	}
	
}

void getData(){
	int i, exec_ttl=0;
	int trn_ttl=0; 
	double average=0;
	printf("\n\n _______________________________________________________________________________________________________________");
	printf("\n| Process_ID \t| Arrival_Time\t| Burst_Time\t| Completion_Time\t| TurnAround_Time\t| Waiting_Time  |");
    
	for(i=0; i<fnl_count; i++){
		int id = Fnl[i].p_id;
		int art=Fnl[i].arr_time+1000;
		int btr=Fnl[i].btr;
		int cpt=Fnl[i].cmpl_time+1000;
		int trn=Fnl[i].cmpl_time-Fnl[i].arr_time;
		int wat=(Fnl[i].cmpl_time-Fnl[i].arr_time) - Fnl[i].btr;
		printf("\n|_______________|_______________|_______________|_______________________|_______________________|_______________|");
		printf("\n| %d\t\t| %d\t\t| %d\t\t| %d\t\t\t| %d\t\t\t| %d\t\t|",id,art,btr,cpt,trn,wat);
		printf("\n|_______________|_______________|_______________|_______________________|_______________________|_______________|");
	    
		exec_ttl=Fnl[0].cmpl_time;
		if(exec_ttl<Fnl[i].cmpl_time){
			exec_ttl=Fnl[i].cmpl_time;
		}
		trn_ttl+=trn;
	}
	average = (trn_ttl/fnl_count);
	if (exec_ttl>=100){
		exec_ttl=exec_ttl-40;
	}
	if(exec_ttl>=200){
		exec_ttl=exec_ttl-80;
	}
	printf("\n\n\nTOTAL TIME SPENT TO PROCESS ALL QUERIES: %d min", exec_ttl);
	printf("\n\nAVERAGE PROCESSING TIME : %lf min\n\n", average);

}
void main()
{
	setData();
	cmpr();
	roundRobin();
	getData();
}
