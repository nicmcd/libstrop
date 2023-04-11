#include "strop.h"

#include <cstring>
#include <string>
#include <vector>

#include "gtest/gtest.h"
using namespace std;
using namespace strop;

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

TEST(test, testStartsWith)
{
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

TEST(test, testEndsWith)
{
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

TEST(test, testTrim)
{
  ASSERT_EQ(FOO, strop::trim(FOO + "  "));
  ASSERT_EQ(FOO, strop::trim(" " + FOO + "  "));
  ASSERT_EQ(FOO, strop::trim(" " + FOO));
  ASSERT_EQ(FOO, strop::trim(FOO + ""));
  ASSERT_EQ("", strop::trim(" \t\r\n "));
  // not remove \b
  // ASSERT_EQ("", strop::trim(" \t\r\n\b "));
  ASSERT_EQ("", strop::trim(""));
}

TEST(test, testJoin_ArrayOfBytes)
{
  ASSERT_EQ("1;2", strop::join(PRIM_LIST, SEPARATOR_CHAR));
}

TEST(test, testJoin_ArrayOfBooleans)
{
  ASSERT_EQ("false;false", strop::join(ARRAY_FALSE_FALSE, SEPARATOR_CHAR));
  ASSERT_EQ("", strop::join(vector<string>({}), SEPARATOR_CHAR));
  ASSERT_EQ("false,true,false", strop::join(ARRAY_FALSE_TRUE_FALSE, COMMA_SEPARATOR_CHAR));
}

TEST(test, testJoin_ArrayString_EmptyDelimiter)
{
  ASSERT_EQ("", strop::join(EMPTY_ARRAY_LIST, ' '));
}

TEST(test, testJoin_ArrayString_NonEmptyDelimiter)
{
  char delimiter = ',';
  ASSERT_EQ("", strop::join(EMPTY_ARRAY_LIST, delimiter));
  ASSERT_EQ((std::string(1, delimiter) + "foo"), strop::join(MIXED_ARRAY_LIST, delimiter));
}

TEST(test, testJoin_List_EmptyDelimiter)
{
  ASSERT_EQ(TEXT_LIST_NOSEP, join(STRING_LIST, ' '));
  ASSERT_EQ("", join(EMPTY_STRING_LIST, ' '));
}

TEST(test, testReplaceAll_StringStringString)
{
  ASSERT_EQ("", strop::replaceAll("", ".+", "zzz"));
}

TEST(test, testReplaceFirst_StringStringString)
{
  ASSERT_EQ("", strop::replaceFirst("", ".+", "zzz"));
}

TEST(test, testSplit_String)
{
  ASSERT_EQ(0, strop::split("", '.').size());
}

GTEST_API_ int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
