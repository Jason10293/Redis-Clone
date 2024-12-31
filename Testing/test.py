import matplotlib.pyplot as plt
import numpy as np

# Data
data = {
    "Operation": ["Insertion", "Retrieval", "Deletion"] * 3,
    "Element": [46655, 46655, 46655, 93310, 93310, 93310, 155517, 155517, 155517],
    "No Resizing (s)": [0.108540, 0.164280, 0.365800, 1.163760, 1.185340, 0.867500, 3.807540, 2.310820, 2.061340],
    "No Resizing (µs/Op)": [2.326439, 3.521166, 7.840532, 12.471975, 12.703247, 9.296967, 24.483111, 14.858954, 13.254757],
    "w/ Resizing (s)": [0.051480, 0.009720, 0.027260, 0.098700, 0.039640, 0.051560, 0.140900, 0.034380, 0.093740],
    "w/ Resizing (µs/Op)": [1.103419, 0.208338, 0.584289, 1.057764, 0.424820, 0.552567, 0.906010, 0.221069, 0.602764]
}

# Convert data to numpy arrays for easier manipulation
operations = np.array(data["Operation"])
elements = np.array(data["Element"])
no_resizing_s = np.array(data["No Resizing (s)"])
no_resizing_us = np.array(data["No Resizing (µs/Op)"])
with_resizing_s = np.array(data["w/ Resizing (s)"])
with_resizing_us = np.array(data["w/ Resizing (µs/Op)"])

# Unique elements and operations for plotting
unique_elements = np.unique(elements)
unique_operations = ["Insertion", "Retrieval", "Deletion"]

# Plot seconds comparison
plt.figure(figsize=(12, 6))
for operation in unique_operations:
    mask = operations == operation
    plt.plot(elements[mask], no_resizing_s[mask], label=f"{operation} (No Resizing)", marker="o")
    plt.plot(elements[mask], with_resizing_s[mask], label=f"{operation} (With Resizing)", marker="x")

plt.title("Operation Time in Seconds")
plt.xlabel("Number of Elements")
plt.ylabel("Time (s)")
plt.legend()
plt.grid(True)
plt.show()

# Plot microseconds per operation comparison
plt.figure(figsize=(12, 6))
for operation in unique_operations:
    mask = operations == operation
    plt.plot(elements[mask], no_resizing_us[mask], label=f"{operation} (No Resizing)", marker="o")
    plt.plot(elements[mask], with_resizing_us[mask], label=f"{operation} (With Resizing)", marker="x")

plt.title("Operation Time in Microseconds per Operation")
plt.xlabel("Number of Elements")
plt.ylabel("Time (µs/Op)")
plt.legend()
plt.grid(True)
plt.show()