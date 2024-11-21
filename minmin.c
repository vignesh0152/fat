#include <stdio.h>
#include <stdlib.h>
typedef struct {
int id;
double length;
double et;
double waitingTime;
int assignedVM;
} Task;
int main() {
int numTasks, numVMs;
printf("Enter the number of tasks: ");
scanf("%d", &numTasks);
printf("Enter the number of VMs: ");
scanf("%d", &numVMs);
Task* tasks = (Task*)malloc(numTasks * sizeof(Task));
double* vmMips = (double*)malloc(numVMs * sizeof(double));
double* vmCompletionTimes = (double*)calloc(numVMs, sizeof(double));
for (int i = 0; i < numTasks; i++) {
printf("Enter length for Task %d: ", i + 1);
scanf("%lf", &tasks[i].length);
printf("Enter execution time for Task %d: ", i + 1);
scanf("%lf", &tasks[i].et);
tasks[i].id = i + 1;
tasks[i].waitingTime = 0;
tasks[i].assignedVM = -1;
}
for (int i = 0; i < numVMs; i++) {
printf("Enter MIPS value for VM%d: ", i + 1);
scanf("%lf", &vmMips[i]);
}
printf("Min-Min Scheduling:\n");
double overallCompletionTime = 0;
double totalWaitingTime = 0;
for (int i = 0; i < numTasks; i++) {
int bestTaskIndex = -1;
int bestVMIndex = -1;
double bestCompletionTime = 1e9;
for (int t = 0; t < numTasks; t++) {
if (tasks[t].assignedVM == -1) {
for (int v = 0; v < numVMs; v++) {
double completionTime = vmCompletionTimes[v] + tasks[t].et;
if (completionTime < bestCompletionTime) {
bestCompletionTime = completionTime;
bestTaskIndex = t;
bestVMIndex = v;
}
}
}
}
tasks[bestTaskIndex].assignedVM = bestVMIndex;
tasks[bestTaskIndex].waitingTime = vmCompletionTimes[bestVMIndex];
vmCompletionTimes[bestVMIndex] += tasks[bestTaskIndex].et;
printf("Task t%d ET: %.2f VM%d Waiting Time: %.2f\n", tasks[bestTaskIndex].id, tasks[bestTaskIndex].et, bestVMIndex + 1, tasks[bestTaskIndex].waitingTime);
totalWaitingTime += tasks[bestTaskIndex].waitingTime;
}
for (int i = 0; i < numVMs; i++) {
if (vmCompletionTimes[i] > overallCompletionTime) {
overallCompletionTime = vmCompletionTimes[i];
}
}
double averageWaitingTime = totalWaitingTime / numTasks;
printf("Total Waiting Time = %.2f\n", totalWaitingTime);
printf("Average Waiting Time = %.2f\n", averageWaitingTime);
printf("Overall Completion Time = %.2f\n", overallCompletionTime);
free(tasks);
free(vmMips);
free(vmCompletionTimes);
}