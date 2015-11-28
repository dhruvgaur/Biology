 library("DMwR")
 matrix<-read.table("C:\\Users\\AmitVerma\\Documents\\databases\\NormalizedParkinsons",header=F,sep=",")
 matrix<-as.matrix(matrix)
 outlier.scores<-lofactor(matrix, k=10)
 meanD<-mean(outlier.scores)
 stdD<-sd(outlier.scores)
 count<-0
 for(i in 1:length(outlier.scores)){
 if(outlier.scores[i]>(2*stdD+meanD)){
 write(i,file="Parkinsons",append=TRUE)
 count<-count+1
 }
 }
 print(count)
