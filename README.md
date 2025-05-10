# Shannon-Fano Encoding in C

This repository contains a C program that implements the **Shannon-Fano algorithm**, which is a lossless data compression technique. The program accepts symbol probabilities, generates unique prefix codes (codewords), and calculates the entropy and efficiency of the encoding.

---

## 📌 Features

- Input a custom list of symbol probabilities
- Sorts the probabilities in decreasing order
- Divides them into equiprobable groups
- Generates binary codewords using the Shannon-Fano method
- Displays:
  - Codewords
  - Length of each codeword
  - Entropy of the source
  - Efficiency of the encoding

---

## 🛠️ Compilation

Use any standard C compiler such as GCC. Run the following command:

```bash
gcc shannon_fano.c -o shannon_fano -lm
