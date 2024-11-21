#include <stdio.h>

int main() {
    int a, b, d = 0;
    printf("Enter the number of VMs: ");
    scanf("%d", &a);
    printf("Enter the number of tasks: ");
    scanf("%d", &b);

    int len[b], le[b], no[b];
    double t[b], t1[b], vm[a];

    printf("Enter the task lengths:\n");
    for (int i = 0; i < b; i++) {
        scanf("%d", &len[i]);
        le[i] = len[i];
    }

    printf("Enter the execution times for tasks:\n");
    for (int i = 0; i < b; i++) {
        scanf("%lf", &t[i]);
    }

    for (int i = 0; i < b; i++) {
        for (int j = i + 1; j < b; j++) {
            if (le[i] > le[j]) {
                d = le[i];
                le[i] = le[j];
                le[j] = d;
            }
        }
    }

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < b; j++) {
            if (le[i] == len[j]) {
                no[i] = j;
                len[j] = i + 987998;
                break;
            }
        }
        t1[i] = t[no[i]];
    }

    for (int i = 0; i < a; i++) {
        vm[i] = 0;
    }

    for (int i = 0; i < b; i++) {
        int k = i % a;
        if (i < a) {
            printf("Task%d\t%.2lf\tVM%d\n", no[i] + 1, t1[i], k + 1);
        } else {
            printf("Task%d\t%.2lf\tWait(%.2lf)\tVM%d\n", no[i] + 1, t1[i], vm[k], k + 1);
        }
        if (i < (b - a)) {
            vm[k] += t1[i];
        }
    }

    double twt = 0;
    for (int i = 0; i < a; i++) {
        twt += vm[i];
    }
    printf("The total waiting time is: %.2f\n", twt);
    printf("The average waiting time is: %.2f\n", twt / a);

    return 0;
}
