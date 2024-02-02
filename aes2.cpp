#include <iostream>
#include <iomanip>
#include <openssl/aes.h>
#include <openssl/rand.h>

// Function to generate a random key
void generateRandomKey(unsigned char* key, size_t keySize) {
    RAND_bytes(key, keySize);
}

// Function to print hex data
void printHex(const unsigned char* data, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    std::cout << std::dec << std::endl;
}

// Function to perform AES encryption
void aesEncrypt(const unsigned char* plaintext, size_t plaintextSize,
                const unsigned char* key, unsigned char* ciphertext) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}

// Function to perform AES decryption
void aesDecrypt(const unsigned char* ciphertext, size_t ciphertextSize,
                const unsigned char* key, unsigned char* decryptedtext) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    AES_decrypt(ciphertext, decryptedtext, &aesKey);
}

int main() {
    const size_t keySize = 16;
    const size_t blockSize = AES_BLOCK_SIZE;

    unsigned char key[keySize];
    generateRandomKey(key, keySize);

    std::cout << "Generated AES Key: ";
    printHex(key, keySize);

    const char* plaintext = "Hello, AES Encryption!";
    size_t plaintextSize = strlen(plaintext);

    unsigned char ciphertext[plaintextSize + blockSize];
    unsigned char decryptedtext[plaintextSize + blockSize];

    // Encryption
    aesEncrypt(reinterpret_cast<const unsigned char*>(plaintext), plaintextSize, key, ciphertext);

    std::cout << "Encrypted Text: ";
    printHex(ciphertext, plaintextSize + blockSize);

    // Decryption
    aesDecrypt(ciphertext, plaintextSize + blockSize, key, decryptedtext);

    std::cout << "Decrypted Text: " << decryptedtext << std::endl;

    return 0;
}
