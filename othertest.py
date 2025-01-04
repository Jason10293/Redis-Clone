import matplotlib.pyplot as plt

# Data for the operations
operations = ['LPUSH', 'LPOP', 'RPUSH', 'RPOP']
elements = [
    [15552, 31104, 46655, 93310, 155517,233275, 466549],  # Number of elements for each operation
]
average_time_per_op = [
    [0.153999, 0.142533, 0.143393, 0.167713, 0.135998, 0.176549, 0.152123],  # LPUSH
    [0.943943, 0.920568, 0.979531, 0.999361, 1.181734, 1.324574, 1.280425],  # LPOP
    [0.180229, 0.147562, 0.134391, 0.144893, 0.131208, 0.153338, 0.298050],  # RPUSH
    [0.905684, 0.991692, 1.091416, 1.076412, 1.277170, 1.332119, 1.358870],  # RPOP
]

# Create a single plot for all operations
plt.figure(figsize=(10, 6))
plt.title("Average Time per Operation vs. Number of Elements", fontsize=16)
plt.xlabel('Number of Elements')
plt.ylabel('Average Time (microseconds)')
plt.grid(True)

# Plot each operation with different colors and labels
plt.plot(elements[0], average_time_per_op[0], marker='o', color='b', label='LPUSH')
plt.plot(elements[0], average_time_per_op[1], marker='o', color='r', label='LPOP')
plt.plot(elements[0], average_time_per_op[2], marker='o', color='g', label='RPUSH')
plt.plot(elements[0], average_time_per_op[3], marker='o', color='purple', label='RPOP')

# Add a legend
plt.legend()

# Adjust the y-axis range (zoom out)
plt.ylim(0, 1.5)

# Show the plot
plt.tight_layout()
plt.show()