#include "../image/image.h"
#include "../model/model.h"
#include "../parser/parser.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  Parser parser;
  Options options;
  options = parser.parseFlags(argc, argv);

  Field map(options.length, options.width);

  std::ifstream file;
  file.open(options.input, std::ios::binary);
  std::string str;
  int x, y, count;
  if (file.is_open()) {
    while (file >> x && file >> y && file >> count) {
      map.SetGrainsNumber(count, x, y);
    }
  } else {
    std::cout << ".tsv file does not exist!\n";
  }
  file.close();

  for (uint64_t i = 1; i < options.max_iter + 1; i++) {
    if (i % options.frequency == 0) {
      map.SaveImage(i, options.output_dir.c_str());
    }
    map.NextIteration();
    if (map.stop_generating || i == options.max_iter) {
      map.SaveImage(i, options.output_dir.c_str());
      break;
    }
  }
  return 0;
}