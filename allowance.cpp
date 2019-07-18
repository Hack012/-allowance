#include <eosio/eosio.hpp>

using namespace eosio;
CONTRACT allowance: public contract {
    public:
    using contract::contract;

    ACTION hi(name user) {
        //require_auth("wonwonwonwon"_n);
        
        address_index forHi(get_self(), get_self().value);
        auto itr = forHi.find(user.value);
        
        if(itr == forHi.end()){
            print("!PLEASE ENROLL FIRST");
        }
        else {
             print("hi, ", user);
        }
        
        
    }

    ACTION insert(name user) {
        //require_auth(user);

        check(has_auth("wonwonwonwon"_n), "!WARN");
        address_index forInsert(get_self(), get_self().value);
        auto itr = forInsert.find(user.value);

        check(itr == forInsert.end(), "!!!already exists!!!");

        forInsert.emplace(user, [&](auto& row){
            row.user = user;
        });

        print("!!!INSERT SUCCESS!!!");
    }

    ACTION remove(name user) {
        //require_auth(user);

        check(has_auth("wonwonwonwon"_n), "!WARN");
        address_index forRemove(get_self(), get_self().value);
        auto itr = forRemove.require_find(user.value, "no account");
        forRemove.erase(itr);

        print("!!!REMOVE SUCCESS!!!");
    }
    private:
    struct [[eosio::table]] person {
        name user;
        
        uint64_t primary_key() const { return user.value; }
    };

    typedef multi_index<"people"_n,person> address_index;

};