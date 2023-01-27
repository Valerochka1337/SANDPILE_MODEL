#include <cstdint>
#include <string>
#include "model.h"
#include "../image/image.h"

const Color kWHITE(0);
const Color kBLACK(1);
const Color kGREEN(2);
const Color kPURPLE(3);
const Color kYELLOW(4);

Field::Field(uint16_t width, uint16_t height)
    : m_width(width), m_height(height),
      field(new uint64_t* [height]), temp_field(new uint64_t* [height]) {
  left_border = 0;
  right_border = m_width;
  top_border = 0;
  bottom_border = m_height;
  stop_generating = false;

  for (int r = 0; r < m_height; r++) {
    field[r] = new uint64_t[m_width];
    temp_field[r] = new uint64_t[m_width];
  }

  for (uint64_t r = 0; r < m_height; r++) {
    for (uint64_t c = 0; c < m_width; c++) {
      field[r][c] = 0;
      temp_field[r][c] = 0;
    }
  }
}

uint64_t Field::GetGrainsNumber(uint16_t x, uint16_t y) const {
  return field[y][x];
}
void Field::SetGrainsNumber(uint64_t value, uint16_t x, uint16_t y) {
  field[y][x] = value;
  temp_field[y][x] = value;
}
void Field::NextIteration() {
  Expand();
  for (int i = top_border; i < bottom_border; i++) {
    for (int j = left_border; j < right_border; j++) {
      if (field[i][j] > 3) {
        temp_field[i - 1][j] += 1;
        temp_field[i + 1][j] += 1;
        temp_field[i][j - 1] += 1;
        temp_field[i][j + 1] += 1;
        temp_field[i][j] -= 4;
      }
    }
  }
  int points = 0;
  for (int i = top_border; i < bottom_border; i++) {
    for (int j = left_border; j < right_border; j++) {
      if (temp_field[i][j] > 3) points = 1;
      field[i][j] = temp_field[i][j];
    }
  }
  if (points == 0) stop_generating = true;
}
uint16_t Field::GetWidth() const {
  return right_border - left_border;
}
uint16_t Field::GetHeight() const {
  return bottom_border - top_border;
}
void Field::Expand() {
  bool l, r, t, b;
  l = false;
  r = false;
  b = false;
  t = false;

  for (int i = top_border; i < bottom_border; i++) {
    if (field[i][left_border] > 3) l = true;
    if (field[i][right_border - 1] > 3) r = true;
  }
  for (int i = left_border; i < right_border; i++) {
    if (field[top_border][i] > 3) t = true;
    if (field[bottom_border - 1][i] > 3) b = true;
  }
  if (t) {
    if (top_border != 0) {
      top_border -= 1;
      t = false;
    }
  }

  if (b) {
    if (bottom_border != m_height) {
      bottom_border += 1;
      b = false;
    }
  }

  if (l) {
    if (left_border != 0) {
      left_border -= 1;
      l = false;
    }
  }

  if (r) {
    if (right_border != m_width) {
      right_border += 1;
      r = false;
    }
  }

  if (t || r || l || b) {
    int prev_top = top_border;
    int prev_left = left_border;
    if (t) {
      top_border = m_height;
      bottom_border += m_height;
    }
    if (t || b) {
      if (t && b) m_height *= 3;
      else m_height *= 2;
    }
    if (l) {
      left_border = m_width;
      right_border += m_width;
    }
    if (l || r) {
      if (l && r) m_width *= 3;
      else m_width *= 2;
    }

    delete[] field;
    field = new uint64_t* [m_height];
    for (int i = 0; i < m_height; i++) {
      field[i] = new uint64_t[m_width];
      for (uint64_t j = 0; j < m_width; j++) {
        field[i][j] = 0;
      }
    }

    for (uint64_t i = top_border; i < bottom_border; i++) {
      for (uint64_t j = left_border; j < right_border; j++) {
        field[i][j] = temp_field[i - top_border + prev_top][j - left_border + prev_left];
      }
    }

    delete[] temp_field;
    temp_field = new uint64_t* [m_height];
    for (int i = 0; i < m_height; i++) {
      temp_field[i] = new uint64_t[m_width];
      for (uint64_t j = 0; j < m_width; j++) {
        temp_field[i][j] = 0;
      }
    }

    for (uint64_t i = 0; i < m_height; i++) {
      for (uint64_t j = 0; j < m_width; j++) {
        temp_field[i][j] = field[i][j];
      }
    }
  }
}
void Field::SaveImage(uint64_t number, const char* path) const {
  Image image(GetWidth(), GetHeight());
  uint64_t point;

  for (int y = 0; y < GetHeight(); y++) {
    for (int x = 0; x < GetWidth(); x++) {
      point = GetGrainsNumber(x + left_border, y + top_border);
      if (point == 0) image.SetColor(kWHITE, x, y);
      else if (point == 1) image.SetColor(kGREEN, x, y);
      else if (point == 2) image.SetColor(kPURPLE, x, y);
      else if (point == 3) image.SetColor(kYELLOW, x, y);
      else image.SetColor(kBLACK, x, y);
    }
  }
  char filename[50] = "";
  strcat(filename, path);
  strcat(filename, std::to_string(number).c_str());
  strcat(filename, ".bmp");
  image.ExportBMP(filename);
}


