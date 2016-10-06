#include "simple_filter.h"

#include <assert.h>

using namespace app;

SimpleFilter::SimpleFilter(const std::string &input_filename, const std::string &target_word)
    : FilterBase(input_filename, target_word),
    input_(input_filename),
    pattern_begin_("^" + target_word + "[ ]", std::regex_constants::optimize),
    pattern_end_("[ ]" + target_word + "$", std::regex_constants::optimize),
    pattern_mid_("[ ]" + target_word + "[ ]", std::regex_constants::optimize) {}

bool SimpleFilter::HasNext() const {
  return input_.is_open() && !input_.eof();
}

std::string SimpleFilter::NextLine() {
  std::string line;
  std::getline(input_, line);

  line = std::regex_replace(line, pattern_mid_, " ");
  line = std::regex_replace(line, pattern_begin_, "");
  line = std::regex_replace(line, pattern_end_, "");
  return line;
}
