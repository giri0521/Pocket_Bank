#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace packetbank {
    struct Transaction {
        std::string id;
        std::string account;
        std::string category;
        double amount{};
        std::string note;
    };

class Ledger {
    public:
        void add(const Transaction& t);
        std::optional<Transaction> get(const std::string& id) const;
        double balance(const std::string& account) const;
        const std::vector<Transaction>& all() const noexcept {return txs_; }
    private:
        std::vector<Transaction> txs_;
};
}