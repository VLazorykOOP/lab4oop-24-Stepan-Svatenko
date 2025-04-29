#include "tasks.h"
#include <limits>
void clear_buffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void interface() {
  char ch = '5';
  do {
    clear_buffer();
    system("clear");
    cout << " Menu \n[1] Task 1\n[2] Task 2\n[3] Task 3\n[ ]\b\b";
    ch = cin.get();
    clear_buffer();
    switch (ch) {
    case '1':
      task1();
      break;
    case '2':
      task2();
      break;
    case '3':
      task3();
      break;
    case '6':
      return;
    }
    clear_buffer();
    cout << " Press any key and enter\n";
  } while (ch != '6');
}
