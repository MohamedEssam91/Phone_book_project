#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct information
{
    string firstName, lastName, phoneNumber, email, gender;
};


information* read_from_file(information arr[], int& size)    //reading information and saving it to the array
{
    fstream myfile;
    myfile.open("phonebook.txt");
    int i = 0;


    if (myfile.peek() == -1)          //checking if the file is empty
    {
        size = 0;
    }

    while (!myfile.eof() && myfile.peek() != -1)
    {

        getline(myfile, arr[i].firstName);
        getline(myfile, arr[i].lastName);
        getline(myfile, arr[i].phoneNumber);
        getline(myfile, arr[i].email);
        getline(myfile, arr[i].gender);
        i++;
    }
    myfile.close();
    return arr;
}

void write(information* arr, int& size)         //saving information from the array to the text files
{
    ofstream myfile;
    myfile.open("phonebook.txt", ios::trunc);
    for (int i = 0; i < size; i++) {
        myfile << arr[i].firstName << "\n" << arr[i].lastName << "\n" << arr[i].phoneNumber << "\n" << arr[i].email << "\n" << arr[i].gender << "\n";
    }
    ofstream num;
    num.open("numberofcontacts.txt", ios::trunc);
    num << size;
    num.close();
    myfile.close();
}

information* add(information arr[], int& size, int& i)  //add new contact
{
    int choice;
    bool isTrue = true;

    while (isTrue) {
        cout << "\nType 0 if you want to go back or type 1 if you want to proceed to adding a new contact : ";
        cin >> choice;
        if (choice == 0)
            return arr;
        else if (choice == 1)
        {
            size++;
            cout << "\nEnter the First Name : ";
            cin >> arr[i].firstName;

            cout << "\nEnter the Last Name : ";
            cin >> arr[i].lastName;

            bool isPhone = false;
            while (!isPhone) {
                cout << "\nEnter the Phone Number without using spaces : ";
                cin >> arr[i].phoneNumber;
                bool isLetter = false;
                bool isNumber = false;
                for(int j = 0; j < arr[i].phoneNumber.size(); j++){
                    if (arr[i].phoneNumber[j] >= '0' && arr[i].phoneNumber[j] <= '9')
                        isNumber = true;
                    else
                        isLetter = true;
                }
                if (isNumber == true && isLetter == false)
                    isPhone = true;
                else
                    cout << "Invalid phone number.\nPlease use only numbers.\n";
            }
            bool isCorrect=false;
            while (!isCorrect) {
                cout << "\nEnter the E-mail : ";
                cin >> arr[i].email;
                bool isAt = false, isDot = false;
                int indexAt = 0, indexDot = 0,count=0;
                for (int j = 0; j < arr[i].email.size(); j++) {
                    if (arr[i].email[j] == '@'){
                        isAt = true;
                        indexAt = j;
                        count++;
                    }
                    if (arr[i].email[j] == '.') {
                        isDot = true;
                        indexDot = j;
                    }
                }
                if (isDot == true && isAt == true && indexAt < indexDot && count == 1)
                    isCorrect = true;
                else
                    cout << "\nInvalid E-mail address.\n";
            }
            bool isGender = false;
            while (!isGender) {
                cout << "\nEnter the Gender (male or female) : ";
                cin >> arr[i].gender;
                if (arr[i].gender == "male" || arr[i].gender == "female")
                    isGender = true;
                else
                    cout << "\nInvalid gender.\nPlease use lowercase letters only while typing the gender.\n";
            }
            i++;
            isTrue = false;
        }
        else
            cout << "Wrong choice!!!";
    }
    cout << "\n\nContact added successfully!\n\n";
    system("pause");   //pausing the system to let the user know that it was added

    return arr;

}

void show(information arr[], int size)   //show all contacts
{
    if (size == 0) {
        cout << "\nThere are no contacts saved.\nPlease add new contact.\n\n";
        system("pause");
        return;
    }
    else {
        for (int i = 0; i < size; i++)
        {
            cout << "\n" << i + 1 << "-" << "First name : " << arr[i].firstName << "\n  Last name : " << arr[i].lastName << "\n  Phone number : " << arr[i].phoneNumber << "\n  E-mail : " << arr[i].email << "\n  Gender : " << arr[i].gender << "\n\n";

        }
        system("pause");         //pausing the system to let the user see all contacts
    }
}
void search(information arr[], int size)    //search for a particular contact by using name or phone number
{
    string firstName, lastName, sphonenumber;
    int choice;

    if (size == 0) {
        cout << "\nThere are no contacts saved.\nPlease add new contact.\n\n";
        system("pause");
        return;
    }
    else {
        cout << "\nHow do you want to search?\nIf you want to search by name, type (1)\nIf you want to search by number, type (2)\nIf you want to go back type (0)\nType here : ";
        cin >> choice;

        if (choice == 0)
            return;

        if (choice == 1)
        {
            bool isAvailable = false;
            cout << "\nPlease enter the contact's name : ";
            cin >> firstName >> lastName;

            for (int i = 0; i < size; i++) {
                if (firstName + " " + lastName == arr[i].firstName + " " + arr[i].lastName)
                {
                    cout << "\nName : " << arr[i].firstName << " " << arr[i].lastName << "\nPhone : " << arr[i].phoneNumber << "\nE-mail : " << arr[i].email << "\nGender : " << arr[i].gender << "\n\n";
                    isAvailable = true;
                }
            }

            if (!isAvailable)
            {
                cout << "Error!!! \nIncorrect Name.\n";
                search(arr, size);
            }
            else
                system("pause");   //letting the user see the contact that was searched for
        }
    }
    if (choice == 2)
    {
        cout << "\nPlease enter the contact's number : ";
        cin >> sphonenumber;
        bool isAvailable = false;
        for (int i = 0; i < size; i++) {

            if (sphonenumber == arr[i].phoneNumber)
            {
                cout << "\nName : " << arr[i].firstName << " " << arr[i].lastName << "\nPhone : " << arr[i].phoneNumber << "\nE-mail : " << arr[i].email << "\nGender : " << arr[i].gender << "\n\n";
                isAvailable = true;
            }
        }

        if (!isAvailable)
        {
            cout << "Error!!! \nIncorrect phone number.\n";
            search(arr, size);
        }
        else
            system("pause");  //letting the user see the contact that was searched for
    }

}


void delete_(information arr[], int& size)   //deleting a contact
{
    if (size == 0) {
        cout << "\nThere are no contacts saved.\nPlease add new contact.\n\n";
        system("pause");
        return;
    }
    else {
        for (int i = 0; i < size; i++)
        {
            cout << "\n" << i + 1 << "-" << "First name:" << arr[i].firstName << "\n  Last name:" << arr[i].lastName << "\n  Phone number:" << arr[i].phoneNumber << "\n  E-mail:" << arr[i].email << "\n  Gender:" << arr[i].gender << "\n";
        }
        int contact;
        bool isTrue = true;
        while (isTrue) {
            cout << "\nType 0 if you want to go back or enter the order of the contact you want to delete from range 1 to " << size << " : ";
            cin >> contact;
            if (contact<0 || contact>size)
                cout << "Incorrect number." << endl;
            else if (contact == 0) {
                return;
            }
            else
                isTrue = false;
        }
        contact = contact - 1;

        for (int i = contact; i < size; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[size - 1].firstName = "";
        arr[size - 1].lastName = "";
        arr[size - 1].phoneNumber = "";
        arr[size - 1].email = "";
        arr[size - 1].gender = "";
        size--;
        cout << "\nContact deleted successfully!\n\n";
        system("pause"); //letting the user know that the contact was deleted
    }
}

void edit(information arr[], int size)    //modifying a contact
{
    if (size == 0) {
        cout << "\nThere are no contacts saved.\nPlease add new contact.\n\n";
        system("pause");
        return;
    }
    else {
        for (int i = 0; i < size; i++)
        {
            cout << "\n" << i + 1 << "-" << "First name : " << arr[i].firstName << "\n  Last name : " << arr[i].lastName << "\n  Phone number : " << arr[i].phoneNumber << "\n  E-mail : " << arr[i].email << "\n  Gender : " << arr[i].gender << "\n";
        }
        int contact;
        bool isTrue = true;
        while (isTrue) {
            cout << "\nType 0 if you want to go back or enter the order of the contact you want to edit from range 1 to " << size << " : ";
            cin >> contact;
            if (contact<0 || contact>size)
                cout << "Incorrect number." << endl;
            else if (contact == 0)
                return;
            else
                isTrue = false;
        }

        cout << "\nEnter the new contact's information:-";

        cout << "\nEnter the new first name : ";
        cin >> arr[contact - 1].firstName;

        cout << "\nEnter the new last name : ";
        cin >> arr[contact - 1].lastName;
        bool isPhone = false;
        while (!isPhone) {
            cout << "\nEnter the new phone number without using spaces : ";
            cin >> arr[contact - 1].phoneNumber;
            bool isLetter = false;
            bool isNumber = false;
            for (char j : arr[contact - 1].phoneNumber) {
                if (j >= '0' && j <= '9')
                    isNumber = true;
                else
                    isLetter = true;
            }
            if (isNumber == true && isLetter == false)
                isPhone = true;
            else
                cout << "Invalid phone number.\nPlease use only numbers.\n";
        }
        bool isCorrect = false;
        while (!isCorrect) {
            cout << "\nEnter the new E-mail : ";
            cin >> arr[contact - 1].email;
            bool isAt = false, isDot = false;
            int indexAt = 0, indexDot = 0, count = 0;
            for (int j = 0; j < arr[contact - 1].email.size(); j++) {
                if (arr[contact - 1].email[j] == '@') {
                    isAt = true;
                    indexAt = j;
                    count++;
                }
                if (arr[contact - 1].email[j] == '.') {
                    isDot = true;
                    indexDot = j;
                }
            }
            if (isDot == true && isAt == true && indexAt < indexDot && count == 1)
                isCorrect = true;
            else
                cout << "\nInvalid E-mail address.\n";
        }
        bool isGender = false;
        while (!isGender) {
            cout << "\nEnter the Gender (male or female) : ";
            cin >> arr[contact - 1].gender;
            if (arr[contact - 1].gender == "male" || arr[contact - 1].gender == "female")
                isGender = true;
            else
                cout << "\nInvalid gender.\nPlease use lowercase letters only while typing the gender.\n";
        }

        cout << "\n\nContact modified successfully!\n\n";
        system("pause");   //letting the user know that the contact was modified
    }
}

int main()
{
    int choice;   //menu choices
    string line;  //to read the line from numberofcontacts file to save it in the size variable
    int i = 0;    //index of array
    int size = 0; //size of contacts
    fstream num;
    num.open("numberofcontacts.txt");
    if (num.peek() == -1)           //checking if the file is empty
    {
        size = 0;
    }
    else
    {
        getline(num, line);
        size = stoi(line);
    }

    auto* arr = new information[1000];   //maximum contacts that can be is saved is 1000
    read_from_file(arr, size);      //getting the contacts from the file to save it in the array
    i = size;
    num.close();

    bool isRunning = true;
    while (isRunning)
    {
        cout << " \nPHONE BOOK APPLICATION\n";
        cout << ":::::::::::MENU:::::::::::\n";
        cout << "1-Add new contact.\n";
        cout << "2-Show contacts.\n";
        cout << "3-Search.\n";
        cout << "4-Edit contact.\n";
        cout << "5-Delete contact.\n";
        cout << "6-Exit and save.\n";

        cout << "Write your choice: ";
        cin >> choice;      //choices from the main menu

        switch (choice)
        {
            case 1:
                add(arr, size, i);
                break;

            case 2:
                show(arr, size);
                break;

            case 3:
                search(arr, size);
                break;
            case 4:
                edit(arr, size);
                break;
            case 5:
                delete_(arr, size);
                break;
            case 6:
                cout << "\nNumber of contacts saved : " << size << endl;
                isRunning = false;
                break;
            default:
                cout << "The choice is incorrect.\n";
                break;
        }
    }
    write(arr, size);        //saving the contacts in a file
    delete[] arr;            //deleting the dynamic array from the memory to save memory space
    return 0;
}
