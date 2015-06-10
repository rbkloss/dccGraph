#include "FibonacciHeap.h"


FibonacciHeap::FibonacciHeap() :n_(0), min_(nullptr) {}
FibonacciHeap::~FibonacciHeap() {
  deleteHeap(min_);
}

void FibonacciHeap::add(std::pair<unsigned, float> value) {
  auto node = insert(value);
  map_node_.insert(std::make_pair(value.first, node));
}

bool FibonacciHeap::pop(std::pair<unsigned, float>& minValue) {
  auto node = extractMin();
  if (node) {
    minValue = node->key_;
    map_node_.erase(minValue.first);
    delete node;
  } else{
    return false;
  }
  return n_ == 0;
}

void FibonacciHeap::update(std::pair<unsigned, float> newValue) {
  auto it = map_node_.find(newValue.first);
  if (it == map_node_.end()) {
    return;
  }
  decreaseKey(it->second, newValue);
}

void FibonacciHeap::setup() {

}

void FibonacciHeap::deleteHeap(FibonacciNode* x) {
  if (!x)
    return;
  if (x->left_ == x->right_ && x->left_ == x) {
    delete x;
    return;
  }

  auto cur = x;
  while (true) {
    if (cur->left_ && cur->left_ != x) {
      auto tmp = cur;
      cur = cur->left_;
      if (tmp->down_)
        deleteHeap(tmp->down_);
      delete tmp;
    } else {
      if (cur->down_)
        deleteHeap(cur->down_);
      delete cur;
      break;
    }
  }
}

/*
*From Cormen:
* insert(x)
* 5. if H.min == NIL
* 6. 	create a root list for H containing just x
* 7. 	H.min = x
* 8. else insert x into H's root list
* 9. 	if x.key < H.min.key
*10. 		H.min = x
*11. H.n = H.n + 1
*/
FibonacciHeap::FibonacciNode* FibonacciHeap::insert(Key k) {
  auto node = new FibonacciNode(k, nullptr);
  insert(node);
  return node;
}

void FibonacciHeap::insert(FibonacciNode* node) {
  if (min_ == nullptr) {
    min_ = node->left_ = node->right_ = node;
  } else {
    min_->left_->right_ = node;
    node->left_ = min_->left_;
    min_->left_ = node;
    node->right_ = min_;

    if (node->key_.second < min_->key_.second) {
      min_ = node;
    }
  }
  ++n_;
}



/*
FIB-HEAP-EXTRACT-MIN.H/
1 z = H:min
2 if z != NIL
3 for each child x of z
4 add x to the root list of H
5 x.p = NIL
6 remove z from the root list of H
7 if z == z.right
8 H:min == NIL
9 else H:min == z.right
10 CONSOLIDATE(H)/
11 H.n = H.n - 1
12 return z
*/
FibonacciHeap::FibonacciNode* FibonacciHeap::extractMin() {
  FibonacciNode *z, *x, *next;
  FibonacciNode** childList;

  z = min_;
  if (z != nullptr) {
    x = z->down_;
    if (x != nullptr) {
      childList = new FibonacciNode*[z->degree_];
      next = x;
      for (int i = 0; i < (z->degree_); i++) {
        //make child list
        childList[i] = next;
        next = next->right_;
      }
      //add each child x to the root list of H
      for (int i = 0; i < (z->degree_); i++) {
        x = childList[i];
        min_->left_->right_ = x;
        x->left_ = min_->left_;
        min_->left_ = x;
        x->right_ = min_;

        x->up_ = nullptr;
      }
      delete[] childList;
    }
    //remove z from the root list
    z->left_->right_ = z->right_;
    z->right_->left_ = z->left_;

    if (z == z->right_) {
      min_ = nullptr;
    } else {
      min_ = z->right_;
      consolidate();
    }
    n_--;
  }
  return z;
}

void FibonacciHeap::consolidate() {
  FibonacciNode* w, *next, *x, *y, *temp;
  FibonacciNode** A, ** rootList;
  
  int d, rootSize;
  int maxDegree = static_cast<int>(floor(log(static_cast<double>(n_))
    / log(static_cast<double>(1 + sqrt(static_cast<double>(5))) / 2)));

  A = new FibonacciNode*[maxDegree + 2]; 

  for (int i = 0; i < maxDegree + 2; ++i){
    A[i] = nullptr;
  }  
  w = min_;
  rootSize = 0;
  next = w;
  do {
    rootSize++;
    next = next->right_;
  } while (next != w);
  rootList = new FibonacciNode*[rootSize];
  for (int i = 0; i < rootSize; i++) {
    rootList[i] = next;
    next = next->right_;
  }
  for (int i = 0; i < rootSize; i++) {
    w = rootList[i];
    x = w;
    d = x->degree_;
    while (A[d] != nullptr) {
      y = A[d];
      if (x->key_.second > y->key_.second) {
        temp = x;
        x = y;
        y = temp;
      }
      heapLink(y, x);
      A[d] = nullptr;
      d++;
    }
    A[d] = x;
  }
  delete[] rootList;
  min_ = nullptr;
  for (int i = 0; i < maxDegree + 2; i++) {
    if (A[i] != nullptr) {
      if (min_ == nullptr) {
        min_ = A[i]->left_ = A[i]->right_ = A[i];
      } else {
        min_->left_->right_ = A[i];
        A[i]->left_ = min_->left_;
        min_->left_ = A[i];
        A[i]->right_ = min_;
        if (A[i]->key_ < min_->key_) {
          min_ = A[i];
        }
      }
    }
  }
  delete[] A;
}

/*
FIB-HEAP-LINK(H,y,x)
1 remove y from the root list of H
2 make y a child of x, incrementing x:degree
3 y:mark = FALSE
*/
void FibonacciHeap::heapLink(FibonacciNode* y, FibonacciNode* x) {
  y->left_->right_ = y->right_;
  y->right_->left_ = y->left_;

  if (x->down_ != nullptr) {
    x->down_->left_->right_ = y;
    y->left_ = x->down_->left_;
    x->down_->left_ = y;
    y->right_ = x->down_;
  } else {
    x->down_ = y;
    y->right_ = y;
    y->left_ = y;
  }
  y->up_ = x;
  x->degree_++;

  y->mark_ = false;
}

/*
FIB-HEAP-DECREASE-KEY.H; x; k/
1 if k > x:key
2 error “new key is greater than current key”
3 x:key D k
4 y D x:p
5 if y ¤ NIL and x:key < y:key
6 CUT.H; x; y/
7 CASCADING-CUT.H; y/
8 if x:key < H:min:key
9 H:min D x
*/
void FibonacciHeap::decreaseKey(FibonacciNode* x, Key k) {
  if (k.second > x->key_.second) {
    fprintf(stderr, "Key is greater than current key");
  }
  x->key_ = k;
  auto y = x->up_;
  if ((y != nullptr) &&
    (x->key_.second < y->key_.second)) {
    cut(x, y);
    cascadingCut(y);
  }
  if (x->key_.second < min_->key_.second)
    min_ = x;
}

/*
CUT.H; x; y/
1 remove x from the child list of y, decrementing y:degree
2 add x to the root list of H
3 x:p = NIL
4 x:mark = FALSE
*/
void FibonacciHeap::cut(FibonacciNode* x, FibonacciNode* y) {
  if (x->right_ == x) {
    y->down_ = nullptr;
  } else {
    x->right_->left_ = x->left_;
    x->left_->right_ = x->right_;
    if (y->down_ == x) {
      y->down_ = x->right_;
    }
  }
  y->degree_--;

  min_->right_->left_ = x;
  x->right_ = min_->right_;
  min_->right_ = x;
  x->left_ = min_;

  x->up_ = nullptr;

  x->mark_ = false;
}
/*
CASCADING-CUT.H; y/
1 z = y:p
2 if z != NIL
3 if y:mark == FALSE
4 y:mark = TRUE
5 else CUT(H, y, z)
6 CASCADING-CUT(H, z)
*/
void FibonacciHeap::cascadingCut(FibonacciNode* x) {
  auto z = x->up_;
  if (z != nullptr) {
    if (x->mark_ == false) {
      x->mark_ = true;
    } else {
      cut(x, z);
      cascadingCut(z);
    }
  }
}

/*
FIB - HEAP - UNION.H1; H2 /
1 H D MAKE - FIB - HEAP. /
2 H:min D H1 : min
3 concatenate the root list of H2 with the root list of H
4 if.H1 : min == NIL / or.H2 : min ¤ NIL and H2 : min : key < H1 : min : key /
5 H : min D H2 : min
6 H : n D H1 : n C H2 : n
7 return H
*/
FibonacciHeap* FibonacciHeap::unionFibHeap(FibonacciHeap*h1, FibonacciHeap* h2) {
  auto newHeap = new FibonacciHeap();
  newHeap->min_ = h1->min_;
  //concatenate h1 and h2 rootlist,
  if (newHeap->min_ != nullptr && h2->min_ != nullptr) {
    newHeap->min_->right_->left_ = h2->min_->left_;
    h2->min_->left_->right_ = newHeap->min_->right_;
    newHeap->min_->right_ = h2->min_;
    h2->min_->left_ = newHeap->min_;
  }
  if ((h1->min_ == nullptr) ||
    (h2->min_ != nullptr &&
    h2->min_->key_.second < h1->min_->key_.second)) {
    newHeap->min_ = h2->min_;
  }
  newHeap->n_ = h1->n_ + h2->n_;
  return newHeap;
}

void FibonacciHeap::removeNode(FibonacciNode* x) {
  decreaseKey(x, 
    std::make_pair(INT_MAX, std::numeric_limits<float>::min()));
  FibonacciNode*fn = extractMin();
  delete fn;
}