# EE-Passcheck
This is an applied security research tool that demonstrates structure based password entropy estimation inspired by Expectation Entropy and provides an offline brute-force crack-time interpretation under simplified attacker assumptions.

The repository accompanies a short research report that explains the background, motivation, mathematical formulation, and limitations of
the approach in detail.

---

## Usage

To run this tool, install any C++17-compatible compiler and compile the provided `main.cpp` source file. The program operates in an interactive mode and prompts the user to enter a password for evaluation.

For a complete explanation of the underlying research logic and assumptions, refer to the accompanying report.

---

## Disclaimer

This tool is intended strictly for **educational and research demonstration purposes**. It does not model real-world password cracking techniques such as dictionary attacks, leaked password datasets, probabilistic language models, or cracking strategies. Estimated cracking times are illustrative only and should not be interpreted as security guarantees.
