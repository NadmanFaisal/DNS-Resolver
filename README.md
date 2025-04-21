# DNS-Resolver

A simple C program that uses the GNNU adns library to resolve both IPv4 and IPv6 addresses from user-taken domain input. 

# Features

- Takes a domain name as user input.
- Resolves and prints:
  - IPv4 addresses (A records).
  - IPv6 addresses (AAAA records).
- Uses asynchronous DNS resolution via `adns`.
- Logs resolver activity to a file.

# Dependencies

- GCC (or any C compiler)
- `libadns` (Advanced DNS client library)

# Installation

## Linux

```
sudo apt-get update
sudo apt-get install libadns1-dev
```

## macOS

If you don't have homebrew, run the following command:-

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Then write the following command to install GNU adns lib:-

```
brew install adns
```

To compile:-

```
gcc main.c -o main -ladns && ./main
```
