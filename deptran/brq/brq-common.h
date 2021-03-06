#pragma once

// #include "all.h"

#include "brq-graph.h"

namespace rococo {

class CommandOutput {
  // TODO
};

class Command {
  // TODO
public:
  std::vector<groupid_t>& get_groups();

  void feed(CommandOutput &output);
};

class SubGraph {
public:
  
};

struct FastAcceptRequest {
  cmdid_t  cmd_id; // used as instance locater
  cooid_t  coo_id;
  ballot_t ballot;
  Command  cmd;
};

struct FastAcceptReply {
  bool     ack; // true or false: yes or no
  SubGraph deps;
};

struct PrepareReqeust {
  cmdid_t  cmd_id;
  cooid_t  coo_id;
  ballot_t ballot;
};

struct PrepareReply {
  bool     ack;
  ballot_t ballot_cmd_vote;
  ballot_t ballot_deps_vote;
  Command  cmd;  // optional
  SubGraph deps; // optional
};

struct AcceptRequest {
  cmdid_t cmd_id;
  ballot_t ballot;
  Command  cmd;
  SubGraph deps;
};

struct AcceptReply {
  bool ack;
};

struct CommitRequest {
  ballot_t ballot;
  Command  cmd;
  SubGraph deps;
};

struct CommitReply {
  CommandOutput output;
};

struct InquiryReply {

};

// struct InquireRequest {
//   cmdid_t cmd_id;
// }
//
// struct InquireReply {
//   SubGraph deps;
// }
//
} // namespace rococo
