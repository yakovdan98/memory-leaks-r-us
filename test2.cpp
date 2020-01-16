#include <cassert>
#include <iostream>

using namespace std;

class NodeTest2 {
  friend ostream &operator<<(ostream &Out, const NodeTest2 &N) {
    Out << "N<" << N.Value << ", " << (N.Next != nullptr) << ">";
    return Out;
  }

public:
  static int NodeCount;
  int Value;
  NodeTest2 *Next;

  explicit NodeTest2(int Value = 0, NodeTest2 *Next = nullptr)
      : Value{Value}, Next{Next} {
    ++NodeCount;
    cout << "Creating " << *this << ", total created: " << NodeCount << endl;
  }
  ~NodeTest2() {
    cout << "Deleting: " << *this;
    --NodeCount;
    cout << ", nodes remaining: " << NodeCount << endl;
    delete Next;
  }
};

int NodeTest2::NodeCount = 0;

NodeTest2 *find(NodeTest2 *Start, int Value) {
  assert(Start != nullptr);
  NodeTest2 *Curr = Start;
  while (Curr != nullptr && Curr->Value != Value)
    Curr = Curr->Next;
  return Curr;
}

// insert B after A, return B
NodeTest2 *addAfter(NodeTest2 *A, NodeTest2 *B) {
  assert(A != nullptr && B != nullptr);
  NodeTest2 *C = A->Next;
  A->Next = B;
  B->Next = C;
  return B;
}

// Given the head of the list, find Node with ValB, insert A to come before B
NodeTest2 *addBefore(NodeTest2 *Start, int ValA, int ValB) {
  assert(Start != nullptr);
  NodeTest2 *NodeB = find(Start, ValB);
  if (NodeB == Start)
    return Start;
  auto *NodeA = new NodeTest2(ValA);
  NodeA->Next = NodeB;
  NodeTest2 *Curr = Start;

  while (Curr->Next != NodeB)
    Curr = Curr->Next;
  Curr->Next = NodeA;
  return Start;
}

NodeTest2 *remove(NodeTest2 *Start, NodeTest2 *N) {
  if (N == nullptr)
    return Start;
  assert(Start != nullptr);
  NodeTest2 *Curr = Start;
  while (Curr != nullptr && Curr->Next != N)
    Curr = Curr->Next;
  if (Curr != nullptr) {

    Curr->Next = N->Next;
    N->Next = nullptr;
    delete N;
  }
  return Start;
}

void displayAll(NodeTest2 *N) {
  cout << "[";
  if (N != nullptr) {
    cout << *N;
    N = N->Next;
  }
  while (N != nullptr) {
    cout << ", " << *N;
    N = N->Next;
  }
  cout << "]" << endl;
}

void test2() {
  auto *Head = new NodeTest2(100);
  NodeTest2 *Tail = Head;
  for (int I = 1; I <= 5; ++I) {
    Tail = addAfter(Tail, new NodeTest2(I * I * I));
  }
  displayAll(Head);
  Head = addBefore(Head, 7, 8);
  addBefore(Head, 13, 125);
  addBefore(Head, 15, 9);
  addBefore(Head, 17, 11);

  addBefore(Head, 19, 100);
  displayAll(Head);
  remove(Head, find(Head, 8));
  remove(Head, find(Head, 77));
  remove(Head, find(Head, 100));
  remove(Head, find(Head, 19));
  displayAll(Head);

  delete Head;
}
