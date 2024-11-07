from collections import Counter
import math

# Function to recursively assign codes based on Shannon-Fano algorithm
def shannon_fano(symbols, code_map, prefix=''):
    if len(symbols) == 1:
        code_map[symbols[0][0]] = prefix
        return
    
    # Split symbols into two halves with nearly equal probabilities
    total_weight = sum(weight for _, weight in symbols)
    acc = 0
    split_idx = 0
    for i, (_, weight) in enumerate(symbols):
        acc += weight
        if acc >= total_weight / 2:
            split_idx = i + 1
            break

    # Assign codes recursively
    shannon_fano(symbols[:split_idx], code_map, prefix + '0')
    shannon_fano(symbols[split_idx:], code_map, prefix + '1')

# Function to compress a file using Shannon-Fano coding
def compress_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        text = file.read()

    # Count occurrences of each character
    char_count = Counter(text)
    total_chars = sum(char_count.values())

    # Create a sorted list of characters by frequency
    symbols = sorted(char_count.items(), key=lambda item: item[1], reverse=True)

    # Generate Shannon-Fano codes
    code_map = {}
    shannon_fano(symbols, code_map)

    # Encode the text into a bit string
    bit_string = ''.join(code_map[char] for char in text)

    # Calculate compression ratio
    initial_size = total_chars * 8  # Initial size in bits
    compressed_size = len(bit_string)  # Compressed size in bits
    compression_ratio = initial_size / compressed_size if compressed_size > 0 else 0

    # Print the Shannon-Fano codes
    print("Shannon-Fano Codes:")
    for char, code in code_map.items():
        display_char = repr(char) if char in ('\n', '\t', ' ') else char
        print(f"{display_char}: {code}")

    # Output results
    print("\nCompressed Bit String:", bit_string)
    print("Compression Ratio:", compression_ratio)

# Example usage
file_path = 'input.txt'  # Replace with your file path
compress_file(file_path)
