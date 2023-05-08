#include <stdio.h>
#include <stdlib.h>

#define FLAG 0x7E // Flag sequence
#define ESC 0x7D  // Escape character

int main() {
    unsigned char data[] = {0x01, 0x02, 0x03, FLAG, ESC, 0x04};
    int len = sizeof(data) / sizeof(data[0]);
    unsigned char* stuffed_data = (unsigned char*) malloc(2 * len * sizeof(unsigned char)); // allocate memory for the stuffed data
    int i, j, count;

    printf("Data before stuffing: ");
    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");

    // Stuffing bits
    j = 0;
    for (i = 0, count = 0; i < len; i++) {
        if (data[i] == FLAG || data[i] == ESC) {
            stuffed_data[j++] = ESC;
            stuffed_data[j++] = data[i] ^ 0x20;
            count++;
        } else {
            stuffed_data[j++] = data[i];
        }
    }

    printf("Data after stuffing: ");
    for (i = 0; i < j; i++) {
        printf("%02X ", stuffed_data[i]);
    }
    printf("\n");

    // Unstuffing bits
    unsigned char* unstuffed_data = (unsigned char*) malloc(len * sizeof(unsigned char)); // allocate memory for the unstuffed data
    j = 0;
    for (i = 0; i < len; i++) {
        if (data[i] == ESC) {
            i++;
            unstuffed_data[j++] = data[i] ^ 0x20;
        } else {
            unstuffed_data[j++] = data[i];
        }
    }

    printf("Data after unstuffing: ");
    for (i = 0; i < j; i++) {
        printf("%02X ", unstuffed_data[i]);
    }
    printf("\n");

    free(stuffed_data);
    free(unstuffed_data);

    return 0;
}
 
