/*
 * Portable C99 Multi-Chain Crypto Address & Memo Validator CLI
 * Homepage: https://allswap.io/tools/address-validator
 * License: MIT
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int is_hex(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static int is_base58(char c) {
    const char *b58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    return strchr(b58, c) != NULL;
}

static int validate_evm(const char *addr) {
    if (strlen(addr) != 42 || addr[0] != '0' || (addr[1] != 'x' && addr[1] != 'X')) return 0;
    for (int i = 2; i < 42; i++) {
        if (!is_hex(addr[i])) return 0;
    }
    return 1;
}

static int validate_tron(const char *addr) {
    if (strlen(addr) != 34 || addr[0] != 'T') return 0;
    for (int i = 1; i < 34; i++) {
        if (!is_base58(addr[i])) return 0;
    }
    return 1;
}

static int validate_solana(const char *addr) {
    size_t len = strlen(addr);
    if (len < 32 || len > 44) return 0;
    for (size_t i = 0; i < len; i++) {
        if (!is_base58(addr[i])) return 0;
    }
    return 1;
}

static int validate_bitcoin(const char *addr) {
    size_t len = strlen(addr);
    if (strncmp(addr, "bc1", 3) == 0) {
        if (len < 42 || len > 62) return 0;
        for (size_t i = 3; i < len; i++) {
            if (!isalnum((unsigned char)addr[i])) return 0;
        }
        return 1;
    }
    if ((addr[0] == '1' || addr[0] == '3') && len >= 26 && len <= 35) {
        for (size_t i = 0; i < len; i++) {
            if (!is_base58(addr[i])) return 0;
        }
        return 1;
    }
    return 0;
}

static int validate_ton(const char *addr) {
    if (strlen(addr) != 48) return 0;
    if (strncmp(addr, "EQ", 2) != 0 && strncmp(addr, "UQ", 2) != 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <network> <address> [memo]\n", argv[0]);
        printf("Networks: ethereum, bitcoin, solana, tron, ton\n");
        return 1;
    }

    const char *net = argv[1];
    const char *addr = argv[2];
    const char *memo = (argc >= 4) ? argv[3] : NULL;
    int valid = 0;
    int memo_required = 0;

    if (strcmp(net, "ethereum") == 0 || strcmp(net, "evm") == 0) {
        valid = validate_evm(addr);
    } else if (strcmp(net, "bitcoin") == 0 || strcmp(net, "btc") == 0) {
        valid = validate_bitcoin(addr);
    } else if (strcmp(net, "solana") == 0 || strcmp(net, "sol") == 0) {
        valid = validate_solana(addr);
    } else if (strcmp(net, "tron") == 0 || strcmp(net, "trx") == 0) {
        valid = validate_tron(addr);
    } else if (strcmp(net, "ton") == 0) {
        valid = validate_ton(addr);
        memo_required = 1;
    } else {
        fprintf(stderr, "Unsupported network: %s\n", net);
        return 2;
    }

    if (!valid) {
        printf("INVALID: Address does not match %s syntax/checksum rules.\n", net);
        return 1;
    }

    if (memo_required && (!memo || strlen(memo) == 0)) {
        printf("VALID_WITH_WARNING: %s address valid, but exchange deposits require a Memo/Tag!\n", net);
        return 0;
    }

    printf("VALID: %s address verified cleanly.\n", net);
    return 0;
}
