#include <iostream>
#include <fstream>
#include <string>


int main() {
    std::string name = "0";
    std::ofstream statement("statement.txt", std::ios::app);
    while (name != "-1") {
        std::cout << "Input name: ";
        std::cin >> name;
        if (name == "-1") {
            continue;
        }

        std::string surname;
        std::cout << "Input surname: ";
        std::cin >> surname;

        bool correct = true;
        std::string date;
        do {
            std::cout << "Input date: ";
            std::cin >> date;
            if (date.length() != 10 
                    || std::stoi(date.substr(0, 2)) > 31 || std::stoi(date.substr(0, 2)) < 1 
                    || std::stoi(date.substr(3, 4)) > 12 || std::stoi(date.substr(3, 4)) < 1) {
                correct = false;
                std::cout << "Invalid input" << std::endl;
            }
            else {
                correct = true;
            }
        } while (!correct);
        
        int payment;
        std::cout << "Input payment: ";
        std::cin >> payment;

        statement << name << " " << surname << " " << date << " " << payment << std::endl;
    }
    statement.close();
}

/*
В одном из прошлых заданий мы уже создавали программу чтения и анализа 
ведомости выплат. Теперь требуется создать простую программу записи в эту ведомость.
Формат ведомости прежний. Сначала идёт имя и фамилия получателя 
денежных средств, далее располагается дата выдачи в формате ДД.ММ.ГГГГ. 
Завершает запись сумма выплаты в рублях. Данные разделяются между 
собой пробелами. В конце каждой записи должен быть расположен перевод строки.
При старте программы пользователь последовательно вводит данные для новой 
записи, которые записываются затем в файл в текстовом режиме. Программа должна 
добавлять новые записи в конец файла, не удаляя его текущее содержимое.
*/