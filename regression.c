#include <stdio.h>
#include <stdlib.h>

float calcMeanINT(int Z[], int n);
float upperMath(int X[], int Y[], float Xmean, float Ymean, int n);
float lowerMath(int X[], float Xmean, int n);
float calculateB(int X[], int Y[], float Xmean, float Ymean, int n);
float calculateA(float meanY, float b, float meanX);
int* getInputs(int n, char listName);

// Y = a + b * X

// b = sum (Xi - X) (Yi - Y) / sum ( Y - b * X)
// a = sum Y - b * X

void main() {
    int n = 5;
    int* X = getInputs(n, 'X'); 
    int* Y = getInputs(n, 'Y');

    float meanX = calcMeanINT(X, n);
    float meanY = calcMeanINT(Y, n);

    float b = calculateB(X, Y, meanX, meanY, n);
    float a = calculateA(meanY, b, meanX);

    printf("Regression model: Y = %f + %f * X\n", a, b);

    // Free allocated memory
    free(X);
    free(Y);
}

int* getInputs(int n, char listName) {
    int* output = (int*)malloc(n * sizeof(int));
    if (output == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        printf("Enter integer for %c[%d]: ", listName, i);
        scanf("%d", &output[i]);
    }
    return output;
}

// It calculates the mean of the integers
float calcMeanINT(int Z[], int n) {
    int sumZ = 0;
    for (int i = 0; i < n; i++) {
        sumZ += Z[i];
    }
    return (float)sumZ / n;
}

float upperMath(int X[], int Y[], float Xmean, float Ymean, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        float current = ((float)X[i] - Xmean) * ((float)Y[i] - Ymean);
        sum += current;
    }
    return sum;
}

float lowerMath(int X[], float Xmean, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        float current = ((float)X[i] - Xmean);
        sum += current * current;
    }
    return sum;
}

float calculateB(int X[], int Y[], float Xmean, float Ymean, int n) {
    float upper = upperMath(X, Y, Xmean, Ymean, n);
    float lower = lowerMath(X, Xmean, n);
    return upper / lower;
}

float calculateA(float meanY, float b, float meanX) {
    return meanY - b * meanX;
}
