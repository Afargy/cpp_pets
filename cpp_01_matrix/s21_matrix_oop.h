#ifndef CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H_

#include <ostream>

namespace s21 {

class S21Matrix {
  friend S21Matrix operator*(const int num, const S21Matrix &matrix) noexcept;
  friend std::ostream &operator<<(std::ostream &stream,
                                  const S21Matrix &matrix);

 public:
  S21Matrix() = default;
  S21Matrix(int size);
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  void operator=(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  void operator=(S21Matrix &&other) noexcept;
  ~S21Matrix();
  double operator()(const int row, const int col) const;
  double &operator()(const int row, const int col);
  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(const int rows);
  void set_cols(const int cols);
  void set_size(const int rows, const int cols);
  bool EqMatrix(const S21Matrix &other) const noexcept;
  bool operator==(const S21Matrix &other) const noexcept;
  void SumMatrix(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  S21Matrix operator*(const double num) noexcept;
  S21Matrix &operator*=(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix Transpose() const noexcept;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
  void Fill() noexcept;
  void Fill(const int num) noexcept;

 private:
  void CreateObject(const int &rows, const int &cols);
  void CopyObject(const S21Matrix &other) noexcept;
  void MoveObject(S21Matrix &other) noexcept;
  void DeleteObject() noexcept;
  void CreateMatrix() noexcept;
  void CopyMatrix(const S21Matrix &other) noexcept;
  void DeleteMatrix();
  bool EqualValues(const int &val_1, const int &val_2) const noexcept;
  bool EqualSize(const S21Matrix &other) const noexcept;
  bool ValidSize(const int &rows, const int &cols) const noexcept;
  void SetSize(const int &rows, const int &cols) noexcept;
  size_t GetSize();
  bool ValidElement(const int &row, const int &col) const noexcept;
  double &FindElement(const int &row, const int &col) const;
  void CheckAndChange(const int &cheked, int &changed) noexcept;
  S21Matrix CalcMinor(const int row, const int col) const noexcept;
  void CheckNullAndSquare() const;
  int rows_{0};
  int cols_{0};
  double **matrix_{nullptr};
};
}  // namespace s21

#endif  // CPP1_S21_MATRIXPLUS_4_S21_MATRIX_OOP_H_
