import re
import matplotlib.pyplot as plt
import sys

# Check if the command line argument for the file path is provided
if len(sys.argv) < 2:
    print("Usage: python script_name.py path_to_log_file")
    sys.exit(1)

# Path to the log file from the command line argument
file_path = sys.argv[1]

# Read file contents
with open(file_path, 'r') as file:
    content = file.read()

# Define the pattern to extract operations and their elapsed times
pattern = re.compile(r'(\./inner_product_gmp_\d+_\w+) \d+ \d+\nElapsed time: ([\d.]+) s')

# Extract data using the defined pattern
data = pattern.findall(content)

# Print extracted data for debugging
print("Extracted data:", data)

# Organize data, removing 'inner_product' from the operation names
operations = [op.replace('inner_product_', '') for op, _ in data]
times = [float(time) for _, time in data]

# Determine colors based on operation types
colors = []
for op in operations:
    if 'mkIISR' in op:
        colors.append('red')
    elif 'mkII' in op:
        colors.append('green')
    elif 'orig' in op:
        colors.append('blue')
    else:
        colors.append('gray')  # Default color for operations that do not match any condition

# Filter data for "openmp" operations
openmp_operations = [op for op in operations if 'openmp' in op]
openmp_times = [times[i] for i, op in enumerate(operations) if 'openmp' in op]

# Print organized operations and times for further debugging
print("Operations:", operations)
print("Elapsed Times:", times)
print("OpenMP Operations:", openmp_operations)
print("OpenMP Elapsed Times:", openmp_times)

# Check if we have data to plot
if not operations:
    print("No data to plot.")
    sys.exit(1)

# Plotting all operations
plt.figure(figsize=(14, 8))
bars = plt.bar(operations, times, color=colors)
plt.xlabel('Operation')
plt.ylabel('Elapsed Time (s)')
plt.title('Elapsed Time for Various GMP Operations in Inner Product Calculations')
plt.xticks(rotation=90)
for bar, time in zip(bars, times):
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, round(time, 2), ha='center', va='bottom')
plt.tight_layout()
plt.savefig('all_operations_elapsed_times_chart.pdf')
plt.close()

# Plotting only "openmp" operations
if openmp_operations:
    plt.figure(figsize=(10, 6))
    bars = plt.bar(openmp_operations, openmp_times, color=colors)	
    plt.xlabel('Operation')
    plt.ylabel('Elapsed Time (s)')
    plt.title('Elapsed Time for OpenMP GMP Operations in Inner Product Calculations')
    plt.xticks(rotation=90)
    for bar, time in zip(bars, openmp_times):
        yval = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2, yval, round(time, 2), ha='center', va='bottom')
    plt.tight_layout()
    plt.savefig('openmp_operations_elapsed_times_chart.pdf')
    plt.close()
else:
    print("No OpenMP data to plot.")
