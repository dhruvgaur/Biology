matrix<-read.table("NormalizedParkinsons",header=F,sep=",")
matrix<-as.matrix(matrix)
kmeans.result <- kmeans(matrix, centers=3)
# cluster centers
#kmeans.result$centers
# calculate distances between objects and cluster centers
centers <- kmeans.result$centers[kmeans.result$cluster, ]
Distance <- sqrt(rowSums((matrix - centers)^2))
meanD<-mean(Distance)
stdD<-sd(Distance)
count<-0
for(i in 1:length(Distance)){
	if(Distance[i]>(2*stdD+meanD)){
		vector<-c(vector,i)
		write(i,file="Dhruv",append=TRUE)		
		count<-count+1
	}
}
print(length(vector))
print(count)
