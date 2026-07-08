#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Car
{
    int id;
    string name;
    string company;
    int price;
    int year;
    string color;
};

Car cars[200];
int carCount = 0;

bool idExists(int id)
{
    for (int i = 0; i < carCount; i++)
    {
        if (cars[i].id == id)
            return true;
    }
    return false;
}

bool login()
{
    string user, pass, u, p;
    ifstream file("users.txt");

    if (!file)
    {
        cout << "Error: users.txt file not found!\n";
        return false;
    }

    cin.ignore();

    cout << "Enter Username: ";
    getline(cin, user);

    cout << "Enter Password: ";
    getline(cin, pass);

    while (file >> u >> p)
    {
        if (u == user && p == pass)
            return true;
    }

    return false;
}

void signup()
{
    string user, pass;
    ofstream file("users.txt", ios::app);

    if (!file)
    {
        cout << "Error opening users.txt\n";
        return;
    }

    cin.ignore();

    cout << "Create Username: ";
    getline(cin, user);

    cout << "Create Password: ";
    getline(cin, pass);

    file << user << " " << pass << endl;
    file.close();

    cout << "\nSignup successful! Please login.\n";
}

void loadFromFile()
{
    ifstream in("cars.txt");
    if (!in)
        return;

    carCount = 0;
    while (in >> cars[carCount].id
              >> cars[carCount].name
              >> cars[carCount].company
              >> cars[carCount].price
              >> cars[carCount].year
              >> cars[carCount].color)
    {
        carCount++;
    }

    in.close();
}

void saveToFile()
{
    ofstream out("cars.txt");
    for (int i = 0; i < carCount; i++)
    {
        out << cars[i].id << " "
            << cars[i].name << " "
            << cars[i].company << " "
            << cars[i].price << " "
            << cars[i].year << " "
            << cars[i].color << endl;
    }
    out.close();
}

void addCar()
{
    cout << "\n--- Add Car ---\n";

    cout << "Enter Car ID: ";
    cin >> cars[carCount].id;

    if (idExists(cars[carCount].id))
    {
        cout << "[ERROR] Car ID already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> cars[carCount].name;

    cout << "Enter Company: ";
    cin >> cars[carCount].company;

    cout << "Enter Price: ";
    cin >> cars[carCount].price;

    cout << "Enter Year: ";
    cin >> cars[carCount].year;

    cout << "Enter Color: ";
    cin >> cars[carCount].color;

    carCount++;
    saveToFile();

    cout << "Car Added Successfully!\n";
}

void displayCars()
{
    if (carCount == 0)
    {
        cout << "[INFO] No cars available.\n";
        return;
    }

    cout << "\n--- Car List ---\n";
    for (int i = 0; i < carCount; i++)
    {
        cout << cars[i].id << " | "
             << cars[i].name << " | "
             << cars[i].company << " | "
             << cars[i].price << " | "
             << cars[i].year << " | "
             << cars[i].color << endl;
    }
}

void searchCar()
{
    int id;
    cout << "Enter Car ID: ";
    cin >> id;

    for (int i = 0; i < carCount; i++)
    {
        if (cars[i].id == id)
        {
            cout << cars[i].id << " | "
                 << cars[i].name << " | "
                 << cars[i].company << " | "
                 << cars[i].price << " | "
                 << cars[i].year << " | "
                 << cars[i].color << endl;
            return;
        }
    }

    cout << "[INFO] Car not found.\n";
}

void updateCar()
{
    int id;
    cout << "Enter Car ID: ";
    cin >> id;

    for (int i = 0; i < carCount; i++)
    {
        if (cars[i].id == id)
        {
            cout << "New Name: ";
            cin >> cars[i].name;

            cout << "New Company: ";
            cin >> cars[i].company;

            cout << "New Price: ";
            cin >> cars[i].price;

            cout << "New Year: ";
            cin >> cars[i].year;

            cout << "New Color: ";
            cin >> cars[i].color;

            saveToFile();
            cout << "Updated!\n";
            return;
        }
    }

    cout << "[INFO] Car not found.\n";
}

void deleteCar()
{
    int id;
    cout << "Enter Car ID: ";
    cin >> id;

    for (int i = 0; i < carCount; i++)
    {
        if (cars[i].id == id)
        {
            for (int j = i; j < carCount - 1; j++)
                cars[j] = cars[j + 1];

            carCount--;
            saveToFile();
            cout << "Car Deleted!\n";
            return;
        }
    }

    cout << "[INFO] Car not found.\n";
}

void compareCars()
{
    int id1, id2;
    int index1 = -1, index2 = -1;

    cout << "Enter first Car ID: ";
    cin >> id1;
    cout << "Enter second Car ID: ";
    cin >> id2;

    for (int i = 0; i < carCount; i++)
        if (cars[i].id == id1)
            index1 = i;

    for (int i = 0; i < carCount; i++)
        if (cars[i].id == id2)
            index2 = i;

    if (index1 == -1 || index2 == -1)
    {
        cout << "[INFO] One or both cars not found.\n";
        return;
    }

    cout << "\n--- Compare Cars ---\n";
    cout << "ID       : " << cars[index1].id << " | " << cars[index2].id << endl;
    cout << "Name     : " << cars[index1].name << " | " << cars[index2].name << endl;
    cout << "Company  : " << cars[index1].company << " | " << cars[index2].company << endl;
    cout << "Price    : " << cars[index1].price << " | " << cars[index2].price << endl;
    cout << "Year     : " << cars[index1].year << " | " << cars[index2].year << endl;
    cout << "Color    : " << cars[index1].color << " | " << cars[index2].color << endl;
}

int main()
{
    int choice;
    bool loggedIn = false;

    while (!loggedIn)
    {
        cout << "\n===== Welcome =====\n";
        cout << "1. Login\n";
        cout << "2. Signup\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (login())
            {
                cout << "Login Successful!\n";
                loggedIn = true;
            }
            else
            {
                cout << "Invalid login!\n";
            }
        }
        else if (choice == 2)
        {
            signup();
        }
        else if (choice == 3)
        {
            cout << "Goodbye!\n";
            return 0;
        }
        else
        {
            cout << "[ERROR] Invalid choice.\n";
        }
    }

    loadFromFile();

    while (true)
    {
        cout << "\n===== CAR MENU =====\n";
        cout << "1. Add Car\n";
        cout << "2. Display Cars\n";
        cout << "3. Search Car\n";
        cout << "4. Update Car\n";
        cout << "5. Delete Car\n";
        cout << "6. Compare Two Cars\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addCar();
        }
        else if (choice == 2)
        {
            displayCars();
        }
        else if (choice == 3)
        {
            searchCar();
        }
        else if (choice == 4)
        {
            updateCar();
        }
        else if (choice == 5)
        {
            deleteCar();
        }
        else if (choice == 6)
        {
            compareCars();
        }
        else if (choice == 7)
        {
            saveToFile();
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "[ERROR] Invalid choice.\n";
        }
    }

    return 0;
}
