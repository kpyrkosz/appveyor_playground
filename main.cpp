#include <algorithm>
#include <array>
#include <boost/thread.hpp>
#include <gtest/gtest.h>
#include <vector>

template <typename InputIt> void fancy_sort(InputIt begin, InputIt end) {
  if (std::distance(begin, end) <= 1)
    return;
  auto pivot = *begin;
  auto midpoint = std::partition(
      begin, end, [pivot](const auto &elem) { return elem < pivot; });
  auto midpoint2 = std::partition(
      midpoint, end, [pivot](const auto &elem) { return !(pivot < elem); });
  boost::thread left([begin, midpoint] { fancy_sort(begin, midpoint); });
  boost::thread right([midpoint2, end] { fancy_sort(midpoint2, end); });
  left.join();
  right.join();
}

TEST(fancy_sort, empty_vector) {
  std::vector<int> foo;
  fancy_sort(begin(foo), end(foo));
  EXPECT_TRUE(std::is_sorted(begin(foo), end(foo)));
}

TEST(fancy_sort, raw_array) {
  int foo[] = {123213, 345345, 34534, 345345, 3423, 123123, 45345};
  fancy_sort(std::begin(foo), std::end(foo));
  EXPECT_TRUE(std::is_sorted(std::begin(foo), std::end(foo)));
}

TEST(fancy_sort, vector_of_ints) {
  std::vector<int> foo{7, 5, 2, 8, 2, 99, 3, 3, 7, 4, 90, 2, 4};
  fancy_sort(begin(foo), end(foo));
  EXPECT_TRUE(std::is_sorted(begin(foo), end(foo)));
}

TEST(fancy_sort, big_array) {
  std::array<int, 200> foo{
      1142,  3875,  30118, 8501,  24750, 28031, 32018, 32659, 22944, 14904,
      3838,  27166, 771,   24320, 17575, 2166,  10206, 12394, 9166,  31634,
      1569,  32411, 9457,  6625,  23100, 19148, 19898, 11790, 17505, 27057,
      8836,  21782, 27153, 22929, 837,   20827, 20698, 19292, 12617, 26425,
      5387,  14362, 23493, 5193,  3238,  7425,  259,   4095,  27403, 25937,
      20381, 31887, 17539, 13236, 5479,  19573, 18806, 5525,  12913, 30331,
      13095, 30804, 4170,  9602,  9261,  23523, 15478, 7222,  30020, 5888,
      10197, 16224, 1282,  29240, 30465, 1947,  9911,  22998, 10519, 28087,
      19771, 9571,  19549, 14689, 23833, 13115, 16932, 4446,  29619, 16122,
      26910, 32184, 31896, 6509,  27940, 12336, 18733, 19535, 3099,  5370,
      28229, 18334, 12307, 24826, 4437,  4553,  22373, 28013, 23891, 20722,
      5978,  14541, 25446, 4733,  27750, 19898, 9732,  2457,  27807, 1999,
      24262, 29496, 7004,  26707, 31497, 21491, 12061, 19270, 4604,  24831,
      15143, 13192, 28044, 10766, 22919, 21816, 7127,  5637,  27622, 26199,
      10813, 15032, 15651, 3980,  20266, 7228,  24716, 16942, 92,    17838,
      20284, 12315, 38,    27686, 20771, 32599, 32125, 30561, 18108, 12582,
      23268, 26463, 21475, 1301,  27350, 17607, 11395, 44,    31297, 24605,
      18019, 17787, 20736, 30581, 29965, 17975, 6530,  20061, 25077, 29521,
      5435,  9977,  21466, 26605, 16912, 26512, 30226, 24182, 28165, 12791,
      28391, 21701, 10961, 8569,  24527, 18399, 14709, 26127, 10157, 560};
  fancy_sort(begin(foo), end(foo));
  EXPECT_TRUE(std::is_sorted(begin(foo), end(foo)));
}