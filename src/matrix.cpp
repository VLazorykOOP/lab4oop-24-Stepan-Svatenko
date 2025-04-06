#include <iostream>

using namespace std;

enum state{
  ERROR_INIT, ERROR_MATH, OK, BAD_INDEX
};

template <typename type_data>
type_data bitwisesum(type_data a, type_data b){
  
  return (a | b);
}

template <typename type_data>
type_data bitwisemod2(type_data a, type_data b){
  return (a ^ b);
}

template <typename type_data>
type_data bitwisemult(type_data a, type_data b){
  return (a & b);
}



template <typename type_data>
class VectorShort{
  type_data* data;
  int size;
  state STATE = OK;
  static int count_obj;
  public:
    VectorShort(): data(nullptr),size(0){}
    VectorShort(int size, type_data init_value = 0) : size(size){
      try {
        data = new type_data[size];
        for(int i = 0; i<size;i++){
          data[i] = init_value;
        }
      }
      catch (...) {
        data = nullptr;
      }
    }
    VectorShort(VectorShort& a) : size(a.size){
      try {
        data = new type_data[size];
        for(int i = 0; i<size;i++){
          data[i] = a.data[i];
        }
      }
      catch (...) {
        data = nullptr;
      }
    }
    ~VectorShort(){
      delete [] data;
    }
    type_data& operator[](int i) {
        if (i >= 0 && i < size) {
            return data[i];
        }
        throw std::out_of_range("Index out of range in VectorShort");
    }
    int getSize() const { return size; }
  VectorShort& operator=(const VectorShort& other) {
    if (this != &other) {  
        delete[] data;  
        size = other.size;
        data = new type_data[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
  }
  VectorShort& operator|(VectorShort& a){
    VectorShort<type_data> temp = *this;
    for(int i = 0; i<size;i++){
      temp.data[i] = bitwisesum(data[i], a.data[i]);
      
    }
    return temp;
  }
  VectorShort& operator^(VectorShort& a){
    VectorShort<type_data> temp = *this;
    for(int i = 0; i<size;i++){
      temp.data[i] = bitwisemod2(data[i], a.data[i]);
    }
    return temp;
  }
  VectorShort& operator&(VectorShort& a){
    VectorShort<type_data> temp = *this;
    for(int i = 0; i<size;i++){
      temp.data[i] = bitwisemult(data[i], a.data[i]);
    }
    return temp;
  }

  VectorShort& operator=(VectorShort&& other) noexcept {
    if (this != &other) {
        delete[] data; 
        data = other.data;  
        size = other.size;
        other.data = nullptr; 
        other.size = 0;
    }
    return *this;
}

    VectorShort& operator++(){
      for(int i = 0; i<size;i++){
        data[i]++;
      }
      return *this;
    }
    VectorShort& operator--(){
      for(int i = 0; i<size;i++){
        data[i]--;
      }
      return *this;
    }
    VectorShort& operator~(){
      VectorShort temp = *this;
      for(int i = 0; i<size;i++){
        temp.data[i] = ~data[i];
      }
      return temp;
    }
    VectorShort& operator-(){
      VectorShort temp = *this;
      for(int i = 0; i<size;i++){
        temp.data[i] = -data[i];
      }
      return temp;
    }
    
};
template <typename type_data>
class MatrixShort{
public:
  template <typename type_is>
  friend ostream& operator<< (ostream& os, const MatrixShort<type_is>& matrix);
  template <typename type_is>
  friend istream& operator>> (istream& is, MatrixShort<type_is>& matrix);
protected:
  VectorShort<type_data>*  ShortArray;
  int n;
  int m;
  state STATE = OK;
  static int count_obj;
public:
  MatrixShort(int n, int m, type_data init_value = 0) : n(n), m(m){
    ShortArray = new VectorShort<type_data>[n];
    for (int i = 0; i < n; i++) ShortArray[i] = VectorShort<type_data>(m, init_value);
  }
  MatrixShort(int size) : n(size), m(size){
    ShortArray = new VectorShort<type_data>[n];
    for (int i = 0; i < n; i++) ShortArray[i] = VectorShort<type_data>(m, 1);
  }
  MatrixShort(const MatrixShort& a) : n(a.n), m(a.m){
    ShortArray = new VectorShort<type_data>[n];
    for (int i = 0; i < n; i++) ShortArray[i] = a.ShortArray[i];
  }
  ~MatrixShort(){
    delete [] ShortArray;
  }
  MatrixShort operator=(const MatrixShort& a){
    if (&a != this){
      delete[] ShortArray;
      n = a.n;
      m = a.m;
      ShortArray = new VectorShort<type_data>[n];
      for (int i = 0; i < n; i++) ShortArray[i] = a.ShortArray[i];
    }
    return *this;
  }

  int getRow() const { return n; }
  int getCols() const { return m; }
  state getState() const { return STATE; }


  MatrixShort& operator++(){
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ShortArray[i][j]++;
    return *this;
  }
  MatrixShort& operator--(){
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ShortArray[i][j]--;
    return *this;
  }

  bool operator!(){
    return (n != 0 && m != 0);
  }
  MatrixShort operator~(){
    MatrixShort temp = *this;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ~ShortArray[i][j];
    return temp;
  }
  MatrixShort operator+(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] + a.ShortArray[i][j];
    return temp;
  }
  MatrixShort operator+(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] + a;
    return temp;
  }
  MatrixShort operator-(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] - a.ShortArray[i][j];
    return temp;
  }
  MatrixShort operator-(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] - a;
    return temp;
  }
  MatrixShort operator*(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] * a.ShortArray[i][j];
    return temp;
  }
  MatrixShort operator*(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] * a;
    return temp;
  }
  MatrixShort operator/(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] / a;
    return temp;
  }
  MatrixShort operator%(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] % a;
    return temp;
  }
 

  MatrixShort& operator+=(type_data a){
    *this = *this + a;
    return *this;
  }
  MatrixShort& operator-=(type_data a){
    *this = *this - a;
    return *this;
  }
  MatrixShort& operator*=(type_data a){
    *this = *this * a;
    return *this;
  }
  MatrixShort& operator/=(type_data a){
    *this = *this / a;
    return *this;
  }
  MatrixShort& operator%=(type_data a){
    *this = *this % a;
    return *this;
  }
  MatrixShort operator|(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] | a.data[j];
    return temp;
  }
  MatrixShort operator|(type_data a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] | a;
    return temp;
  }
  MatrixShort operator^(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] ^ a.data[j];
    return temp;
  }
  MatrixShort operator^(type_data a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] ^ a;
    return temp;
  }
  MatrixShort operator&(MatrixShort a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] & a.data[j];
    return temp;
  }
  MatrixShort operator&(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] & a;
    return temp;
  }
 
  MatrixShort& operator&=(type_data a){
    *this = *this & a;
    return *this;
  }
  MatrixShort operator>>=(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] >> a;
    return temp;
  }
  MatrixShort& operator<<=(short int a){
    
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        ShortArray[i][j] = ShortArray[i][j] << a;
    return *this;
  }
 
  MatrixShort& operator|=(type_data a){
    *this = *this | a;
    return *this;
  }
  MatrixShort& operator^=(type_data a){
    *this = *this ^ a;
    return *this;
  }

  VectorShort<type_data>& operator[](int i) {
        if (i >= 0 && i < n) {
            return ShortArray[i];
        }
        throw std::out_of_range("Index out of range in MatrixShort");
    }

  const type_data& operator[](int i) const {
      if (i >= 0 && i < n) {
        return ShortArray[i];
      }
         throw std::out_of_range("Index out of range in MatrixShort");
    }


  bool operator==(const MatrixShort<type_data>& other) const {
    if (n != other.n || m != other.m)
        return false;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (ShortArray[i][j] != other.ShortArray[i][j])
                return false;
    return true;
  }

  bool operator!=(const MatrixShort<type_data>& other) const {
    return !(*this == other);
  }
  bool operator>(const MatrixShort& a){
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        if(ShortArray[i][j] > a.ShortArray[i][j])
          return true;
    return false;
  }
  bool operator>=(const MatrixShort& a){
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        if(ShortArray[i][j] >= a.ShortArray[i][j])
          return true;
    return false;
  }
  bool operator<(const MatrixShort& a){
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        if(ShortArray[i][j] < a.ShortArray[i][j])
          return true;
    return false;
  }
  bool operator<=(const MatrixShort& a){
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        if(ShortArray[i][j] < a.ShortArray[i][j])
          return true;
    return false;
  }
  


};

// Оператор виводу для матриці
template <typename type_data>
ostream& operator<<(ostream& os, const MatrixShort<type_data>& matrix) {
  for (int i = 0; i < matrix.n; ++i) {
    for (int j = 0; j < matrix.m; ++j) {
      os << matrix.ShortArray[i][j] << " ";  
    }
    os << '\n';  
  }
  return os;
}

// Оператор вводу для матриці
template <typename type_data>
istream& operator>>(istream& is, MatrixShort<type_data>& matrix) {
  for (int i = 0; i < matrix.n; ++i) {
    for (int j = 0; j < matrix.m; ++j) {
      if (!(is >> matrix.ShortArray[i][j])) {  
        cerr << "Invalid input at position (" << i << ", " << j << ")." << endl;
        is.setstate(ios::failbit);  
        return is;
      }
    }
  }
  return is;
}



int main (int argc, char *argv[]) {
 // Створення двох матриць
    MatrixShort<int> mat1(3, 3, 1);  // 3x3 матриця, ініціалізована значеннями 1
    MatrixShort<int> mat2(3, 3, 2);  // 3x3 матриця, ініціалізована значеннями 2

    // Виведення початкових матриць
    cout << "Matrix 1:\n" << mat1;
    cout << "Matrix 2:\n" << mat2;

    // Операції додавання
    MatrixShort<int> mat3 = mat1 + mat2;
    cout << "Matrix 1 + Matrix 2:\n" << mat3;

    // Операція віднімання
    MatrixShort<int> mat4 = mat2 - mat1;
    cout << "Matrix 2 - Matrix 1:\n" << mat4;

    // Операція множення на скаляр
    MatrixShort<int> mat5 = mat1 * 2;
    cout << "Matrix 1 * 2:\n" << mat5;

    // Операція ділення на скаляр
    MatrixShort<int> mat6 = mat2 / 2;
    cout << "Matrix 2 / 2:\n" << mat6;

    // Операція порівняння (==)
    cout << "Matrix 1 == Matrix 2? " << (mat1 == mat2 ? "Yes" : "No") << endl;

    // Операція порівняння (!=)
    cout << "Matrix 1 != Matrix 2? " << (mat1 != mat2 ? "Yes" : "No") << endl;

    // Операція порівняння (>)
    cout << "Matrix 1 > Matrix 2? " << (mat1 > mat2 ? "Yes" : "No") << endl;

    // Операція індексації
    cout << "Element at (0, 0) of Matrix 1: " << mat1[0][0] << endl;

    // Операція інкременту
    ++mat1;
    cout << "Matrix 1 after increment:\n" << mat1;

    // Операція декременту
    --mat1;
    cout << "Matrix 1 after decrement:\n" << mat1;

    // Операція інкременту з присвоєнням
    mat1 += 3;
    cout << "Matrix 1 after += 3:\n" << mat1;

    // Операція декременту з присвоєнням
    mat1 -= 1;
    cout << "Matrix 1 after -= 1:\n" << mat1;

    // Операція множення на скаляр з присвоєнням
    mat1 *= 2;
    cout << "Matrix 1 after *= 2:\n" << mat1;

    // Операція ділення на скаляр з присвоєнням
    mat1 /= 2;
    cout << "Matrix 1 after /= 2:\n" << mat1;

    // Операція порівняння (>=)
    cout << "Matrix 1 >= Matrix 2? " << (mat1 >= mat2 ? "Yes" : "No") << endl;

    // Операція порівняння (<=)
    cout << "Matrix 1 <= Matrix 2? " << (mat1 <= mat2 ? "Yes" : "No") << endl;

    // Операція побітового OR
    MatrixShort<int> mat7 = mat1 | 1;
    cout << "Matrix 1 | 1:\n" << mat7;

    // Операція побітового AND
    MatrixShort<int> mat8 = mat1 & 1;
    cout << "Matrix 1 & 1:\n" << mat8;

    // Операція побітового XOR
    MatrixShort<int> mat9 = mat1 ^ 1;
    cout << "Matrix 1 ^ 1:\n" << mat9;

    // Операція побітового зміщення вправо
    MatrixShort<int> mat10 = mat1 >>= 1;
    cout << "Matrix 1 after >>= 1:\n" << mat10;

    // Операція побітового зміщення вліво
    mat1 <<= 1;
    cout << "Matrix 1 after <<= 1:\n" << mat1;

    // Операція побітового OR з присвоєнням
    mat1 |= 3;
    cout << "Matrix 1 after |= 3:\n" << mat1;

    // Операція побітового AND з присвоєнням
    mat1 &= 3;
    cout << "Matrix 1 after &= 3:\n" << mat1;

    // Операція побітового XOR з присвоєнням
    mat1 ^= 2;
    cout << "Matrix 1 after ^= 2:\n" << mat1;

    return 0;
}
