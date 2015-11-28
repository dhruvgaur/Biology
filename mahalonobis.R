matrix<-read.table("NormalizedParkinsons",header=F,sep=",")
matrix<-as.matrix(matrix)
mean<-colMeans(matrix)
Sx<-cov(matrix)
Distance<-mahalanobis(matrix,mean,Sx)
meanD<-mean(Distance)
stdD<-sd(Distance)
count<-0
for(i in 1:length(Distance)){
	if(Distance[i]>(2*stdD+meanD)){
		vector<-c(vector,i)
		write(i,file="Dip",append=TRUE)
		count<-count+1
	}
}
print(count)
