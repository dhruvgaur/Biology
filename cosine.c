#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int rows;
int columns;
int sampleSize;
double data[16500][1000]= {0};
double similarity[16500][16500]= {0};
double aibi[1000]= {0};
double a2[1000]= {0};
double b2[1000]= {0};
int sampleData[1000]= {0};
int kCount[16700]={0};


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


void sampleGeneration()
{
    int i;
    for(i=0; i<sampleSize; i++)
    {
        sampleData[i]=rand()%rows;
    }
}


int main()
{

    getRowsColumns("NormalizedDorothea");
    printf("Rows : %d\nColumns : %d\n",rows,columns);

    getData("NormalizedDorothea");

    double sumAB=0;
    double sumA2=0;
    double sumB2=0;

    int i,j,k;

    sampleSize=rows;

    FILE *fp=fopen("similarities","w");

    //sampleGeneration();

    for(i=0; i<rows; i++)
    {
        sampleGeneration();
        for(j=0; j<sampleSize; j++)
        {
            sumAB=0;
            sumA2=0;
            sumB2=0;
            for(k=0; k<columns; k++)
            {
                /*sumAB+=data[i][k]*data[sampleData[j]][k]
                sumA2+=data[i][k]*data[i][k];
                sumB2+=data[sampleData[j]][k]*data[sampleData[j]][k];*/
                sumAB+=data[i][k]*data[j][k];
                sumA2+=data[i][k]*data[i][k];
                sumB2+=data[j][k]*data[j][k];
            }
//            printf("sumAB : %lf\tsumA2 : %lf\tsumB2 : %lf\n",sumAB,sumA2,sumB2);
            //sleep(1);
            sumA2=sqrt(sumA2);
            sumB2=sqrt(sumB2);
            similarity[i][j]=sumAB/(sumA2*sumB2);
            fprintf(fp,"%lf,",similarity[i][j]);
            //printf("%d.%d %s : %lf\n",i,j,strerror(errno),similarity[i][j]);
        }
        fprintf(fp,"\n");
    }

    fclose(fp);

    fp=fopen("kCount","w");

    double sumKCount=0;

    for(i=0;i<rows;i++)
    {
        for(j=0;j<sampleSize;j++)
        {
            if(similarity[i][j]<0)
            {
                kCount[i]++;
                sumKCount++;
            }
        }
        fprintf(fp,"%d\n",kCount[i]);
    }
    fclose(fp);

    sumKCount=sumKCount/rows;
    printf("Average Kcount is : %lf\n",sumKCount);

    double sd=0;

    for(i=0;i<rows;i++)
    {
        sd=sd+(kCount[i]-sumKCount)*(kCount[i]-sumKCount);
    }
    sd=sqrt(sd/rows);

    printf("Average Kcount is : %lf\n",sumKCount);
    printf("SD Is : %lf\n",sd);

    fp=fopen("./output/similarity/Outliers_Cosine_Dorothea","w");

    for(i=0;i<rows;i++)
    {
        if(kCount[i]>sumKCount+sd)
        {
            fprintf(fp,"%d\n",i);
        }
    }
    fclose(fp);

    printf("Done..\n");

    return 0;
}
