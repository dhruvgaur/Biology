
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<math.h>

double data[16700][100]={0.0};
double mean[100]={ 0 };
double sd[100]={0};

int main()
{
    FILE *fp;
    fp=fopen("geneExpData.csv","r");
    double val;
    char ch;
    int rows=0,columns=0;
    while(fscanf(fp,"%lf%c",&val,&ch)!=EOF)
    {
        if(ch!=',')
        {
            rows++;
        }
        columns++;
    }
    printf("Rows : %d\nColumns : %d\n",rows,columns/rows);

    fseek(fp,0,SEEK_SET);
    printf("%s\n",strerror(errno));

    columns=columns/rows;

    int i,j;

    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            fscanf(fp,"%lf%c",&val,&ch);
            data[i][j]=val;
        }
    }

    fclose(fp);

    double sumAll=0;

    for(i=0;i<columns;i++)
    {
        sumAll=0.0;
        for(j=0;j<rows;j++)
        {
            sumAll+=data[j][i];
        }
        mean[i]=sumAll/rows;
    }

    for(i=0;i<columns;i++)
    {
        sumAll=0;
        for(j=0;j<rows;j++)
        {
            sumAll+=(data[j][i]-mean[i])*(data[j][i]-mean[i]); ///standard score normalization
        }
        sd[i]=sqrt(sumAll/rows);
    }

    printf("SD : %lf\n",sd[20]);

    for(i=0;i<columns;i++)
    {
        for(j=0;j<rows;j++)
        {
            data[j][i]=(data[j][i]-mean[i])/sd[i];
        }
    }


    fp=fopen("Normalized_geneExpData","w");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            fprintf(fp,"%lf",data[i][j]);
            if(j==columns-1)
            {
                fprintf(fp,"\n");
            }
            else
            {
                fprintf(fp,",");
            }
        }
    }
    fclose(fp);

    printf("%s\n",strerror(errno));

    return 0;
}
