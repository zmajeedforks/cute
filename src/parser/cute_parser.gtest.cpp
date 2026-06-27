// cute_parser.gtest.cpp

/*
MIT License

Copyright (c) 2026 Zartaj Majeed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sstream>
#include <string>
#include <print>

#include <gtest/gtest.h>

#include "lexer/cute_lexer.h"
#include "cute_parser.bison.h"

using namespace std;

using namespace ::testing;

namespace cuteparser::testing {

TEST(BisonParser, test_000) {

  stringstream s("url");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  CuteParser parser([&lexer](LexParam& lexParam) -> CuteParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);
  
  EXPECT_EQ(parser(), 0);
}

TEST(BisonParser, test_001) {

  stringstream s("url --set http://example.com");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

// fake lexical feedback callback
  lexParam.get_arg_count = [](const string&) {
    return 1;
  };

  
  CuteParser parser([&lexer](LexParam& lexParam) -> CuteParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);
  
  EXPECT_EQ(parser(), 0);
}

TEST(BisonParser, test_002) {

  stringstream s("url --replace v1, v2");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

// fake lexical feedback callback
  lexParam.get_arg_count = [](const string&) {
    return 2;
  };

  CuteParser parser([&lexer](LexParam& lexParam) -> CuteParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);
  
#if 0
  lexer.set_debug(1);
  parser.set_debug_level(1);
#endif

  EXPECT_EQ(parser(), 0);
}

TEST(BisonParser, test_003) {

  stringstream s(R"%(
url --set http://example.com
url --set "http://example.com/path with spaces"
url --match api/v1 --replace v1, v2
)%");
  Lexer lexer(s);
  BisonParam bisonParam;
  LexParam lexParam;

  CuteParser parser([&lexer](LexParam& lexParam) -> CuteParser::symbol_type {
    return lexer.yylex(lexParam);
  },
  bisonParam,
  lexParam);

  auto& ast = bisonParam.ast;

  EXPECT_EQ(parser(), 0);

  println("print ast");
  ast.print(0);
}

}


