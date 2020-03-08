//
// Created by User on 08.03.2020.
//
#include "string.hpp"

String::~String() {
  delete[] Data;
}

String::String() {
  Data = new char[10];
  capacity = 10;
  length = 0;
}

String::String(const String& rhs) {
  Data = new char[rhs.capacity];
  length = rhs.length;
  capacity = rhs.capacity;

  for (size_t i = 0; i < length; i++){
    Data[i] = rhs.Data[i];
  }

}

String::String(const char* data) {
  //finding length
  length = 0;
  while (data[length] != '\0') length++;

  Data = new char[length + 10];
  capacity = length + 10;

  for (size_t i = 0; i < length; i++)
    Data[i] = data[i];
}

String& String::operator=(const String& rhs){
  Data = new char[rhs.capacity];
  length = rhs.length;
  capacity = rhs.capacity;

  for (size_t i = 0; i < length; i++)
    Data[i] = rhs.Data[i];

  return *this;
}

String& String::operator+=(const String& rhs){
  //saving old pointer
  char* saved_data = Data;

  //allocating new one
  Data = new char[capacity + rhs.capacity];
  capacity += rhs.capacity;

  //rewriting 1st part
  for (size_t i = 0; i < length; i++)
    Data[i] = saved_data[i];

  //rewriting 2nd part
  for (size_t i = 0; i < rhs.length; i++)
    Data[length + i] = rhs.Data[i];

  length += rhs.length;
  delete[] saved_data;
  return *this;
}

String& String::operator*=(unsigned int m){
  //saving old pointer
  char* saved_data = Data;
  unsigned int old_len = length;

  length *= m;
  capacity = length + 10;
  Data = new char[capacity];

  for (unsigned int i = 0; i < m; i++)
    for (size_t j = 0; j < old_len; j++){
      Data[i * old_len + j] = saved_data[j];
    }
  return  *this;
}

bool String::operator==(const String& rhs) const{
  if (length != rhs.length) return false;

  for (size_t i = 0; i < length; i++)
    if (Data[i] != rhs.Data[i]) return false;

  return true;
}

bool String::operator<(const String& rhs) const{
  unsigned int min_length;
  length < rhs.length ? min_length = length : min_length = rhs.length;

  for (size_t i = 0; i < min_length; i++){
    if(Data[i] < rhs.Data[i]) return true;
    if(Data[i] > rhs.Data[i]) return false;
  }

  //  if all chars from 0 to min_length are equal then *this < rhs only if
  //  length < rhs.length
  return length < rhs.length;
}

size_t String::Find(const String& substr) const{
  for(size_t pos = 0; pos < this->length - substr.length + 1; pos++){

    bool equal = true;

    for(size_t i = 0; i < substr.length; i++){
      if(Data[pos + i] != substr[i])
        equal = false;
    }
    if (equal)
      return pos;
  }
  return -1;
}

void String::Replace(char oldSymbol, char newSymbol){
  for(size_t i = 0; i < length; i++)
    if(Data[i] == oldSymbol) Data[i] = newSymbol;
}

size_t String::Size() const { return length; }

bool String::Empty() const { return  !length; }

char String::operator[](size_t index) const { return Data[index]; }

char& String::operator[](size_t index) { return Data[index]; }

void String::LTrim(char symbol){
  size_t offset;
  for (offset = 0; ((Data[offset] == symbol) && (offset < length)); offset++);

  Data += offset;
  length -= offset;
  capacity -= offset;
}

void String::RTrim(char symbol){
  while ((Data[length - 1] == symbol) && (length))
    length--;
}

void String::swap(String& oth){
  size_t temp = length;
  length = oth.length;
  oth.length = temp;

  temp = capacity;
  capacity = oth.capacity;
  oth.capacity = temp;

  char* temp_ptr = Data;
  Data = oth.Data;
  oth.Data = temp_ptr;
}

std::ostream& operator<<(std::ostream& out, const String& str){
  for(size_t i = 0; i < str.length; i++) out << str[i];
  return out;
}

String operator+(const String& a, const String& b){
  String temp = a;
  temp += b;
  return temp;
}

String operator*(const String& a, unsigned int b){
  String temp = a;
  temp *= b;
  return temp;
}

bool operator!=(const String& a, const String& b) { return !(a == b); }

bool operator>(const String& a, const String& b) { return !((a == b) || (a < b)); }

void String::extend_linear(const size_t value){
  char* new_data = new char[capacity + value];

  for (size_t i = 0; i < length; i++) new_data[i] = Data[i];

  delete[] Data;
  Data = new_data;
  capacity += value;
}

void String::append_char(const char c) {
  if (length + 1 >= capacity) extend_linear(10);
  Data[length] = c;
  length++;
}

bool operator== (const char* chars, const String str){ return String(chars) == str; }