#pragma once
#ifndef LABWORK_3_VALEROCHKA1337_IMAGES_PARSER_H_
#define LABWORK_3_VALEROCHKA1337_IMAGES_PARSER_H_

#endif //LABWORK_3_VALEROCHKA1337_IMAGES_PARSER_H_
#include <cstdint>
#include <string>
struct Options {
  uint16_t length;
  uint16_t width;
  std::string input;
  std::string output_dir;
  uint64_t max_iter;
  uint64_t frequency;
};

class Parser {
 public:
  static Options parseFlags(int argc, char** argv);
};