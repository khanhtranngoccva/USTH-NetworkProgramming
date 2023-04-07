import os

with open("test.txt", "r") as file:
    files = file.read().split("\n")
    os.makedirs("test", exist_ok=True)
    for filename in files:
        with open(os.path.join("test", filename), "w") as file:
            pass