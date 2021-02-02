
/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** main
*/

#include "address.hpp"
#include "autoCompletion.hpp"
#include "Exception.hpp"

int main(int ac, char** av)
{
    std::string input;
    AutoComp autocomp;

    if (ac == 2) {
        try {
            autocomp.ProcessFile(av[1]);
            for (int i; autocomp.fivemost(i) != true; i++);
            if (autocomp.getCheck() == true) {
                if (autocomp.searchCity("") != 1) {
                    while (std::getline(std::cin, input)) {
                        if (input == "ABORT")
                            return 84;
                        if (autocomp.searchCity(input) == 1)
                            break;
                    }
                }
            } else
                while (std::getline(std::cin, input)) {
                    if (input == "ABORT")
                        return 84;
                    if (autocomp.searchCity(input) == 1)
                        break;
                }
        } catch (Exception &e) {
            std::cout << e.err() << std::endl;
            return 84;
        }
        if (autocomp.getList().size() == 1) {
            std::cout << "=> " << autocomp.getList().begin()->getAddr() << std::endl;
            return 0;
        }/* else if (autocomp.getList().size() == 2)
            std::cout << "2 choices" << std::endl;*/
        autocomp.ResetChecker();
        try {
            autocomp.fivemostAddr();
            while (std::getline(std::cin, input)) {
                if (input == "ABORT")
                    return 84;
                if (autocomp.searchStreet(input) == 1)
                    break;
            }
        } catch (Exception &e) {
            std::cout << e.err() << std::endl;
            return 84;
        }
        if (autocomp.getList().size() == 1) {
            std::cout << "=> " << autocomp.getList().begin()->getAddr() << std::endl;
            return 0;
        }
    }  else
        return 84;
//    std::cout << "end" << std::endl;
    return 0;
}
