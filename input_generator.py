import random
import json
import sys
import numpy as np


def generate_input_and_solutions(Op, n_arrays, dtype, kernel_height, kernel_width, input_file, solution_file):
    kernel_size = int(kernel_height) * int(kernel_width)
    width_bin = f'{int(kernel_width):08b}'
    height_bin = f'{int(kernel_height):b}'
    size_bin = "0b" + height_bin + width_bin
    kernel_size_input = int(size_bin, 2)
    pooling_method = 0
    data_format = 0

    # Create an empty list to hold the results
    arr = []
    results = []
    solutions = []

    # create and store inputs
    for i in range(int(n_arrays)):

        # Create an array of 64 elements with the chosen data type
        if dtype == "int8":
            max = 2**8
            arr = np.random.randint(max, size=kernel_size).astype(np.int8)
            data_format = 1
        if dtype == "int16":
            max = 2**16
            arr = np.random.randint(max, size=kernel_size).astype(np.int16)
            data_format = 0

        results.append(arr)
        if Op == "max":
            solutions.append(np.max(arr))
            pooling_method = 1
        elif Op == "min":
            solutions.append(np.min(arr))
            pooling_method = 2
        elif Op == "mean":
            solutions.append(np.mean(arr))
            pooling_method = 0

    prologue = '''
    {
      "program fragment": [
        {
            "instr No.": 0,
            "pdp_csb2pdp_addr": "0x008",
            "pdp_csb2pdp_data": 1,
            "pdp_csb2pdp_write": 1,
            "pdp_csb2pdp_vld": 1,
            "pdp_pdp_last_input_batch": false,
            "pdp_pdp_input_vld": false
        }
        '''

    epilogue = """
      ]
    }
        """

    with open(input_file, "w") as file1:
        file1.write(prologue)
        tabs = "\t\t\t"
        file1.write(",{\n")
        file1.write(tabs + f"\"instr No.\": {1}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_addr\": \"0x024\", \n")
        file1.write(tabs + f"\"pdp_csb2pdp_data\": {str(pooling_method)}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_write\": 1, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_vld\": 1, \n")
        file1.write(tabs + f"\"pdp_pdp_last_input_batch\": false, \n")
        file1.write(tabs + f"\"pdp_pdp_input_vld\": false \n")
        file1.write("\t\t}\n")

        tabs = "\t\t\t"
        file1.write("\t\t,{\n")
        file1.write(tabs + f"\"instr No.\": {2}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_addr\": \"0x034\", \n")
        file1.write(
            tabs + f"\"pdp_csb2pdp_data\": {str(kernel_size_input)}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_write\": 1, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_vld\": 1, \n")
        file1.write(tabs + f"\"pdp_pdp_last_input_batch\": false, \n")
        file1.write(tabs + f"\"pdp_pdp_input_vld\": false \n")
        file1.write("\t\t}\n")

        tabs = "\t\t\t"
        file1.write("\t\t,{\n")
        file1.write(tabs + f"\"instr No.\": {3}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_addr\": \"0x084\", \n")
        file1.write(tabs + f"\"pdp_csb2pdp_data\": {str(data_format)}, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_write\": 1, \n")
        file1.write(tabs + f"\"pdp_csb2pdp_vld\": 1, \n")
        file1.write(tabs + f"\"pdp_pdp_last_input_batch\": false, \n")
        file1.write(tabs + f"\"pdp_pdp_input_vld\": false \n")
        file1.write("\t\t}\n")

        for k in range(len(results)):
            file1.write("\t\t,{\n")
            file1.write(tabs + f"\"instr No.\": {k + 4}, \n")
            file1.write(
                tabs + f"\"pdp_pdp_last_input_batch\": {str(k == len(results) - 1).lower()}, \n")
            file1.write(tabs + f"\"pdp_pdp_input_vld\": true, \n")

            for i in range(len(arr) - 1):
                file1.write(
                    tabs + f'\"pdp_pdp_input_{i}\": {results[k][i]}, \n')
            file1.write(
                tabs + f'\"pdp_pdp_input_{len(arr) - 1}\": {results[k][(len(arr) - 1)]} \n')
            file1.write("\t\t}\n")

        file1.write(epilogue + "\n")
    print("Results saved to " + input_file)

    # write solutions
    with open(solution_file, "w") as file1:
        file1.write("instr 0: 0 \n")
        file1.write("instr 1: 0 \n")
        file1.write("instr 2: 0 \n")
        file1.write("instr 3: 0 \n")
        for i in range(len(solutions)):
            file1.write("instr " + str(i+4) + ": ")
            file1.write(str(solutions[i]))
            file1.write("\n")

    print("solutions saved to " + solution_file)


def main():
    if len(sys.argv) != 8:
        print(str(len(sys.argv)) + " args passed. Expected 7")
        print(
            "Usage: input_generator.py [ max | min | mean ]  n_arrays [ int8 | int16 ] kernel_height kernel_width input_file solution_file")
        exit

    _, Op, n_arrays, dtype, kernel_height, kernel_width, input_file, solution_file = sys.argv

    generate_input_and_solutions(
        Op, n_arrays, dtype, kernel_height, kernel_width, input_file, solution_file)
    print("done")


# generate random inputs and store in user specified file along with results - dtype feature_no. instr.out
# take in input file and generate output - dtype feature_no

if __name__ == "__main__":
    main()
