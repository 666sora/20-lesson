#include <iostream>
#include <fstream>
#include <vector>

bool kmp(std::string &str, std::string &substr)
 {
    std::vector<int> p(substr.size() + str.size(), -1);
    
    for (int i = 0, j = -1;i < substr.size();)
    {
        while (j > -1 && substr[i] != substr[j])
            j = p[j];
        i++;
        j++;
        p[i] = j;
    }
     for (int i=0, j = 0;i < str.size();)
    {
        while (j > -1 && str[i] != substr[j])
            j = p[j];
        i++;
        j++;
        if (j == substr.size())
        {
            return true;
        }
 
    }
    return false;
 }

int main() {
    std::string catchingFish;
    std::cout << "Input fish to catch: ";
    std::cin >> catchingFish;
    std::ifstream river("river.txt");
    bool find = false;
    while(!river.eof() && !find) {
        std::string riverFish;
        river >> riverFish;
        find = kmp(riverFish, catchingFish);
    }
    river.close();
    if (find) {
        std::cout << catchingFish << " was caught" << std::endl;
        std::ofstream basket("basket.txt", std::ios::app);
        basket << catchingFish << std::endl;
        basket.close();
    }
    else {
        std::cout << catchingFish << "was not caught" << std::endl;
    }
}

/*
Реализуйте простую симуляцию игры в рыбалку. В исходном текстовом файле реки 
(river.txt) задаётся список из видов рыб, которые можно в ней поймать. 
Рыбок может быть сколько угодно, разных видов. Виды при этом могут повторяться.
В начале программы пользователь указывает, какую именно рыбу он сейчас 
будет ловить — вид этой рыбы. После этого из первого файла друг за другом 
осуществляется чтение его содержимого, вид за видом. Если на отдельных шагах 
вид совпал с указанным пользователем, в выходной файл basket.txt (корзинка) записывается этот вид.
В конце программы показывается, сколько было поймано рыб за текущую ловлю. 
Программу можно запускать несколько раз, при этом уже пойманные рыбы должны сохраняться в файле-корзинке.
*/