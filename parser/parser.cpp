#include "parser.h"
#include <iostream>

Options Parser::parseFlags(int argc, char** argv) {
  Options options = {};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        if (i + 1 <  argc) {
          if (std::strcmp(argv[i], "--length") == 0) {
            options.length = atoi(argv[i + 1]);
          } else if (std::strcmp(argv[i], "--width") == 0) {
            options.width = atoi(argv[i + 1]);
          } else if (std::strcmp(argv[i], "--max-iter") == 0) {
            options.max_iter = atoi(argv[i + 1]);
          } else if (std::strcmp(argv[i], "--freq") == 0) {
            options.frequency = atoi(argv[i + 1]);
          } else if (std::strcmp(argv[i], "--input") == 0) {
            options.input = argv[i + 1];
          } else if (std::strcmp(argv[i], "--output") == 0) {
            options.output_dir = argv[i + 1];
          }
        } else {
          std::cout << "No argument after " << argv[i] << "\n";
        }
      } else {
        for (int j = 1; argv[i][j] != '\0'; j++) {
          if (i + j < argc) {
            switch (argv[i][j]) {
              case 'l': {
                options.length = atoi(argv[i + j]);
                break;
              }
              case 'w': {
                options.width = atoi(argv[i + j]);
                break;
              }
              case 'i': {
                options.input = argv[i + j];
                break;
              }
              case 'o': {
                options.output_dir = argv[i + j];
                break;
              }
              case 'm': {
                options.max_iter = atoi(argv[i + j]);
                break;
              }
              case 'f': {
                options.frequency = atoi(argv[i + j]);
                break;
              }
            }
          } else {
            std::cout << "No argument for " << argv[i][j] << '\n';
          }
        }
      }
    }

  }
  return options;
}
