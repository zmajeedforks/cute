#ifndef CUTE_AST_H
#define CUTE_AST_H

#include <string>
#include <functional>
#include <variant>
#include <chrono>
#include <print>

namespace {

template<class... Ts>
struct overload: Ts... { using Ts::operator()...; };

}

namespace cuteparser {

using namespace std;
using namespace chrono;

struct ASTNode;
struct Mutation;
struct Operation;

#if 1
using Statement = Mutation;
#else
struct Statement;
#endif


struct NodeBase {
  string name = "NodeBase";
};

struct Script: public NodeBase {
  vector<Statement> statements{};
  void print() const;
};

#if 0
struct Statement: public NodeBase {
};
#endif

struct Option: public NodeBase {
};

struct Mutation: public NodeBase {
  string target{};
  vector<Operation> operations{};
  void print() const;
};

struct Operation: public NodeBase {
  string op_name{};
  vector<string> arg_list{};
  void print() const {
    println("operation op_name {}", op_name);
    for(const auto& arg: arg_list) {
      println("operation {} arg {}", op_name, arg);
    }
  }
};

struct ASTNode: variant<Script, Mutation, Operation, Option> {
  using variant::variant;

  string name() const {
    return visit(overload{

      [](const auto& a) -> string {
        return a.name;
      }

    });
  }

  void print() const {

    visit(overload{

      [](const Script& s) -> void {
        println("ast visit script name {}", s.name);
        s.print();
      },

      [](const Mutation& m) -> void {
        println("ast visit mutation name {}", m.name);
        m.print();
      },

      [](const Operation& o) -> void {
        println("ast visit operation name {}", o.name);
        o.print();
      },

      [](const auto&) -> void {
        println("ast visit catchall pattern match");
      }
    });
  }

};

inline
void Script::print() const {
  for(const auto& statement: statements) {
    statement.print();
  }
}

inline
void Mutation::print() const {
  println("mutation target {}", target);
  for(const auto& op: operations) {
    op.print();
  }
}

}

#endif

