#include "image.h"
#include <iostream>
#include <fstream>

const unsigned char kWhiteRGB[] = {255, 255, 255, 0};
const unsigned char kBlackRGB[] = {0, 0, 0, 0};
const unsigned char kGreenRGB[] = {120, 214, 0, 0};
const unsigned char kPurpleRGB[] = {255, 0, 139, 0};
const unsigned char kYellowRGB[] = {0, 237, 255, 0};

Color::Color(uint8_t color)
    : color(color) {
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height)) {
}
Color Image::GetColor(int x, int y) const {
  return m_colors[y * m_width + x];
}
void Image::SetColor(const Color& color, int x, int y) {
  m_colors[y * m_width + x].color = color.color;
}
void Image::ExportBMP(const char* path) const {
  std::ofstream file;
  file.open(path, std::ios::out | std::ios::binary);
  if (!file.is_open()) {
    std::cout << "Error: file could not be opened\n";

    return;
  }

  const int kBitsPerPixel = 4;
  const int kColorsAmount = 5;
  const int kColorPlanesAmount = 1;

  unsigned char bmpPad[3] = {0, 0, 0};
  const int kPaddingAmount = ((4 - (m_width + 1) / 2 % 4) % 4);

  const int kFileHeaderSize = 14;
  const int kInformationHeaderSize = 40;
  const uint32_t kFileSize = kFileHeaderSize + kInformationHeaderSize +
      (m_width + 1) / 2 * m_height + kPaddingAmount * m_height + kColorsAmount * 4;

  unsigned char fileHeader[kFileHeaderSize];

  fileHeader[0] = 'B';
  fileHeader[1] = 'M';

  fileHeader[2] = kFileSize;
  fileHeader[3] = kFileSize >> 8;
  fileHeader[4] = kFileSize >> 16;
  fileHeader[5] = kFileSize >> 24;

  fileHeader[10] = kFileHeaderSize + kInformationHeaderSize + kColorsAmount * 4;

  unsigned char informationHeader[kInformationHeaderSize];

  informationHeader[0] = kInformationHeaderSize;

  informationHeader[4] = m_width;
  informationHeader[5] = m_width >> 8;
  informationHeader[6] = m_width >> 16;
  informationHeader[7] = m_width >> 24;

  informationHeader[8] = m_height;
  informationHeader[9] = m_height >> 8;
  informationHeader[10] = m_height >> 16;
  informationHeader[11] = m_height >> 24;

  informationHeader[12] = kColorPlanesAmount;

  informationHeader[14] = kBitsPerPixel;

  informationHeader[32] = kColorsAmount;

  file.write(reinterpret_cast<char*>(fileHeader), kFileHeaderSize);
  file.write(reinterpret_cast<char*>(informationHeader), kInformationHeaderSize);

  file.write(reinterpret_cast<const char*>(kWhiteRGB), 4);
  file.write(reinterpret_cast<const char*>(kBlackRGB), 4);
  file.write(reinterpret_cast<const char*>(kGreenRGB), 4);
  file.write(reinterpret_cast<const char*>(kPurpleRGB), 4);
  file.write(reinterpret_cast<const char*>(kYellowRGB), 4);

  for (int y = 0; y < m_height; y++) {
    unsigned char col = 0;
    for (int x = 0; x < m_width; x++) {
      unsigned char r = static_cast<unsigned char>(GetColor(x, y).color);
      if (x % 2 == 0) col = r << 4;
      else {
        col += r;
        unsigned char color[] = {col};

        file.write(reinterpret_cast<char*>(color), 1);
        col = 0;
      }
    }
    if (m_width % 2 == 1) {
      unsigned char color[] = {col};
      file.write(reinterpret_cast<char*>(color), 1);
    }
    file.write(reinterpret_cast<char*>(bmpPad), kPaddingAmount);
  }

  file.close();
  std::cout << "Image created\n";
}
