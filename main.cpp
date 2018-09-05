#include <iostream>
#include <stdexcept>

using namespace std;


template <class T>
class Stack_list
{
    private:    
        template <class Type>
        struct Node
        {
            Type data;
            Node <Type> *predecessor;
        };

        Node <T> *nodeTop;
        int sizeStack;
    public:
        Stack_list();
        Stack_list(Stack_list<T> &stack);
        ~Stack_list(){ if(!isEmpty()) clear(); }

        inline void pushEnd(T data);
        inline void popEnd();
        inline void clear();
        inline T top() { return (nodeTop != NULL ?
                        nodeTop->data : throw logic_error{"Top is not exist."}); }
        inline bool isEmpty() { return bool(sizeStack == 0); }
        inline int size() const { return sizeStack; }
        inline void print() const;

        Stack_list<T>& operator= (Stack_list<T> &copyMyStack);
        T &operator[] (int index); // speed - O(n)

};


bool equal(char char1, char char2){
    if(char1 == '(' && char2 == ')') return true;
    if(char1 == '{' && char2 == '}') return true;
    if(char1 == '[' && char2 == ']') return true;
    return false;
}


string checkBrackets(string input)
{
    string result = "Success";
    Stack_list <char> stackBrackets;
    Stack_list <int> stackPosition;
    int step = 0;

    for (size_t var = 0; var < input.size(); ++var)
    {
        step++;
        char br = input[var];
        if(br == '(' || br == ')' || br == '{' || br == '}' || br == '[' || br == ']'){
            if(br == '(' || br == '{' || br == '['){
                stackBrackets.pushEnd(input[var]);
                stackPosition.pushEnd(step);
            }
            else{// closed bracket
                if(!stackBrackets.isEmpty()){
                    if(equal(stackBrackets.top(), input[var])){
                        stackBrackets.popEnd();
                        stackPosition.popEnd();
                    }
                    else{
                        return to_string(step);
                    }
                }
                else{// if you enter closed bracket and stackBrackets.isEmpty()
                    return to_string(step);
                }
            }
        }
    }
    if(step == 0){
        return to_string(step);
    }
    if(!stackBrackets.isEmpty()){
       return to_string(stackPosition.top());
    }
    return result;
}


int main()
{

//    string str = "";
//    cin >> str;
//    cout << str << endl;
//    cout << checkBrackets(str) << endl;

    Stack_list <string> textBrackets;
    textBrackets.pushEnd("([](){([])})");
    textBrackets.pushEnd("()[]}");
    textBrackets.pushEnd("{{[()]]");
    textBrackets.pushEnd("foo(bar);");
    textBrackets.pushEnd("foo(bar[i);");
    for (int var = 0; var < textBrackets.size(); ++var)
    {
        cout << textBrackets[var] << endl;
        cout << checkBrackets(textBrackets[var]) << endl;
    }


    return 0;
}

template <class T>
Stack_list<T>::Stack_list() : nodeTop(NULL), sizeStack(0)
{

}

template <class T>
Stack_list<T>::Stack_list(Stack_list<T> &stack)
{/* finish at the end */
        Node <T> *current = stack;
        while (current->predecessor != NULL)
        {
            this->pushEnd(current->data);
            current = current->predecessor;
        }
}


template <class T>
void Stack_list<T>::pushEnd(T data)
{
    Node <T> *newNode = new Node <T>;
    newNode->data = data;
    sizeStack++;
    if(nodeTop == NULL){ // if the node is first
        newNode->predecessor = NULL;
        nodeTop = newNode;
        return;
    }
    newNode->predecessor = nodeTop;
    nodeTop = newNode;
}

template <class T>
void Stack_list<T>::popEnd()
{
    if(nodeTop != NULL){
        Node <T> *deleteNode;
        deleteNode = nodeTop;
        sizeStack--;
        if(deleteNode->predecessor == NULL){ // if the predecessor is out
            nodeTop = NULL;
            delete deleteNode;
            return;
        }
        nodeTop = deleteNode->predecessor;
        delete deleteNode;
    }
}

template <class T>
void Stack_list<T>::clear()
{
    while(nodeTop != NULL){
        popEnd();
    }
    sizeStack = 0;
}

template <class T>
void Stack_list<T>::print() const
{
    Node <T> *current = nodeTop;
    while (current->predecessor != NULL)
    {
        cout << current->data << endl;
        current = current->predecessor;
    }
    cout << "--------------" << endl;
}


template <class T>
Stack_list<T>& Stack_list<T>::operator= (Stack_list<T> &copyStack)
{
    if (this != &copyStack){
        this->clear();
        Node <T> *current = copyStack;
        while (current->predecessor != NULL)
        {
            this->pushEnd(current->data);
            current = current->predecessor;
        }
    }
    return *this;
}

template <class T>
T &Stack_list<T>::operator[](int index)
{
    T *result = NULL;
    try{
        if(index >= sizeStack || index < 0){
            throw 0;
        }
    }
    catch(int num){
        cout << "Error #" << to_string(num) << ". Array index out of bounds " << endl;
    }

    Node <T> *current = nodeTop;
    result = &(current->data);
    for (int var = 0; var < sizeStack - index - 1; ++var)
    {
        current = current->predecessor;
        result = &(current->data);
    }
    return *result;
}

