#include<stdio.h>
#include<errno.h>
#include<string.h>

double data[16500][1000]={0.0};
double min[1000]={ [0 ... 999]=100.0 };
double max[1000]={0.0};
int main()
{
    FILE *fp;
    fp=fopen("dorothea.csv","r");
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


    for(i=0;i<columns;i++)
    {
        for(j=0;j<rows;j++)
        {
            if(data[j][i]>max[i])
            {
                max[i]=data[j][i];
            }
            if(data[j][i]<min[i])
            {
                min[i]=data[j][i];
            }
        }
    }

    for(i=0;i<columns;i++)
    {
        for(j=0;j<rows;j++)
        {
            data[j][i]=(data[j][i]-min[i])/(max[i]-min[i]); ///[0,1] normalization
        }
    }

    fp=fopen("NormalizedDorothea","w");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            fprintf(fp,"%f",data[i][j]);
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
