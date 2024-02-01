#include <iostream>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <iomanip>
#include <stdexcept>

class AESKeyGenerationError : public std::runtime_error {
public:
    AESKeyGenerationError(const std::string& message) : std::runtime_error(message) {}
};

void generateAESKey(int keySize) {
    unsigned char key[keySize / 8]; // in bits

    if (RAND_bytes(key, sizeof(key)) != 1) {
        throw AESKeyGenerationError("Error generating random bytes.");
    }

    std::cout << "Generated AES Key (" << keySize << " bits): ";
    for (size_t i = 0; i < sizeof(key); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i]);
    }
    std::cout << std::dec << std::endl;
}

int main() {
    int keySize = 128;

    try {
        OpenSSL_add_all_algorithms();
        generateAESKey(keySize);

        EVP_cleanup();
    } catch (const AESKeyGenerationError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
