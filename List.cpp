//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT.
//-----------------------------------------------------------------------------

#include "List.h"

// Constructors and Destructors -----------------------------------------------

// List()
// Creates new List in the empty state.
List::List(){
frontDummy = new Node(-1);
backDummy = new Node(-1);
beforeCursor = frontDummy;
afterCursor = backDummy;
frontDummy->next = afterCursor;
backDummy->prev = beforeCursor;
pos_cursor = 0;
num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
frontDummy = new Node(-1);
backDummy = new Node(-1);
beforeCursor = frontDummy;
afterCursor = backDummy;
frontDummy->next = afterCursor;
backDummy->prev = beforeCursor;
pos_cursor = 0;
num_elements = 0;


Node* temp = L.frontDummy->next;
while (temp != L.afterCursor) {
    insertAfter(temp->data);
    temp = temp->next;
}
}

// Destructor
List::~List(){
clear();
delete frontDummy;
delete backDummy;
}

// Access functions ------------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
if (num_elements == 0) {
std::cerr << "List Error: front() called on empty List" << std::endl;
exit(EXIT_FAILURE);
}
return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
if (num_elements == 0) {
std::cerr << "List Error: back() called on empty List" << std::endl;
exit(EXIT_FAILURE);
}
return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
if (pos_cursor == num_elements) {
std::cerr << "List Error: peekNext() called at back of List" << std::endl;
exit(EXIT_FAILURE);
}
return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
if (pos_cursor == 0) {
std::cerr << "List Error: peekPrev() called at front of List" << std::endl;
exit(EXIT_FAILURE);
}
return beforeCursor->data;
}

// Manipulation procedures -----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
while (num_elements > 0) {
eraseFront();
}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
pos_cursor = 0;
beforeCursor = frontDummy;
afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
pos_cursor = num_elements;
afterCursor = backDummy;
beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed
ListElement List::moveNext() {
if (pos_cursor < num_elements) {
beforeCursor = afterCursor;
afterCursor = afterCursor->next;
pos_cursor++;
return beforeCursor->data;
} else {
return -1; // Error: cursor at back of List
}
}

ListElement List::movePrev() {
if (pos_cursor > 0) {
afterCursor = beforeCursor;
beforeCursor = beforeCursor->prev;
pos_cursor--;
return afterCursor->data;
} else {
return -1; // Error: cursor at front of List
}
}

void List::insertAfter(ListElement x) {
Node* N = new Node(x);
N->prev = beforeCursor;
N->next = afterCursor;
beforeCursor->next = N;
afterCursor->prev = N;
afterCursor = N;
num_elements++;
}

void List::insertBefore(ListElement x) {
Node* N = new Node(x);
N->prev = beforeCursor->prev;
N->next = beforeCursor;
beforeCursor->prev = N;
N->prev->next = N;
beforeCursor = N;
num_elements++;
}

void List::setAfter(ListElement x) {
if (afterCursor != nullptr) {
afterCursor->data = x;
}
}

void List::setBefore(ListElement x) {
if (beforeCursor != nullptr) {
beforeCursor->data = x;
}
}

void List::eraseAfter() {
if (afterCursor != backDummy) {
Node* oldNode = afterCursor;
afterCursor = afterCursor->next;
beforeCursor->next = afterCursor;
afterCursor->prev = beforeCursor;
delete oldNode;
num_elements--;
}
}

void List::eraseBefore() {
if (beforeCursor != frontDummy) {
Node* oldNode = beforeCursor;
beforeCursor = beforeCursor->prev;
beforeCursor->next = afterCursor;
afterCursor->prev = beforeCursor;
delete oldNode;
num_elements--;
}
}

int List::findNext(ListElement x) {
Node* temp = afterCursor;
int i = pos_cursor;
while (temp != backDummy) {
if (temp->data == x) {
beforeCursor = temp->prev;
afterCursor = temp;
pos_cursor = i;
return i;
}
temp = temp->next;
i++;
}
beforeCursor = backDummy->prev;
afterCursor = backDummy;
pos_cursor = num_elements;
return -1;
}

int List::findPrev(ListElement x) {
Node* temp = beforeCursor;
int i = pos_cursor - 1;
while (temp != frontDummy) {
if (temp->data == x) {
beforeCursor = temp->prev;
afterCursor = temp;
pos_cursor = i;
return i;
}
temp = temp->prev;
i--;
}
beforeCursor = frontDummy;
afterCursor = frontDummy->next;
pos_cursor = 0;
return -1;
}

void List::cleanup() {
Node* current = frontDummy->next;
Node* temp;
while (current != backDummy) {
Node* runner = current->next;
while (runner != backDummy) {
if (runner->data == current->data) {
// remove duplicate node
temp = runner;
runner->prev->next = runner->next;
runner->next->prev = runner->prev;
runner = runner->next;
delete temp;
num_elements--;
} else {
runner = runner->next;
}
}
current = current->next;
}
}

List List::concat(const List& L) const {
List result;
Node* current = frontDummy->next;
while (current != backDummy) {
result.insertBefore(current->data);
current = current->next;
}
current = L.frontDummy->next;
while (current != L.backDummy) {
result.insertBefore(current->data);
current = current->next;
}
result.moveFront();
return result;
}

std::string List::to_string() const {
std::string result = "(";
Node* current = frontDummy->next;
while (current != backDummy) {
result += std::to_string(current->data);
if (current->next != backDummy) {
result += ",";
}
current = current->next;
}
result += ")";
return result;
}

bool List::equals(const List& R) const {
if (num_elements != R.num_elements) {
return false;
}
Node* current = frontDummy->next;
Node* rCurrent = R.frontDummy->next;
while (current != backDummy) {
if (current->data != rCurrent->data) {
return false;
}
current = current->next;
rCurrent = rCurrent->next;
}
return true;
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
stream << L.to_string();
return stream;
}

bool operator==(const List& A, const List& B) {
return A.equals(B);
}

bool operator!=(const List& A, const List& B) {
return !(A == B);
}