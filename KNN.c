#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
//#define alpha 240

int rows=0,columns=0;
double sumAll=0.0;
double cMean=0.0;
double sd=0.0;

double data[16500][600]= {0};
double meanDistance[16500]= {0};
int kValueCount[16500]= {0};
double distance[16500][16500]= {0};

void getRowsColumns(char *file)
{
    FILE *fp=fopen(file,"r");
    double val;
    char ch;
    while(fscanf(fp,"%lf%c",&val,&ch)!=EOF)
    {
        if(ch!=',')
        {
            rows++;
        }
        columns++;
    }
    columns=columns/rows;
    fclose(fp);
}


void getData(char *file)
{
    FILE *fp=fopen(file,"r");
    double val;
    char ch;
    int i,j;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            fscanf(fp,"%lf%c",&val,&ch);
            data[i][j]=val;
        }
    }
    fclose(fp);
}


void Euclidean()
{
    int i,j,k;
    double sum=0;
    double singleDistance=0.0;
    double add=0.0;

    //FILE *fp=fopen("distancesEuc","w");

    for(i=0; i<rows; i++)
    {
        sum=0;
        for(j=0; j<rows; j++)
        {
            add=0.0;
            singleDistance=0.0;
            for(k=0; k<columns; k++)
            {
                singleDistance=singleDistance+(data[i][k]-data[j][k])*(data[i][k]-data[j][k]);
            }
            add=sqrt(singleDistance);
            sum+=add;
            distance[i][j]=add;
            //fprintf(fp,"%lf , ",distance[i][j]);
        }
        //fprintf(fp,"\n");
        sumAll+=sum;
        meanDistance[i]=sum/rows;
    }
    //fclose(fp);
}


void Manhattan()
{
    int i,j,k;
    double sum=0;
    double singleDistance=0.0;

    //FILE *fp=fopen("distancesMan","w");

    for(i=0; i<rows; i++)
    {
        sum=0;
        for(j=0; j<rows; j++)
        {
            singleDistance=0.0;
            for(k=0; k<columns; k++)
            {
                singleDistance=singleDistance+abs(data[i][k]-data[j][k]);
            }
            sum+=singleDistance;
            distance[i][j]=singleDistance;
      //      fprintf(fp,"%lf , ",distance[i][j]);
        }
        //fprintf(fp,"\n");
        sumAll+=sum;
        meanDistance[i]=sum/rows;
    }
//    fclose(fp);
}


double standardDeviation()
{
    int i;
    double sd=0.0;
    for(i=0; i<rows; i++)
    {
        sd=sd+(cMean-meanDistance[i])*(cMean-meanDistance[i]);
    }
    sd=sqrt(sd/rows);
    return sd;
}

int main()
{
    int i,j;

    getRowsColumns("NormalizedEEG100");
    printf("Rows : %d\nColumns : %d\n",rows,columns);

    getData("NormalizedEEG");

    printf("getDATA done..\n");

    Euclidean();

    //Manhattan();

    printf("Euclidean done..\n");

    cMean=sumAll/(rows*rows);

    sd=standardDeviation();

    printf("SD done..\n");

    printf("Standard Deviation of Mean Distance is : %lf\n",sd);

    for(i=0; i<rows; i++)
    {
        kValueCount[i]=0;
    }

    double kSum=0.0;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<rows; j++)
        {
            if(distance[i][j]>(cMean+2*sd))
            {
                kValueCount[i]++;
                kSum++;
            }
        }
    }

    printf("KSUM : %lf\n",kSum/rows);

    kSum=kSum/rows;

    double ksd=0.0;

    for(i=0; i<rows; i++)
    {
        ksd=ksd+(kSum-kValueCount[i])*(kSum-kValueCount[i]);
    }

    ksd=sqrt(ksd/rows);

    printf("KSD : %lf\n",ksd);
    int alpha=kSum+2*ksd;
    printf("alpha : %d\n",alpha);

    FILE *fp=fopen("./output/OutliersEEG100","w");

    for(i=0; i<rows; i++)
    {
        if(kValueCount[i]>alpha)
        {
            fprintf(fp,"%d\n",i);
        }
    }
    fclose(fp);

    return 0;
}

