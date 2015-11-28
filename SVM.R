matrix<-read.table("NormalizedEEG",header=F,sep=",")
matrix<-as.matrix(matrix)
library(kernlab)
res <- ksvm(matrix, type="one-svc", kernel="rbfdot",kpar=list(sigma=sigest(matrix)[2]))
Distance <- -1 * predict(res, matrix, type="decision")
meanD<-mean(Distance)
stdD<-sd(Distance)
count<-0
for(i in 1:length(Distance)){
	if(Distance[i]>(4.5*stdD+meanD)){
		vector<-c(vector,i)
		write(i,file="Rsvm",append=TRUE)		
		count<-count+1
	}
}
print(length(vector))
print(count)
