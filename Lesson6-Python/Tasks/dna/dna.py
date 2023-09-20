import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: ./dna database sequence")
        exit()

    # Read database file into a variable
    with open(sys.argv[1], "r") as database_file:
        reader = csv.reader(database_file)
        #next(reader)
        database = []
        for row in reader:
            database.append(row)
            
    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence_file:
        dna_sequence = sequence_file.read()

    sub_sequences = {}
    # Gets name of dnas and fills counters
    for column_name in database[0][1:]:
        sub_sequences[column_name] = 0

    for sub_sequence in sub_sequences:
        # Find longest match of each STR in DNA sequence
        longest_run = longest_match(dna_sequence, sub_sequence)
        sub_sequences[sub_sequence] = longest_run

    # Check database for matching profiles
    for row in database[1:]:
        # Had to use chatgpt for this one, confusing...
        # Basically it creates data dict like sub_sequences, excludes name from the row
        row_data = {k: int(v) for k, v in zip(sub_sequences.keys(), row[1:])}
        if row_data == sub_sequences:
            print(row[0])
            exit()
        
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
