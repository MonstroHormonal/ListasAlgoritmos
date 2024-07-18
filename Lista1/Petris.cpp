#include <iostream>
#include <string>

using namespace std;

struct Link {
    int element;
    Link *next;
};

struct List {
    Link *head;
    Link *tail;
    Link *curr;
    int count;
};

Link* create_link(int it, Link *nextval = nullptr) {
    Link *n = new Link;
    n->element = it;
    n->next = nextval;
    return n;
}

List* create_list() {
    List *l = new List;
    l->head = l->tail = l->curr = create_link(0); // Dummy node
    l->count = 0;
    return l;
}

void insert(List *l, int it) {
    l->curr->next = create_link(it, l->curr->next);
    if (l->tail == l->curr) {
        l->tail = l->curr->next;
    }
    l->count++;
}

void moveToStart(List *l) {
    l->curr = l->head;
}

void prev(List *l) {
    if (l->curr == l->head) return;
    Link *temp = l->head;
    while (temp->next != l->curr) temp = temp->next;
    l->curr = temp;
}

void next(List *l) {
    if (l->curr != l->tail) l->curr = l->curr->next;
}

int remove(List *l) {
    if (l->curr->next == nullptr) return 0;
    int it = l->curr->next->element;
    Link *temp = l->curr->next;
    if (l->tail == l->curr->next) {
        l->tail = l->curr;
    }
    l->curr->next = l->curr->next->next;
    delete temp;
    l->count--;
    return it;
}

void delete_list(List *l) {
    while (l->head != nullptr) {
        Link *temp = l->head;
        l->head = l->head->next;
        delete temp;
    }
    delete l;
}

void addStone(List **columns, int S, int C, int &numCols) {
    if (S == 0) {
        // Create a new column to the left
        List *newColumn = create_list();
        insert(newColumn, C);
        for (int i = numCols; i > 0; --i) {
            columns[i] = columns[i - 1];
        }
        columns[0] = newColumn;
        numCols++;
    } else if (S == numCols + 1) {
        // Create a new column to the right
        List *newColumn = create_list();
        insert(newColumn, C);
        columns[numCols] = newColumn;
        numCols++;
    } else {
        // Add stone to the specified column
        List *column = columns[S - 1];
        moveToStart(column);
        // Check if the top element is the same color
        if (column->curr->next != nullptr && column->curr->next->element == C) {
            // Remove all elements with the same color at the top
            while (column->curr->next != nullptr && column->curr->next->element == C) {
                remove(column);
            }
        } else {
            insert(column, C);
        }

        // Check if the column became empty
        if (column->count == 0) {
            delete_list(column);
            for (int i = S - 1; i < numCols - 1; ++i) {
                columns[i] = columns[i + 1];
            }
            numCols--;
        }
    }
}


void print_columns(List **columns, int numCols, int caseNum) {
    cout << "caso " << caseNum << ":";
    if (numCols > 0) {
        for (int i = 0; i < numCols; ++i) {
            moveToStart(columns[i]);
            next(columns[i]);  // Move to the first actual element
            cout << " " << columns[i]->curr->element;
        }
    }
    cout << endl;
}

int main() {
    int P;
    cin >> P;
    cin.ignore(); // Ignore the newline after reading P
    for (int i = 0; i < P; ++i) {
        List **columns = new List*[1000]; // Assuming a maximum of 1000 columns
        int numCols = 0;
        string str;
        while (true) {
            getline(cin, str);
            if (str == "END") {
                break;
            }
            int S, C;
            size_t pos = str.find(' ');
            S = stoi(str.substr(0, pos));
            C = stoi(str.substr(pos + 1));
            addStone(columns, S, C, numCols);
        }
        cin.ignore(); // Ignore the newline after reading the last "END"
        
        // Output result for this case
        print_columns(columns, numCols, i);
        
        // Clean up memory
        for (int j = 0; j < numCols; ++j) {
            delete_list(columns[j]);
        }
        delete[] columns;
    }
    return 0;
}
