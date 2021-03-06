#pragma once

#include "all.h"
#include "graph.hpp"

/**
 * This is NOT thread safe!!!
 */
namespace rococo {

class DepGraph {
public:
//    Graph<PieInfo> pie_gra_;
    Graph<TxnInfo> txn_gra_;

    std::vector<rrr::Client*> rpc_clients_;
    std::vector<RococoProxy*> rpc_proxies_;
    std::vector<std::string> server_addrs_;


    DepGraph() {
        // TODO remove this out       
        Config::get_config()->get_all_site_addr(server_addrs_);
        rpc_clients_ = std::vector<rrr::Client*>(server_addrs_.size(), nullptr);
        rpc_proxies_ = std::vector<RococoProxy*>(server_addrs_.size(), nullptr);
    }

    ~DepGraph() {
        // XXX hopefully some memory leak here does not hurt. :(
    }

    RococoProxy* get_server_proxy(uint32_t id);

    /** on start_req */
    void start_pie(
            txnid_t txn_id,
            Vertex<TxnInfo> **tv
    );

    void union_txn_graph(Graph<TxnInfo>& gra) {
        txn_gra_.union_graph(gra, true);
    }

    std::vector<Vertex<TxnInfo>*> find_txn_scc(TxnInfo &ti) {
        return txn_gra_.find_scc(ti);
    }

    void find_txn_anc_opt(
            Vertex<TxnInfo>* source,
            std::unordered_set<Vertex<TxnInfo>*> &ret_set
    );

    void find_txn_anc_opt(
            uint64_t txn_id,
            std::unordered_set<Vertex<TxnInfo>*> &ret_set
    );

    void find_txn_nearest_anc(
            Vertex<TxnInfo>* v,
            std::set<Vertex<TxnInfo>*> &ret_set
    ) {
        for (auto &kv: v->from_) {
            ret_set.insert(kv.first);
        }
    }

    void find_txn_scc_nearest_anc(
            Vertex<TxnInfo> *v,
            std::set<Vertex<TxnInfo>*> &ret_set
    ) {
        std::vector<Vertex<TxnInfo>*> scc = txn_gra_.find_scc(v);
        for (auto v: scc) {
            find_txn_nearest_anc(v, ret_set);
        }

        for (auto &scc_v: scc) {
            ret_set.erase(scc_v);
        }

        //if (RandomGenerator::rand(1, 100) == 1) {
        //    Log::info("scc anc size: %d", ret_set.size());
        //}
    }


    void find_txn_scc_anc_opt(
            uint64_t txn_id,
            std::unordered_set<Vertex<TxnInfo>*> &ret_set
    );

    uint64_t sub_txn_graph(
            uint64_t tid,
            GraphMarshaler &gra_m
    );
};
} // namespace rcc
