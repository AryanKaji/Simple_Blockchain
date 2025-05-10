# Simple C++ Blockchain

This project is a basic implementation of a blockchain in C++, 
demonstrating core blockchain principles such as data immutability, 
chaining via cryptographic hashes, and timestamping using SHA-256 (via OpenSSL).
---

## Features

- Creates a blockchain starting with a genesis block.
- Each block contains:
  - An index
  - Timestamp
  - Data
  - Previous block's hash
  - Its own current hash
- SHA-256 hashing is performed using OpenSSL.
- Outputs the entire blockchain to the console.
---

## Requirements

- C++ compiler (e.g., g++, clang++)
- [OpenSSL](https://www.openssl.org/) library installed
- Windows users: Ensure MinGW/MSYS2 is configured with OpenSSL support
---

## How to Build

### Windows (MSYS2 example):

```bash
g++ blockchain.cpp -o blockchain -lssl -lcrypto
