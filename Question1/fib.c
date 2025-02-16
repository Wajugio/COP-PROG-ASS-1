#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long fib(long long n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <max_fib_number>\n", argv[0]);
        return 1;
    }

    int max_num = atoi(argv[1]);
    if (max_num < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    printf("Fibonacci sequence up to %d:\n", max_num);
    for (int i = 0; i <= max_num; i++) {
        printf("%lld ", fib(i));
        fflush(stdout);
        usleep(500000); 
    }
    printf("\n");

    return 0;
}
