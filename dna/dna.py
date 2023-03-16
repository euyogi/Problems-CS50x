import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py database_name.csv sequence_name.txt')
        return

    # Read database csv file into a list variable, a list of dictionaries
    with open(sys.argv[1], 'r') as database_file:
        database = list(csv.DictReader(database_file))

    # Read DNA sequence txt file into a string variable
    with open(sys.argv[2], 'r') as sequence_file:
        sequence = sequence_file.read()

    # Gets the STRs in the database by reading the first dictionary of our database
    # taking only the keys, converting the dict_keys to a list so we can slice it
    # Then getting the second element till the last, because the first element is
    # 'name' and we just want the STRs
    STRs = list(database[0].keys())[1:]

    # Find longest match of each STR in DNA sequence and put each in a list
    matches = {STR: str(longest_match(sequence, STR)) for STR in STRs}

    # Check database for matching profiles
    for individue_data in database:
        # Copy the name of the individue as we are going to delete it
        name = individue_data['name']

        # Delete the key 'name' because in matches we don't have a key 'name'
        del individue_data['name']

        # If our matches are equal to our individue_data then it's the same individue
        if matches == individue_data:
            # Print it's name
            print(name)
            return

    # If no match was found
    print('No match')
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
