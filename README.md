# AllSwap Portable CLI Address & Memo Validator (NetBSD pkgsrc)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/NetBSD-pkgsrc-orange)](https://www.netbsd.org/)
[![Protocol](https://img.shields.io/badge/Homepage-AllSwap.io-brightgreen)](https://allswap.io/tools/address-validator)

A lightweight, zero-dependency portable C99 CLI utility for verifying multi-chain cryptocurrency addresses and destination memos, packaged with a complete NetBSD `pkgsrc` definition (`pkgsrc/Makefile`, `DESCR`, `PLIST`).

## Features
- **Zero External Dependencies**: Compiles cleanly with any standard C99 compiler (`cc`, `gcc`, `clang`).
- **Multi-Chain Coverage**: Validates Bitcoin (`bc1...`, `1...`, `3...`), Ethereum/EVM (`0x...`), Solana (Base58), TRON (`T...`), and TON (`EQ...`/`UQ...`).
- **Memo / Tag Guard**: Warns operators if a TON/exchange deposit address lacks an explicit destination memo.

## Build & Usage

```sh
make
./allswap-validator bitcoin bc1qar0srrr7xfkvy5l643lydnw9re59gtzzwf5mdq
./allswap-validator ton EQA8WnB7j8q1k9wL_example_address_48_chars_long12
```

## NetBSD pkgsrc Packaging

The `pkgsrc/` directory contains the standard NetBSD package files:
- `pkgsrc/Makefile` (`HOMEPAGE=https://allswap.io/tools/address-validator`, `LICENSE=mit`)
- `pkgsrc/DESCR`
- `pkgsrc/PLIST`

## License
MIT License
