#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double length;
    double et;
    double waitingTime;
} Task;

int compareTasks(const void* a, const void* b) {
    Task* taskA = (Task*)a;
    Task* taskB = (Task*)b;
    return (taskB->length > taskA->length) - (taskB->length < taskA->length);
}

int compareMips(const void* a, const void* b) {
    double* mipsA = (double*)a;
    double* mipsB = (double*)b;
    return (*mipsB > *mipsA) - (*mipsB < *mipsA);
}

int main() {
    int numTasks, numVMs;
    printf("Enter the number of tasks: ");
    scanf("%d", &numTasks);
    printf("Enter the number of VMs: ");
    scanf("%d", &numVMs);

    Task* tasks = (Task*)malloc(numTasks * sizeof(Task));
    double* vmMips = (double*)malloc(numVMs * sizeof(double));
    double* vmCompletionTimes = (double*)calloc(numVMs, sizeof(double));
    int* vmIndices = (int*)malloc(numVMs * sizeof(int));

    for (int i = 0; i < numTasks; i++) {
        printf("Enter length for Task %d: ", i + 1);
        scanf("%lf", &tasks[i].length);
        printf("Enter execution time for Task %d: ", i + 1);
        scanf("%lf", &tasks[i].et);
        tasks[i].id = i + 1;
        tasks[i].waitingTime = 0;
    }

    for (int i = 0; i < numVMs; i++) {
        printf("Enter MIPS value for VM%d: ", i + 1);
        scanf("%lf", &vmMips[i]);
        vmIndices[i] = i;
    }

    qsort(tasks, numTasks, sizeof(Task), compareTasks);
    qsort(vmMips, numVMs, sizeof(double), compareMips);

    printf("Max-Min Scheduling:\n");
    double abb = 0;
    double overallCompletionTime = 0;

    for (int i = 0; i < numTasks; i++) {
        int vmIndex = i % numVMs;
        Task* task = &tasks[i];
        task->waitingTime = vmCompletionTimes[vmIndex];
        vmCompletionTimes[vmIndex] += task->et;
        printf("Task t%d ET: %.2f VM%d (MIPS: %.2f) Waiting Time: %.2f\n", task->id, task->et, vmIndex + 1, vmMips[vmIndex], task->waitingTime);
        if (i >= numTasks - numVMs) {
            abb += task->waitingTime;
        }
    }

    for (int i = 0; i < numVMs; i++) {
        if (vmCompletionTimes[i] > overallCompletionTime) {
            overallCompletionTime = vmCompletionTimes[i];
        }
    }

    double averageWaitingTime = abb / numVMs;
    printf("Total Waiting Time = %.2f\n", abb);
    printf("Average Waiting Time = %.2f\n", averageWaitingTime);
    printf("Overall Completion Time = %.2f\n", overallCompletionTime);

    free(tasks);
    free(vmMips);
    free(vmCompletionTimes);
    free(vmIndices);
    return 0;
}
