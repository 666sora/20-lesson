#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void deposit (int* atm) {
    std::ofstream atm_deposit("atm.bin", std::ios::binary);
    std::srand(std::time(nullptr));
    for (int i = 0; i < 1000; i++) {
        if (atm[i] == 0) {
            atm[i] = std::rand() % 4901 + 100;
            atm_deposit << atm[i] << std::endl;
        }
    }
    atm_deposit.close();
}

int withdraw (int* atm, int &cash) {
    std::ifstream atm_withdraw("atm.bin", std::ios::binary);
    int i = 0;
    int temp;
    while (!atm_withdraw.eof()) {
        atm_withdraw >> temp;
        if (cash > temp - 100 && cash < temp + 100) {
            atm[i] = 0;
            cash = temp;
            break;
        }
        i++;
    }
    if (temp != cash) {
        return -1;
    }
    atm_withdraw.close();
    std::ofstream atm_refresh("atm.bin", std::ios::binary);
    for (int i = 0; i < 1000; i++) {
        atm_refresh << atm[i] << std::endl;
    }
    atm_refresh.close();
    return 0;
}

int main() {
    int atm[1000];
    std::ifstream atm_check("atm.bin", std::ios::binary);
    if (atm_check.peek() == atm_check.eof()) {
        for (int i = 0; i < 1000; i++) {
            atm[i] = 0;
        }
    }
    else {
        for (int i = 0; i < 1000; i++) {
            atm_check >> atm[i];
        }    
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