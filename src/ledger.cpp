#include "pocketbank/Ledger.hpp"
#include <numeric>

namespace pocketbank{
    void Ledger::add(const Transaction& t){txs_.push_back(t);}

    std::optional<Transaction> Ledger::get(const std::string& id) const {
        for(const auto& t : txs_){
            if(t.id == id){
                return t;
            }
        }
        return std::nullopt;
    }

    double Ledger::balance(const std::string& account) const {
        double sum = 0.0;
        for(const auto& t : txs_){
            if(t.account == account){
                sum +=t.amount;
            }
        }
        return sum;
    }
};