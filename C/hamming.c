#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert a character to an 8-bit binary string
void char_to_binary(char c, char *binary) {
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = ((c >> i) & 1) + '0';
    }
    binary[8] = '\0';
}

// Function to generate Hamming(7,4) code
void generate_hamming_code(const char *data_bits, char *hamming_code) {
    int data[4];
    for (int i = 0; i < 4; i++) {
        data[i] = data_bits[i] - '0';
    }

    // Calculate parity bits
    int p1 = data[0] ^ data[1] ^ data[3];
    int p2 = data[0] ^ data[2] ^ data[3];
    int p3 = data[1] ^ data[2] ^ data[3];

    // Construct the Hamming code
    hamming_code[0] = p1 + '0';
    hamming_code[1] = p2 + '0';
    hamming_code[2] = data[0] + '0';
    hamming_code[3] = p3 + '0';
    hamming_code[4] = data[1] + '0';
    hamming_code[5] = data[2] + '0';
    hamming_code[6] = data[3] + '0';
    hamming_code[7] = '\0';
}

// Function to detect and correct a single-bit error in a Hamming(7,4) code
void detect_and_correct_error(char *hamming_code) {
    int hamming[7];
    for (int i = 0; i < 7; i++) {
        hamming[i] = hamming_code[i] - '0';
    }

    // Calculate parity checks
    int p1 = hamming[0] ^ hamming[2] ^ hamming[4] ^ hamming[6];
    int p2 = hamming[1] ^ hamming[2] ^ hamming[5] ^ hamming[6];
    int p3 = hamming[3] ^ hamming[4] ^ hamming[5] ^ hamming[6];

    // Calculate error position
    int error_pos = p1 * 1 + p2 * 2 + p3 * 4;

    // Correct the error if there is one
    if (error_pos != 0) {
        hamming[error_pos - 1] ^= 1;
    }

    // Update the corrected Hamming code
    for (int i = 0; i < 7; i++) {
        hamming_code[i] = hamming[i] + '0';
    }
}

// Function to encode a binary string using Hamming(7,4) encoding
void encode_binary_string(const char *data_bits, char *encoded_string) {
    size_t len = strlen(data_bits);
    char hamming_code[8];
    encoded_string[0] = '\0';

    for (size_t i = 0; i < len; i += 4) {
        generate_hamming_code(data_bits + i, hamming_code);
        strcat(encoded_string, hamming_code);
    }
}

// Function to decode a binary string encoded with Hamming(7,4) and correct errors
void decode_binary_string(const char *encoded_string, char *decoded_string) {
    size_t len = strlen(encoded_string);
    char hamming_code[8];
    char corrected_code[5];
    decoded_string[0] = '\0';

    for (size_t i = 0; i < len; i += 7) {
        strncpy(hamming_code, encoded_string + i, 7);
        hamming_code[7] = '\0';
        detect_and_correct_error(hamming_code);

        // Extract the original data bits
        corrected_code[0] = hamming_code[2];
        corrected_code[1] = hamming_code[4];
        corrected_code[2] = hamming_code[5];
        corrected_code[3] = hamming_code[6];
        corrected_code[4] = '\0';

        strcat(decoded_string, corrected_code);
    }
}

// Main function for CLI tool
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <encode|decode> <string>\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];
    char *input_string = argv[2];

    if (strcmp(operation, "encode") == 0) {
        // Convert the input string to a binary string
        size_t input_len = strlen(input_string);
        char *binary_string = (char *)malloc(input_len * 8 + 1);
        binary_string[0] = '\0';
        for (size_t i = 0; i < input_len; i++) {
            char binary_char[9];
            char_to_binary(input_string[i], binary_char);
            strcat(binary_string, binary_char);
        }

        // Encode the binary string
        char *encoded_string = (char *)malloc(input_len * 14 + 1);  // Rough estimate for encoded size
        encode_binary_string(binary_string, encoded_string);
        printf("Encoded binary string: %s\n", encoded_string);

        free(binary_string);
        free(encoded_string);
    } else if (strcmp(operation, "decode") == 0) {
        // Decode the binary string
        size_t input_len = strlen(input_string);
        char *corrected_string = (char *)malloc(input_len / 7 * 4 + 1);
        decode_binary_string(input_string, corrected_string);

        // Convert the corrected binary string back to text
        size_t corrected_len = strlen(corrected_string);
        char *decoded_text = (char *)malloc(corrected_len / 8 + 1);
        for (size_t i = 0; i < corrected_len; i += 8) {
            char byte_str[9];
            strncpy(byte_str, corrected_string + i, 8);
            byte_str[8] = '\0';
            decoded_text[i / 8] = (char)strtol(byte_str, NULL, 2);
        }
        decoded_text[corrected_len / 8] = '\0';
        printf("Decoded text: %s\n", decoded_text);

        free(corrected_string);
        free(decoded_text);
    } else {
        fprintf(stderr, "Invalid operation. Use 'encode' or 'decode'.\n");
        return 1;
    }

    return 0;
}