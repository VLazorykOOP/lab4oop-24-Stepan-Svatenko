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
    int& operator[](int i){
      if(i >= 0 && i<size) return data[i];
      return data[size-1];
    }
    int getSize() const { return size; }
  VectorShort& operator=(const VectorShort& other) {
    if (this != &other) {  // Перевірка на самокопіювання
        delete[] data;  // Звільняємо стару пам'ять
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
        delete[] data;  // Звільняємо стару пам'ять
        data = other.data;  // Переміщаємо дані
        size = other.size;
        other.data = nullptr;  // Обнуляємо тимчасовий об'єкт
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
  MatrixShort(MatrixShort& a) : n(a.n), m(a.m){
    ShortArray = new VectorShort<type_data>[n];
    for (int i = 0; i < n; i++) ShortArray[i] = a.ShortArray[i];
  }
  ~MatrixShort(){
    delete [] ShortArray;
  }
  MatrixShort operator=(MatrixShort& a){
    if (a != this){
      delete[] ShortArray;
      n = a.n;
      m = a.m;
      ShortArray = new VectorShort[n];
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
  MatrixShort& operator~(){
    MatrixShort temp = *this;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ~ShortArray[i][j];
    return temp;
  }
  MatrixShort& operator+(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] + a.ShortArray[i][j];
    return temp;
  }
  MatrixShort& operator+(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] + a;
    return temp;
  }
  MatrixShort& operator-(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] - a.ShortArray[i][j];
    return temp;
  }
  MatrixShort& operator-(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] - a;
    return temp;
  }
  MatrixShort& operator*(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] * a.ShortArray[i][j];
    return temp;
  }
  MatrixShort& operator*(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] * a;
    return temp;
  }
  MatrixShort& operator/(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] / a;
    return temp;
  }
  MatrixShort& operator%(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] % a;
    return temp;
  }
  MatrixShort& operator+=(MatrixShort& a){
    *this = *this + a;
    return *this;
  }
  MatrixShort& operator-=(MatrixShort& a){
    *this = *this - a;
    return *this;
  }
  MatrixShort& operator*=(MatrixShort& a){
    *this = *this * a;
    return *this;
  }
  MatrixShort& operator%=(MatrixShort& a){
    *this = *this % a;
    return *this;
  }

  MatrixShort& operator+=(short int a){
    *this = *this + a;
    return *this;
  }
  MatrixShort& operator-=(short int a){
    *this = *this - a;
    return *this;
  }
  MatrixShort& operator*=(short int a){
    *this = *this * a;
    return *this;
  }
  MatrixShort& operator/=(short int a){
    *this = *this / a;
    return *this;
  }
  MatrixShort& operator%=(short int a){
    *this = *this % a;
    return *this;
  }
  MatrixShort& operator|(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] | a.data[j];
    return temp;
  }
  MatrixShort& operator|(type_data a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] | a;
    return temp;
  }
  MatrixShort& operator^(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] ^ a.data[j];
    return temp;
  }
  MatrixShort& operator^(type_data a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] ^ a;
    return temp;
  }
  MatrixShort& operator&(MatrixShort& a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] & a.data[j];
    return temp;
  }
  MatrixShort& operator&(short int a){
    MatrixShort<type_data> temp = *this;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        temp.ShortArray[i][j] = ShortArray[i][j] & a;
    return temp;
  }
  MatrixShort& operator&=(MatrixShort& a){
    *this = *this & a;
    return *this;
  }
  MatrixShort& operator&=(type_data a){
    *this = *this & a;
    return *this;
  }
  MatrixShort& operator>>=(short int a){
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
  MatrixShort& operator|=(MatrixShort& a){
    *this = *this & a;
    return *this;
  }
  MatrixShort& operator|=(type_data a){
    *this = *this | a;
    return *this;
  }
  template <typename type_data_is>
  MatrixShort& operator^=(type_data_is& a){
    *this = *this ^ a;
    return *this;
  }
  







};

int main (int argc, char *argv[]) {
  MatrixShort<int> m(2, 2);  
  return 0;
  m<<=1;
}
