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
            Node <Type> *nodePredecessor;
            Node <Type> *nodeSuccessor;
            Node(){
                nodePredecessor = NULL;
                nodeSuccessor = NULL;
            }
        };

        Node <T> *nodeFirst;
        Node <T> *nodeTop;
        int sizeStack;
    public:
        class IteratorMy
        {
            public:
            Node <T> *nodeIt;
            IteratorMy(Node <T> *node_ = NULL) : nodeIt(node_) {}

            bool operator==(const IteratorMy &otherIt) { return (this == &otherIt ? true :
                                                (nodeIt == otherIt.nodeIt)); }
            bool operator!=(const IteratorMy &otherIt) { return !operator ==(otherIt); }
            T& operator* () const { return this->nodeIt->data; }
            void operator++ () { if(nodeIt != NULL){ nodeIt = nodeIt->nodeSuccessor; } }
        };
    public:
        Stack_list();
        Stack_list(Stack_list<T> &stack);
        ~Stack_list(){ if(!isEmpty()) clear(); }

        inline void pushEnd(T data);
        inline void popEnd();
        inline IteratorMy begin() { return IteratorMy (nodeFirst); }
        inline IteratorMy end() { return IteratorMy (NULL); }
        inline T top() { return (nodeTop != NULL ?
                        nodeTop->data : throw logic_error{"Top is not exist."}); }
        inline bool isEmpty() { return bool(sizeStack == 0); }
        inline int size() const { return sizeStack; }
        inline void clear();
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

    cout << "-*-*-*-*-*-*-*-*-" << endl;
    Stack_list <int> stack1;
    Stack_list <int> stack2;
    Stack_list <int> stack3;
    stack2.pushEnd(-12);
    stack2.pushEnd(-13);
    stack2.pushEnd(-14);
    stack2.pushEnd(-15);
    stack2.pushEnd(-16);
    stack3 = stack2;
    Stack_list <int> stack4(stack3);
    stack1 = stack4;
    stack1.print();


    return 0;
}



template <class T>
Stack_list<T>::Stack_list() : nodeFirst(NULL), nodeTop(NULL), sizeStack(0)
{

}

template <class T>
Stack_list<T>::Stack_list(Stack_list<T> &stack) : Stack_list()
{
    *this = stack;
}


template <class T>
void Stack_list<T>::pushEnd(T data)
{
    Node <T> *newNode = new Node <T>();
    newNode->data = data;
    sizeStack++;
    if(nodeTop == NULL){ // if the node is first
        nodeTop = newNode;
        nodeFirst = newNode;
        return;
    }
    newNode->nodePredecessor = nodeTop;
    newNode->nodeSuccessor = NULL;
    nodeTop->nodeSuccessor = newNode;
    nodeTop = newNode;
}

template <class T>
void Stack_list<T>::popEnd()
{
    if(nodeTop != NULL && sizeStack > 0){
        Node <T> *deleteNode;
        deleteNode = nodeTop;
        if(sizeStack == 1){ // if the size is one
            nodeFirst = NULL;
            nodeTop = NULL;
            delete deleteNode;
            sizeStack = 0;
            return;
        }
        Node <T> *nodePrecursor = nodeTop->nodePredecessor;
        nodePrecursor->nodeSuccessor = NULL;
        nodeTop = nodePrecursor;
        delete deleteNode;
        sizeStack--;
    }
}


template <class T>
void Stack_list<T>::clear()
{
    while(nodeTop != NULL){
        popEnd();
    }
    nodeFirst = NULL;
    nodeTop = NULL;
    sizeStack = 0;
}

template <class T>
void Stack_list<T>::print() const
{
    if(nodeTop == NULL) return;

    Node <T> *currentNode = nodeFirst;
    while (currentNode != NULL) {
        cout << currentNode->data << endl;
        currentNode = currentNode->nodeSuccessor;
    }
    cout << "--------------" << endl;
}


template <class T>
Stack_list<T>& Stack_list<T>::operator= (Stack_list<T> &copyStack)
{
    if (this != &copyStack){
        this->clear();
        for (IteratorMy it = copyStack.begin(); it != copyStack.end(); ++it){
            this->pushEnd(*it);
        }
    }
    return *this;
}

template <class T>
T &Stack_list<T>::operator[](int index)
{
    try{
        if(index >= sizeStack || index < 0){
            throw 0;
        }
    }
    catch(int num){
        cout << "Error #" << to_string(num) << ". Array index out of bounds " << endl;
    }

    IteratorMy it = begin();
    for (int var = 0; var < index; ++var) {
        ++it;
    }
    return *it;
}

