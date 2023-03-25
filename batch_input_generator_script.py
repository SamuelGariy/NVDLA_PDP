import subprocess

# define the number of times to run the script
num_runs = 5

# loop through and run the script multiple times
for i in range(num_runs):
    subprocess.run(['python', 'path/to/your/script.py'])
