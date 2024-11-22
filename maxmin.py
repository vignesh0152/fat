def allocate_jobs_to_resources(job_count, resource_count, processing_durations):
    resource_times = [0] * resource_count
    job_to_resource = [-1] * job_count
    job_completion_times = [-1] * job_count
    print("\nAllocating Jobs to Resources:\n")

    for _ in range(job_count):
        min_durations = []
        for job_id in range(job_count):
            if job_to_resource[job_id] == -1:
                shortest_time = float('inf')
                assigned_resource = -1
                for res_id in range(resource_count):
                    projected_time = resource_times[res_id] + processing_durations[job_id][res_id]
                    if projected_time < shortest_time:
                        shortest_time = projected_time
                        assigned_resource = res_id
                min_durations.append((job_id, shortest_time, assigned_resource))
        chosen_job, min_duration, selected_resource = min(min_durations, key=lambda x: x[1])
        job_to_resource[chosen_job] = selected_resource
        job_completion_times[chosen_job] = min_duration
        resource_times[selected_resource] = min_duration
        print(f"Job {chosen_job + 1} assigned to Resource r{selected_resource + 1}")

    print("\nJob Completion Report:")
    print("-------------------------------")
    print("| Job | Completion Time |")
    print("-------------------------------")
    for job_id in range(job_count):
        print(f"| {job_id + 1} | {job_completion_times[job_id]:.2f} |")
    print("-------------------------------")
    max_completion_time = max(resource_times)
    print(f"\nTotal Completion Time for All Jobs: {max_completion_time:.2f}")


if __name__ == "__main__":
    job_count = int(input("Enter the number of jobs: "))
    resource_count = int(input("Enter the number of resources: "))
    processing_durations = []
    for job_id in range(job_count):
        print(f"\nEnter processing times for Job {job_id + 1} on each resource:")
        durations = []
        for res_id in range(resource_count):
            time = float(input(f"Resource r{res_id + 1}: "))
            durations.append(time)
        processing_durations.append(durations)
    allocate_jobs_to_resources(job_count, resource_count, processing_durations)
