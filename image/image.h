#pragma once
#ifndef LABWORK_3_VALEROCHKA1337_IMAGE_IMAGE_H_
#define LABWORK_3_VALEROCHKA1337_IMAGE_IMAGE_H_

#endif //LABWORK_3_VALEROCHKA1337_IMAGE_IMAGE_H_
#include <vector>

struct Color {
  uint8_t color;

  explicit Color(uint8_t color = 0);
};

class Image {
 public:
  Image(int width, int height);
  Color GetColor(int x, int y) const;
  void SetColor(const Color& color, int x, int y);

  void ExportBMP(const char* path) const;

 private:
  int m_width;
  int m_height;
  std::vector<Color> m_colors;
};