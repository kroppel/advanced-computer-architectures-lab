#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <unistd.h>
#include "Timer.hpp"

void key_scheduling_alg(unsigned char*       S,
                        const unsigned char* key,
                        const int            key_length) {
    for (int i = 0; i < 256; ++i)
        S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + key[i % key_length]) % 256;
        std::swap(S[i], S[j]);
    }
}

void pseudo_random_gen(unsigned char* S,
                       unsigned char* stream,
                       int            input_length) {
    for (int x = 0; x < input_length; ++x) {
        int i = (i + 1) % 256;
        int j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        stream[x] = S[(S[i] + S[j]) % 256];
    }
}

bool chech_hex(const unsigned char* cipher_text,
              const unsigned char* stream,
              const int            key_length) {
    for (int i = 0; i < key_length; ++i) {
        if (cipher_text[i] != stream[i])
            return false;
    }
    return true;
}

void print_hex(const unsigned char* text, const int length, const char* str) {
    std::cout << std::endl << std::left << std::setw(15) << str;
    for (int i = 0; i < length; ++i)
        std::cout << std::hex << std::uppercase << (int) text[i] << ' ';
    std::cout <<  std::dec << std::endl;
}

void RC4_ST() {
    unsigned char S[256],
    stream[key_length],
    key[key_length]         = {'K','e','y'},
    Plaintext[key_length]   = {'j','j','j'},
    cipher_text[key_length] = {0xB, 0xC7, 0x85};

    print_hex(Plaintext, key_length, "Plaintext:");
    print_hex(cipher_text, key_length, "cipher_text:");
    print_hex(key, key_length, "Key:");

    // -------------------------------------------------------------------------

    key_scheduling_alg(S, key, key_length);
    pseudo_random_gen(S, stream, key_length);

    print_hex(stream, key_length, "PRGA Stream:");

    // Encryption of plaintext by XOR with random number
    for (int i = 0; i < key_length; ++i)
        stream[i] = stream[i] ^ Plaintext[i];        // XOR

    print_hex(stream, key_length, "XOR:");
    if (chech_hex(cipher_text, stream, key_length))
        std::cout << "\n\ncheck ok!\n\n";
    std::cout << "\nCracking..." << std::endl;

    // --------------------- CRACKING Single-Threaded------------------------------------------

    timer::Timer<timer::HOST> TM;
    TM.start();

    std::fill(key, key + key_length, 0);

    for (int k = 0; k < (1<<24); ++k) {
        key_scheduling_alg(S, key, key_length);
        pseudo_random_gen(S, stream, key_length);

        for (int i = 0; i < key_length; ++i)
            stream[i] = stream[i] ^ Plaintext[i];        // XOR

        if (chech_hex(cipher_text, stream, key_length)) {
            std::cout << " <> CORRECT\n\n";
            break;
        }
        int next = 0;
        while (key[next] == 255) {
            key[next] = 0;
            ++next;
        }
        ++key[next];
    }

    TM.stop();
    double t_seq = TM.duration();

    std::cout << "Duration Single-threaded: " << TM.duration() << " ms.\n";

    if (not key_found) {
        std::cout << "\nERROR!! key not found\n\n";
    }
}

void RC4_MT() {
    unsigned char S[256],
    stream[key_length],
    key[key_length]         = {'K','e','y'},
    Plaintext[key_length]   = {'j','j','j'},
    cipher_text[key_length] = {0xB, 0xC7, 0x85};

    print_hex(Plaintext, key_length, "Plaintext:");
    print_hex(cipher_text, key_length, "cipher_text:");
    print_hex(key, key_length, "Key:");

    // -------------------------------------------------------------------------

    key_scheduling_alg(S, key, key_length);
    pseudo_random_gen(S, stream, key_length);

    print_hex(stream, key_length, "PRGA Stream:");

    // Encryption of plaintext by XOR with random number
    for (int i = 0; i < key_length; ++i)
        stream[i] = stream[i] ^ Plaintext[i];        // XOR

    print_hex(stream, key_length, "XOR:");
    if (chech_hex(cipher_text, stream, key_length))
        std::cout << "\n\ncheck ok!\n\n";
    std::cout << "\nCracking..." << std::endl;

    // --------------------- CRACKING Multi-Threaded------------------------------------------

    bool key_found = false;
    timer::Timer<timer::HOST> TM;

    TM.start();

    std::fill(key, key + key_length, 0);

#pragma omp parallel for schedule(dynamic) num_threads(1) shared(key_found, key_length) private(S, stream) firstprivate(key)
    for (int k = 0; k < (1<<24); ++k) {
        if (key_found) {
            continue;
        }
        std::cout << k;

        key_scheduling_alg(S, key, key_length);
        pseudo_random_gen(S, stream, key_length);

        for (int i = 0; i < key_length; ++i)
            stream[i] = stream[i] ^ Plaintext[i];        // XOR

        if (chech_hex(cipher_text, stream, key_length)) {
            std::cout << " <> CORRECT\n\n";
            key_found = true;
        }
        int next = 0;
        while (key[next] == 255) {
            key[next] = 0;
            ++next;
        }
        ++key[next];
    }

    TM.stop();
    double t_par = TM.duration();

    std::cout << "Duration Multi-threaded: " << TM.duration() << " ms.\n";

    std::cout << "Speedup: " << t_seq/t_par << std::endl;


    if (not key_found) {
        std::cout << "\nERROR!! key not found\n\n";
    }

    return 0;
}

const int bitLength  = 24;
const int key_length = bitLength / 8;

int main() {
    RC4_ST();
    RC4_MT();
}
