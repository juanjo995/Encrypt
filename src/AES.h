#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <sstream>
#include <fstream>

extern "C" {
    #include "../include/tiny-AES-c/aes.h"
}

inline std::string toHexString(const std::vector<uint8_t>& data) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for(const auto& byte : data) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    
    return ss.str();
}

inline std::vector<uint8_t> fromHexString(const std::string& hexStr) {
    // Check for valid input: must have even length
    if(hexStr.length() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even number of characters");
    }
    
    std::vector<uint8_t> result;
    result.reserve(hexStr.length() / 2);
    
    for(size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        
        // Convert hex string to integer using std::stoi with base 16
        try {
            uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
            result.push_back(byte);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid hex character in string");
        }
    }
    
    return result;
}

// Pad data to be a multiple of AES block size (16 bytes)
inline std::vector<uint8_t> padData(const std::string& input) {
    size_t inputLength = input.length();
    size_t paddedLength = ((inputLength + 15) / 16) * 16; // Round up to multiple of 16
    
    std::vector<uint8_t> padded(paddedLength, 0);
    std::copy(input.begin(), input.end(), padded.begin());
    
    // Add PKCS#7 padding
    uint8_t paddingValue = paddedLength - inputLength;
    for(size_t i = inputLength; i < paddedLength; i++) {
        padded[i] = paddingValue;
    }
    
    return padded;
}

// Remove padding from decrypted data
inline std::string removePadding(const std::vector<uint8_t>& padded) {
    if(padded.empty()) return "";
    
    uint8_t paddingValue = padded.back();
    if(paddingValue > 16) return std::string(padded.begin(), padded.end()); // Invalid padding
    
    size_t dataLength = padded.size() - paddingValue;
    return std::string(padded.begin(), padded.begin() + dataLength);
}

inline std::vector<uint8_t> keyFromPassword(const std::string& password, size_t keyLength = 16) {
    std::vector<uint8_t> key(keyLength, 0);
    // Simple key derivation - still not secure for production
    for(size_t i = 0; i < password.length(); i++) {
        key[i % keyLength] ^= static_cast<uint8_t>(password[i]);
    }
    // Additional mixing
    for(size_t i = 1; i < keyLength; i++) {
        key[i] ^= key[i-1];
    }
    
    return key;
}

inline std::vector<uint8_t> generate_random_iv() {
    std::vector<uint8_t> iv(16); // AES block size is 16 bytes
    
    // Use a cryptographically secure random number generator if possible
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    
    // Fill the IV with random bytes
    for(auto& byte : iv) {
        byte = static_cast<uint8_t>(distrib(gen));
    }
    
    return iv;
}

inline void encrypt(const std::string& path, const std::string& message, const std::string& password) {
    std::vector<uint8_t> key = keyFromPassword(password);
    std::vector<uint8_t> iv = generate_random_iv();

    std::vector<uint8_t> paddedMessage = padData(message);
    std::vector<uint8_t> encrypted = paddedMessage;

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key.data(), iv.data());

    AES_CBC_encrypt_buffer(&ctx, encrypted.data(), encrypted.size());

    std::string output = toHexString(encrypted) + '\n' + toHexString(iv);

    std::ofstream out(path);
    if(out.is_open()) {
        out << output;
        out.close();
    } else {
        std::cout << "No se pudo abrir el fichero.\n";
    }
}

inline std::string decrypt(const std::string& path, const std::string& password) {
    std::ifstream in(path);
    std::string encryptedMessageHex;
    std::string ivHex;
    if(in.is_open()) {
        std::getline(in, encryptedMessageHex);
        std::getline(in, ivHex);
        in.close();
    } else {
        std::cout << "No se pudo abrir el fichero.\n";
        return "";
    }

    std::vector<uint8_t> key = keyFromPassword(password);
    std::vector<uint8_t> iv = fromHexString(ivHex);

    std::vector<uint8_t> decrypted = fromHexString(encryptedMessageHex);

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key.data(), iv.data());

    AES_CBC_decrypt_buffer(&ctx, decrypted.data(), decrypted.size());

    std::string decryptedMessage = removePadding(decrypted);
    return decryptedMessage;
}
