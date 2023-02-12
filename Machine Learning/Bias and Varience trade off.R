set.seed(123)

library(FNN)
library(ggplot2)
rm(list=ls())

ntrain <- 50 # Training
ntest <- 500 # Testing
nrep <- 100 # repeat 100 times
p <- 20
# puse <- c(1, 2, 3, 4, 10, 20) # number of predictors
puse <- c(1, 2, 3)
k <- c(1:9)

sigma <- 0.025

Xtrain <- matrix(runif(ntrain * p, -1, 1), ntrain, p)
Xtest <- matrix(runif(ntest * p, -1, 1), ntest, p)
y0 <- sin(2 * Xtrain[, 1]) # Only the first predictor is related to y
ytest <- sin(2 * Xtest[, 1])

out_knn <- data.frame() # Output results
out_lm <- data.frame()

for(i in 1:length(puse)){
    yhat_lm <- matrix(0, ntest, nrep)
    yhat_knn <- replicate(length(k), matrix(0, ntest, nrep))
    
    for(l in 1:nrep){
        y <- y0 + rnorm(ntrain, 0, sigma)
    
        ######### fit linear regression using lm funciton, assign predicted value to yhat_lm[,l] #########
        fit_lm <- lm(y ~ ., data.frame(y = y, x = Xtrain[, 1 : puse[i]]))
        yhat_lm[, l] <- predict(fit_lm, data.frame(x = Xtest[, 1 : puse[i]])) # predicted value by lm
      
    
        for(j in 1:length(k)){
            ######### fit knn using knn.reg funciton, assign predicted value to yhat_knn[, l, j] #########
            fit_knn <- knn.reg(train = data.matrix(Xtrain[, 1 : puse[i]]), test = data.matrix(Xtest[, 1 : puse[i]]), y = y, k = k[j])
            yhat_knn[, l, j] <- fit_knn$pred # predicted value by knn.reg
        }
        
        cat(i, "-th p, ", l, "-th repitition finished. \n")
    }
  
    ######### DO: compute bias and variance of linear regression #########
    
    # Compute mean of predicted values
    ybar_lm <- rowMeans(yhat_lm) # E(f^hat)
    
    # Compute bias^2
    biasSQ_lm <- mean((ytest - ybar_lm)^2) # E[ (f - E(f^hat))^2 ]
    
    # Compute variance
    variance_lm <- mean((yhat_lm - ybar_lm)^2) # E[ (E(f^hat) - f^hat)^2 ]
    
    # Compute total MSE
    err_lm <- mean((yhat_lm - c(ytest))^2)
  
    out_lm <- rbind(out_lm, data.frame(error = biasSQ_lm, component = "squared-bias", p = paste0("p = ", puse[i])))
    out_lm <- rbind(out_lm, data.frame(error = variance_lm, component = "variance", p = paste0("p = ", puse[i])))
    out_lm <- rbind(out_lm, data.frame(error = err_lm, component = "MSE", p = paste0("p = ", puse[i])))
  
  
    ######### compute bias and variance of knn regression #########
    
    # Compute mean of predicted values
    ybar_knn <- apply(yhat_knn, c(1, 3), mean) # E(f^hat)
    
    # Compute bias^2
    biasSQ_knn <- colMeans((ytest - ybar_knn)^2) # E[ (f - E(f^hat))^2 ]
    
    # Compute variance
    variance_knn <- sapply(1:length(k), function(idx) mean((yhat_knn[, , idx] - ybar_knn[, idx])^2)) # E[ (E(f^hat) - f^hat)^2 ]
    
    # Compute total MSE
    err_knn <- apply(yhat_knn, 3, function(x) mean((x - ytest)^2))
  
    out_knn <- rbind(out_knn, data.frame(error = biasSQ_knn, component = "squared-bias", K = 1/k, p = paste0("p = ", puse[i])))
    out_knn<- rbind(out_knn, data.frame(error = variance_knn, component = "variance", K = 1/k, p = paste0("p = ", puse[i])))
    out_knn<- rbind(out_knn, data.frame(error = err_knn, component = "MSE", K = 1/k, p = paste0("p = ", puse[i])))
}
