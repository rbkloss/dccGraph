x = seq(500,9500,by = 1000)

yBin1 = read.csv("sparse/1/timeLogBin.csv", sep=" ", header=F)$V1
yBin2 = read.csv("sparse/2/timeLogBin.csv", sep=" ", header=F)$V1
yBin3 = read.csv("sparse/3/timeLogBin.csv", sep=" ", header=F)$V1

yFib1 = read.csv("sparse/1/timeLogFib.csv", sep=" ", header=F)$V1
yFib2 = read.csv("sparse/2/timeLogFib.csv", sep=" ", header=F)$V1
yFib3 = read.csv("sparse/3/timeLogFib.csv", sep=" ", header=F)$V1

yVec1 = read.csv("sparse/1/timeLogVec.csv", sep=" ", header=F)$V1
yVec2 = read.csv("sparse/2/timeLogVec.csv", sep=" ", header=F)$V1
yVec3 = read.csv("sparse/3/timeLogVec.csv", sep=" ", header=F)$V1

yBin = (yBin1 + yBin2 + yBin3)/3
yFib = (yFib1 + yFib2 + yFib3)/3
yVec = (yVec1 + yVec2 + yVec3)/3

yVec= timeLogVec$V1
yBin= timeLogBin$V1
yFib= timeLogFib$V1

plot(x, yBin,t='b', col='red', main="comparison on sparse graph", 
     ylab="time(ms)",xlab="|V|", 
     xlim=c(500,10000),ylim=c(100,10000))
lines(x, yFib, col='blue',type='b')
lines(x, yVec,col='green', type='b')

legend("topleft", inset=.05, title="Data Structures",
       c("Bin","Fib","Vec"), fill=c("red", "blue", "green"), horiz=TRUE)

lines(x, (x*(log(x)/log(2)))/1000,type='p', col='brown')
lines(x, (x*x)/100000,type='p', col='dark blue')


######################################################################


yBin1 = read.csv("dense/1/timeLogBin.csv", sep=" ", header=F)$V1/1000
yBin2 = read.csv("dense/2/timeLogBin.csv", sep=" ", header=F)$V1/1000
yBin3 = read.csv("dense/3/timeLogBin.csv", sep=" ", header=F)$V1/1000

yFib1 = read.csv("dense/1/timeLogFib.csv", sep=" ", header=F)$V1/1000
yFib2 = read.csv("dense/2/timeLogFib.csv", sep=" ", header=F)$V1/1000
yFib3 = read.csv("dense/3/timeLogFib.csv", sep=" ", header=F)$V1/1000

yVec1 = read.csv("dense/1/timeLogVec.csv", sep=" ", header=F)$V1/1000
yVec2 = read.csv("dense/2/timeLogVec.csv", sep=" ", header=F)$V1/1000
yVec3 = read.csv("dense/3/timeLogVec.csv", sep=" ", header=F)$V1/1000

yBin = (yBin1 + yBin2 + yBin3)/3
yFib = (yFib1 + yFib2 + yFib3)/3
yVec = (yVec1 + yVec2 + yVec3)/3


yVec= timeLogVec$V1
yBin= timeLogBin$V1
yFib= timeLogFib$V1

plot(x, yBin,t='b', col='red', main="comparison on dense graph", 
     ylab="time(ms)",xlab="|V|", 
     xlim=c(500,10000),ylim=c(100,10000))
lines(x, yFib, col='blue',type='b')
lines(x, yVec,col='green', type='b')

legend("topleft", inset=.05, title="Data Structures",
       c("Bin","Fib","Vec"), fill=c("red", "blue", "green"), horiz=TRUE)

######################################################################


yBin1 = read.csv("complete/1/timeLogBin.csv", sep=" ", header=F)$V1
yBin2 = read.csv("complete/2/timeLogBin.csv", sep=" ", header=F)$V1
yBin3 = read.csv("complete/3/timeLogBin.csv", sep=" ", header=F)$V1

yFib1 = read.csv("complete/1/timeLogFib.csv", sep=" ", header=F)$V1
yFib2 = read.csv("complete/2/timeLogFib.csv", sep=" ", header=F)$V1
yFib3 = read.csv("complete/3/timeLogFib.csv", sep=" ", header=F)$V1

yVec1 = read.csv("complete/1/timeLogVec.csv", sep=" ", header=F)$V1
yVec2 = read.csv("complete/2/timeLogVec.csv", sep=" ", header=F)$V1
yVec3 = read.csv("complete/3/timeLogVec.csv", sep=" ", header=F)$V1


yBin = (yBin1 + yBin2 + yBin3)/3
yFib = (yFib1 + yFib2 + yFib3)/3
yVec = (yVec1 + yVec2 + yVec3)/3

yVec= timeLogVec$V1
yBin= timeLogBin$V1
yFib= timeLogFib$V1

plot(x, yBin,t='b', col='red', main="comparison on complete graph", 
     ylab="time(ms)",xlab="|V|", 
     xlim=c(500,10000),ylim=c(100,10000))
lines(x, yFib, col='blue',type='b')
lines(x, yVec,col='green', type='b')

legend("topleft", inset=.05, title="Data Structures",
       c("Bin","Fib","Vec"), fill=c("red", "blue", "green"), horiz=TRUE)



