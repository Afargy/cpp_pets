#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

namespace s21 {

void CompareMatrices(const S21Matrix &m1, const S21Matrix &m2);
void CompareTransposed(const S21Matrix &m1, const S21Matrix &m2);

TEST(S21MatrixTest, Create) {
  EXPECT_ANY_THROW(S21Matrix(-5, -5));
  EXPECT_ANY_THROW(S21Matrix(-5, 1));
  EXPECT_ANY_THROW(S21Matrix(1, -5));
  EXPECT_ANY_THROW(S21Matrix(-5));

  EXPECT_NO_THROW(S21Matrix(5, 1));
  EXPECT_NO_THROW(S21Matrix(1, 5));
  EXPECT_NO_THROW(S21Matrix(5, 5));
  EXPECT_NO_THROW(S21Matrix(1));

  EXPECT_NO_THROW(S21Matrix(0, 0));
  EXPECT_NO_THROW(S21Matrix(5, 0));
  EXPECT_NO_THROW(S21Matrix(0, 5));
  EXPECT_NO_THROW(S21Matrix(0));
}

TEST(S21MatrixTest, Fill) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  for (int i = 1; i <= m1.get_rows(); ++i) {
    for (int j = 1; j <= m1.get_cols(); ++j) {
      EXPECT_EQ(m1(i, j), m2(i, j));
    }
  }
  m1.Fill();
  for (int i = 1; i <= m1.get_rows(); ++i) {
    for (int j = 1; j <= m1.get_cols(); ++j) {
      EXPECT_NE(m1(i, j), m2(i, j));
    }
  }
  m2.Fill();
  for (int i = 1; i <= m1.get_rows(); ++i) {
    for (int j = 1; j <= m1.get_cols(); ++j) {
      EXPECT_EQ(m1(i, j), m2(i, j));
    }
  }
}

TEST(S21MatrixTest, Delete) {
  S21Matrix m1(3, 3);
  m1.~S21Matrix();
  EXPECT_EQ(m1.get_rows(), 0);
  EXPECT_EQ(m1.get_rows(), 0);
}

TEST(S21MatrixTest, Copy) {
  {
    S21Matrix m1(5, 5);
    m1.Fill();
    S21Matrix m2 = m1;
    EXPECT_TRUE(m1.EqMatrix(m2));
  }
  {
    S21Matrix m1(6, 6);
    m1.Fill(12);
    S21Matrix m2(5, 4);
    m2.Fill(1);
    m2 = m1;
    EXPECT_TRUE(m1.EqMatrix(m2));
  }
  {
    S21Matrix m1;
    m1.~S21Matrix();
    S21Matrix m2;
    m1 = m2;
    EXPECT_TRUE(m1.EqMatrix(m2));
  }
}

TEST(S21MatrixTest, Move) {
  S21Matrix m1(6, 6);
  m1.Fill();
  S21Matrix m2 = std::move(m1);
  S21Matrix m3;
  S21Matrix m4(6, 6);
  m4.Fill();
  EXPECT_TRUE(m1.EqMatrix(m3));
  EXPECT_TRUE(m2.EqMatrix(m4));
}

TEST(S21MatrixTest, SetRows0) {
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m1.set_rows(-1));
  S21Matrix m2(3, 3);
  EXPECT_NO_THROW(m2.set_rows(0));
  S21Matrix m3(3, 3);
  EXPECT_NO_THROW(m3.set_rows(1));
}

TEST(S21MatrixTest, SetRows1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  m1.set_rows(1);
  EXPECT_EQ(m1.get_rows(), 1);
  EXPECT_EQ(m1.get_cols(), 3);
  EXPECT_DOUBLE_EQ(m1(1, 1), 1);
}

TEST(S21MatrixTest, SetRows2) {
  S21Matrix m1(3, 3);
  m1.Fill();
  m1.set_rows(4);
  EXPECT_EQ(m1.get_rows(), 4);
  EXPECT_EQ(m1.get_cols(), 3);
  EXPECT_DOUBLE_EQ(m1(1, 1), 1);
  for (int i = 1; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(m1(4, i), 0);
  }
}

TEST(S21MatrixTest, SetRows3) {
  S21Matrix m1;
  m1.set_rows(1);
  S21Matrix m2(1, 1);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, SetCols0) {
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m1.set_cols(-1));
  S21Matrix m2(3, 3);
  EXPECT_NO_THROW(m2.set_cols(0));
  S21Matrix m3(3, 3);
  EXPECT_NO_THROW(m3.set_cols(1));
}

TEST(S21MatrixTest, SetCols1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  m1.set_cols(1);
  EXPECT_EQ(m1.get_rows(), 3);
  EXPECT_EQ(m1.get_cols(), 1);
  EXPECT_DOUBLE_EQ(m1(1, 1), 1);
}

TEST(S21MatrixTest, SetCols2) {
  S21Matrix m1(3, 3);
  m1.Fill();
  m1.set_cols(4);
  EXPECT_EQ(m1.get_rows(), 3);
  EXPECT_EQ(m1.get_cols(), 4);
  EXPECT_DOUBLE_EQ(m1(1, 1), 1);
  for (int i = 1; i < 4; ++i) {
    EXPECT_DOUBLE_EQ(m1(i, 4), 0);
  }
}

TEST(S21MatrixTest, SetCols3) {
  S21Matrix m1;
  m1.set_cols(1);
  S21Matrix m2(1, 1);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, SetValue0) {
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m1(4, 1) = 123);
  EXPECT_ANY_THROW(m1(1, 4) = 123);
  EXPECT_ANY_THROW(m1(0, 0) = 123);
}

TEST(S21MatrixTest, SetValue1) {
  S21Matrix m1(3, 3);
  m1(1, 1) = 123.1234;
  EXPECT_DOUBLE_EQ(m1(1, 1), 123.1234);
}

TEST(S21MatrixTest, Sum0) {
  S21Matrix m1;
  S21Matrix m2;
  EXPECT_NO_THROW(m1.SumMatrix(m2));
  m1.set_size(1, 1);
  m2.set_size(1, 3);
  EXPECT_ANY_THROW(m1.SumMatrix(m2));
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1.SumMatrix(m2));
}

TEST(S21MatrixTest, Sum1) {
  S21Matrix m1(6, 6);
  S21Matrix m2(6, 6);
  S21Matrix m3(6, 6);
  m1.Fill();
  m2.Fill();
  m3.Fill();
  m1.SumMatrix(m2);
  for (int i = 0; i < m2.get_rows(); ++i) {
    for (int j = 0; j < m2.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(i + 1, j + 1), m2(i + 1, j + 1) + m3(i + 1, j + 1));
    }
  }
}

TEST(S21MatrixTest, Sub0) {
  S21Matrix m1;
  S21Matrix m2;
  EXPECT_NO_THROW(m1.SubMatrix(m2));
  m1.set_size(1, 1);
  m2.set_size(1, 3);
  EXPECT_ANY_THROW(m1.SubMatrix(m2));
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1.SubMatrix(m2));
}

TEST(S21MatrixTest, Sub1) {
  S21Matrix m1(6, 6);
  S21Matrix m2(6, 6);
  S21Matrix m3(6, 6);
  m1.Fill();
  m2.Fill();
  m3.Fill();
  m1.SubMatrix(m2);
  for (int i = 0; i < m2.get_rows(); ++i) {
    for (int j = 0; j < m2.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(i + 1, j + 1), m2(i + 1, j + 1) - m3(i + 1, j + 1));
    }
  }
}

TEST(S21MatrixTest, MulNum1) {
  S21Matrix m1(6, 6);
  S21Matrix m2(6, 6);
  m1.Fill();
  m2.Fill();
  m1.MulNumber(0.5);
  for (int i = 0; i < m2.get_rows(); ++i) {
    for (int j = 0; j < m2.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(i + 1, j + 1), m2(i + 1, j + 1) * 0.5);
    }
  }
}

TEST(S21MatrixTest, MulNum2) {
  S21Matrix m1(6, 6);
  S21Matrix m2(6, 6);
  m1.Fill();
  m2.Fill();
  m1.MulNumber(2);
  for (int i = 0; i < m2.get_rows(); ++i) {
    for (int j = 0; j < m2.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(i + 1, j + 1), m2(i + 1, j + 1) * 2);
    }
  }
}

TEST(S21MatrixTest, MulMatrix0) {
  S21Matrix m1(3, 3);
  S21Matrix m2;
  EXPECT_ANY_THROW(m1.MulMatrix(m2));
  m2.set_size(1, 3);
  EXPECT_ANY_THROW(m1.MulMatrix(m2));
}

TEST(S21MatrixTest, MulMatrix1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 1);
  m1.Fill();
  m2.Fill();
  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 14);
  EXPECT_DOUBLE_EQ(m1(2, 1), 32);
  EXPECT_DOUBLE_EQ(m1(3, 1), 50);
}

TEST(S21MatrixTest, Equal1) {
  S21Matrix m1;
  S21Matrix m2;
  EXPECT_TRUE(m1.EqMatrix(m2));
  m1.set_size(3, 3);
  m2.set_size(3, 3);
  EXPECT_TRUE(m1.EqMatrix(m2));
  m1.Fill();
  m2.Fill();
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, Equal2) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_FALSE(m1.EqMatrix(m2));
  m2.set_size(3, 1);
  EXPECT_FALSE(m1.EqMatrix(m2));
  m2.set_size(3, 3);
  m1.Fill();
  EXPECT_FALSE(m1.EqMatrix(m2));
  m2.Fill();
  m2(3, 3) = 100;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(S21MatrixTest, Transpose1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  S21Matrix m2 = m1.Transpose();
  CompareTransposed(m1, m2);
}

TEST(S21MatrixTest, Transpose2) {
  S21Matrix m1(3, 1);
  m1.Fill();
  S21Matrix m2 = m1.Transpose();
  CompareTransposed(m1, m2);
}

TEST(S21MatrixTest, Transpose3) {
  S21Matrix m1(1, 3);
  m1.Fill();
  S21Matrix m2 = m1.Transpose();
  CompareTransposed(m1, m2);
}

TEST(S21MatrixTest, Compliment0) {
  S21Matrix m1(3, 2);
  EXPECT_ANY_THROW(m1.CalcComplements());
  m1.set_size(2, 3);
  EXPECT_ANY_THROW(m1.CalcComplements());
  m1.set_size(1, 1);
  EXPECT_ANY_THROW(m1.CalcComplements());
  m1.set_size(0, 0);
  EXPECT_ANY_THROW(m1.CalcComplements());
}

TEST(S21MatrixTest, Compliment1) {
  S21Matrix m1(2, 2);
  m1.Fill();
  S21Matrix m2 = m1.CalcComplements();
  EXPECT_DOUBLE_EQ(m2(1, 1), 4);
  EXPECT_DOUBLE_EQ(m2(1, 2), -3);
  EXPECT_DOUBLE_EQ(m2(2, 1), -2);
  EXPECT_DOUBLE_EQ(m2(2, 2), 1);
}

TEST(S21MatrixTest, Determinant0) {
  S21Matrix m1(3, 2);
  EXPECT_ANY_THROW(m1.Determinant());
  m1.set_size(3, 2);
  EXPECT_ANY_THROW(m1.Determinant());
  m1.set_size(0, 0);
  EXPECT_ANY_THROW(m1.Determinant());
}

TEST(S21MatrixTest, Determinant1) {
  S21Matrix m1(1, 1);
  m1.Fill(123);
  EXPECT_DOUBLE_EQ(m1.Determinant(), m1(1, 1));
  m1.set_size(3, 3);
  m1.Fill();
  EXPECT_DOUBLE_EQ(m1.Determinant(), 0);
  m1(1, 1) = 100;
  EXPECT_DOUBLE_EQ(m1.Determinant(), -297);
}

TEST(S21MatrixTest, Inverse0) {
  S21Matrix m1(3, 1);
  EXPECT_ANY_THROW(m1.InverseMatrix());
  m1.set_size(1, 3);
  EXPECT_ANY_THROW(m1.InverseMatrix());
  m1.set_size(1, 1);
  EXPECT_ANY_THROW(m1.InverseMatrix());
  m1.set_size(0, 0);
  EXPECT_ANY_THROW(m1.InverseMatrix());
  m1.set_size(3, 3);
  m1.Fill();
  EXPECT_ANY_THROW(m1.InverseMatrix());
}

TEST(S21MatrixTest, Inverse1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  m1(1, 1) = 100;
  S21Matrix m2 = m1.InverseMatrix();
  EXPECT_DOUBLE_EQ(m2(1, 1), 1.0 / 99);
  EXPECT_DOUBLE_EQ(m2(1, 2), -2.0 / 99);
  EXPECT_DOUBLE_EQ(m2(1, 3), 1.0 / 99);
  EXPECT_DOUBLE_EQ(m2(2, 1), -2.0 / 99);
  EXPECT_DOUBLE_EQ(m2(2, 2), -293.0 / 99);
  EXPECT_DOUBLE_EQ(m2(2, 3), 196.0 / 99);
  EXPECT_DOUBLE_EQ(m2(3, 1), 1.0 / 99);
  EXPECT_DOUBLE_EQ(m2(3, 2), 262.0 / 99);
  EXPECT_DOUBLE_EQ(m2(3, 3), -164.0 / 99);
}

TEST(S21MatrixTest, Plus0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 + m2);
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1 + m2);
}

TEST(S21MatrixTest, Plus1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  S21Matrix m2(3, 3);
  m2.Fill();
  S21Matrix m3 = m1 + m2;
  m1.SumMatrix(m2);
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, Minus0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 - m2);
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1 - m2);
}

TEST(S21MatrixTest, Minus1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  S21Matrix m2(3, 3);
  m2.Fill();
  S21Matrix m3 = m1 - m2;
  m1.SubMatrix(m2);
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, MulNumber1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  S21Matrix m2 = m1 * 100;
  m1.MulNumber(100);
  EXPECT_TRUE(m2.EqMatrix(m1));
  S21Matrix m3 = 100 * m1;
  m1 = 100 * m1;
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, MulMat0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 * m2);
}

TEST(S21MatrixTest, MulMat1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1.Fill();
  m2.Fill();
  S21Matrix m3 = m1 * m2;
  m1.MulMatrix(m2);
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, OperatorEqual1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  EXPECT_TRUE(m1 == m2);
  m1.Fill();
  m2.Fill();
  EXPECT_TRUE(m1 == m2);
}

TEST(operators, equal_3) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1.Fill();
  EXPECT_FALSE(m1 == m2);
}

TEST(S21MatrixTest, OperatorPlusEq0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 += m2);
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1 += m2);
}

TEST(S21MatrixTest, OperatorPlusEq1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1.Fill();
  m2.Fill();
  S21Matrix m3 = m1 + m2;
  m1 += m2;
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, OperatorMinusEq0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 -= m2);
  m2.set_size(3, 1);
  EXPECT_ANY_THROW(m1 -= m2);
}

TEST(S21MatrixTest, OperatorMinusEq1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1.Fill();
  m2.Fill();
  S21Matrix m3 = m1 - m2;
  m1 -= m2;
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, OperatorMulEqNum) {
  S21Matrix m1(3, 3);
  m1.Fill();
  S21Matrix m2 = m1 * 100;
  m1 *= 100;
  EXPECT_TRUE(m2.EqMatrix(m1));
}

TEST(S21MatrixTest, OperatorMulEqMatrix0) {
  S21Matrix m1(3, 3);
  S21Matrix m2(1, 3);
  EXPECT_ANY_THROW(m1 *= m2);
}

TEST(S21MatrixTest, OperatorMulEqMatrix1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1.Fill();
  m2.Fill();
  S21Matrix m3 = m1 * m2;
  m1 *= m2;
  EXPECT_TRUE(m3.EqMatrix(m1));
}

TEST(S21MatrixTest, GetValue0) {
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m1(0, 0));
  EXPECT_ANY_THROW(m1(1, 4));
  EXPECT_ANY_THROW(m1(4, 1));
  EXPECT_ANY_THROW(m1(1, -1));
  EXPECT_ANY_THROW(m1(-1, 1));
}

TEST(S21MatrixTest, GetValue1) {
  S21Matrix m1(3, 3);
  m1.Fill();
  EXPECT_DOUBLE_EQ(m1(1, 1), 1);
  EXPECT_DOUBLE_EQ(m1(1, 2), 2);
  EXPECT_DOUBLE_EQ(m1(1, 3), 3);
  EXPECT_DOUBLE_EQ(m1(2, 1), 4);
  EXPECT_DOUBLE_EQ(m1(2, 2), 5);
  EXPECT_DOUBLE_EQ(m1(2, 3), 6);
  EXPECT_DOUBLE_EQ(m1(3, 1), 7);
  EXPECT_DOUBLE_EQ(m1(3, 2), 8);
  EXPECT_DOUBLE_EQ(m1(3, 3), 9);
}

TEST(S21MatrixTest, OperatorMove) {
  S21Matrix m1(6, 6);
  S21Matrix m2(6, 6);
  m1.Fill();
  m2.Fill();
  S21Matrix m3;
  m3 = std::move(m1);
  CompareMatrices(m3, m2);
  EXPECT_EQ(m1.get_rows(), 0);
  EXPECT_EQ(m1.get_cols(), 0);
}

TEST(Matix, Show) {
  S21Matrix m1(3, 3);
  m1.Fill();
  EXPECT_NO_THROW(std::cout << m1);
  m1.~S21Matrix();
  EXPECT_NO_THROW(std::cout << m1);
}

void CompareMatrices(const S21Matrix &m1, const S21Matrix &m2) {
  EXPECT_EQ(m1.get_rows(), m2.get_rows());
  EXPECT_EQ(m1.get_cols(), m2.get_cols());
  for (int i = 0; i < m1.get_rows(); ++i) {
    for (int j = 0; j < m1.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(i + 1, j + 1), m2(i + 1, j + 1));
    }
  }
}

void CompareTransposed(const S21Matrix &m1, const S21Matrix &m2) {
  EXPECT_EQ(m1.get_rows(), m2.get_cols());
  EXPECT_EQ(m1.get_cols(), m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i) {
    for (int j = 0; j < m2.get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(m1(j + 1, i + 1), m2(i + 1, j + 1));
    }
  }
}

}  // namespace s21

using namespace std;
using namespace s21;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
