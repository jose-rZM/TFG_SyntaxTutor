#include "grammar.hpp"
#include "ll1_parser.hpp"
#include <algorithm>
#include <gtest/gtest.h>

void SortProductions(Grammar& grammar) {
    for (auto& [nt, productions] : grammar.g_) {
        std::sort(productions.begin(), productions.end());
    }
}

TEST(LL1__Test, FirstSet) {
    Grammar g;

    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});

    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {"b"});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b"};
    ll1.First({{"A", g.st_.EOL_}}, result);
    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithNullableSymbols) {
    Grammar g;

    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});

    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", g.st_.EPSILON_};
    ll1.First({{"A", g.st_.EOL_}}, result);
    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetMultipleSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b", g.st_.EPSILON_};
    ll1.First({{"A", "B"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetEndingWithNullable) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", g.st_.EPSILON_};
    ll1.First({{"A", g.st_.EOL_}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithAllSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("D", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"a", "B", "D"});
    g.AddProduction("A", {"C", "B"});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"d", "B", "c"});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("D", {"a", "B"});
    g.AddProduction("D", {"d"});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b", "d"};
    ll1.First({{"A", "B", "D", "C", "D"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithOneSymbolAndEpsilon) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("D", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"a", "B", "D"});
    g.AddProduction("A", {"C", "B"});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"d", "B", "c"});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("D", {"a", "B"});
    g.AddProduction("D", {"d"});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b", "d", g.st_.EPSILON_};
    ll1.First({{"A"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithMultipleSymbols2) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"(", "n", "+", g.st_.EPSILON_};
    ll1.First({{"T", "E'"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithTerminalSymbolAtTheBeginning) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"+"};
    ll1.First({{"+", "T", "E'"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithOnlyEpsilon) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{g.st_.EPSILON_};
    ll1.First({{g.st_.EPSILON_}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithEpsilon2) {
    Grammar g;
    g.st_.PutSymbol("S'", false);
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A'", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S'";

    g.AddProduction("S'", {"S", g.st_.EOL_});
    g.AddProduction("S", {"A", "B", "C"});
    g.AddProduction("A", {"a", "A", "a"});
    g.AddProduction("A", {"B", "d"});
    g.AddProduction("B", {"b"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("C", {"c"});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"b", "c", g.st_.EPSILON_};
    ll1.First({{"B", "C"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithNestedNullableSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b", g.st_.EPSILON_};
    ll1.First({{"A", "B"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithMultipleNullableSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", g.st_.EOL_});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{g.st_.EPSILON_};
    ll1.First({{"A", "B"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithTerminalAtEnd) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "b", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b"};
    ll1.First({{"A", "b"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithIndirectLeftRecursion) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"B", "a"});
    g.AddProduction("B", {"A", "b"});
    g.AddProduction("B", {"a"});

    LL1Parser ll1(g);
    ll1.ComputeFirstSets();

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a"};
    ll1.First({{"A"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FirstSetWithComplexNullableSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", "C", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"c", "C"});
    g.AddProduction("C", {g.st_.EPSILON_});

    LL1Parser ll1(g);
    ll1.ComputeFirstSets();

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"a", "b", "c", g.st_.EPSILON_};
    ll1.First({{"A", "B", "C"}}, result);

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, AllFirstSets) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("D", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"a", "B", "D"});
    g.AddProduction("A", {"C", "B"});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"d", "B", "c"});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("D", {"a", "B"});
    g.AddProduction("D", {"d"});

    LL1Parser ll1(g);

    std::unordered_map<std::string, std::unordered_set<std::string>> expected{
        {"S", {"a", "b", "d", g.st_.EPSILON_}},
        {"A", {"a", "b", "d", g.st_.EPSILON_}},
        {"B", {"b", g.st_.EPSILON_}},
        {"C", {"d", g.st_.EPSILON_}},
        {"D", {"a", "d"}}};

    EXPECT_EQ(ll1.first_sets_, expected);
}

TEST(LL1__Test, FollowSet2) {
    Grammar g;
    g.st_.PutSymbol("S'", false);
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A'", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S'";

    g.AddProduction("S'", {"S", g.st_.EOL_});
    g.AddProduction("S", {"A", "B", "C"});
    g.AddProduction("A", {"a", "A", "a"});
    g.AddProduction("A", {"B", "d"});
    g.AddProduction("B", {"b"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("C", {"c"});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"b", "c", "a", g.st_.EOL_};
    result = ll1.Follow("A");

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowTest1) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{g.st_.EOL_, ")"};
    result = ll1.Follow("E");

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowTest2) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{g.st_.EOL_, ")"};
    result = ll1.Follow("E'");

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowSetWithNestedProductions) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"b", g.st_.EOL_};
    result = ll1.Follow("A");

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowSetWithMultipleOccurrences) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_set<std::string> result;
    std::unordered_set<std::string> expected{"b", g.st_.EOL_};
    result = ll1.Follow("A");

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowSetWithIndirectLeftRecursion) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"B", "a"});
    g.AddProduction("B", {"A", "b"});
    g.AddProduction("B", {"a"});

    LL1Parser ll1(g);
    ll1.ComputeFirstSets();
    ll1.ComputeFollowSets();

    std::unordered_set<std::string> result = ll1.Follow("A");
    std::unordered_set<std::string> expected{"b", g.st_.EOL_};

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, FollowSetWithMultipleNullableSymbols) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", "B", "C", g.st_.EOL_});
    g.AddProduction("A", {"a", "A"});
    g.AddProduction("A", {g.st_.EPSILON_});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"c", "C"});
    g.AddProduction("C", {g.st_.EPSILON_});

    LL1Parser ll1(g);
    ll1.ComputeFirstSets();
    ll1.ComputeFollowSets();

    std::unordered_set<std::string> result = ll1.Follow("B");
    std::unordered_set<std::string> expected{"c", g.st_.EOL_};

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, AllFollowSets) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("E", false);
    g.st_.PutSymbol("E'", false);
    g.st_.PutSymbol("T", false);
    g.st_.PutSymbol("+", true);
    g.st_.PutSymbol("(", true);
    g.st_.PutSymbol(")", true);
    g.st_.PutSymbol("n", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"E", g.st_.EOL_});
    g.AddProduction("E", {"T", "E'"});
    g.AddProduction("E'", {"+", "T", "E'"});
    g.AddProduction("E'", {g.st_.EPSILON_});
    g.AddProduction("T", {"(", "E", ")"});
    g.AddProduction("T", {"n"});
    g.AddProduction("T", {g.st_.EPSILON_});

    LL1Parser ll1(g);

    std::unordered_map<std::string, std::unordered_set<std::string>> result;
    std::unordered_map<std::string, std::unordered_set<std::string>> expected{
        {"S", {g.st_.EOL_}},
        {"E", {")", g.st_.EOL_}},
        {"E'", {")", g.st_.EOL_}},
        {"T", {"+", ")", g.st_.EOL_}}};

    for (const std::string& nt : g.st_.non_terminals_) {
        result[nt] = ll1.Follow(nt);
    }

    EXPECT_EQ(result, expected);
}

TEST(LL1__Test, AllFollowSets2) {
    Grammar g;
    g.st_.PutSymbol("S", false);
    g.st_.PutSymbol("A", false);
    g.st_.PutSymbol("B", false);
    g.st_.PutSymbol("C", false);
    g.st_.PutSymbol("D", false);
    g.st_.PutSymbol("a", true);
    g.st_.PutSymbol("b", true);
    g.st_.PutSymbol("c", true);
    g.st_.PutSymbol("d", true);
    g.st_.PutSymbol(g.st_.EPSILON_, true);

    g.axiom_ = "S";

    g.AddProduction("S", {"A", g.st_.EOL_});
    g.AddProduction("A", {"a", "B", "D"});
    g.AddProduction("A", {"C", "B"});
    g.AddProduction("B", {"b", "B"});
    g.AddProduction("B", {g.st_.EPSILON_});
    g.AddProduction("C", {"d", "B", "c"});
    g.AddProduction("C", {g.st_.EPSILON_});
    g.AddProduction("D", {"a", "B"});
    g.AddProduction("D", {"d"});

    LL1Parser ll1(g);

    std::unordered_map<std::string, std::unordered_set<std::string>> result;
    std::unordered_map<std::string, std::unordered_set<std::string>> expected{
        {"S", {g.st_.EOL_}},
        {"A", {g.st_.EOL_}},
        {"B", {"a", "d", "c", g.st_.EOL_}},
        {"C", {"b", g.st_.EOL_}},
        {"D", {g.st_.EOL_}}};

    for (const std::string& nt : g.st_.non_terminals_) {
        result[nt] = ll1.Follow(nt);
    }

    EXPECT_EQ(result, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
