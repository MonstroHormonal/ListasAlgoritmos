#include <iostream>
using namespace std;

struct Link {
    int element;
    Link* next;
};

struct Stack {
    Link* top;
    int count;
};

Stack* createStack() {
    auto s = new Stack;
    s->top = nullptr;
    s->count = 0;
    return s;
}

Link* createLink(int var, Link* nextLink) {
    auto* l = new Link;
    l->element = var;
    l->next = nextLink;
    return l;
}

void push(Stack* s, int var) {
    s->top = createLink(var, s->top);
    s->count++;
}

int pop(Stack* s) {
    int var = s->top->element;
    Link* temp = s->top;
    s->top = s->top->next;
    delete temp;
    s->count--;
    return var;
}

bool isEmpty(Stack* s) {
    return s->count == 0;
}

int peek(Stack* s) {
    if (s->top != nullptr) {
        return s->top->element;
    }
    return -1;
}

int absolute(int x) {
    return x < 0 ? -x : x;
}

int main() {
    int casos;
    cin >> casos;

    for (int i = 0; i < casos; ++i) {
        Stack* pilha = createStack();
        int num;

        while (true) {
            cin >> num;
            if (num == 0) break;

            if (!isEmpty(pilha) && (((num % 2 == 0 || num == 0) && (peek(pilha) % 2 == 0 || peek(pilha) == 0)) || (num % 2 != 0 && peek(pilha) % 2 != 0))) {
                int result = absolute(num - pop(pilha));
                if (result != 0) {
                    push(pilha, result);
                    //cout << "\nTopo: " << peek(pilha) << "\n";
                } 
            } else {
                push(pilha, num);
                //cout << "\nTopo: " << peek(pilha) << "\n";
            }
        }

        int tamanho = pilha->count;
        int top;
        if (tamanho > 0) {
            top = peek(pilha);
        } 
        else {
            top = -1;
        }

        cout << "Pilha " << i + 1 << ": " << tamanho << " " << top << "\n";

        while (!isEmpty(pilha)) {
            pop(pilha);
        }

        delete pilha;
    }

    return 0;
}
