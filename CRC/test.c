#include <stdio.h>
#include <string.h>

#define MESSAGE_SIZE 10 // Size of the message
#define DIVISOR_SIZE 5  // Size of the divisor

// Function to perform CRC division
void crcDivision(char *message, char *divisor, char *remainder) {
    int msgLen = strlen(message);
    int divLen = strlen(divisor);
    
    // Append zeros to message for the divisor size
    char paddedMsg[msgLen + divLen - 1];
    strcpy(paddedMsg, message);
    strcat(paddedMsg, "00000"); // Assuming divisor size is 4
    
    // Perform CRC division
    for (int i = 0; i < msgLen; i++) {
        if (paddedMsg[i] == '1') {
            for (int j = 0; j < divLen; j++) {
                paddedMsg[i + j] = paddedMsg[i + j] == divisor[j] ? '0' : '1';
            }
        }
    }
    
    // Copy the remainder to the output
    strncpy(remainder, &paddedMsg[msgLen], divLen - 1);
    remainder[divLen - 1] = '\0';
}

int main() {
    char message[] = "1010101010"; // Message
    char divisor[] = "11001";            // Divisor
    char remainder[DIVISOR_SIZE];       // Remainder
    
    // Perform CRC division
    crcDivision(message, divisor, remainder);
    
    // Print the CRC remainder
    printf("CRC Remainder: %s\n", remainder);
    
    return 0;
}

