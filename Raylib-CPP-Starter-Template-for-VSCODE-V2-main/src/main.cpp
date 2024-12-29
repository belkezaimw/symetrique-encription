#include "raylib.h"
#include <string.h>

// Simple Caesar cipher for symmetric encryption
void EncryptText(char *text, int key, int step) {
    if (text[step] == '\0') return;
    if (text[step] >= 'A' && text[step] <= 'Z') {
        text[step] = 'A' + (text[step] - 'A' + key) % 26;
    } else if (text[step] >= 'a' && text[step] <= 'z') {
        text[step] = 'a' + (text[step] - 'a' + key) % 26;
    }
}

void DecryptText(char *text, int key, int step) {
    if (text[step] == '\0') return;
    if (text[step] >= 'A' && text[step] <= 'Z') {
        text[step] = 'A' + (text[step] - 'A' - key + 26) % 26;
    } else if (text[step] >= 'a' && text[step] <= 'z') {
        text[step] = 'a' + (text[step] - 'a' - key + 26) % 26;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Symmetric Encryption Animation");

    SetTargetFPS(30); // Slower frame rate for better visualization

    char plainText[64] = "";         // Original text input by the user
    char processedText[64] = "";    // Processed text
    int inputCursor = 0;             // Cursor for user input

    int key = 3;                      // Encryption key
    int step = 0;                     // Current letter being processed
    int displayedKey = 0;             // Animated key display
    int delayCounter = 0;             // Counter to slow down animation
    const int delayThreshold = 15;    // Frames to wait between updates
    bool isEncrypting = false;        // State of encryption
    bool isDecrypting = false;        // State of decryption
    bool inputComplete = false;       // User has completed input

    while (!WindowShouldClose()) {
        // Handle user text input
        if (!inputComplete) {
            int keyPressed = GetKeyPressed();
            if (keyPressed >= 32 && keyPressed <= 126 && inputCursor < sizeof(plainText) - 1) {
                plainText[inputCursor++] = (char)keyPressed;
                plainText[inputCursor] = '\0';
            }
            if (IsKeyPressed(KEY_BACKSPACE) && inputCursor > 0) {
                plainText[--inputCursor] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && inputCursor > 0) {
                strcpy(processedText, plainText); // Copy plain text for processing
                inputComplete = true;
            }
        }

        // Start encryption animation
        if (inputComplete && IsKeyPressed(KEY_E) && !isEncrypting && !isDecrypting) {
            strcpy(processedText, plainText);
            step = 0;
            displayedKey = 0;
            delayCounter = 0;
            isEncrypting = true;
        }

        // Start decryption animation
        if (inputComplete && IsKeyPressed(KEY_D) && !isDecrypting && !isEncrypting) {
            strcpy(processedText, plainText);
            step = 0;
            displayedKey = 0;
            delayCounter = 0;
            isDecrypting = true;
        }

        // Process one letter per frame for encryption or decryption
        if ((isEncrypting || isDecrypting) && delayCounter >= delayThreshold) {
            delayCounter = 0; // Reset delay counter

            if (isEncrypting && step < strlen(plainText)) {
                if (displayedKey < key) {
                    displayedKey++;
                } else {
                    EncryptText(processedText, key, step);
                    step++;
                    displayedKey = 0;
                    if (step == strlen(plainText)) isEncrypting = false;
                }
            }

            if (isDecrypting && step < strlen(plainText)) {
                if (displayedKey < key) {
                    displayedKey++;
                } else {
                    DecryptText(processedText, key, step);
                    step++;
                    displayedKey = 0;
                    if (step == strlen(plainText)) isDecrypting = false;
                }
            }
        } else {
            delayCounter++; // Increment delay counter
        }

        // Draw frame
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!inputComplete) {
            DrawText("Enter text and press ENTER:", 20, 20, 20, DARKGRAY);
            DrawText(plainText, 20, 60, 30, BLUE);
        } else {
            DrawText("Press 'E' to Encrypt or 'D' to Decrypt", 20, 20, 20, DARKGRAY);

            // Draw original text
            DrawText("Original Text:", 100, 100, 20, BLACK);
            DrawText(plainText, 100, 130, 30, BLUE);

            // Draw processed text
            DrawText("Processed Text:", 100, 200, 20, BLACK);
            DrawText(processedText, 100, 230, 30, ORANGE);

            // Display animation state
            if (isEncrypting) {
                DrawText("Encrypting letter by letter...", 400, 100, 20, GREEN);
                DrawText(TextFormat("Key: %d", displayedKey), 400, 130, 20, GREEN);
            } else if (isDecrypting) {
                DrawText("Decrypting letter by letter...", 400, 100, 20, RED);
                DrawText(TextFormat("Key: %d", displayedKey), 400, 130, 20, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
