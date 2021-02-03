//
// dna.h
// Author: Michal Fitrzyk
// TODO(mfitrz2): Nothing
// Header file for the dna class which stores a letter in a node in
// a linked list.
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

class dna {
private:
    //
    // This implementation is a doubly-linked structure.  The nodes are structs
    // called Nucleotides.  Size could keep track of how many Nucleotides are
    // currently in the list.  front should always point to the first
    // Nucleotide and back should point to the last one.
    struct Nucleotide {
        char value;
        Nucleotide *next;
        Nucleotide *prev;
    };
    int Size;
    Nucleotide *front;
    Nucleotide *back;
    //
    // findFirst: (private)
    //
    // Searches dna for the first copy of the sequence target, returning a
    // pointer to that occurrence or nullptr if the target sequence isn't
    // present.
    // Performance requirement:  this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    Nucleotide* findFirst(dna target) {
        Nucleotide* curr = front;
        int nodeIndex = 0;
        // Converts the target dna object to a string using the public 
        // member function, toString(), because I find it easier
        // to manage and I am more comfortable with string methods.
        string search = target.toString(), out = "";
        // Loops through the current dna object (this) until it finds the first
        // letter of the given target object. It then checks all the next
        // letters to see if they match the target. If not, then the pointer
        // advances to the next node in the list. If the end of the list is
        // reached and the target was not found, then it returns a nullptr.
        while (curr != nullptr) {
            bool good = false;
            // The current letter that is being pointed to is equal to the first
            // letter of the dna object.
            if (curr->value == search.at(0)) {
                Nucleotide* temp = curr->next;
                // Loops through to check each concurrent letter matches each
                // letter from the dna object.
                for (int i = 1; i < (int)search.length(); i++) {
                    if (temp == nullptr) {
                        good = false;
                        break;
                    }
                    if (temp->value != search.at(i)) {
                        good = false;
                        break;
                    }
                    good = true;
                    temp = temp->next;
                }
                // If all the letters matched, then this is the first occurrence
                // of the target in the current linked list so it returns a
                // pointer to the first letter of that found word.
                if (good) {
                    return curr;
                }
            }
            nodeIndex++;
            curr = curr->next;
        }
        return nullptr;
    }
public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create an empty dna object with two
    // Nucleotides, each with the value of 'X'.
    //
    dna() {
        // Allocates memory on the heap for two seperate nodes
        Nucleotide* newNode1 = new Nucleotide;
        Nucleotide* newNode2 = new Nucleotide;
        newNode1->value = 'X';
        newNode2->value = 'X';
        // First node is linked together with the second
        newNode1->prev = nullptr;
        newNode1->next = newNode2;
        // Second node is linked together with the first
        newNode2->prev = newNode1;
        newNode2->next = nullptr;

        Size = 2;
        front = newNode1;
        back = newNode2;
    }
    //
    // second constructor:
    //
    // Produces a new strand of nucleotides spelled out in the sequence given
    // by str.
    // Performance requirement: O(n)
    //
    dna(const string& str) {
        // If the string length is excatly one, then the front and back
        // both point to the same node that is created.
        if (str.length() > 0) {
            Nucleotide* newNode = new Nucleotide;  // Allocation for a node
            newNode->value = str.at(0);
            newNode->prev = nullptr;
            front = newNode;
            // If the string has 2 or more letters than the front points
            // to the first new node created, and then subsequent nodes
            // are created in a loop and linked together.
            if (str.length() > 1) {
                Nucleotide* curr = new Nucleotide;  // Allocates node
                curr->value = str.at(1);
                curr->prev = newNode;
                newNode->next = curr;  // Links first to second node
                // Loop that executes if the word has more than 2 letters
                // that creates a new node and links it to the previous
                // node.
                for (int i = 2; i < (int)str.length(); i++) {
                    Nucleotide* prev = curr;
                    Nucleotide* temp = new Nucleotide;  // Allocates node
                    temp->value = str.at(i);
                    temp->prev = prev;
                    curr->next = temp;
                    curr = temp;
                }
                // Ends the linked list
                curr->next = nullptr;
                // Updates the back pointer to the last node
                back = curr;
                Size = str.length();
            } else {
                // Points back to the same node as front
                newNode->next = nullptr;
                back = newNode;
                Size = 1;
            }
            // Otherwise the string is empty and no node is created
            // and front/back point to null
        } else {
            Size = 0;
            front = nullptr;
            back = nullptr;
        }
    }
    //
    // copy constructor:
    //
    // Called automatically by C++ to create a dna object that contains a copy
    // of an existing dna object.
    // Performance requirement: O(n)
    //
    dna(const dna& other) {
        // If the other object's size is excatly one, then the front and back
        // both point to the same node that is created.
        if (other.Size > 0) {
            Nucleotide* newNode = new Nucleotide;  // Allocates memory on heap
            Nucleotide* otherNode = other.front;
            newNode->value = otherNode->value;
            newNode->prev = nullptr;
            this->front = newNode;
            // If the other object has 2 or more letters than the front points
            // to the first new node created, and then subsequent nodes
            // are created in a loop and linked together.
            if (other.Size > 1) {
                otherNode = otherNode->next;
                Nucleotide *curr = new Nucleotide;  // Allocates memory on heap
                curr->value = otherNode->value;
                curr->prev = newNode;
                newNode->next = curr;  // Links first to second node
                // Loop that executes if the other object has more
                // than 2 letters and creates a new node and links it to the
                // previous node.
                for (int i = 2; i < other.Size; i++) {
                    otherNode = otherNode->next;
                    Nucleotide* prev = curr;
                    Nucleotide* temp = new Nucleotide;  // Allocates node
                    temp->value = otherNode->value;
                    temp->prev = prev;
                    curr->next = temp;
                    curr = temp;
                }
                curr->next = nullptr;
                this->back = curr;
                this->Size = other.Size;
            } else {
                newNode->next = nullptr;
                // Points back to the same node as front
                this->back = newNode;
                Size = 1;
            }
        } else {
            // Otherwise the string is empty and no node is created
            // and front/back point to null
            this->Size = 0;
            this->front = nullptr;
            this->back = nullptr;
        }
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by
    // the dna object.
    // Performance requirement: O(n)
    //
    virtual ~dna() {
        Nucleotide* curr = front;
        Nucleotide* next = nullptr;
        // Goes trough the linked list dealloacating each node at a time
        while (curr != nullptr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
        // front and back point to nullptr
        front = curr;
        back = nullptr;
        Size = 0;
        delete front;
        delete back;
    }
    //
    // clear:
    //
    // Frees all memory in the chain of nucleotides in the dna obeject.  This
    // function should also set front, back, and Size, appropriately.
    // Performance requirement: O(n)
    //
    void clear() {
        Nucleotide* curr = front;
        Nucleotide* next = nullptr;
        // Goes trough the linked list dealloacating each node at a time
        while (curr != nullptr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
        // front and back point to nullptr
        front = curr;
        back = nullptr;
        Size = 0;
    }
    //
    // operator=
    //
    // Called when you assign one dna object into another, i.e. this = other;
    // Performance requirement: O(n)
    //
    dna& operator=(const dna& other) {
        // Returns the current object since it is indentical to ther other
        if (this == &other) {
            return *this;
        }
        Nucleotide* curr = front;
        Nucleotide* next = nullptr;
        // Deallocates the old object which is a linked list
        while (curr != nullptr) {
            next = curr->next;
            delete curr;
            curr = next;
        }
        // If the other object's size is excatly one, then the front and back
        // both point to the same node that is created.
        if (other.Size > 0) {
            Nucleotide* newNode = new Nucleotide;  // Allocates new node
            Nucleotide* otherNode = other.front;
            newNode->value = otherNode->value;
            newNode->prev = nullptr;
            this->front = newNode;
            // If the other object has 2 or more letters than the front points
            // to the first new node created, and then subsequent nodes
            // are created in a loop and linked together.
            if (other.Size > 1) {
                otherNode = otherNode->next;
                Nucleotide *curr = new Nucleotide;  // Allocates new node
                curr->value = otherNode->value;
                curr->prev = newNode;
                newNode->next = curr;
                // Loop that executes if the other object has more
                // than 2 letters and creates a new node and links it to the
                // previous node.
                for (int i = 2; i < other.Size; i++) {
                    otherNode = otherNode->next;
                    Nucleotide* prev = curr;
                    Nucleotide* temp = new Nucleotide;  // Allocates new node
                    temp->value = otherNode->value;
                    temp->prev = prev;
                    curr->next = temp;
                    curr = temp;
                }
                curr->next = nullptr;
                this->back = curr;
                this->Size = other.Size;
            } else {
                newNode->next = nullptr;
                this->back = newNode;
                Size = 1;
            }
        } else {
            // Otherwise the string is empty and no node is created
            // and front/back point to null
            this->Size = 0;
            this->front = nullptr;
            this->back = nullptr;
        }
        return *this;  // Returns a pointer to this new object created
    }
    //
    // size:
    //
    // Returns the # of Nucleotides currently in the dna strand.
    // Performance requirement: O(1)
    //
    int size() const {
        return Size;
    }
    //
    // at(i):
    //
    // Returns a reference to the ith Nucleotide's value, which allows
    // you to read (access) or write (modify) this value.  If i is out of
    // bounds, an exception is thrown.
    // Performance requirement: O(n)
    //
    char& at(int i) {
        // Trows an out_of_range error if the given index is less than 0 or
        // greater than the current objects size
        if (i < 0 || i > Size) {
            throw std::out_of_range("dna: i out of bounds");
        } else {
            int index = 0;
            Nucleotide* temp = front;
            // Loops through the linked list until it reaches the given index
            while (temp != nullptr) {
                if (index == i) {
                    return temp->value;
                }
                temp = temp->next;
                index++;
            }
        }
    }
    //
    // toString:
    //
    // Returns a string spelling out the contents of the dna sequence.
    // Performance requirement: O(n)
    //
    string toString() const {
        Nucleotide* node = front;
        string out = "";
        // Goes through the linked list and adds each letter stored at each
        // node to a string that is returned
        while (node != nullptr) {
            out += node->value;
            node = node->next;
        }
        return out;
    }
    //
    // operator==
    //
    // This operator determines how you define equality between two operators.
    // In this function, you should compare other and this.  The two objects
    // should be considered equal if they have the same sequence of values and
    // in the same order.
    // Performance requirement: O(n)
    //
    bool operator==(const dna& other) const {
        // Only loops through both objects if they are the same size. If they
        // are not the same size, then they can not be equal.
        if (this->Size == other.Size) {
            Nucleotide* head1 = this->front;
            Nucleotide* head2 = other.front;
            // Loops through both linked lists and if one of their values do not
            // match, then they are not equal. The loop then breaks, and false
            // is returned.
            while (head1 != nullptr && head2 != nullptr) {
                if (head1->value != head2->value) {
                    return false;
                }
                head1 = head1->next;
                head2 = head2->next;
            }
            return true;
        } else {
            // Returns false if the sizes of the two objects are not the same
            return false;
        }
    }
    //
    // splice:
    //
    // Removes the first copy of the sequence in target that appears in the
    // dna sequence of current object.  This requires the linked structure to
    // be properly re-wired after removal.
    // Performance requirement: this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    bool splice(dna target) {
        // Firsts gets a pointer to the first occurrence of the target word
        Nucleotide* ptr = findFirst(target);
        // If the target was not found, then ptr is nullptr which immediately
        // prompts the function to return false.
        if (ptr != nullptr) {
            Nucleotide* nextPtr = ptr;
            Nucleotide* prev = nextPtr->prev;
            // If the word is at the beginning of the linked list
            if (prev == nullptr) {
                // The nodes containing the word are deallocated
                for (int i = 0; i < target.Size; i++) {
                    Nucleotide* tempNext = nextPtr->next;
                    delete nextPtr;
                    nextPtr = tempNext;
                }
                // If the word is at the beginning and once it is deleted
                // there is nothing after it, then the list is empty at
                // this point so front and back are nullptrs
                if (nextPtr == nullptr) {
                    front = nullptr;
                    back = nullptr;
                    Size = 0;
                    return true;
                }
                // The front of the list points to the node after the last
                // letter in the target word now.
                nextPtr->prev = nullptr;
                front = nextPtr;
                Size -= target.Size;
                return true;
            }
            // The word is not at the front of the linked list
            // This loop deallocates each node of the target word that was found
            // in the current linked list.
            for (int i = 0; i < target.Size; i++) {
                Nucleotide* tempNext = nextPtr->next;
                delete nextPtr;
                nextPtr = tempNext;
            }
            prev->next = nextPtr;
            // If the word was removed at the end of the linked list
            // then the node before the first letter is now the back
            if (nextPtr == nullptr) {
                back = prev;
                Size -= target.Size;
                return true;
            }
            // Otherwise, the word was removed in the middle so neither
            // the front or back is updated
            nextPtr->prev = prev;
            Size -= target.Size;
            return true;
        } else {
            // the target was not found in the current linked list object so
            // nothing gets spliced
            return false;
        }
    }
    //
    // isLinked()
    //
    // Checks if a strand is linked correctly.  This is provided for you.
    // You should use it to test your linked structure often.
    // Performance requirement: O(n)
    //
    bool isLinked() {
        Nucleotide* start = front;
        // If we're at the start of a strand,
        // we should not have a previous pointer.
        if (start != nullptr && start->prev != nullptr) {
            return false;
        }
        // Walk the list, ensuring at each point that the next/prev pointers
        // are consistent with one another.
        for (Nucleotide* curr = start; curr != nullptr; curr = curr->next) {
            if (curr->next != nullptr && curr->next->prev != curr) return false;
            if (curr->prev != nullptr && curr->prev->next != curr) return false;
        }
        return true;
    }
};
