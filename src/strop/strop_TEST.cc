/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "strop/strop.h"

#include <cstring>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "prim/prim.h"


const string foo = "foo";
const string bar = "bar";
const string foobar = "foobar";
const string FOO = "FOO";
const string BAR = "BAR";
const string FOOBAR = "FOOBAR";
const string TEXT_LIST_NOSEP = "foo bar baz";

const vector<string> PRIM_LIST = {"1", "2"};
const vector<string> ARRAY_FALSE_FALSE = {"false", "false"};
const vector<string> ARRAY_FALSE_TRUE = {"false", "true"};
const vector<string> ARRAY_FALSE_TRUE_FALSE = {"false", "true", "false"};
const vector<string> EMPTY_ARRAY_LIST = {};
const vector<string> ARRAY_LIST = {"foo", "bar", "baz"};
const vector<string> MIXED_ARRAY_LIST = {"", "foo"};
const vector<string> MIXED_TYPE_LIST = {"foo", to_string(2L)};
const vector<string> STRING_LIST = {"foo", "bar", "baz"};
const vector<string> EMPTY_STRING_LIST = {};

const char SEPARATOR_CHAR = ';';
const char COMMA_SEPARATOR_CHAR = ',';

TEST(StrOp, trim) {
  ASSERT_EQ("str ", strop::leftTrim(" str "));
  ASSERT_EQ(" str", strop::rightTrim(" str "));
  ASSERT_EQ("str", strop::trim(" str "));
  ASSERT_EQ("str    ", strop::leftTrim("    str    "));
  ASSERT_EQ("    str", strop::rightTrim("    str    "));
  ASSERT_EQ("str", strop::trim("    str    "));
}

TEST(StrOp, lowerUpper) {
  ASSERT_EQ("lower", strop::toLower("LoWeR"));
  ASSERT_EQ("UPPER", strop::toUpper("uPpEr"));
}

TEST(StrOp, split) {
  std::vector<std::string> exp = {"1", "2", "3"};
  std::vector<std::string> act;

  act = strop::split("1 2 3", ' ');
  ASSERT_EQ(exp.size(), act.size());
  for (u8 i = 0; i < exp.size(); i++) {
    ASSERT_EQ(act[i], exp[i]);
  }

  act = strop::split("1=2=3", '=');
  ASSERT_EQ(exp.size(), act.size());
  for (u8 i = 0; i < exp.size(); i++) {
    ASSERT_EQ(act[i], exp[i]);
  }
}

TEST(StrOp, join) {
  ASSERT_EQ(strop::join(std::vector<std::string>({"1", "2", "3"}), ','),
            "1,2,3");
  ASSERT_EQ(strop::join(std::vector<std::string>({"1", "2", "3"}), '-'),
            "1-2-3");
  ASSERT_EQ(strop::join(std::vector<std::string>({"1"}), '-'), "1");
  ASSERT_EQ(strop::join(std::vector<std::string>(), '-'), "");
}

TEST(StrOp, vecString_defDelim) {
  ASSERT_EQ("[1,2,3]", strop::vecString<u32>({1, 2, 3}));
  ASSERT_EQ("[1,2,3]", strop::vecString<char>({'1', '2', '3'}));
  ASSERT_EQ("[-1,2,-3]", strop::vecString<s64>({-1, 2, -3}));
}

TEST(StrOp, vecString_specDelim1) {
  ASSERT_EQ("[1,2,3]", strop::vecString<u32>({1, 2, 3}, ','));
  ASSERT_EQ("[1,2,3]", strop::vecString<char>({'1', '2', '3'}, ','));
  ASSERT_EQ("[-1,2,-3]", strop::vecString<s64>({-1, 2, -3}, ','));
}

TEST(StrOp, vecString_specDelim2) {
  ASSERT_EQ("[1-2-3]", strop::vecString<u32>({1, 2, 3}, '-'));
  ASSERT_EQ("[1-2-3]", strop::vecString<char>({'1', '2', '3'}, '-'));
  ASSERT_EQ("[-1-2--3]", strop::vecString<s64>({-1, 2, -3}, '-'));
}

TEST(StrOp, vecString_specDelim3) {
  ASSERT_EQ("[1.2.3]", strop::vecString<u32>({1, 2, 3}, '.'));
  ASSERT_EQ("[1.2.3]", strop::vecString<char>({'1', '2', '3'}, '.'));
  ASSERT_EQ("[-1.2.-3]", strop::vecString<s64>({-1, 2, -3}, '.'));
}

TEST(StrOp, vecString_floatDefPrec) {
  std::vector<f32> vals({1.0 / 3, 2.0 / 3, 3.0 / 3});
  ASSERT_EQ("[0.333333,0.666667,1]", strop::vecString<f32>(vals, ','));
  ASSERT_EQ("[0.333333-0.666667-1]", strop::vecString<f32>(vals, '-'));
}

TEST(StrOp, vecString_floatSpecificPrec) {
  std::vector<f64> vals({1.0 / 3, 2.0 / 3, 3.0 / 3});
  ASSERT_EQ("[0,1,1]", strop::vecString<f64>(vals, ',', 0));
  ASSERT_EQ("[0.3,0.7,1.0]", strop::vecString<f64>(vals, ',', 1));
  ASSERT_EQ("[0.33,0.67,1.00]", strop::vecString<f64>(vals, ',', 2));
  ASSERT_EQ("[0.333,0.667,1.000]", strop::vecString<f64>(vals, ',', 3));
}

TEST(StrOp, vecString_empty) {
  std::vector<f64> vals;
  ASSERT_EQ("[]", strop::vecString<f64>(vals, ','));
}

TEST(StrOp, toCharArrays) {
  std::vector<std::string> v1({"-n", "10", "--page_size", "4096"});
  std::vector<char*> v2 = strop::toCharArrays(v1);
  ASSERT_EQ(v1.size(), v2.size());
  for (u32 i = 0; i < v1.size(); i++) {
    ASSERT_EQ(0, std::strcmp(v1.at(0).c_str(), v2.at(0)));
  }
  for (char* s : v2) {
    delete[] s;
  }
}

TEST(StrOp, replaceFirst) {
  ASSERT_EQ(strop::replaceFirst("here is some text some", "some", "a lot"),
            "here is a lot text some");
  ASSERT_EQ(strop::replaceFirst("something", "eth", "blahethblah"),
            "somblahethblahing");
  ASSERT_EQ(strop::replaceFirst("I $op you, do you $op me?", "$op", "love"),
            "I love you, do you $op me?");
}

TEST(StrOp, replaceAll) {
  ASSERT_EQ(strop::replaceAll("here is some text some", "some", "a lot"),
            "here is a lot text a lot");
  ASSERT_EQ(strop::replaceAll("somethething", "eth", "blahethblah"),
            "somblahethblahblahethblahing");
  ASSERT_EQ(strop::replaceAll("I $op you, do you $op me?", "$op", "love"),
            "I love you, do you love me?");
}

TEST(StrOp, startsWith) {
  ASSERT_TRUE(strop::startsWith("hello", "hello"));
  ASSERT_TRUE(strop::startsWith("hello", "hell"));
  ASSERT_TRUE(strop::startsWith("hello", "hel"));
  ASSERT_TRUE(strop::startsWith("hello", "he"));
  ASSERT_TRUE(strop::startsWith("hello", "h"));
  ASSERT_TRUE(strop::startsWith("hello", ""));
  ASSERT_FALSE(strop::startsWith("hello", "hellX"));
  ASSERT_FALSE(strop::startsWith("hello", "Xello"));
}

TEST(StrOp, endsWith) {
  ASSERT_TRUE(strop::endsWith("hello", "hello"));
  ASSERT_TRUE(strop::endsWith("hello", "ello"));
  ASSERT_TRUE(strop::endsWith("hello", "llo"));
  ASSERT_TRUE(strop::endsWith("hello", "lo"));
  ASSERT_TRUE(strop::endsWith("hello", "o"));
  ASSERT_TRUE(strop::endsWith("hello", ""));
  ASSERT_FALSE(strop::endsWith("hello", "hellX"));
  ASSERT_FALSE(strop::endsWith("hello", "Xello"));
}

TEST(StrOp, findNth) {
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 0), 1);
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 1), 3);
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 2), 5);
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 3), 7);
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 4), 9);
  ASSERT_EQ(strop::findNth("a,b,c,d,e,f", ',', 5), std::string::npos);
}

// a suite of tests migrated from the commons-lang library

TEST(test, testStartsWith) {
  ASSERT_TRUE(strop::startsWith(FOOBAR, ""));

  ASSERT_TRUE(strop::startsWith(foobar, foo));
  ASSERT_TRUE(strop::startsWith(FOOBAR, FOO));
  ASSERT_FALSE(strop::startsWith(foobar, FOO));
  ASSERT_FALSE(strop::startsWith(FOOBAR, foo));

  ASSERT_FALSE(strop::startsWith(foo, foobar));
  ASSERT_FALSE(strop::startsWith(bar, foobar));

  ASSERT_FALSE(strop::startsWith(foobar, bar));
  ASSERT_FALSE(strop::startsWith(FOOBAR, BAR));
  ASSERT_FALSE(strop::startsWith(foobar, BAR));
  ASSERT_FALSE(strop::startsWith(FOOBAR, bar));
}

TEST(test, testEndsWith) {
  ASSERT_TRUE(strop::endsWith(FOOBAR, ""));
  ASSERT_FALSE(strop::endsWith(foobar, foo));
  ASSERT_FALSE(strop::endsWith(FOOBAR, FOO));
  ASSERT_FALSE(strop::endsWith(foobar, FOO));
  ASSERT_FALSE(strop::endsWith(FOOBAR, foo));

  ASSERT_FALSE(strop::endsWith(foo, foobar));
  ASSERT_FALSE(strop::endsWith(bar, foobar));

  ASSERT_TRUE(strop::endsWith(foobar, bar));
  ASSERT_TRUE(strop::endsWith(FOOBAR, BAR));
  ASSERT_FALSE(strop::endsWith(foobar, BAR));
  ASSERT_FALSE(strop::endsWith(FOOBAR, bar));

  ASSERT_TRUE(strop::endsWith("\u03B1\u03B2\u03B3\u03B4", "\u03B4"));
  ASSERT_FALSE(strop::endsWith("\u03B1\u03B2\u03B3\u03B4", "\u03B3\u0394"));
}

TEST(test, testTrim) {
  ASSERT_EQ(FOO, strop::trim(FOO + "  "));
  ASSERT_EQ(FOO, strop::trim(" " + FOO + "  "));
  ASSERT_EQ(FOO, strop::trim(" " + FOO));
  ASSERT_EQ(FOO, strop::trim(FOO + ""));
  ASSERT_EQ("", strop::trim(" \t\r\n "));
  // not remove \b
  // ASSERT_EQ("", strop::trim(" \t\r\n\b "));
  ASSERT_EQ("", strop::trim(""));
}

// migrate tests from commons-lang
TEST(test, testJoin_ArrayOfBytes) {
  ASSERT_EQ("1;2", strop::join(PRIM_LIST, SEPARATOR_CHAR));
}

TEST(test, testJoin_ArrayOfBooleans) {
  ASSERT_EQ("false;false", strop::join(ARRAY_FALSE_FALSE, SEPARATOR_CHAR));
  ASSERT_EQ("", strop::join(vector<string>({}), SEPARATOR_CHAR));
  ASSERT_EQ("false,true,false", strop::join(ARRAY_FALSE_TRUE_FALSE, COMMA_SEPARATOR_CHAR));
}

TEST(test, testJoin_ArrayString_EmptyDelimiter) {
  ASSERT_EQ("", strop::join(EMPTY_ARRAY_LIST, ' '));
}

TEST(test, testJoin_ArrayString_NonEmptyDelimiter) {
  char delimiter = ',';
  ASSERT_EQ("", strop::join(EMPTY_ARRAY_LIST, delimiter));
  ASSERT_EQ((std::string(1, delimiter) + "foo"), strop::join(MIXED_ARRAY_LIST, delimiter));
}

TEST(test, testJoin_List_EmptyDelimiter) {
  ASSERT_EQ(TEXT_LIST_NOSEP, join(STRING_LIST, ' '));
  ASSERT_EQ("", join(EMPTY_STRING_LIST, ' '));
}

TEST(test, testReplaceAll_StringStringString) {
  ASSERT_EQ("", strop::replaceAll("", ".+", "zzz"));
}

TEST(test, testReplaceFirst_StringStringString) {
  ASSERT_EQ("", strop::replaceFirst("", ".+", "zzz"));
}

TEST(test, testSplit_String) {
  ASSERT_EQ(0, strop::split("", '.').size());
}
