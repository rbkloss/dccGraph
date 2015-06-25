
x = c(100,1100,2100,3100,4100,5100,6100,7100,8100,9100)/1000

yBin1 = read.csv("sparse/1/timeLogBin.csv", sep=" ", header=F)$V1/1000
yBin2 = read.csv("sparse/2/timeLogBin.csv", sep=" ", header=F)$V1/1000
yBin3 = read.csv("sparse/3/timeLogBin.csv", sep=" ", header=F)$V1/1000

yFib1 = read.csv("sparse/1/timeLogFib.csv", sep=" ", header=F)$V1/1000
yFib2 = read.csv("sparse/2/timeLogFib.csv", sep=" ", header=F)$V1/1000
yFib3 = read.csv("sparse/3/timeLogFib.csv", sep=" ", header=F)$V1/1000

yVec1 = read.csv("sparse/1/timeLogVec.csv", sep=" ", header=F)$V1/1000
yVec2 = read.csv("sparse/2/timeLogVec.csv", sep=" ", header=F)$V1/1000
yVec3 = read.csv("sparse/3/timeLogVec.csv", sep=" ", header=F)$V1/1000

?plot
?lines

yBin = (yBin1 + yBin2 + yBin3)/3
plot(x, yBin1, t='b', col='red', main="comparison on sparse graph", ylab="time(s)",xlab="|V|/1000")
yFib = (yFib1 + yFib2 + yFib3)/3
lines(x, yFib1, col='blue',type='b')
yVec = (yVec1 + yVec2 + yVec3)/3
lines(x, yVec1,col='green', type='b')
lines(x, (x*(log(x)/log(2)))/10,type='p', col='gold')
lines(x, (x*x)/10,type='p', col='purple')
x*(log(x)/log(2))
x*x

legend("topleft", inset=.05, title="Data Structures",
       c("Bin","Fib","Vec"), fill=c("red", "blue", "green"), horiz=TRUE)
######################################################################


yBin1 = read.csv("dense/1/timeLogBin.csv", sep=" ", header=F)$V1
yBin2 = read.csv("dense/2/timeLogBin.csv", sep=" ", header=F)$V1
yBin3 = read.csv("dense/3/timeLogBin.csv", sep=" ", header=F)$V1

yFib1 = read.csv("sparse/1/timeLogFib.csv", sep=" ", header=F)$V1
yFib2 = read.csv("sparse/2/timeLogFib.csv", sep=" ", header=F)$V1
yFib3 = read.csv("sparse/3/timeLogFib.csv", sep=" ", header=F)$V1

yVec1 = read.csv("sparse/1/timeLogVec.csv", sep=" ", header=F)$V1
yVec2 = read.csv("sparse/2/timeLogVec.csv", sep=" ", header=F)$V1
yVec3 = read.csv("sparse/3/timeLogVec.csv", sep=" ", header=F)$V1


yBin = (yBin1 + yBin2 + yBin3)/3
plot(x, yBin, t='lines', col='red', main="comparison on dense graph", ylab="time(s)",xlab="|V|")
yFib = (yFib1 + yFib2 + yFib3)/3
lines(x, yFib, col='blue')
yVec = (yVec1 + yVec2 + yVec3)/3
lines(x, yVec,col='green')

legend("topleft", inset=.05, title="Data Structures",
       c("Bin","Fib","Vec"), fill=c("red", "blue", "green"), horiz=TRUE)


