#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class Stack //contains stack methods and conversion method to convert infix to postfix
{
public:
  char stack[100]; //stack array
  int top = -1;

  int size = 100;

  void push(int element) // pushes element in stack[]
  {
    if (!isFull())
      stack[++top] = element;
  }
  void pop() //removes top element
  {
    if (isEmpty())
      return;
    else
      top--;
  }
  bool isEmpty() //if there is no element in stack[]
  {
    return top <= -1;
  }
  bool isFull() //if the stack is full
  {
    return top - 1 == 100;
  }
  void clear() //clears the stack with no elements
  {
    while (top != -1)
      pop();
  }
  char peek() //returns the top element in stack[]
  {
    if (!isEmpty())
      return stack[top];
    else
      return '&';
  }

  char postfix[100]; //this array will contain the elements of converted postfix expression
  int postfix_top = -1;

  void push_output(char element) //method to push elements in postfix[]
  {
    if (postfix_top <= 100)
    {
      ++postfix_top;
      postfix[postfix_top] = element;
    }
  }
  int operator_prec(char op) //method to check operator precedence
  {

    if (op == '+' || op == '-') //lowest precedence
      return 1;
    else if (op == '/' || op == '*') //medium precedence
      return 2;
    else if (op == '^') //highest precedence
      return 3;
    else
      return 0; //for brackets and spaces
  }
  void conversion(string expression) //method to convert infix to postfix
  {

    for (int i = 0; i <= expression.length(); i++)
    {

      if (isdigit(expression[i]) || expression[i] == ' ') //for spaces and digits, element will be pushed to postfix[]

        push_output(expression[i]);

      else if (expression[i] == '(' || expression[i] == '^') //for ( and ^ element will be pushed as ^ has highest precedence
        push(expression[i]);
      else if (expression[i] == ')') //for closing bracket
      {
        while (isEmpty() || peek() != '(') //looks for opening bracket
        {
          push_output(peek()); //pushes top item in given string to postfix and removes it from string
          pop();
        }
        pop();
      }
      else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') //for operators
      {

        if (operator_prec(expression[i]) > operator_prec(peek())) //for higher precedence, simply push operator in postfix[]
          push(expression[i]);
        else
        {
          while (operator_prec(expression[i]) <= operator_prec(peek())) //for equal or lower precedence
          {
            push_output(peek());
            pop(); //push in postfix and pop from string as long as precedence condition is fulfilled
          }
          push_output((expression[i]));
        }
      }
    }
    for (int i = 0; i <= top; i++)
    {
      push_output(stack[i]); //for remaining elements
      pop();
    }
  }
  void show() //methis to show postfix expression
  {
    for (int i = 0; i <= postfix_top; i++)
      cout << postfix[i];
  }
};
class Evaluation //Evaluation class provides methods for evaluating postfix expression
{
public:
  int top_eval = -1; //Creating integer stack for evaluation

  int eval[100];         //stack to store evaluated values
  void push(int element) //pushes element in eval[]
  {
    if (!isFull())
      eval[++top_eval] = element;
  }
  void pop() //pops top element from eval[]
  {
    if (isEmpty())
      return;
    else
      top_eval--;
  }
  bool isEmpty() //if top_eval is less than 0
  {
    return top_eval <= -1;
  }
  bool isFull() //for full array having size 100
  {
    return top_eval - 1 == 100;
  }
  void clear() //clears all the elements in stack
  {
    while (top_eval != -1)
      pop();
  }
  int peek() //returns top element in stack i.e. eval[]
  {
    return eval[top_eval];
  }

  int evaluation(char array[100]) //evaluates postfix i.e. array[] and returns integer value
  {
    for (int i = 0; array[i]; ++i) //assesses all indexes of the array
    {
      if (array[i] == ' ') //incase of space, for loop will move to next iteration, space indicates a separation
        continue;

      else if (isdigit(array[i])) //for digits
      {
        int n = 0; //initially n (number to be pushed in int stack) is 0

        //extract full number
        while (isdigit(array[i]))
        {
          n = n * 10 + (int)(array[i] - '0'); //for multi digit number while loop will have another iteration
          array[i] = ' ';
          i++; //for checking next index
        }
        i--;

        push(n); //push the number in the eval[] stack
      }
      else //incase of operators
      {
        int val2 = peek(); //top element will be stored in variable val 2
        pop();             //removed from the stack
        int val1 = peek(); //new top  element will be stored in variable val 1
        pop();             //top element will be removed

        switch (array[i]) //evaluates the operator
        {
        case '+':
          push(val1 + val2); //for + , sum will be pushed in eval stack
          break;
        case '-':
          push(val1 - val2); //for - , difference will be pushed in eval stack
          break;
        case '*':
          push(val1 * val2); //for * , product will be pushed in eval stack
          break;
        case '/':
          push(val1 / val2); //for / , division result will be pushed in eval stack
          break;
        case '^':
          push(pow(val1, val2)); //for ^ , exponential result will be pushed in eval stack
          break;
        }
      }
    }
    return peek(); //Returns the only element left in eval[] stack.
    pop();
  }
};
int main()
{

  Stack postfix_obj; //creating object of Stack Class
  Evaluation eval;   //creating object of Evaluation Class
   cout << "Given Infix Expression: ((7 - 5 )^(7 + 1 ))";
  
  postfix_obj.conversion("((7 - 5 )^(7 + 1 ))");
  //Given expression must have spaces (in case of brackets, spaces are not required) after each operator and operand.
  //Conversion Method converts infix to postfix
  //Stores the postfix expression in postfix array
  cout << "\nConverted Infix to Postfix Expression: ";
  postfix_obj.show(); //displays the postfix expression
  cout << "\nEvaluation: "

       << eval.evaluation(postfix_obj.postfix); //Evaluates any postfix expression.
                                                //In this case, the postfix converted expression is passed directly.
}
