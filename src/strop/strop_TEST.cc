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

#include <gtest/gtest.h>
#include <prim/prim.h>

#include <cstring>

#include <string>
#include <vector>

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
  std::vector<f32> vals({1.0/3, 2.0/3, 3.0/3});
  ASSERT_EQ("[0.333333,0.666667,1]", strop::vecString<f32>(vals, ','));
  ASSERT_EQ("[0.333333-0.666667-1]", strop::vecString<f32>(vals, '-'));
}

TEST(StrOp, vecString_floatSpecificPrec) {
  std::vector<f64> vals({1.0/3, 2.0/3, 3.0/3});
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

TEST(StrOp, startswith) {
  ASSERT_TRUE(strop::startswith("hello", "hello"));
  ASSERT_TRUE(strop::startswith("hello", "hell"));
  ASSERT_TRUE(strop::startswith("hello", "hel"));
  ASSERT_TRUE(strop::startswith("hello", "he"));
  ASSERT_TRUE(strop::startswith("hello", "h"));
  ASSERT_TRUE(strop::startswith("hello", ""));
  ASSERT_FALSE(strop::startswith("hello", "hellX"));
  ASSERT_FALSE(strop::startswith("hello", "Xello"));
}

TEST(StrOp, endswith) {
  ASSERT_TRUE(strop::endswith("hello", "hello"));
  ASSERT_TRUE(strop::endswith("hello", "ello"));
  ASSERT_TRUE(strop::endswith("hello", "llo"));
  ASSERT_TRUE(strop::endswith("hello", "lo"));
  ASSERT_TRUE(strop::endswith("hello", "o"));
  ASSERT_TRUE(strop::endswith("hello", ""));
  ASSERT_FALSE(strop::endswith("hello", "hellX"));
  ASSERT_FALSE(strop::endswith("hello", "Xello"));
}
