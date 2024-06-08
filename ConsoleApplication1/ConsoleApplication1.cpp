// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <windows.h>

using namespace std;

//нода
struct Node {
    Node* next; // ссылка на следующий элемент
    int age; // возраст
    string name;

    //конструктор ноды
    Node(int age = int(), string name = string(), Node* next = nullptr) {
        this->age = age;
        this->name = name;
        this->next = next;
    }
};

//линейный список
class LinearList {
private:
    Node* head; //голова списка

public:
    //кол-во элементов
    int Size() {
        int count = 0;
        Node* current = this->head;

        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // создание пустого списка
    LinearList() {
        head = nullptr;
    }

    //добавление пациента в конец
    void add_patient_end(int age, string name) {
        if (head == nullptr) {
            this->head = new Node(age, name);
        }
        else {
            Node* current = this->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(age, name);
        }
    }

    //добавление пациента в начало
    void add_patient_start(int age, string name) {
        if (head == nullptr) {
            head = new Node(age, name);
        }
        else {
            Node* current = this->head;
            this->head = new Node(age, name, current);
        }
    }

    //вывод всех пациентов начиная с первого
    void show_patients_from_first() {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            while (current != nullptr) {
                cout << "Имя: " << current->name << ", Возраст: " << current->age << endl;
                current = current->next;
            }
        }
    }

    //вывод по возрастанию
    static void sorted_patients_from_lower(LinearList li) {
        LinearList copy;

        //копирование списка, чтобы не менять настоящий
        for (int i = 0; i < li.Size(); i++) {
            Node elem = li[i];
            copy.add_patient_end(elem.age, elem.name);
        }

        if (copy.head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            bool is_sorted = false;
            while (!is_sorted) {
                is_sorted = true;
                Node* current = copy.head;
                Node* prev = nullptr;

                while (current->next != nullptr) {
                    if (current->age > current->next->age) {
                        Node* temp = current->next;
                        current->next = temp->next;
                        temp->next = current;
                        if (prev == nullptr) {
                            copy.head = temp;
                        }
                        else {
                            prev->next = temp;
                        }
                        prev = temp;
                        is_sorted = false;
                    }
                    else {
                        prev = current;
                        current = current->next;
                    }
                }
            }
            copy.show_patients_from_first();
        }
    }

    //вывод по убыванию
    static void sorted_patients_from_upper(LinearList li) {
        LinearList copy;

        //копирование списка, чтобы не менять настоящий
        for (int i = 0; i < li.Size(); i++) {
            Node elem = li[i];
            copy.add_patient_end(elem.age, elem.name);
        }

        if (copy.head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            bool is_sorted = false;
            while (!is_sorted) {
                is_sorted = true;
                Node* current = copy.head;
                Node* prev = nullptr;

                while (current->next != nullptr) {
                    if (current->age < current->next->age) {
                        Node* temp = current->next;
                        current->next = temp->next;
                        temp->next = current;
                        if (prev == nullptr) {
                            copy.head = temp;
                        }
                        else {
                            prev->next = temp;
                        }
                        prev = temp;
                        is_sorted = false;
                    }
                    else {
                        prev = current;
                        current = current->next;
                    }
                }
            }
            copy.show_patients_from_first();
        }
    }

    //поиск по различным параметрам (методы ниже просто перегружают текущий)
    void find_patients(string name) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            bool found = false;

            while (current != nullptr) {
                if (current->name == name) {
                    cout << "Имя: " << current->name << ", Возраст: " << current->age << endl;
                    found = true;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким именем не существует" << endl;
            }
        }
    }

    void find_patients(int age) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            bool found = false;
            while (current != nullptr) {
                if (current->age == age) {
                    cout << "Имя: " << current->name << ", Возраст: " << current->age << endl;
                    found = true;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким возрастом не существует" << endl;
            }
        }
    }

    void find_patients(int age, string name) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            bool found = false;
            while (current != nullptr) {
                if (current->age == age && current->name == name) {
                    cout << "Имя: " << current->name << ", Возраст: " << current->age << endl;
                    found = true;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким именем и возрастом не существует" << endl;
            }
        }
    }

    //поиск по индексу с возвратом ссылки(перегружает оператор)
    Node& operator[](const int index) {
        if (head == nullptr) {
            throw out_of_range("Список пустой");
        }
        else {
            Node* current = this->head;
            int idx = 0;

            while (current != nullptr) {
                if (index == idx) {
                    return *current;
                }
                current = current->next;
                idx++;
            }
            throw out_of_range("Пациент с таким индексом не существует");
        }
    }

    //удаление пациентов
    void delete_patients(string name) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            Node* prev = nullptr;
            bool found = false;

            while (current != nullptr) {
                if (current->name == name) {
                    if (prev == nullptr) {
                        head = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }
                    delete current;
                    found = true;
                    cout << "Удален пациент с именем: " << name << endl;
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким именем не существует" << endl;
            }
        }
    }

    void delete_patients(int age) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            Node* prev = nullptr;
            bool found = false;

            while (current != nullptr) {
                if (current->age == age) {
                    if (prev == nullptr) {
                        head = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }
                    delete current;
                    found = true;
                    cout << "Удален пациент с возрастом: " << age << endl;
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким возрастом не существует" << endl;
            }
        }
    }

    void delete_patients(int age, string name) {
        if (head == nullptr) {
            cout << "Список пустой" << endl;
        }
        else {
            Node* current = this->head;
            Node* prev = nullptr;
            bool found = false;

            while (current != nullptr) {
                if (current->age == age && current->name == name) {
                    if (prev == nullptr) {
                        head = current->next;
                    }
                    else {
                        prev->next = current->next;
                    }
                    delete current;
                    found = true;
                    cout << "Удален пациент с именем: " << name << " и возрастом: " << age << endl;
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (!found) {
                cout << "Пациентов с таким именем и возрастом не существует" << endl;
            }
        }
    }
};

// Программа с интерактивным интерфейсом и добавленными переходами
void SleepWithDots(int milliseconds) {
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        Sleep(milliseconds / 3);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle(L"База данных пациентов");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    LinearList patientsList;
    int choice = 0;

    while (choice != 9) {
        SetConsoleTextAttribute(hConsole, 14); // Желтый цвет для меню
        cout << "Меню:\n";
        cout << "1. Добавить пациента в начало\n";
        cout << "2. Добавить пациента в конец\n";
        cout << "3. Показать всех пациентов\n";
        cout << "4. Показать пациентов по возрастанию возраста\n";
        cout << "5. Показать пациентов по убыванию возраста\n";
        cout << "6. Найти пациента по имени\n";
        cout << "7. Найти пациента по возрасту\n";
        cout << "8. Найти пациента по имени и возрасту\n";
        cout << "9. Выйти\n";
        cout << "Введите номер опции: ";
        SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
        cin >> choice;

        switch (choice) {
        case 1: {
            SetConsoleTextAttribute(hConsole, 10); // Зеленый цвет для ввода данных
            cout << "Введите имя пациента: ";
            string name;
            cin >> name;
            cout << "Введите возраст пациента: ";
            int age;
            cin >> age;
            cout << "Добавляем пациента";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.add_patient_start(age, name);
            cout << "Пациент добавлен в начало списка\n";
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        case 2: {
            SetConsoleTextAttribute(hConsole, 10); // Зеленый цвет для ввода данных
            cout << "Введите имя пациента: ";
            string name;
            cin >> name;
            cout << "Введите возраст пациента: ";
            int age;
            cin >> age;
            cout << "Добавляем пациента";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.add_patient_end(age, name);
            cout << "Пациент добавлен в конец списка\n";
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        case 3: {
            cout << "Показ пациентов";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.show_patients_from_first();
            break;
        }
        case 4: {
            cout << "Сортировка и показ пациентов по возрастанию возраста";
            SleepWithDots(1000); // 1 секунда с точками
            LinearList::sorted_patients_from_lower(patientsList);
            break;
        }
        case 5: {
            cout << "Сортировка и показ пациентов по убыванию возраста";
            SleepWithDots(1000); // 1 секунда с точками
            LinearList::sorted_patients_from_upper(patientsList);
            break;
        }
        case 6: {
            SetConsoleTextAttribute(hConsole, 10); // Зеленый цвет для ввода данных
            cout << "Введите имя пациента: ";
            string name;
            cin >> name;
            cout << "Поиск пациента";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.find_patients(name);
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        case 7: {
            SetConsoleTextAttribute(hConsole, 10); // Зеленый цвет для ввода данных
            cout << "Введите возраст пациента: ";
            int age;
            cin >> age;
            cout << "Поиск пациента";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.find_patients(age);
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        case 8: {
            SetConsoleTextAttribute(hConsole, 10); // Зеленый цвет для ввода данных
            cout << "Введите имя пациента: ";
            string name;
            cin >> name;
            cout << "Введите возраст пациента: ";
            int age;
            cin >> age;
            cout << "Поиск пациента";
            SleepWithDots(1000); // 1 секунда с точками
            patientsList.find_patients(age, name);
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        case 9: {
            cout << "Выход из программы";
            SleepWithDots(1000); // 1 секунда с точками
            break;
        }
        default: {
            SetConsoleTextAttribute(hConsole, 12); // Красный цвет для ошибок
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            SetConsoleTextAttribute(hConsole, 7); // Возвращаем стандартный цвет
            break;
        }
        }
        cout << endl;
    }
    return 0;
}
