#include <iostream>
#include <vector>
#include <string>
#include <list>

// A struct to represent a job
struct Job {
    std::string id;
    int arrival_time;
    int service_time;
};

int main() {
    // Job data
    std::vector<Job> jobs = {
        {"a", 1, 2},
        {"b", 2, 1},
        {"c", 3, 2},
        {"d", 8, 2},
        {"e", 8, 3},
        {"f", 9, 2}
    };

    // Data structures for the simulation
    std::list<Job> work_queue;
    std::vector<std::string> jobs_complete;

    // Variables for the simulation state
    std::string job_in_service = "";
    int service_time_left = 0;

    int clock = 0;
    int limit = 20;

    while (clock < limit) {
        // 0. If a job is being serviced, decrement its time
        if (job_in_service != "") {
            service_time_left--;
            std::cout << clock << ": " << job_in_service << " has " << service_time_left << " time left" << std::endl;
        }

        // 1. If job is done then remove it
        if (job_in_service != "" && service_time_left == 0) {
            std::cout << clock << ": " << job_in_service << " complete" << std::endl;
            jobs_complete.push_back(job_in_service);
            job_in_service = "";
        }

        // 2. Add new jobs to queue
        // A simple way to handle this with a vector is to check from the front.
        // The Python script's pop(0) is inefficient for lists, but the C++ vector is not.
        while (!jobs.empty() && jobs.front().arrival_time == clock) {
            Job j = jobs.front();
            jobs.erase(jobs.begin());
            work_queue.push_back(j);
            std::cout << clock << ": " << j.id << " added to queue" << std::endl;
        }

        // 3. If no job is being serviced, then add a job
        if (job_in_service == "" && !work_queue.empty()) {
            Job j = work_queue.front();
            work_queue.pop_front();
            job_in_service = j.id;
            service_time_left = j.service_time;
            std::cout << clock << ": " << j.id << " in service" << std::endl;

            std::cout << "Work queue: [ ";
            for (const auto& job : work_queue) {
                std::cout << job.id << " ";
            }
            std::cout << "] Current: " << job_in_service << std::endl;
        }

        clock++;
    }

    std::cout << std::endl;
    std::cout << "Jobs complete: ";
    for (const auto& j : jobs_complete) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    return 0;
}