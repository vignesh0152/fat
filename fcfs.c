#include <stdio.h>

int main() {
    int a, b;
    printf("Enter the number of VMs: ");
    scanf("%d", &a);
    printf("Enter the number of tasks: ");
    scanf("%d", &b);

    int len[b];
    double vm[a], t[b], wait[b];

    printf("Enter the lengths of the tasks:\n");
    for (int i = 0; i < b; i++) {
        scanf("%d", &len[i]);
    }

    printf("Enter the execution times for tasks:\n");
    for (int i = 0; i < b; i++) {
        scanf("%lf", &t[i]);
    }

    for (int i = 0; i < a; i++) {
        vm[i] = 0;
    }

    for (int i = 0; i < b; i++) {
        int k = i % a;
        wait[i] = vm[k];
        vm[k] += t[i];
        if (i < a) {
            printf("Task%d (Length: %d)\t%.2lf\tVM%d\n", i + 1, len[i], t[i], k + 1);
        } else {
            printf("Task%d (Length: %d)\t%.2lf\tWait(%.2lf)\tVM%d\n", i + 1, len[i], t[i], wait[i], k + 1);
        }
    }

    double twt = 0;
    for (int i = 0; i < b; i++) {
        twt += wait[i];
    }

    printf("The total waiting time is: %.2lf\n", twt);
    printf("The average waiting time is: %.2lf\n", twt / a);

    return 0;
}
