def naive_string_matching():
    """
    Performs naive string matching algorithm to find occurrences of a pattern in a text.

    This function takes user input for the text and pattern, and then slides the pattern over the text
    one by one to check for a match. If a match is found, it prints the index where the pattern is found.

    Args:
        None

    Returns:
        None
    """
    text = input("Enter the text: ")
    pattern = input("Enter the pattern: ")

    M = len(pattern)
    N = len(text)

    # A loop to slide pattern over text one by one
    for i in range(N - M + 1):
        j = 0

        # For current index i, check for pattern match
        while(j < M):
            if (text[i + j] != pattern[j]):
                break
            j += 1

        if (j == M):  # if pattern is found
            print("Pattern found at index ", i)
if __name__ == "__main__":
    naive_string_matching()