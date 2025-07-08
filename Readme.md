
# 📬 Basic gRPC Email Verifier in C++

Have you ever signed up for an app and suddenly got this message?

> **"Invalid email!"**

Even though it was just a small typo?

In this project, we’re building a simple **Email Verifier** system using **gRPC** and **C++**, just like the ones used in real-world applications to validate email inputs before account creation.

---

## 🚀 What Does It Do?

This gRPC service:

- Accepts an email address from the client
- Checks if the format is valid (i.e., contains `@`)
- Extracts the domain part
- Determines if the domain is a common provider (like Gmail, Yahoo, etc.)

---

## 📦 Prerequisites

Make sure your system has the following:

- **CMake**
- **Protocol Buffers**
- **gRPC**
- **BloomRPC** (for testing)

### Install Dependencies (Ubuntu)

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  cmake \
  libprotobuf-dev \
  protobuf-compiler \
  protobuf-compiler-grpc \
  libgrpc++-dev \
  libgrpc-dev
```

### Verify Installation

```bash
cmake --version
protoc --version
which grpc_cpp_plugin
```

---

## 🗂 Project Structure

```
basic-grpc-emailverifier/
├── CMakeLists.txt
├── proto/
│   └── emailverifier.proto
└── src/
    ├── client.cpp
    └── server.cpp
```

## ⚙️ Building the Project

From the root directory:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

This generates two executables: `client` and `server`.

---

## ▶️ Running the Program

### Start the Server (Terminal 1)

```bash
./server
```

### Start the Client (Terminal 2)

```bash
./client
```

You’ll be prompted to enter an email address. The output will include:

- Whether the email is valid
- The extracted domain
- Whether the domain is a common provider

---

## 🧪 Test Using BloomRPC

1. Open **BloomRPC**
2. Import `proto/emailverifier.proto`
3. Set server URL: `localhost:50051`
4. Choose method: `CheckEmail`
5. Send a request like:

```json
{
  "email": "someone@gmail.com"
}
```

6. Click Run ▶ to see the response

---

## 💡 Notes

- Email validation is kept simple for demo purposes (just checks for the presence of `@`)
- Common domains are hardcoded (e.g., `gmail.com`, `yahoo.com`, etc.)
- Can be extended with DNS lookups, regex validation, or domain reputation checks

---

## 🤝 Contributing

Contributions are welcome! You can help by:

- Improving validation logic
- Externalizing the list of common domains
- Adding unit tests or CI setup

---

## 📎 References

- [gRPC C++ Docs](https://grpc.io/docs/languages/cpp/)
- [Protocol Buffers](https://protobuf.dev/)
- [BloomRPC](https://github.com/bloomrpc/bloomrpc)

---

## 📄 License

MIT License © 2025 Mahardika Pratama
