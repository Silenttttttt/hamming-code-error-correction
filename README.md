# Hamming Code Error Correction

This repository contains a Python implementation of the Hamming(7,4) code, which is used for error detection and correction in binary data. The project provides functions to encode binary strings using Hamming codes, detect and correct single-bit errors, and convert between binary strings and bytes. A special feature of this implementation is the automatic handling of padding to ensure data integrity during encoding and decoding.

## Features

- **Hamming(7,4) Encoding**: Encode 4-bit binary data into 7-bit Hamming code.
- **Error Detection and Correction**: Detect and correct single-bit errors in the encoded data.
- **Binary String Conversion**: Convert between binary strings and byte data.
- **Automatic Padding Management**: Automatically handle padding to ensure data integrity.

## Getting Started

### Prerequisites

- Python 3.x

### Installation

Clone the repository to your local machine:

git clone https://github.com/Silenttttttt/hamming-code-error-correction.git
cd hamming-code-error-correction

### Usage

Run `python hamming.py` to see an example of the encoding and decoding:

python hamming.py

### Example

The script includes an example that encodes the string "Hello world!" into a binary string, introduces an error, and then decodes and corrects the error to retrieve the original message.

## Functions

- `generate_hamming_code(data_bits: str) -> str`: Generates a Hamming(7,4) code from 4 data bits.
- `detect_and_correct_error(hamming_code: str) -> str`: Detects and corrects a single-bit error in a Hamming(7,4) code.
- `encode_binary_string(data_bits: str) -> str`: Encodes a binary string using Hamming(7,4) encoding.
- `decode_binary_string(encoded_string: str) -> str`: Decodes a binary string encoded with Hamming(7,4) and corrects errors.
- `bytes_to_binary_string(byte_data: bytes) -> str`: Converts bytes to an 8-bit binary string.
- `binary_string_to_bytes(binary_str: str) -> bytes`: Converts a binary string back to bytes.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- The big man Hamming
