#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
    int key;
    struct Node *left,  *right;
};

int height(Node* root);
int noNodes(Node* root);
struct Node* maxNode(Node* root);
struct Node* minNode(Node* root);

void searchParentBst(struct Node* T, int searchKey, Node*& q, Node*& p);
struct Node* getNode(int key);
void inorderBST(Node* root);
void insertBST(Node*& T, int key);
void deleteBST(struct Node*& T, int key);



int height(Node* root){
  if (root == NULL)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}
int noNodes(Node* root){
  if (root == NULL)
    return 0;
  return 1 + noNodes(root->left) + noNodes(root->right);
}
struct Node* maxNode(Node* root){
  struct Node* temp = root;
  while(temp->right != NULL)
    temp = temp->right;
  return temp;
}
struct Node* minNode(Node* root){
  struct Node* temp = root;
  while(temp->left != NULL)
    temp = temp->left;
  return temp;
}
void searchParentBst(struct Node* T, int searchKey, Node*& q, Node*& p){
  //return 은 searchkey의 parentNode
    q = NULL;
    p = T;
    while(p != NULL){
      if(searchKey == p->key)
        return;
      q = p;
      if(searchKey < p->key)
        p = p->left;
      else
        p = p->right;
    }
    return;
}

struct Node* getNode(int key){
    struct Node* newNode
            = (Node*)malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;
    return newNode;
}

void inorderBST(Node* root){
    if (root != NULL) {
        inorderBST(root->left);
        cout<< (root->key)<< " ";
        inorderBST(root->right);
    }
}

void insertBST(Node*& T, int key){
    struct Node* q = NULL;
    struct Node* p = T;
    while(p != NULL){
      if(key == p->key)
        return;
      q = p;//q는 p의 부모
      if(key < p->key)//left
        p = p->left;
      else
        p = p->right;
    }
    struct Node* newNode;
    newNode = getNode(key);

    if (T == NULL)
        T = newNode;
    else if (key < q->key)
        q->left = newNode;
    else
        q->right = newNode;
    return;
}

void deleteBST(struct Node*& T, int key){
    struct Node* q = NULL;
    struct Node* p = NULL;
    searchParentBst(T, key, q, p);//q는 부모 p는 삭제
    struct Node* R = NULL;

    if(p == NULL)
      return;
/*
    if(q == NULL) {//루트노드만 있을경우 루트를 삭제????????
        if((p->left == NULL) && (p->right == NULL))
          T = NULL;
    }*/
    if((p->left == NULL) && (p->right == NULL)){//차수0
      if(q == NULL){//p가 root일때
        T = NULL;
        return;
      }
        if(q->left == p)
          q->left = NULL;
        else
          q->right = NULL;
    }
    else if((p->left == NULL) || (p->right == NULL)){//차수1
      if(q == NULL){//p가 root일때
        if(p->right == NULL)
          T = p->left;
        else
          T = p->right;
        return;
      }
      if(p->right == NULL){//차수 == left
          if(q->left == p)
            q->left = p->left;
          else
            q->right = p->left;
      }
      else{//차수 == right
          if(q->left == p)
            q->left = p->right;
          else
            q->right = p->right;
      }
    }
    else{//차수 2
      int flag;//flag 0 -> left //flag 1 -> right
      int LH = height(p->left);
      int RH = height(p->right);
      int numL = noNodes(p->left);
      int numR = noNodes(p->right);

      if(LH > RH){//height 비교
        flag = 0;
        R = maxNode(p->left);
      }
      else if(LH < RH){
        flag = 1;
        R = minNode(p->right);
      }
      else{//height 같을 때 noNodes비교
        if(numL >= numR){
          R = maxNode(p->left);
          flag = 0;
        }
        else{
          R = minNode(p->right);
          flag = 1;
        }
      }

      p->key = R->key;
      if(flag == 0)
        deleteBST(p->left, R->key);
      else
        deleteBST(p->right, R->key);
    }
    return;
}

int main() {
  int sample[20] = {25,  500,  33,  49,  17,  403,  29, 105,  39,  66,
                  305,  44,   19,  441,  390,  12,  81,  50,  100,  999};

  Node* root = NULL;

  for(int i = 0; i<20;i++){//삽입1
    insertBST(root, sample[i]);
    inorderBST(root); cout << endl;
  }
  for(int i = 0; i<20;i++){//삭제1
    deleteBST(root, sample[i]);
    inorderBST(root); cout << endl;
  }

  root = NULL;//초기화

  for(int i = 0; i<20;i++){//재삽입
    insertBST(root, sample[i]);
    inorderBST(root); cout << endl;
  }
  for(int i = 19; i>=0;i--){//삭제 역순
    deleteBST(root, sample[i]);
    inorderBST(root); cout << endl;
  }


    return 0;
}
