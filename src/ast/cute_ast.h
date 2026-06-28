#ifndef CUTE_AST_H
#define CUTE_AST_H

#include <string>
#include <memory>
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

struct AndExpression;
struct ASTNode;
struct Block;
struct Expr;
struct Mutation;
struct NotExpr;
struct Pipeline;
struct Operation;
struct OrExpr;
struct Segment;

#if 1
using Statement = Mutation;
#else
struct Statement;
#endif


struct NodeBase {
  string name = "NodeBase";
};

struct Script: public NodeBase {
  vector<Pipeline> pipelines{};
};

struct Pipeline: public NodeBase {
  vector<Segment> segments{};
};

struct Segment: public NodeBase {
  vector<Statement> statements{};
};

struct Block: public NodeBase {
  vector<Statement> statements;
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

struct LitExpr: variant<monostate, bool> {
  using variant::variant;
};

struct AndExpr: public NodeBase {
  unique_ptr<Expr> left;
  unique_ptr<Expr> right;
};

struct OrExpr: public NodeBase {
  unique_ptr<Expr> left;
  unique_ptr<Expr> right;
};

struct NotExpr: public NodeBase {
  unique_ptr<Expr> expr;
};

struct Expr: variant<LitExpr, AndExpr, OrExpr, NotExpr> {
  using variant::variant;
};

struct ASTNode: variant<Script, Pipeline, Segment, Mutation, Operation> {
  using variant::variant;

  string name() const {
    return visit(overload{

      [](const auto& a) -> string {
        return a.name;
      }

    });
  }

  void printAst(int indent) const {

    visit(overload{

      [indent](this auto&& self, const Script& s) -> void {
        print("{:>{}}", "", indent);
        println("ast visit script name {} indent {}", s.name, indent);
        for(auto& pipeline: s.pipelines) {
          self(pipeline, indent + 2);
        }
      },

      [](this auto&& self, const Pipeline& p, int indent) -> void {
        print("{:>{}}", "", indent);
        println("ast visit pipeline name {} indent {}", p.name, indent);
        for(auto& segment: p.segments) {
          self(segment, indent + 2);
        }
      },

      [](this auto&& self, const Segment& s, int indent) -> void {
        print("{:>{}}", "", indent);
        println("ast visit segment name {} indent {}", s.name, indent);
        for(auto& statement: s.statements) {
          self(statement, indent + 2);
        }
      },

      [](this auto&& self, const Mutation& m, int indent) -> void {
        print("{:>{}}", "", indent);
        println("ast visit mutation name {} indent {}", m.name, indent);
        print("{:>{}}", "", indent);
        println("mutation target {}", m.target);
        for(auto& op: m.operations) {
          self(op, indent + 2);
        }
      },

      [](this auto&&, const Operation& o, int indent) -> void {
        print("{:>{}}", "", indent);
        println("ast visit operation name {} indent {}", o.name, indent);
        print("{:>{}}", "", indent);
        println("operation op_name {}", o.op_name);
        for(const auto& arg: o.arg_list) {
          print("{:>{}}", "", indent);
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

