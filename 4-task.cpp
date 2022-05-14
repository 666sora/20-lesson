#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void deposit(int* atm) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < 1000; i++) {
        if (atm[i] == 0) {
            atm[i] = std::rand() % 4901 + 100;
        }
    }
    std::ofstream atm_deposit("atm.bin", std::ios::binary);
    atm_deposit.write((char*)atm, 1000);
    atm_deposit.close();
}

int withdraw(int* atm, int& cash) {
    std::ifstream atm_withdraw("atm.bin", std::ios::binary);
    atm_withdraw.read((char*)atm, 1000);
    atm_withdraw.close();
    for (int i = 0; i < 1000; i++) {
        if (cash > atm[i] - 100 && cash < atm[i] + 100) {
            cash = atm[i];
            atm[i] = 0;
            return 0;
        }
    }
    return -1;
}

void refresh (int* atm) {
    std::ofstream atm_refresh("atm.bin", std::ios::binary);
    atm_refresh.write((char*)atm, 1000);
    atm_refresh.close();
}

int main() {
    int atm[1000];
    std::ifstream atm_check("atm.bin", std::ios::binary);
    if (atm_check.peek() == EOF) {
        for (int i = 0; i < 1000; i++) {
            atm[i] = 0;
        }
    }
    else {
        atm_check.read((char*)atm, 1000);
    }
    atm_check.close();
    char answer;
    std::cout << "Deposit or withdraw(+/-): ";
    std::cin >> answer;
    if (answer == '+') {
        deposit(atm);
    }
    else if (answer == '-') {
        int cash;
        std::cout << "Input cash you want to withdraw: ";
        std::cin >> cash;
        if (withdraw(atm, cash) == 0) {
            std::cout << cash << " were withdrawn" << std::endl;
            refresh(atm);
        }
        else {
            std::cout << "Requested cash are not available" << std::endl;
        }
    }   
}

/*
Требуется реализовать упрощённую симуляцию работы банкомата. В банкомате могут
храниться только бумажные купюры номиналом от 100 до 5000 рублей. Максимально
в банкомате может храниться только 1000 купюр. Все они записываются в отдельный
файл. У банкомата, как у устройства, две основных операции — снятие денег пользователем
и наполнение деньгами инкассаторами банка.
Наполнение банкомата происходит, если при старте программы в консоль вводится символ
плюс “+”.  Количество купюр рассчитывается так, чтобы банкомат был заполнен полностью.
Все купюры при этом выбираются случайным образом.
Если на старте программы в консоль вводится минус (“-”), то симулируется снятие
пользователем денег. Пользователь указывает сумму с точностью до 100 рублей.
Мы будем считать, что каждый клиент обладает неограниченным балансом в системе и
теоретически может снять любую сумму. На практике, если данная сумма не может быть снята
из-за отсутствия подходящих денег в машине, показывается сообщение, что эта операция невозможна.
После выполнения любой из операций программа завершает выполнение. Состояние банкомата
должно храниться в отдельном бинарном файле, автономно.
*/