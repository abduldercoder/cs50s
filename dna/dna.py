import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: Python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    csv_file = sys.argv[1]
    with open(csv_file) as file:
        reader = csv.DictReader(file)
        str_list = reader.fieldnames[1:]
        individuals = []
        for row in reader:
            individuals.append(row)

    # Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file) as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_count = {}
    for subsequence in str_list:
        str_count[subsequence] = longest_match(dna_sequence, subsequence)

    # Check database for matching profiles
    for person in individuals:
        match = True
        for subsequence in str_list:
            if int(person[subsequence]) != str_count[subsequence]:
                match = False
                break
        if match:
            print(person["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)
    return longest_run


main()
