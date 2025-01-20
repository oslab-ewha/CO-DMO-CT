import numpy as np
import time
import hashlib
import pandas as pd
import os

def matrix_multiplication():
    global ratio
    size = int(6000 * ratio)
    A = np.random.rand(size, size)
    B = np.random.rand(size, size)
    return np.dot(A, B)

def hash_computation():
    global ratio
    data = b"AWS Nitro Enclave Performance Test" * int(1000000 * ratio)
    return hashlib.sha256(data).hexdigest()

def file_io_test():
    global ratio
    filename = "/tmp/test_large_file.csv"
    data = "A,B,C,D\n" + "\n".join(["1,2,3,4"] * int(20000000 * (1 - ratio)))
    with open(filename, "w") as f:
        f.write(data)

    df = pd.read_csv(filename)
    os.remove(filename)

print(f"start")

ratio = float(os.getenv("MIXED_RATIO"))

start = time.time()
matrix_multiplication()
hash_computation()
file_io_test()
end = time.time()

print(f"Mixed Task Completed in {end - start:.2f} seconds")
