#include <iostream>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <cstring>

using namespace std;

string aes_encrypt(const string& plaintext, const unsigned char* key, int key_length) {
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key, key_length * 8, &aes_key) < 0) {
        cerr << "Failed to set AES encryption key\n";
        return "";
    }

    int padding = AES_BLOCK_SIZE - (plaintext.length() % AES_BLOCK_SIZE);
    string padded_plain = plaintext;
    if (padding != AES_BLOCK_SIZE) {
        padded_plain.append(padding, padding);
    }

    string ciphertext;
    ciphertext.resize(padded_plain.size());
    AES_encrypt((const unsigned char*)padded_plain.c_str(), (unsigned char*)ciphertext.data(), &aes_key);

    return ciphertext;
}

string aes_decrypt(const string& ciphertext, const unsigned char* key, int key_length) {
    AES_KEY aes_key;
    if (AES_set_decrypt_key(key, key_length * 8, &aes_key) < 0) {
        cerr << "Failed to set AES decryption key\n";
        return "";
    }

    string plaintext;
    plaintext.resize(ciphertext.size());
    AES_decrypt((const unsigned char*)ciphertext.c_str(), (unsigned char*)plaintext.data(), &aes_key);

    size_t padding = (size_t)plaintext.back();
    plaintext.resize(plaintext.size() - padding);

    return plaintext;
}

int main() {
    const int key_length = 32;
    unsigned char key[key_length];
    RAND_bytes(key, key_length);

    string plaintext = "Hello World!";

    string ciphertext = aes_encrypt(plaintext, key, key_length);
    cout << "Ciphertext: " << ciphertext << endl;

    string decrypted_text = aes_decrypt(ciphertext, key, key_length);
    cout << "Decrypted: " << decrypted_text << endl;

    return 0;
}
