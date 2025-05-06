#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <ctime>
#include <chrono>

using namespace std;

const int MAX_TRANSACTIONS = 3; // Limit per block

class Block {
private:
    int index;
    string prev_hash;
    int nonce;
    vector<string> transactions; // Stores multiple transactions

public:
    string time_stamp;
    string curr_hash;

    Block(int index, vector<string> transactions, string prev_hash)
        : index(index), transactions(transactions), prev_hash(prev_hash), nonce(0) {
        time_stamp = getCurrentTime();
        curr_hash = mineBlock(4);
    }

    void getBlock() {
        cout << "\n==============================";
        cout << "\nBlock Mined!";
        cout << "\nIndex: " << index;
        cout << "\nPrevious Hash: #" << prev_hash;
        cout << "\nTime Stamp: " << time_stamp;
        cout << "\nTransactions:";
        for (const string& tx : transactions) {
            cout << "\n  - " << tx;
        }
        cout << "\nNonce: " << nonce;
        cout << "\nCurrent Hash: #" << curr_hash;
        cout << "\n==============================\n";
    }

    string getCurrentTime() {
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        struct tm* parts = localtime(&now_c);

        stringstream timeStream;
        timeStream << put_time(parts, "%d/%m/%Y %H:%M:%S");
        return timeStream.str();
    }

    string calculateHash() {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        stringstream ss;
        string inputStr = to_string(index) + prev_hash + time_stamp + to_string(nonce);

        for (const string& tx : transactions) {
            inputStr += tx;
        }

        SHA256(reinterpret_cast<const unsigned char*>(inputStr.c_str()), inputStr.size(), hash);

        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        return ss.str();
    }

    string mineBlock(int difficulty) {
        string target(difficulty, '0');
        do {
            nonce++;
            curr_hash = calculateHash();
        } while (curr_hash.substr(0, difficulty) != target);

        return curr_hash;
    }
};

class Blockchain {
private:
    vector<Block> chain;

    Block createGenesisBlock() {
        return Block(0, {"Genesis Block"}, "None");
    }

public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    Block getLatestBlock() {
        return chain.back();
    }

    void addBlock(vector<string> transactions) {
        Block newBlock(chain.size(), transactions, getLatestBlock().curr_hash);
        chain.push_back(newBlock);
    }

    void displayChain() {
        for (int i = 0; i < chain.size(); i++) {
            chain[i].getBlock();
        }
    }
};

// Function to get user transactions
vector<string> getTransactions() {
    vector<string> transactions;
    char choice;

    while (transactions.size() < MAX_TRANSACTIONS) {
        string sender, receiver, amount, transaction;
        
        cout << "\nEnter Transaction Details:";
        cout << "\nSender: ";
        cin >> sender;
        cout << "Receiver: ";
        cin >> receiver;
        cout << "Amount: ";
        cin >> amount;

        transaction = sender + " pays " + receiver + " " + amount + " BTC";
        transactions.push_back(transaction);

        if (transactions.size() == MAX_TRANSACTIONS) {
            cout << "\nTransaction limit reached. Block will be automatically mined.\n";
            break;
        }

        cout << "Do you want to add another transaction? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    return transactions;
}

int main() {
    Blockchain myBlockchain;
    char choice;

    while (true) {
        cout << "\nAdding a new block...\n";
        vector<string> transactions = getTransactions();

        cout << "\nFinalizing block and mining...\n";
        myBlockchain.addBlock(transactions);

        cout << "Do you want to add another block? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    cout << "\nBlockchain Structure:\n";
    myBlockchain.displayChain();

    return 0;
}