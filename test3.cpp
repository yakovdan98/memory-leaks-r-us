#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class StringT3 {
private:
	//bool if object is the originator of memory
  bool ownMemory = false;

public:
	//Mystrings starts as nullptr
  string *MyStrings = nullptr;
  StringT3() = default;
  StringT3(string A, string B, string C) : ownMemory(true) {
	  //Mystrings gets initialized
    MyStrings = new string[3];
    MyStrings[0] = A; // NOLINT - not using move
    MyStrings[1] = B; // NOLINT - not using move
    MyStrings[2] = C; // NOLINT - not using move
    cout << "Created " << MyStrings[0] << MyStrings[1] << MyStrings[2] << endl;
  }

  //copy constructor that uses others Mystring array
  StringT3(const StringT3 &other) {
    MyStrings = other.MyStrings;
    ownMemory = false;
  }

  ~StringT3() {
	  //deletes if object owns the Mystrings array
    if (ownMemory && MyStrings != nullptr) {
      cout << "Deleting " << MyStrings[0] << MyStrings[1] << MyStrings[2]
           << endl;
      delete[] MyStrings;
    }
  }

  //assignment operator that uses other objects Mystrings array
  StringT3 &operator=(const StringT3 &other) {
    if (ownMemory)
		//deletion of original memory
      delete[] MyStrings;
    MyStrings = other.MyStrings;
    ownMemory = false;
    return *this;
  }
};

void test3() {
  StringT3 S1("a", "b", "c");
  StringT3 T1;
  T1 = S1;
  StringT3 U1(S1);
  U1.MyStrings[0] = "q";

  auto *S2ptr = new StringT3("w", "x", "y");
  StringT3 *T2ptr;
  T2ptr = S2ptr;

  vector<StringT3> V1;
  V1.push_back(S1);
  V1.push_back(T1);
  V1.push_back(U1);

  vector<StringT3 *> V2;
  V2.push_back(S2ptr);
  V2.push_back(T2ptr);

  delete S2ptr;

  cout << "test3 is done" << endl;
}