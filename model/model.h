#pragma once
#ifndef LABWORK_3_VALEROCHKA1337_MODEL_MODEL_H_
#define LABWORK_3_VALEROCHKA1337_MODEL_MODEL_H_
#endif //LABWORK_3_VALEROCHKA1337_MODEL_MODEL_H_

class Field {
 private:
  int m_width;
  int m_height;
  uint64_t** field;
  uint64_t** temp_field;

 public:
  bool stop_generating;
  uint16_t left_border;
  uint16_t right_border;
  uint16_t bottom_border;
  uint16_t top_border;
  Field(uint16_t width, uint16_t height);
  uint64_t GetGrainsNumber(uint16_t x, uint16_t y) const;
  void SetGrainsNumber(uint64_t value, uint16_t x, uint16_t y);
  void NextIteration();
  uint16_t GetWidth() const;
  uint16_t GetHeight() const;
  void Expand();
  void SaveImage(uint64_t number, const char* path) const;

};