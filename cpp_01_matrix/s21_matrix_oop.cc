#include "s21_matrix_oop.h"

#include <math.h>

#include <cstring>

namespace s21 {

S21Matrix::S21Matrix(int size) : S21Matrix(size, size) {}

S21Matrix::S21Matrix(int rows, int cols) { CreateObject(rows, cols); }

S21Matrix::S21Matrix(const S21Matrix& other) { CopyObject(other); }

void S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DeleteMatrix();
    CopyObject(other);
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept { MoveObject(other); }

void S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DeleteMatrix();
    MoveObject(other);
  }
}

S21Matrix::~S21Matrix() { DeleteObject(); }

double S21Matrix::operator()(const int row, const int col) const {
  return FindElement(row, col);
}

double& S21Matrix::operator()(const int row, const int col) {
  return FindElement(row, col);
}

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

void S21Matrix::set_rows(const int rows) {
  CheckAndChange(rows, cols_);
  set_size(rows, cols_);
}

void S21Matrix::set_cols(const int cols) {
  CheckAndChange(cols, rows_);
  set_size(rows_, cols);
}

void S21Matrix::set_size(const int rows, const int cols) {
  if (rows < 0 || cols < 0) {
    throw std::logic_error("setter: rows or cols less than zero");
  }
  S21Matrix temp{std::move(*this)};
  CreateObject(rows, cols);
  temp.rows_ = std::min(rows_, temp.rows_);
  temp.cols_ = std::min(cols_, temp.cols_);
  CopyMatrix(temp);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (!EqualSize(other)) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    if (memcmp(matrix_[i], other.matrix_[i], cols_ * sizeof(double))) {
      return false;
    }
  }
  return true;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!EqualSize(other)) {
    throw std::logic_error("SumMatrix: diffrent size");
  }
  for (size_t i = 0; i < GetSize(); ++i) {
    matrix_[0][i] += other.matrix_[0][i];
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result{*this};
  return result += other;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!EqualSize(other)) {
    throw std::logic_error("SubMatrix: diffrent size");
  }
  for (size_t i = 0; i < GetSize(); ++i) {
    matrix_[0][i] -= other.matrix_[0][i];
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result{*this};
  return result -= other;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (size_t i = 0; i < GetSize(); ++i) {
    matrix_[0][i] *= num;
  }
}

S21Matrix S21Matrix::operator*(const double num) noexcept {
  S21Matrix result{*this};
  return result *= num;
}

S21Matrix& S21Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!EqualValues(cols_, other.rows_)) {
    throw std::logic_error("MulMatrix: M1(cols) != M2(rows)");
  }
  S21Matrix temp{rows_, other.cols_};
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(temp);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result{*this};
  return result *= other;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  CheckNullAndSquare();
  if (EqualValues(rows_, 1)) {
    return matrix_[0][0];
  }
  double result = 0.0;
  for (int i = 0; i < cols_; ++i) {
    S21Matrix temp = CalcMinor(0, i);
    result += pow(-1, i) * (matrix_[0][i] * temp.Determinant());
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckNullAndSquare();
  if (EqualValues(rows_, 1)) {
    throw std::logic_error("Matrix 1x1 has no compliment");
  }
  double determinant = 0.0;
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = CalcMinor(i, j);
      determinant = minor.Determinant();
      result.matrix_[i][j] = pow(-1, (i + j)) * determinant;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  CheckNullAndSquare();
  if (EqualValues(rows_, 1)) {
    throw std::logic_error("Matrix 1x1 can't be inversed");
  }
  double determinant = Determinant();
  if (!determinant) {
    throw std::logic_error("Determinant is zero");
  }
  S21Matrix result = Transpose().CalcComplements();
  result.MulNumber(1 / determinant);
  return result;
}

void S21Matrix::Fill() noexcept { Fill(1); }

void S21Matrix::Fill(const int num) noexcept {
  for (size_t i = 0; i < GetSize(); ++i) {
    matrix_[0][i] = i + num;
  }
}

void S21Matrix::CreateObject(const int& rows, const int& cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("Constructor: negative rows or cols");
  }
  SetSize(rows, cols);
  CreateMatrix();
}

void S21Matrix::CopyObject(const S21Matrix& other) noexcept {
  CreateObject(other.rows_, other.cols_);
  CopyMatrix(other);
}

void S21Matrix::MoveObject(S21Matrix& other) noexcept {
  SetSize(other.rows_, other.cols_);
  other.SetSize(0, 0);
  std::swap(matrix_, other.matrix_);
}

void S21Matrix::DeleteObject() noexcept {
  SetSize(0, 0);
  DeleteMatrix();
}

void S21Matrix::CreateMatrix() noexcept {
  if (rows_) {
    matrix_ = new double* [rows_] { 0 };
    matrix_[0] = new double[GetSize()]{0};
    for (int i = 1; i < rows_; ++i) {
      matrix_[i] = *matrix_ + cols_ * i;
    }
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) noexcept {
  if (rows_) {
    size_t size{static_cast<size_t>(std::min(cols_, other.cols_)) *
                static_cast<size_t>(sizeof(double))};
    for (int i = 0; i < std::min(rows_, other.rows_); ++i) {
      memcpy(matrix_[i], other.matrix_[i], size);
    }
  }
}

void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    if (matrix_[0] != nullptr) {
      delete[](*matrix_);
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqualValues(const int& val_1, const int& val_2) const noexcept {
  if (val_1 != val_2) {
    return false;
  }
  return true;
}

bool S21Matrix::EqualSize(const S21Matrix& other) const noexcept {
  if (EqualValues(cols_, other.cols_) && EqualValues(rows_, other.rows_)) {
    return true;
  }
  return false;
}

void S21Matrix::SetSize(const int& rows, const int& cols) noexcept {
  if (rows == 0 || cols == 0) {
    rows_ = 0;
    cols_ = 0;
  } else {
    rows_ = rows;
    cols_ = cols;
  }
}

size_t S21Matrix::GetSize() {
  return static_cast<size_t>(rows_) * static_cast<size_t>(cols_);
}

bool S21Matrix::ValidElement(const int& row, const int& col) const noexcept {
  if (row <= 0 || col <= 0 || rows_ <= row - 1 || cols_ <= col - 1) {
    return false;
  }
  return true;
}

double& S21Matrix::FindElement(const int& row, const int& col) const {
  if (!ValidElement(row, col)) {
    throw std::logic_error("(): element doesn't exist");
  }
  return matrix_[row - 1][col - 1];
}

void S21Matrix::CheckAndChange(const int& cheked, int& changed) noexcept {
  if (cheked > 0 && changed == 0) {
    changed = 1;
  }
}

S21Matrix operator*(const int num, const S21Matrix& matrix) noexcept {
  S21Matrix result{matrix};
  return result * num;
}

std::ostream& operator<<(std::ostream& stream, const S21Matrix& matrix) {
  if (matrix.matrix_) {
    for (int i = 0; i < matrix.rows_; ++i) {
      for (int j = 0; j < matrix.cols_; ++j) {
        stream << matrix.matrix_[i][j] << "\t";
      }
      stream << std::endl;
    }
  } else {
    stream << "Matrix is NULL" << std::endl;
  }
  return stream;
}

S21Matrix S21Matrix::CalcMinor(const int row, const int col) const noexcept {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, minor_row = 0; i < rows_; ++i) {
    for (int j = 0, minor_col = 0; j < cols_; ++j) {
      if (i != row && j != col) {
        result.matrix_[minor_row][minor_col] = matrix_[i][j];
        minor_col++;
      }
    }
    if (i != row) minor_row++;
  }
  return result;
}

void S21Matrix::CheckNullAndSquare() const {
  if (EqualValues(rows_, 0)) {
    throw std::logic_error("Operation with NULL mattrix");
  }
  if (!EqualValues(rows_, cols_)) {
    throw std::logic_error("Matirx isn't square");
  }
}

};  // namespace s21
