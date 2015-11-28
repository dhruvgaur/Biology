#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int rows;
int columns;
int sampleSize;
double sumAll=0.0;
double cMean=0.0;
double sd=0.0;

double data[16700][1000];
double meanDistance[16700];
int kValueCount[16700];

int sampleData[1000];

double distance[16700][1000];



void getRowsColumns(char *file)
{
    FILE *fp=fopen(file,"r");
    double val;
    char ch;
    while(fscanf(fp,"%lf%c",&val,&ch)!=EOF)
    {
        if(ch=='\n')
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
            //*((data+i*columns)+j)=val;
        }
    }
    fclose(fp);
}


int randomGeneration(int min, int max)
{
    srand(time(NULL));
    return min+rand()%(max-min+1);
}


void sampleGeneration()
{
    int i;
    srand(time(NULL));
    for(i=0; i<sampleSize; i++)
    {
        sampleData[i]=rand()%rows;
    }
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
    int i,j,k;

    srand(time(NULL));


    getRowsColumns("NormalizedLeukemia");
    printf("Rows : %d\nColumns : %d\n",rows,columns);

    getData("NormalizedLeukemia");

    sampleSize=randomGeneration(150,200);

    double singleDistance=0.0;
    double add=0.0;
    double sum=0;

    // FILE *fp=fopen("distRandSamplingEuc","w");

    //sampleGeneration();

    for(i=0; i<rows; i++)
    {
        sum=0;
        sampleGeneration();
        for(j=0; j<sampleSize; j++)
        {
            singleDistance=0;
            add=0;
            for(k=0; k<columns; k++)
            {
                singleDistance=singleDistance+(data[i][k]-data[sampleData[j]][k])*(data[i][k]-data[sampleData[j]][k]);
            }
            add=sqrt(singleDistance);
            sum+=add;
            distance[i][j]=add;
            //fprintf(fp,"%lf, ",distance[i][j]);
        }
        //fprintf(fp,"\n");
        sumAll+=sum;
        meanDistance[i]=sum/sampleSize;
    }
    //fclose(fp);

    cMean=sumAll/(rows*sampleSize);

    sd=standardDeviation();

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
    int alpha=kSum+3.1*ksd;
    printf("alpha : %d\n",alpha);

    FILE *fp=fopen("./output/sampling/random/Outliers_random_Leukemia","w");
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
