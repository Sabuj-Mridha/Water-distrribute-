
#include<stdio.h>
#include<string.h>
int main()
{
                  /* variable declareation*/
float availableWater=13500;
int totalZones = 6;
char zoneID[6][10]={"Z01","Z02","Z03","Z04","Z05","Z06"};
char zoneType[6][20]={"Hospital","Emergency Shelter","Residential","Residential","Emergency Shelter","Emergency Service"};
float requested[6]={4000,3500,4500,3800,2600,2000};
float minimum[6]={3000,2500,2000,1800,1600,1500};
float loss[6]={2,4,8,12,5,1};
int waiting[6]={0,1,2,3,1,0};
int importance[6];
float priority[6];
int order[6]={0,1,2,3,4,5};
int temp;
int i,j;
float allocated[6];
float effective[6];
float shortage[6];
float needed;
int zoneIndex;
float remainingWater;
 remainingWater=availableWater;
printf("Available Water=%.0f L\n",availableWater);
printf("Total Zones=%d\n",totalZones);



                        /*1. importance calculater*/
for(i=0;i<totalZones;i++)
{
    if(strcmp(zoneType[i],"Hospital")==0)
    {
        importance[i]=4;
    }
    else if(strcmp(zoneType[i],"Emergency Service")==0)
    {
        importance[i]=4;
    }
    else if(strcmp(zoneType[i],"Emergency Shelter")==0)
    {
      importance[i]=3;
    }
    else
    {
        importance[i]=2;
    }
}
                        /* 2.calculating priority*/
    for(i=0;i<totalZones;i++)
   {
    priority[i]=((importance[i]*10)+(minimum[i]/100)+(waiting[i]*2)-loss[i]);
    }

                   /*3.shorting */
for (i=0;i<totalZones-1;i++)
{
    for (j=0;j<(totalZones-1-i);j++)
    {
        if(priority[order[j]]<priority[order[j+1]])
        {
            temp=order[j];
            order[j]=order[j+1];
            order[j+1]=temp;
        }
    }
}
            /*4.priority order*/
 printf("\nPriority Order:\n");
  remainingWater=availableWater;
for (i=0;i<totalZones; i++)
{
    printf("%d.%s-Priority: %.2f\n",i+1,zoneID[order[i]],priority[order[i]]);
}

                     /*5.Water Allocation Calculation*/
   printf("\n\nAllocation Result:\n");


    for (i=0;i<totalZones;i++)
    {
        zoneIndex=order[i];
        needed=requested[zoneIndex];

        if (remainingWater >= needed)
        {
            allocated[zoneIndex] = needed;
            shortage[zoneIndex] = 0;
            remainingWater=remainingWater-allocated[zoneIndex];
        }
        else
        {
            allocated[zoneIndex]=remainingWater;
            shortage[zoneIndex]=needed-allocated[zoneIndex];
            remainingWater=0;
        }

        effective[zoneIndex]=allocated[zoneIndex]*(1-loss[zoneIndex]/100.0);
    }


           /*6.Display information*/
printf("\nZone Information:\n");
for (i=0;i<totalZones;i++)
{
printf("\nZone ID: %s\n", zoneID[i]);
printf("Zone Type: %s\n", zoneType[i]);
printf("Importance: %d\n", importance[i]);
printf("Priority Score: %.2f\n", priority[i]);

printf("Requested Water: %.0f L\n", requested[i]);
printf("Minimum Water: %.0f L\n", minimum[i]);
printf("Loss: %.0f%%\n", loss[i]);
printf("Waiting Cycles: %d\n", waiting[i]);
printf("Allocated Water: %.0f L\n", allocated[i]);
printf("Shortage: %.0f L\n", shortage[i]);printf("Effective Water (After Loss): %.2f L\n",effective[i]);
    }



return 0;
}


