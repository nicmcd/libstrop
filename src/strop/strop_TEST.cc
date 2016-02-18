/*
 * Copyright (c) 2012-2015, Nic McDonald
 * All rights reserved.
 *
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
 * - Neither the name of prim nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
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
