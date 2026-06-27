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
};

struct Operation: public NodeBase {
  string op_name{};
  vector<string> arg_list{};

};

struct ASTNode: variant<Script, Mutation, Operation> {
  using variant::variant;

  string name() const {
    return visit(overload{

      [](const auto& a) -> string {
        return a.name;
      }

    });
  }

  void print(int indent) const {

    visit(overload{

      [indent](this auto&& self, const Script& s) -> void {
        (void)indent;
        println("{:>{}}ast visit script name {} indent {}", "", indent, s.name, indent);
        for(auto& statement: s.statements) {
          self(statement, indent + 2);
        }
      },

      [](this auto&& self, const Mutation& m, int indent) -> void {
        (void)indent;
        println("{:>{}}ast visit mutation name {} indent {}", "", indent, m.name, indent);
        println("mutation target {}", m.target);
        for(auto& op: m.operations) {
          self(op, indent + 2);
        }
      },

      [](this auto&&, const Operation& o, int indent) -> void {
        (void)indent;
        println("{:>{}}ast visit operation name {} indent {}", "", indent, o.name, indent);
        println("operation op_name {}", o.op_name);
        for(const auto& arg: o.arg_list) {
          println("operation {} arg {}", o.op_name, arg);
        }
      },

      [](const auto&) -> void {
        println("ast visit 0 param catchall pattern match");
      },

      [](const auto&, int) -> void {
        println("ast visit 1 param catchall pattern match");
      },

    });
  }

};

}

#endif

