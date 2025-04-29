#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

enum state{
  ERROR_INIT, ERROR_MATH, OK, BAD_INDEX
};

class Vector3
{
  state STATE = OK;
  

  public:
    float* d;
    Vector3(){
      d = new float[3];
      d[0] = d[1] = d[2];
    }
    Vector3(float a){
      d = new float[3];
      d[0] = d[1] = d[2] = a;
    }
    Vector3(float a, float b, float c){
      d = new float[3];
      d[0] = a;
      d[1] = b;
      d[2] = c;
    }

    Vector3(float *a) {if(a == NULL){cout << "ERROR: Vector3(float *a) a == NULL \n";}else {d = new float[3];d[0] = a[0]; d[1] = a[1]; d[2] = a[2];} }
    ~Vector3(){cout << "Vector3 ~ \n"; cout << this->d[0] << " " << this->d[1] << " " << this->d[2] << " STATE:" << this->STATE << " \n"; delete[] d; }

    void operator++(int){ d[0]++; d[1]++; d[2]++;}
    void operator--(int){ d[0]--; d[1]--; d[2]--;}
    bool operator!() const {return (d[0] == 0 && d[1] == 0 && d[2] == 0); };
    Vector3& operator=(Vector3& a ){ 
      if (this != &a) {
            delete[] d;
            d = new float[3];
            for (int i = 0; i < 3; ++i){ 
              d[i] = a.d[i];
              cout << a.d[i] << " ";
              
            }
            STATE = a.STATE;
        }
        return *this;
    }

   vector<float> operator~() {
        if (d[0] != 0) {
            return {-d[1], d[0], 0};  // Перпендикулярний вектор до (x, y, z)
        }
        else if (d[1] != 0) {
            return {0, -d[2], d[1]};  // Перпендикулярний вектор до (0, y, z)
        }
        else {
            return {d[2], 0, -d[1]};  // Перпендикулярний вектор до (0, 0, z)
        }
    }
    Vector3 operator-(){
      return Vector3{-d[0], -d[1], -d[2]};
    }
    Vector3 operator+(Vector3 &a){
      Vector3 tmp(this->d[0] + a.d[0], this->d[1] + a.d[1], this->d[2] + a.d[2]);
      return tmp;
    }
    Vector3 operator-(Vector3 &a){
      Vector3 tmp(this->d[0] - a.d[0], this->d[1] - a.d[1], this->d[2] - a.d[2]);
      return tmp;
    }
    Vector3 operator*(Vector3 &a){
      Vector3 tmp(this->d[0] * a.d[0], this->d[1] * a.d[1], this->d[2] * a.d[2]);
      return tmp;
    }
    Vector3 operator*(float a){
      Vector3 tmp(this->d[0] * a, this->d[1] * a, this->d[2] * a);
      return tmp;
    }
    Vector3 operator/(Vector3 &a){
      Vector3 tmp(this->d[0] / a.d[0], this->d[1] / a.d[1], this->d[2] / a.d[2]);
      return tmp;
    }
    Vector3 operator/(float a){
      Vector3 tmp(this->d[0] / a, this->d[1] / a, this->d[2] / a);
      return tmp;
    }
    Vector3 operator%(Vector3 &a){
      Vector3 tmp((int)this->d[0] % (int)a.d[0], (int)this->d[1] % (int)a.d[1], (int)this->d[2] % (int)a.d[2]);
      return tmp;
    }
    Vector3 operator%(int a){
      Vector3 tmp((int)this->d[0] % a, (int)this->d[1] % a, (int)this->d[2] % a);
      return tmp;
    }
    
    Vector3& operator-=(Vector3& a){
      this->d[0] -= a.d[0];
      this->d[1] -= a.d[1];
      this->d[2] -= a.d[2];
      return *this;
    }
    Vector3& operator+=(Vector3& a){
      this->d[0] += a.d[0];
      this->d[1] += a.d[1];
      this->d[2] += a.d[2];
      return *this;
    }
    Vector3& operator*=(Vector3& a){
      this->d[0] *= a.d[0];
      this->d[1] *= a.d[1];
      this->d[2] *= a.d[2];
      return *this;
    }
    Vector3& operator*=(float a){
      this->d[0] *= a;
      this->d[1] *= a;
      this->d[2] *= a;
      return *this;
    }
    Vector3& operator/=(Vector3& a){
      this->d[0] /= a.d[0];
      this->d[1] /= a.d[1];
      this->d[2] /= a.d[2];
      return *this;
    }
    Vector3& operator/=(float a){
      this->d[0] /= a;
      return *this;
    }
    Vector3& operator&=(Vector3& a){
      this->d[0] = (this->d[1] *a.d[2] - this->d[2] * a.d[1]);
      this->d[1] = (this->d[2] *a.d[0] - this->d[0] * a.d[2]);
      this->d[2] = (this->d[0] *a.d[1] - this->d[1] * a.d[0]);
      return *this;
    }

    bool operator==(Vector3& a){
      for(int i = 0; i < 3; i++){
        if(this->d[i] == a.d[i]) return true;
        else return false;
      }
    }
    bool operator!=(Vector3& a){
      for(int i = 0; i < 3; i++){
        if(this->d[i] == a.d[i]) return false;
        else return true;
      }
    }
  float& operator[](int index) {
    if (index >= 0 && index < 3) {
      STATE = OK;
      return d[index];
     } else {
      STATE = BAD_INDEX;
      return d[2]; // Повертаємо z як запасний варіант
     }
  }
  bool operator>(Vector3& a){
    int module = sqrt((this->d[0] * this->d[0]) + (this->d[1] * this->d[1]) + (this->d[2] * this->d[2]));
    int module2 = sqrt((a.d[0] * a.d[0]) + (a.d[1] * a.d[1]) + (a.d[2] * a.d[2]));
    return module > module2;
  }

  bool operator>=(Vector3& a){
    int module = sqrt((this->d[0] * this->d[0]) + (this->d[1] * this->d[1]) + (this->d[2] * this->d[2]));
    int module2 = sqrt((a.d[0] * a.d[0]) + (a.d[1] * a.d[1]) + (a.d[2] * a.d[2]));
    return module >= module2;
  }
  bool operator<(Vector3& a){
    int module = sqrt((this->d[0] * this->d[0]) + (this->d[1] * this->d[1]) + (this->d[2] * this->d[2]));
    int module2 = sqrt((a.d[0] * a.d[0]) + (a.d[1] * a.d[1]) + (a.d[2] * a.d[2]));
    return module < module2;
  }
  bool operator<=(Vector3& a){
    int module = sqrt((this->d[0] * this->d[0]) + (this->d[1] * this->d[1]) + (this->d[2] * this->d[2]));
    int module2 = sqrt((a.d[0] * a.d[0]) + (a.d[1] * a.d[1]) + (a.d[2] * a.d[2]));
    return module <= module2;
  }

  friend ostream& operator<<(ostream& os, const Vector3& v);
  friend ostream& operator>>(ostream& is, const Vector3& v);
};


istream& operator>>(istream& is, const Vector3& v)
  {
    int i;
    for (i = 0; i < 3; i++) is >> v.d[i];
    return is;
  }
ostream& operator<<(ostream& os, const Vector3& v)
  {
    int i;
    for (i = 0; i < 3; i++) os << " " << v.d[i] << " ";
    return os;
  }




int unit_vector3()
{
  float arr[] = {0.0,1.0,3.0};
  Vector3 a ,b(1.1), c(arr);
  cout << "A: " << a << " B: " << b << " C: " <<c<< endl;
  cout << "(!a)" <<(!a) << endl;

  cout << "OUTPUT:" << a << "OUTPUT(by index): "<< a[1] << endl;
  
  b++;
  cout << "b++" <<b <<endl;

  c--;
  cout << "c--" <<c <<endl;

  ~a;
  cout << "~a" << a << endl;
  
  a++;
  cout << "a++" <<a <<endl;
  
  b--;
  cout << "b--" <<b <<endl;
  
  -a;
  cout << "-a" << a << endl;
  
  a+=b;
  cout << "a+=b" << a << endl;
  
  a-=b;
  cout << "a-=b" << a << endl;
  
  a*=b;
  cout << "a*=b" << a << endl;
  
  a/=b;
  cout << "a/=b" << a << endl;
  
  a&=b;
  cout << "a&=b" << a << endl;
  
  a=b;
  cout << "a=b" << a << endl;

  
  return 0;
}
