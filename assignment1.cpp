// Samir Ali
// assignment1.cpp
// CPSC 2430
// Professor Diaz

// Purpose: To create an animal shelter that can store cats and dogs.
// Given a file, with specified inputs between 1-5, the program can 
// proceed to do a set amount of actions, such as inserting an animal into
// the shelter, take out specifically a cat or dog to promote, and be able
// to take out the more recent animal, regardless of type.

// Sources: CodesDope's C++: Linked lists in C++ (Singly linked list).
// I used this resource to help me with syntax regarding C++ linkedlists, and how
// to properly format my class. I defaulted to using a linkedlist, as I was not
// envisioning a way this assignment would go using a stack without multiple stacks.

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Desc: Sets the Pet class, holds the name of pet, as well as the type
// Pre: N/A
// Post: Created an class of Pet, and points to the next node.
class Pet {
public:
    string name;
    string type; // "dog" or "cat"
    Pet* next;
};

// Desc: Creates a linkedList for holding the Pet objects, as well as holds
// all the methods that can promote, or add a pet
// Pre: N/A
// Post: Creates a linkedList with multiple methods that can call the nodes
// depending on type of Pet, or can insert a node.
class AnimalShelter { 
private:
    Pet* head; // Hiding the head

public:
    AnimalShelter() { // Sets the head to be nullptr for 
        head = nullptr;
    }
    // Desc: Adds an animal into the linkedlist, sets it at the front of the line.
    // Pre: The name of the animal, given by the file, and the type of animal, given by information from the file
    // Post: A node filled with a Pet, with a type of Pet, and name of Pet, at the front of the linkedList
    void addAnimal(string name, string type) { 
        Pet* newPet = new Pet();
        newPet->name = name;
        newPet->type = type;
        newPet->next = head;
        head = newPet;
        cout << "Adding " << type << " with name: " << name << endl;
    }

    // Desc: Object method allowing us to grab the Pet object from the linkedList
    // Pre: type of Pet wanted, given by information from the file
    // Post: Returns a pet, or nullptr if no Pet is ready to be promoted
    Pet* getAnimal(string type) {
        Pet* current = head;
        Pet* prev = nullptr;
        while (current != nullptr) {
            if (current->type == type) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                current->next = nullptr;
                return current;
            }
            prev = current;
            current = current->next;
        }
        return nullptr;
    }

    // Desc: Promotes the most recent animal of its type, and prints the name.
    // Pre: Type of Pet wanting to promote
    // Post: Prints the name and type of animal to be promoted
    void promoteAnimal(string type) {
        Pet* pet = getAnimal(type);
        if (pet != nullptr) {
            if (type == "dog") {
                cout << "The dog to be promoted is: " << pet->name << endl;
            } else if (type == "cat") {
                cout << "The cat to be promoted is: " << pet->name << endl;
            }
            delete pet;
        } else {
            cout << "Sorry, there are no " << type << "s left in the shelter." << endl;
        }
    }

    // Desc: Promotes the mst recent animal, regardless of type, and prints the name.
    // Pre: N/A
    // Post: Prints the name of the animal to be promoted.
    void promoteAnyAnimal() {
        Pet* pet = getAnimal("dog");
        if (pet == nullptr) {
            pet = getAnimal("cat");
        }
        if (pet != nullptr) {
            cout << "The animal to be promoted is a " << pet->type << ": " << pet->name << endl;
            delete pet;
        } else {
            cout << "Sorry, there are no animals left in the shelter." << endl;
        }
    }
    // Desc: Deconstructor for AnimalShelter class, frees up space
    // Pre: N/A
    // Post: N/A
    ~AnimalShelter() {
        while (head != nullptr) {
            Pet* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Desc: Holds all the parameters given through the terminal by the user, processes the filename given,
// and holds all the possible cases that the file may have.
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: assignment1 <testFileName>" << endl;
        return 1;
    }

    string filename = argv[1]; // User provided filename
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return 1;
    }

    AnimalShelter shelter; // Creating shelter
    string line; // holds the line in the file
    while (getline(infile, line)) {
        string name; // name of animal, provided by file
        char choice = line[0];
        switch (choice) { // allows for multiple inputs from file
            case '1':
                getline(infile, name);
                shelter.addAnimal(name, "cat");
                break;
            case '2':
                getline(infile, name);
                shelter.addAnimal(name, "dog");
                break;
            case '3':
                shelter.promoteAnimal("cat");
                break;
            case '4':
                shelter.promoteAnimal("dog");
                break;
            case '5':
                shelter.promoteAnyAnimal();
                break;
        }
    }

    return 0;
}