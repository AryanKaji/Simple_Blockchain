#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/ssl.h>
#include <openssl/sha.h>

using namespace std;

class Block{
    int index;
    string prev_hash;
    string time_stamp;
    string data;
public:
    string curr_hash;

    Block(int index, string data, string prev_hash){
        this->index = index;
        this->data = data;
        this->prev_hash = prev_hash;
        time_stamp = getCurrentTime();
        curr_hash = calculateHash ();
    }

    void getBlock(){
        cout << "\nIndex: " << index;
        cout << "\nPrevious Hash: #" << prev_hash;
        cout << "\nTime Stamp: " << time_stamp;
        cout << "\nData: " << data;
        cout << "\nCurrent Hash: #" << curr_hash;
        cout << "\n-------\n";
    }

    string calculateHash(){
        string inputStr = to_string(index) + prev_hash + time_stamp + data;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        const unsigned char* dataBytes = reinterpret_cast<const unsigned char*>(inputStr.c_str());
        SHA256(dataBytes, inputStr.size(), hash);
    
        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
    
    string getCurrentTime() {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
        return std::string(buffer);
    }
};

class Blockchain{
    vector<Block> chain;
    Block createGenesisBlock(){
        return Block (0, "This is Genesis Block...\nA simple C++ blockchain implementation that uses \nSHA-256 hashing via OpenSSL to securely link blocks \ncontaining data.", "Non");
    }

public:
    Blockchain(){
        chain.push_back(createGenesisBlock());
    }

    Block getLatestBlock(){
         return chain.back();
    }

    void addBlock(string data){ 
        Block newBlock(chain.size(), data, getLatestBlock().curr_hash);
        chain.push_back(newBlock);
    }

    void displayChain(){
        for (int i = 0; i < chain.size(); i++) {
            chain[i].getBlock();
        }
    }
};

int main() {
    Blockchain myBlockchain;
    myBlockchain.addBlock("hello 0");
    myBlockchain.addBlock("hello 1");
    myBlockchain.addBlock("hello 2");
    myBlockchain.addBlock("hello 3");
    myBlockchain.addBlock("hello 4");
    myBlockchain.displayChain();
    return 0;
}
