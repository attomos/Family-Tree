/**
 * <Copyright Nattaphoom Ch.>
 */
#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::string;

// Utility functions
bool EqualsIgnoreCase(const string &str1, const string &str2);
bool SuperReplace(string &str, const string &from, const string &to);
void SuperTrim(string &str);
void Trim(string &str);
void PrintHeader(string str);

const char kFemale[] = "female";
const char kMale[] = "male";
const char kNotIdentified[] = "not identified";

// 6 major commands
const int kUnknownCommand = -187;
const int kAddNewPerson = 1001;
const int kDeletePerson = 1002;
const int kFindAndDisplayPerson = 1003;
const int kShowAllRelatives = 1004;
const int kQuitProgram = 1005;

/**
 * Compares two strings, ignore the case and "not identified" too.
 * Returns true if `str1` and `str2` is the same (case insensitive).
 */
bool EqualsIgnoreCase(const string &str1, const string &str2) {
    // "not identified" cannot compare, returns false by default
    if (str1.compare(kNotIdentified) == 0 ||
        str2.compare(kNotIdentified) == 0) {
        return false;
    }
    if (str1.size() != str2.size()) {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin();
            c1 != str1.end();
            ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}


/**
 * Trims beginning and ending whitespace of given string `str`, then
 * trims the long length of spaces, i.e., 2 or more spaces into one space.
 */
void SuperTrim(string &str) {
    int first_white_space = static_cast<int>(str.find_first_of(" "));
    if (first_white_space < 0) {
        return;  // No whitespace.
    }
    // Trim the beginning and ending whitespace first.
    Trim(str);

    // Replace the middle running length of spaces to just one string.
    string middle_white_spaces;
    int previous = str.find_first_of(' ');
    int i, current;
    for (i = 0, current = 0; i < str.length(); i++) {
        if (str.at(i) == ' ') {
            current = i;
            if (current - previous > 1) {
                break;
            }
            middle_white_spaces += str.at(i);
            previous = i;
        }
    }
    SuperReplace(str, middle_white_spaces, " ");

    // Do it again and again for the rest of running length whitespaces.
    previous = str.find("  ");
    while (previous > 0) {
        middle_white_spaces = "";
        for (i = previous, current = previous; i < str.length(); i++) {
            if (str.at(i) == ' ') {
                current = i;
                if (current - previous > 1) {
                    break;
                }
                middle_white_spaces += str.at(i);
                previous = i;
            }
        }
        SuperReplace(str, middle_white_spaces, " ");
        previous = str.find("  ");
    }
}

/**
 * Replaces the first occurrence of `from` and replace to `to` in the given
 * string `str`.
 * Returns true if replace is proceeded.
 */
bool SuperReplace(string &str, const string &from, const string &to) {
    size_t start_position = str.find(from);
    if (start_position == string::npos) {
        return false;
    }
    str.replace(start_position, from.length(), to);
    return true;
}

/**
 * Trims the beginning and ending whitespace of the given string `str`.
 */
void Trim(string &str) {
    char white_space = ' ';
    const int str_begin = str.find_first_not_of(white_space);

    if (str_begin == string::npos) {
        return;  // No content.
    }

    const int str_end = str.find_last_not_of(white_space);
    const int str_range = str_end - str_begin + 1;
    str = str.substr(str_begin, str_range);
}

/**
 * Prints header of the given string `str`, just for beauty and
 * I just like it personally.
 */
void PrintHeader(string str) {
    printf("\n===================== %s =====================\n\n", str.c_str());
}

/**
 * Class prototype for person.
 * Each person has the following details:
 * full name, age, gender, father's full name and mother's full name.
 */
class Person {
    public:
        Person();
        Person(string full_name, unsigned int age, string gender,
                string father_full_name, string mother_full_name);
        int age();
        string full_name();
        string gender();
        string father_full_name();
        void set_father_full_name(string father_full_name);
        string mother_full_name();
        void set_mother_full_name(string mother_full_name);
        string ToString();
    private:
        string full_name_;
        unsigned int age_;
        string gender_;
        string father_full_name_;
        string mother_full_name_;
};

/**
 * Default constructor of person.
 * Initialise all of the string member variables with "not identified"
 * and age_ with 0.
 */
Person::Person() {
    full_name_ = kNotIdentified;
    age_ = 0;
    gender_ = kNotIdentified;
    father_full_name_ = kNotIdentified;
    mother_full_name_ = kNotIdentified;
}

/**
 * Constructs a person from the given `full_name`, `age`,
 * `gender`, `father_full_name`, `mother_full_name`.
 * If `father_full_name` or `mother_full_name` is empty string
 * it will replace with "not identified" by default.
 */
Person::Person(string full_name, unsigned int age, string gender,
        string father_full_name, string mother_full_name) {
    full_name_ = full_name;
    age_ = age;
    gender_ = gender;
    father_full_name_ = father_full_name;
    mother_full_name_ = mother_full_name;
    if (father_full_name.compare("") == 0) {
        father_full_name_ = kNotIdentified;
    }
    if (mother_full_name.compare("") == 0) {
        mother_full_name_ = kNotIdentified;
    }
}

/**
 * Returns age of the person.
 */
int Person::age() {
    return age_;
}

/**
 * Returns full name of the person.
 */
string Person::full_name() {
    return full_name_;
}

/**
 * Returns gender of the person.
 */
string Person::gender() {
    return gender_;
}

/**
 * Returns father's full name of the person.
 */
string Person::father_full_name() {
    return father_full_name_;
}

/**
 * Changes father's full name of the person from the
 * given `father_full_name`.
 */
void Person::set_father_full_name(string father_full_name) {
    father_full_name_ = father_full_name;
}

/**
 * Returns mother's full name of the person.
 */
string Person::mother_full_name() {
    return mother_full_name_;
}

/**
 * Changes mother's full name of the person from the
 * given `mother_full_name`.
 */
void Person::set_mother_full_name(string mother_full_name) {
    mother_full_name_ = mother_full_name;
}

/**
 * Returns the representation of the person as a string.
 * The information includes all of the member variables.
 */
string Person::ToString() {
    std::stringstream ss;
    ss << full_name_ << ", " << age_ << " years old, " << gender_ <<
    ", father: " << father_full_name_ <<
    ", mother: " << mother_full_name_;
    return ss.str();
}

/**
 * Structure prototype for family node.
 * FamilyNode consists of Person object and
 * FamilyNode pointer point to the next node.
 */
struct FamilyNode {
    Person person;
    FamilyNode *next;

    int age() {
        return person.age();
    }
    string full_name() {
        return person.full_name();
    }

    string father() {
        return person.father_full_name();
    }

    string mother() {
        return person.mother_full_name();
    }

    string sex() {
        return person.gender();
    }
};

/**
 * Class prototype for linked list of the family tree.
 */
class FamilyLinkedList {
    public:
        FamilyLinkedList();
        ~FamilyLinkedList();
        FamilyNode *Get(string full_name);
        void PrintAncestors(string full_name, int level);
        void PrintDescendants(string full_name, int level);
        void PrintSiblings(string full_name);
        void Add(Person p);
        FamilyNode *Delete(string full_name);
        void PrintAllNodes();
        void PrintRelativesOf(string full_name);
        int size();
        FamilyNode *head_;
    private:
        int size_;
};

/**
 * Constructs empty linked list.
 */
FamilyLinkedList::FamilyLinkedList() {
    head_ = NULL;
    size_ = 0;
}

/**
 * Destructor for FamilyLinkedList.
 */
FamilyLinkedList::~FamilyLinkedList() {
    while (head_ != NULL) {
        FamilyNode *n = head_->next;
        delete head_;
        head_ = n;
    }
}

/**
 * Returns the FamilyNode from the given `full_name`.
 */
FamilyNode *FamilyLinkedList::Get(string full_name) {
    if (head_ == NULL) {
        return NULL;
    }
    FamilyNode *node = head_;
    while (node != NULL) {
        if (EqualsIgnoreCase(node->full_name(), full_name)) {
            return node;
        }
        node = node->next;
    }
    // return NULL if full_name is not exist
    return NULL;
}

/**
 * Prints all of ancestors of the given `full_name`, `level` is used
 * for indicates the level of ancestors.
 */
void FamilyLinkedList::PrintAncestors(string full_name, int level) {
    FamilyNode *person = Get(full_name);
    // base case
    if (person == NULL || full_name.compare(kNotIdentified) == 0) {
        return;
    }
    FamilyNode *node = head_;

    string prefix = "grand ";
    int i;
    // level - 1 because 1 level (grand father is not great-grand father)
    for (i = 0; i < level - 1; i++) {
        prefix = "great-" + prefix;
    }
    if (level == 0) {
        prefix = "";
    }

    // printf("L %d\n", level);
    // Only father and mother is look up based on the member variable not the
    // node in linked list.
    if (person->father().compare(kNotIdentified) != 0) {
        printf("%s, %sfather\n", person->father().c_str(), prefix.c_str());
        PrintAncestors(person->father(), level + 1);
    }
    if (person->mother().compare(kNotIdentified) != 0) {
        printf("%s, %smother\n", person->mother().c_str(), prefix.c_str());
        PrintAncestors(person->mother(), level + 1);
    }
}

/**
 * Prints all of descendants of the given `full_name`, `level` is used
 * for indicates the level of descendants.
 */
void FamilyLinkedList::PrintDescendants(string full_name, int level) {
    FamilyNode *person = Get(full_name);
    FamilyNode *node = head_;
    int counter = 0;
    string prefix = "grand ";
    int i;
    // level -1 because 1 level is grand daughter or grand son
    for (i = 0; i < level - 1; i++) {
        prefix = "great-" + prefix;
    }
    if (level == 0) {
        prefix = "";
    }

    while (node != NULL) {
        if (EqualsIgnoreCase(node->father(), full_name) ||
            EqualsIgnoreCase(node->mother(), full_name)) {
            if (EqualsIgnoreCase(node->sex(), kFemale)) {
                printf("%s, %sdaughter\n", node->full_name().c_str(),
                        prefix.c_str());
            } else {
                printf("%s, %sson\n", node->full_name().c_str(),
                        prefix.c_str());
            }
            // print descendants recursively
            PrintDescendants(node->full_name(), level + 1);
        }
        node = node->next;
    }
}

/**
 * Prints siblings of `full_name`.
 */
void FamilyLinkedList::PrintSiblings(string full_name) {
    FamilyNode *person = Get(full_name);
    FamilyNode *node = head_;

    while (node != NULL) {
        // Common father or mother
        if ((EqualsIgnoreCase(node->father(), person->father()) ||
             EqualsIgnoreCase(node->mother(), person->mother())) &&
             !EqualsIgnoreCase(node->full_name(), person->full_name())) {
            if (EqualsIgnoreCase(node->sex(), kFemale)) {
                if (node->age() == person->age()) {
                    printf("%s, sister [same age %d]\n",
                            node->full_name().c_str(),
                            person->age());
                } else if (node->age() > person->age()) {
                    printf("%s, elder sister\n",
                            node->full_name().c_str());
                } else {
                    printf("%s, younger sister\n",
                            node->full_name().c_str());
                }
            } else {
                if (node->age() == person->age()) {
                    printf("%s, brother [same age %d]\n",
                            node->full_name().c_str(),
                            person->age());
                } else if (node->age() > person->age()) {
                    printf("%s, elder brother\n",
                            node->full_name().c_str());
                } else {
                    printf("%s, younger brother\n",
                            node->full_name().c_str());
                }
            }
        }
        node = node->next;
    }
}

/**
 * Adds person `p` to head of the linked list.
 */
void FamilyLinkedList::Add(Person p) {
    FamilyNode *new_node = new FamilyNode;
    new_node->person = p;
    new_node->next = head_;
    head_ = new_node;
    size_++;
}

/**
 * Deletes `full_name` from the linked list and returns
 * the deleted person as a FamilyNode.
 */
FamilyNode *FamilyLinkedList::Delete(string full_name) {
    FamilyNode *return_node = NULL;
    if (head_ == NULL) {
        return return_node;
    }
    FamilyNode *current_node = head_->next;
    FamilyNode *previous_node = head_;
    FamilyNode *obsolete_node = new FamilyNode;
    // head will be eliminated
    if (previous_node != NULL &&
            EqualsIgnoreCase(previous_node->person.full_name(), full_name)) {
        head_ = previous_node->next;
        obsolete_node = previous_node;
        return_node = previous_node;
        delete obsolete_node;
        size_--;
        return return_node;
    }

    while (current_node != NULL) {
        if (EqualsIgnoreCase(current_node->person.full_name(), full_name)) {
            obsolete_node = current_node;
            return_node = current_node;
            // last node will be eliminated
            if (current_node->next == NULL) {
                FamilyNode *temp_node = new FamilyNode;
                // Searching for the node prior the tail
                while (previous_node != current_node) {
                    temp_node = previous_node;
                    previous_node = previous_node->next;
                }
                temp_node->next = NULL;
            } else {
                // middle node will be eliminated
                previous_node->next = current_node->next;
            }
            delete obsolete_node;
            size_--;
            return return_node;
        }
        current_node = current_node->next;
        previous_node = previous_node->next;
    }
    return return_node;
}

/**
 * Prints all nodes in the linked list.
 */
void FamilyLinkedList::PrintAllNodes() {
    FamilyNode *node = head_;
    if (size_ < 1) {
        printf("[]\n");
        return;
    }
    int i;
    while (node != NULL) {
        printf("%s\n", node->person.ToString().c_str());
        node = node->next;
    }
    printf("Total: %d\n", size());
}

/**
 * Prints all of the relative of `full_name`.
 * The person full_name=`full_name` must exists in the linked list.
 */
void FamilyLinkedList::PrintRelativesOf(string full_name) {
    printf("\n%s's relatives:\n\n", full_name.c_str());
    PrintAncestors(full_name, 0);
    PrintDescendants(full_name, 0);
    PrintSiblings(full_name);
    return;
}

/**
 * Returns the current size of the linked list.
 */
int FamilyLinkedList::size() {
    return size_;
}

/**
 * Adds new person to the family tree.
 * `family_linked_list` is the main linked list.
 * `ghost_family_linked_list` is make re-add the deleted person faster.
 * (No need to re enter all of the information.
 */
void AddNewPerson(FamilyLinkedList *family_linked_list,
                  FamilyLinkedList *ghost_family_linked_list) {
    PrintHeader("Add new person");
    string full_name;
    string age;
    int age_value;
    string gender;
    string father_full_name;
    string mother_full_name;
    printf("Please enter a name: ");
    getline(cin, full_name);
    if (EqualsIgnoreCase(full_name, "")) {
        printf("\nFull name cannot be null\n");
        return;
    }
    SuperTrim(full_name);
    if (family_linked_list->Get(full_name)) {
        printf("\n%s already exist!\n\n", full_name.c_str());
        printf("%s\n",
                family_linked_list->Get(full_name)->person.ToString().c_str());
        return;
    }
    // Exist in the ghost linked list.
    FamilyNode *ghost_person = ghost_family_linked_list->Get(full_name);
    if (ghost_person) {
        printf("\nFullname: %s\n", ghost_person->full_name().c_str());
        printf("age: %d\n", ghost_person->age());
        printf("gender: %s\n", ghost_person->sex().c_str());
        printf("father's name: %s\n", ghost_person->father().c_str());
        printf("mother's name: %s\n", ghost_person->mother().c_str());
        family_linked_list->Add(ghost_person->person);
        // Welcome back message
        printf("\nWelcome back %s!\n\n", full_name.c_str());
        return;
    }
    printf("Enter age: ");
    getline(cin, age);
    if (EqualsIgnoreCase(age, "")) {
        printf("\nAge cannot be null\n");
        return;
    }
    std::stringstream ss(age);
    ss >> age_value;
    if (!ss) {
        printf("\nInvalid age: %s\n", age.c_str());
        return;
    }
    printf("Gender:");
    getline(cin, gender);
    Trim(gender);
    if (EqualsIgnoreCase(gender, "")) {
        printf("\nGender cannot be null\n");
        return;
    }
    if (!EqualsIgnoreCase(gender, kMale) &&
        !EqualsIgnoreCase(gender, kFemale)) {
        printf("\nInvalid gender: %s\n", gender.c_str());
        return;
    }
    printf("Father's name: ");
    getline(cin, father_full_name);
    printf("Mother's name: ");
    getline(cin, mother_full_name);

    Person new_person(full_name, age_value, gender,
            father_full_name, mother_full_name);
    family_linked_list->Add(new_person);
    ghost_family_linked_list->Add(new_person);

    printf("\nWelcome %s!\n\n", full_name.c_str());
}

/**
 * Deletes the person from the main `family_linked_list`.
 */
void DeletePerson(FamilyLinkedList *family_linked_list) {
    PrintHeader("Delete person");
    string full_name;
    printf("\nPlease enter a name: ");
    getline(cin, full_name);
    SuperTrim(full_name);
    FamilyNode *node = family_linked_list->Get(full_name);
    if (node) {
        printf("\n%s\n\n", node->person.ToString().c_str());
        string confirm;
        printf("Area you sure to delete %s (y/n)", full_name.c_str());
        getline(cin, confirm);
        if (EqualsIgnoreCase(confirm, "y")) {
            family_linked_list->Delete(full_name);
            printf("%s has been deleted!\n", full_name.c_str());
        } else {
            printf("OK, you decided to not delete %s.\n",
                    full_name.c_str());
        }
    } else {
        printf("\n%s does not exist in the Family Tree\n", full_name.c_str());
    }
}

/**
 * Finds and displays the information of the person from main
 * `family_linked_list`.
 */
void FindAndDisplayPerson(FamilyLinkedList *family_linked_list) {
    PrintHeader("Find and display person");
    string full_name;
    printf("\nPlease enter a name: ");
    getline(cin, full_name);
    printf("!%s\n", full_name.c_str());
    SuperTrim(full_name);
    printf("!%s\n", full_name.c_str());
    FamilyNode *node = family_linked_list->Get(full_name);
    if (node) {
        printf("%s\n", node->person.ToString().c_str());
    } else {
        printf("\n%s does not exist in the Family Tree\n", full_name.c_str());
    }
}

/**
 * Shows all relatives of the persons from the main `family_linked_list`.
 */
void ShowAllRelatives(FamilyLinkedList *ghost_family_linked_list) {
    PrintHeader("Show all relatives");
    string full_name;
    printf("\nPlease enter a name: ");
    getline(cin, full_name);
    SuperTrim(full_name);
    FamilyNode *node = ghost_family_linked_list->Get(full_name);
    if (node) {
        ghost_family_linked_list->PrintRelativesOf(node->full_name());
    } else {
        printf("\n%s does not exist in the Family Tree\n", full_name.c_str());
    }
}

/**
 * Prints the main menu, read the menu input from user,
 * then returns the command code for
 * do the next process.
 */
int ReadMainPrompt() {
    PrintHeader("Family Trees Main Menu");
    printf("(A)dd a new-not existing person\n");
    printf("(D)elete an existing person\n");
    printf("(F)ind and display the details of a person\n");
    printf("show all (R)elatives of a person\n");
    printf("(Q)uit the program\n");
    printf("\nPlease select an operation: ");
    string menu_input;
    getline(cin, menu_input);

    if (EqualsIgnoreCase(menu_input, "a")) {
        return kAddNewPerson;
    } else if (EqualsIgnoreCase(menu_input, "d")) {
        return kDeletePerson;
    } else if (EqualsIgnoreCase(menu_input, "f")) {
        return kFindAndDisplayPerson;
    } else if (EqualsIgnoreCase(menu_input, "r")) {
        return kShowAllRelatives;
    } else if (EqualsIgnoreCase(menu_input, "q")) {
        return kQuitProgram;
    }

    if (EqualsIgnoreCase(menu_input, "")) {
    } else {
        printf("\n\nUnknown command: %s\n\n", menu_input.c_str());
    }
    return kUnknownCommand;
}

/**
 * Main method for run the Family Tree program.
 */
int main(int argc, const char *argv[]) {
    FamilyLinkedList family_linked_list;
    // Used as a ghost data, i.e., its data will change when add new person.
    FamilyLinkedList ghost_family_linked_list;

    bool is_done = false;

    while (!is_done) {
        int main_prompt = ReadMainPrompt();
        switch (main_prompt) {
            case kAddNewPerson:
                AddNewPerson(&family_linked_list, &ghost_family_linked_list);
                break;
            case kDeletePerson:
                DeletePerson(&family_linked_list);
                break;
            case kFindAndDisplayPerson:
                FindAndDisplayPerson(&family_linked_list);
                break;
            case kShowAllRelatives:
                ShowAllRelatives(&family_linked_list);
                break;
            case kQuitProgram:
                is_done = true;
                PrintHeader("Goodbye dude");
                break;
        }
    }

    return 0;
}
