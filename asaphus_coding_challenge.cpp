/**
 * @file asaphus_coding_challenge.cpp
 * @version 1.1
 * @copyright Copyright (c) 2022 Asaphus Vision GmbH
 *
 * The goal is to implement the mechanics of a simple game and write test cases for them.
 * The rules of the game are:
 * - There are two types of boxes, green and blue. 
 * - Both can absorb tokens of a given weight, which they add to their own total weight. 
 * - Both are initialized with a given initial weight.
 * - After a box absorbs a token weight, it outputs a score. 
 * - Green and blue boxes calculate the score in different ways:
 * - A green box calculates the score as the square of the mean of the 3 weights that it most recently absorbed (square of mean of all absorbed weights if there are fewer than 3).
 * - A blue box calculates the score as Cantor's pairing function of the smallest and largest weight that it has absorbed so far, i.e. pairing(smallest, largest), where pairing(0, 1) = 2
 * - The game is played with two green boxes with initial weights 0.0 and 0.1, and two blue boxes with initial weights 0.2 and 0.3.
 * - There is a list of input token weights. Each gets used in one turn.
 * - There are two players, A and B. Both start with a score of 0. 
 * - The players take turns alternatingly. Player A starts.
 * - In each turn, the current player selects one of the boxes with the currently smallest weight, and lets it absorb the next input token weight. Each input weight gets only used once.
 * - The result of the absorption gets added to the current player's score.Q
 * - When all input token weights have been used up, the game ends, and the player with highest score wins.
 *
 * Task:
 * - Create a git repo for the implementation. Use the git repository to have a commit history.
 * - Implement all missing parts, marked with "TODO", including the test cases.
 * - Split the work in reasonable commits (not just one commit).
 * - Make sure the test cases succeed.
 * - Produce clean, readable code.
 *
 * Notes:
 * - Building and running the executable: g++ --std=c++14 asaphus_coding_challenge.cpp -o challenge && ./challenge
 * - Feel free to add a build system like CMake, meson, etc.
 * - Feel free to add more test cases, if you would like to test more.
 * - This file includes the header-only test framework Catch v2.13.9.
 * - A main function is not required, as it is provided by the test framework.
 */

#include <algorithm>
#include <memory>
#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

class Box {
public:
  explicit Box(double initial_weight) : weight_(initial_weight) {}
  virtual ~Box() = default;
    static std::unique_ptr<Box> makeGreenBox(double initial_weight);

    static std::unique_ptr<Box> makeBlueBox(double initial_weight);
  bool operator<(const Box& rhs) const { return weight_ < rhs.weight_; }

  virtual double absorbWeight(double tokenWeight) = 0;
  double getWeight() const {
      return weight_;
  }
 protected:
  double weight_;
};

class GreenBox : public Box {
public:
    explicit GreenBox(double initial_weight) : Box(initial_weight){}
    double absorbWeight(double token_weight) override {
        double mean{0.0};
        if (absorbed_weights_.size() < weight_count_for_mean_) {
            for(const auto& weight : absorbed_weights_) {
                mean += weight;
            }
        } else {
             for(int i{0} ; i < weight_count_for_mean_; ++i) {
                 mean += absorbed_weights_.at(i);
             }
        }

        mean /= weight_count_for_mean_;
        return mean;
    }
private:
    static constexpr int weight_count_for_mean_{3};
    std::vector<double> absorbed_weights_;

};

class BlueBox : public Box {
public:
    explicit BlueBox(double initial_weight) : Box(initial_weight), smallest_weight_(initial_weight), largest_weight_(initial_weight){}
    double absorbWeight(double token_weight) override {
        if (token_weight > smallest_weight_) {
            smallest_weight_ = token_weight;
        }

        if (token_weight >  largest_weight_) {
            largest_weight_ = token_weight;
        }
        return cantorPairing(smallest_weight_, largest_weight_);
    }
    static double cantorPairing(double a, double b) {
        return 0.5 * (a + b) * (a + b + 1) + b;
    }
private:
    double smallest_weight_;
    double largest_weight_;
};

// TODO

class Player {
 public:
  void takeTurn(uint32_t input_weight,
                const std::vector<std::unique_ptr<Box> >& boxes) {
    // TODO
  }
  double getScore() const { return score_; }

 private:
  double score_{0.0};
};

std::unique_ptr<Box> Box::makeGreenBox(double initial_weight) {
    return std::make_unique<GreenBox>(initial_weight);
}

std::unique_ptr<Box> Box::makeBlueBox(double initial_weight) {
    return std::make_unique<BlueBox>(initial_weight);
}

std::pair<double, double> play(const std::vector<uint32_t>& input_weights) {
  std::vector<std::unique_ptr<Box> > boxes;
  boxes.emplace_back(Box::makeGreenBox(0.0));
  boxes.emplace_back(Box::makeGreenBox(0.1));
  boxes.emplace_back(Box::makeBlueBox(0.2));
  boxes.emplace_back(Box::makeBlueBox(0.3));
  Player player_A;
  Player player_B;
  // TODO

  std::cout << "Scores: player A " << player_A.getScore() << ", player B "
            << player_B.getScore() << std::endl;
  return std::make_pair(player_A.getScore(), player_B.getScore());
}

TEST_CASE("Final scores for first 4 Fibonacci numbers", "[fibonacci4]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3};
  auto result = play(inputs);
  REQUIRE(result.first == 13.0);
  REQUIRE(result.second == 25.0);
}

TEST_CASE("Final scores for first 8 Fibonacci numbers", "[fibonacci8]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3, 5, 8, 13, 21};
  auto result = play(inputs);
  REQUIRE(result.first == 155.0);
  REQUIRE(result.second == 366.25);
}

TEST_CASE("Test absorption of green box", "[green]") {
  // TODO
}

TEST_CASE("Test absorption of blue box", "[blue]") {
  // TODO
}
