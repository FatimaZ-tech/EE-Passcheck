#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <map>
#include <iomanip>

using namespace std;

// Utility

double bits_to_seconds(double bits, double guesses_per_sec) {
    return exp2(bits) / guesses_per_sec;
}

string human_time(double seconds) {
    if (seconds < 60) return to_string((int)round(seconds)) + " seconds";
    if (seconds < 3600) return to_string((int)round(seconds / 60)) + " minutes";
    if (seconds < 86400) return to_string((int)round(seconds / 3600)) + " hours";
    if (seconds < 31536000) return to_string((int)round(seconds / 86400)) + " days";
    return to_string((int)round(seconds / 31536000)) + " years";
}

// Expectation Entropy inspired operationalization

double expectation_entropy(const string &pw) {
    if (pw.empty()) return 0.0;

    map<string, int> freq;
    for (unsigned char c : pw) {
        if (islower(c)) freq["lower"]++;
        else if (isupper(c)) freq["upper"]++;
        else if (isdigit(c)) freq["digit"]++;
        else freq["symbol"]++;
    }

    double L = pw.length();
    double per_char_entropy = 0.0;

    for (auto &kv : freq) {
        double p = kv.second / L;

        double class_pool = 26;
        if (kv.first == "digit")  class_pool = 10;
        if (kv.first == "symbol") class_pool = 32;

        double symbol_prob = p / class_pool;
        if (symbol_prob > 0) {
            per_char_entropy += -p * log2(symbol_prob);
        }
    }

    return per_char_entropy * L;
}

// Main

int main() {

    cout << "=== Educational Password Strength Estimator ==="<<endl<<endl;
    cout << "DISCLAIMER:"<<endl;
    cout << "This tool provides an EDUCATIONAL estimation based on Expectation Entropy and simplified offline attacker assumptions. It does NOT account for leaked passwords or advanced cracking strategies."<<endl<<endl;

    string password;
    cout << "Enter a password to evaluate: ";
    cin>>password;

    double entropy_bits = expectation_entropy(password);

    const double gpu_attacker = 1e9;     // guesses/sec
    const double state_attacker = 1e12;  // guesses/sec

    double time_gpu = bits_to_seconds(entropy_bits, gpu_attacker);
    double time_state = bits_to_seconds(entropy_bits, state_attacker);

    cout <<endl<< "=== Results ==="<<endl<<endl;
    cout << "Estimated entropy: " << (int)round(entropy_bits) << " bits"<<endl<<endl;

    cout << "Estimated offline brute-force crack time:"<<endl;
    cout << "1) GPU-scale attacker (1e9 guesses/sec): "
         << human_time(time_gpu) << endl;
    cout << "2) Nation-state attacker (1e12 guesses/sec): "
         << human_time(time_state) << endl;

    cout <<endl;
    cout << "These estimates show how long a offline brute-force attack might take under the documented assumptions. They are NOT guarantees of real-world security."<<endl;

    return 0;
}
