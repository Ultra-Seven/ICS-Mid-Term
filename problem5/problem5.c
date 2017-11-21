//gcc problem5.c -lm -o problem5
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAXSIZE 1024
#define CORRECTNESS 0
#if CORRECTNESS == 1
    #define THRESHOLD 10
#else 
    #define THRESHOLD 100000
#endif
typedef struct
{
    int level;
    int sibling;
    char short_node;
    struct node *left;
    struct node *right;
} node;

node *start;


typedef struct {  
    node* data[MAXSIZE];  
    int top;  
}Stack;  
  
Stack* InitStack() {  
    Stack* stack;  
    stack = (Stack*)malloc(sizeof(Stack));  
    if (!stack) {  
        return NULL;  
    }  
    stack->top = 0;  
    return stack;  
}  
  
int IsFull(Stack* stack) {  
    if (stack->top == MAXSIZE - 1) {  
        return 1;  
    }  
    return 0;  
}  
  
int IsEmpty(Stack* stack) {  
    if (stack->top == 0) {  
        return 1;  
    }  
    return 0;  
}  
  

void Push(Stack* stack, node* item) {  
    if (IsFull(stack)) {  
        return;  
    }  
    stack->data[++stack->top] = item;  
}  
  
 
node* Pop(Stack* stack) {  
    if (IsEmpty(stack)) {
      
    }  
    return stack->data[stack->top--];  
}  



void calculateDistance(node *target, int threshold) {
    double d = sqrt(pow(target->level - start->level, 2) +pow(target->sibling - start->sibling, 2));
    #if CORRECTNESS == 1
    printf("calculate level: %d, sibling: %d, distance: %f\n", target->level, target->sibling, d);
    #endif
    target->short_node =  d <= threshold;
}
void calculateTreeNode(node *root)
{
    if(!root)
        return;
    calculateTreeNode(root -> left);
    calculateDistance(root, THRESHOLD);
    calculateTreeNode(root ->right);
}
void calculateTreeNode_no_tail_recursion(node *root)
{
    if(!root)
        return;
    
    node *next = root;
    while (next){
      calculateTreeNode_no_tail_recursion(next -> left);
      calculateDistance(next, THRESHOLD);
      if (next -> short_node == 0) {
          return;
      }
      next = next -> right;
    }  
}
void calculateTreeNode_no_recursion(node *root)
{
    if(root == NULL)
      return;
 
    Stack* nstack = InitStack();
    Push(nstack, root);
    node *next = root->left;
 
    while (next != NULL || !IsEmpty(nstack))
    {
      while (next != NULL)
      {
        Push(nstack, next);
        calculateDistance(next, THRESHOLD);
        if(next -> short_node == 0) {
            break;
        }
        next = next->left;
      }
      next = Pop(nstack);
      next = next->right;
    }
}
void initilizeTree() {
  start = (node* )(malloc(sizeof(node)));
  start -> level = 1;
  start -> sibling = 1;
  int count = 2;
  node* root = start;
  while(count < THRESHOLD) {
      node *left2 = (node* )(malloc(sizeof(node)));
      left2 -> level = count;
      left2 -> sibling = root -> sibling;
      node *right2 = (node* )(malloc(sizeof(node)));
      right2 -> level = count;
      right2 -> sibling = root -> sibling + 1;
      
      root -> left = left2;
      root -> right = right2;
      if(rand() % 2 == 0) {
        root = left2;
      }
      else {
        root = right2;
      }
      count++;
  }
}
void recursion_baseline() {
  clock_t start_time, finish;
  start_time = clock();
  calculateTreeNode(start);
  finish = clock();
  double total = (double) (finish - start_time) / CLOCKS_PER_SEC * 1000;
  printf("total time:%f ms\n", total);
}
void eliminate_tail_recursion() {
  clock_t start_time, finish;
  start_time = clock();
  calculateTreeNode_no_tail_recursion(start);
  finish = clock();
  double total = (double) (finish - start_time) / CLOCKS_PER_SEC * 1000;
  printf("total time:%f ms\n", total);
}
void no_recursion() {
  clock_t start_time, finish;
  start_time = clock();
  calculateTreeNode_no_recursion(start);
  finish = clock();
  double total = (double) (finish - start_time) / CLOCKS_PER_SEC * 1000;
  printf("total time:%f ms\n", total);
}
int main() {
  initilizeTree();
  printf("Recursion:\n");
  recursion_baseline();
  printf("Eliminate Tail Recursion:\n");
  eliminate_tail_recursion();
  printf("No Recursion:\n");
  no_recursion();
}
