#include <stdio.h>

void Encrypt(const char *plaintext, char *encrypted, char key) {
    while (*plaintext) {
        *encrypted = *plaintext + key;  // Encrypt by adding the key
        encrypted++;
        plaintext++;

    }
    *encrypted = '\0';  // Null-terminate the encrypted string
}

void Decrypt(const char *encrypted, char *decrypted, char key) {
    while (*encrypted) {
        *decrypted = *encrypted - key;
        decrypted++;
        encrypted++;
    }
    *decrypted = '\0';
}

int main() {
    char key = 7,
     message[200],
     encrypted[50],
    decrypted[50];

    printf("type your message :");
    gets(message);
    Encrypt(message, encrypted, key);
    Decrypt(encrypted, decrypted, key);

    printf("Original: %s\n", message);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}




