import csv
import matplotlib.pyplot as plt


N = []
rectangle_time = []
rectangle_error = []
montecarlo_time = []
montecarlo_error = []


with open("results.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        N.append(int(row["N"]))
        rectangle_time.append(float(row["rectangle_time"]))
        rectangle_error.append(float(row["rectangle_error"]))
        montecarlo_time.append(float(row["montecarlo_time"]))
        montecarlo_error.append(float(row["montecarlo_error"]))


plt.figure(figsize=(16, 9))

plt.plot(N, rectangle_time, label="Rectangle")
plt.plot(N, montecarlo_time, label="Monte Carlo")
plt.xlabel("N")
plt.ylabel("Time, microseconds")
plt.title("Execution time t(N)")
plt.legend()
plt.grid()

plt.savefig("time.png")
plt.close()

plt.figure(figsize=(16, 9))
plt.yscale('log')
plt.plot(N, rectangle_time, label="Rectangle")
plt.plot(N, montecarlo_time, label="Monte Carlo")
plt.xlabel("N")
plt.ylabel("Time, microseconds")
plt.title("Execution time t(N)")
plt.legend()
plt.grid()

plt.savefig("time_log.png")
plt.close()


plt.figure(figsize=(16, 9))
plt.yscale('log')

plt.plot(N, rectangle_error, label="Rectangle")
plt.plot(N, montecarlo_error, label="Monte Carlo")

plt.xlabel("N")
plt.ylabel("Relative error")
plt.title("Error epsilon(N)")
plt.legend()
plt.grid()

plt.savefig("error.png")
plt.close()


threads = []
rectangle_thread_time = []
montecarlo_thread_time = []

with open("threads.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        threads.append(int(row["threads"]))
        rectangle_thread_time.append(float(row["rectangle_time"]))
        montecarlo_thread_time.append(float(row["montecarlo_time"]))


plt.figure(figsize=(16, 9))

plt.plot(threads, rectangle_thread_time, label="Rectangle")

plt.plot(threads, montecarlo_thread_time, label="Monte Carlo")

plt.xlabel("Number of threads")
plt.ylabel("Time, microseconds")
plt.title("Execution time depending on number of threads")

plt.xticks(threads)
plt.legend()

plt.savefig("threads_time.png")
plt.close()